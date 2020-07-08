using Microsoft.Win32;
using Microsoft.Win32.SafeHandles;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Forms;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;
using static WpfApp20.winapi;
namespace WpfApp20
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    /// 

    public partial class MainWindow : Window
    {

/*        static void QuickSort0(byte[] data, int left, int right)
        {
            int i = left - 1,
                j = right;

            while (true)
            {
                byte d = data[left];
                do i++; while (data[i] < d);
                do j--; while (data[j] > d);

                if (i < j)
                {
                    byte tmp = data[i];
                    data[i] = data[j];
                    data[j] = tmp;
                }
                else
                {
                    if (left < j) QuickSort0(data, left, j);
                    if (++j < right) QuickSort0(data, j, right);
                    return;
                }
            }
        }

        static void QuickSort(byte[] a, int start, int end)
        {
            if (start >= end)
            {
                return;
            }

            int num = a[start];

            int i = start, j = end;

            while (i < j)
            {
                while (i < j && a[j] > num)
                {
                    j--;
                }

                a[i] = a[j];

                while (i < j && a[i] < num)
                {
                    i++;
                }

                a[j] = a[i];
            }

            a[i] = (byte)num;
            QuickSort(a, start, i - 1);
            QuickSort(a, i + 1, end);
        }*/


        class FileBlock
        {
            public string filename;
            public int size = 0;
            public IntPtr fileHandle = IntPtr.Zero;
            public int MAXValue, MINValue;
            public List<FileBlock> sub_blocks;
            public FileBlock(string filename, IntPtr fileHandle, int minvalue, int maxvalue)
            {
                this.filename = filename; this.size = 0; this.fileHandle = fileHandle; this.MAXValue = maxvalue; this.MINValue = minvalue;
            }
        }

        //string example0 = ReadRegKey(HKEY_LOCAL_MACHINE, @"SOFTWARE\Xiph.Org\Open Codecs", "MediaDescNum");



        int partition<T>(T[] m, int a, int b) where T : IComparable<T>
        {
            int i = a;
            for (int j = a; j <= b; j++)         // просматриваем с a по b
            {
                if (m[j].CompareTo(m[b]) <= 0)  // если элемент m[j] не превосходит m[b],
                {
                    T t = m[i];                  // меняем местами m[j] и m[a], m[a+1], m[a+2] и так далее...
                    m[i] = m[j];                 // то есть переносим элементы меньшие m[b] в начало,
                    m[j] = t;                    // а затем и сам m[b] «сверху»
                    i++;                         // таким образом последний обмен: m[b] и m[i], после чего i++
                }
            }
            return i - 1;                        // в индексе i хранится <новая позиция элемента m[b]> + 1
        }

        void quicksort<T>(T[] m, int a, int b) where T : IComparable<T>// a - начало подмножества, b - конец
        {                                        // для первого вызова: a = 0, b = <элементов в массиве> - 1
            if (a >= b) return;
            int c = partition(m, a, b);
            quicksort(m, a, c - 1);
            quicksort(m, c + 1, b);
        }


        private static string ReadRegKey(UIntPtr rootKey, string keyPath, string valueName)
        {
            UIntPtr hKey = UIntPtr.Zero;
            if (RegOpenKeyEx(rootKey, keyPath, 0, (int)RegistrySecurity.KEY_READ, out hKey) == 0)
            {
                int size = 1024;
                RegistryValueKind type = RegistryValueKind.String;
                string keyValue = null;
                StringBuilder keyBuffer = new StringBuilder((int)size);

                //ObjectHandleExtensions.ToIntPtr(keyBuffer);
                if (RegQueryValueEx(hKey, valueName, 0, ref type, keyBuffer, ref size) == 0)
                    keyValue = keyBuffer.ToString();

                //RegCloseKey(hKey);

                return (keyValue);
            }

            uint lasterror = GetLastError();
            return (null);  // Return null if the value could not be read
        }


        


        static IntPtr infileHANDLE, outfileHANDLE;
        string infileName = ReadRegKey(HKEY_LOCAL_MACHINE, @"SOFTWARE\lab5", "IN_File"), outfileName = ReadRegKey(HKEY_LOCAL_MACHINE, @"SOFTWARE\lab5", "OUT_File");

        int filecounter = 0;
        int outfilePointer = 0;
        void RecursiveBlockSort(string InFileName, string OutFileName, int sizeToRead, int parts, ulong RAMAviable, bool firstcall=true)
        {
            infileHANDLE = CreateFile(
             (string)InFileName,
             winapi.FileAccess.FILE_GENERIC_READ,
             winapi.FileShare.Write | winapi.FileShare.Read | winapi.FileShare.Delete,
             IntPtr.Zero,
             System.IO.FileMode.Open,
             winapi.FileAttributes.Overlapped,
             IntPtr.Zero
             );

            byte[] buf = new byte[RAMAviable];

            List<FileBlock> fileblocks = new List<FileBlock>();
            long fileSize;
            GetFileSizeEx(infileHANDLE, out fileSize);

            Dispatcher.Invoke(() => logbox.Text += string.Format("FreeBytesAvailable = {0} < fileSize * 2 = {1}\r\n", FreeBytesAvailable, (ulong)fileSize * 2));

            if (FreeBytesAvailable > (ulong)fileSize * 2)
            {
                uint readedbyte = 0;
                IntPtr myEventHandle = CreateEvent(IntPtr.Zero, false, true, "MyEvent");
                OVERLAPPED overlapped = new OVERLAPPED();
                overlapped.EventHandle = myEventHandle;


                overlapped.Offset = 0;
                ReadFile(infileHANDLE, buf, 1, ref readedbyte, ref overlapped);
                int MAXvalue = buf[0], MINvalue = buf[0];


                overlapped.Offset = 0;
                for (overlapped.Offset = 0; overlapped.Offset < fileSize; overlapped.Offset += 1)
                {
                    ReadFile(infileHANDLE, buf, 1, ref readedbyte, ref overlapped);

                    if (buf[0] > MAXvalue) MAXvalue = buf[0];
                    if (buf[0] < MINvalue) MINvalue = buf[0];
                }

                float k = (float)(MAXvalue - MINvalue) / parts;

                MINvalue--;



                for (int i = 0; i < parts; i++)
                {
                    fileblocks.Add(new FileBlock(String.Format(@"tmp{0}.txt", filecounter), CreateFile(
                        String.Format(@"tmp{0}.txt", filecounter++),
                        winapi.FileAccess.GenericAll,
                        winapi.FileShare.Write | winapi.FileShare.Read | winapi.FileShare.Delete,
                        IntPtr.Zero,
                        System.IO.FileMode.Create,
                        winapi.FileAttributes.Overlapped,
                        IntPtr.Zero
                        ), (int)Math.Ceiling(MINvalue + k * i + 1), (int)Math.Ceiling(MINvalue + k * (i + 1))));
                }
                fileblocks[fileblocks.Count - 1].MAXValue++;



                for (int i = 0; i < fileSize; i += 1)
                {
                    overlapped.Offset = (uint)i;

                    ReadFile(infileHANDLE, buf, (uint)1, ref readedbyte, ref overlapped);

                    for (int j = 0; j < fileblocks.Count; j++)
                    {
                        if ((fileblocks[j].MINValue <= buf[0]) && (fileblocks[j].MAXValue >= buf[0]))
                        {
                            overlapped.Offset = (uint)fileblocks[j].size++;
                            WriteFile(fileblocks[j].fileHandle, buf, 1, out readedbyte, ref overlapped);
                            break;
                        }
                    }
                }

                CloseHandle(infileHANDLE);

                for (int i = 0; i < fileblocks.Count; i++)
                {

                    if (fileblocks[i].size <= (int)RAMAviable)
                    {
                        overlapped.Offset = 0;
                        ReadFile(fileblocks[i].fileHandle, buf, (uint)fileblocks[i].size, ref readedbyte, ref overlapped);
                        quicksort<byte>(buf, 0, fileblocks[i].size - 1);
                        overlapped.Offset = (uint)outfilePointer;
                        WriteFile(outfileHANDLE, buf, (uint)fileblocks[i].size, out readedbyte, ref overlapped);
                        outfilePointer += fileblocks[i].size;

                        CloseHandle(fileblocks[i].fileHandle);
                        DeleteFile(String.Format(fileblocks[i].filename, i));
                    }
                    else
                    {
                        int duplicates = 0;
                        byte[] firstelement = new byte[1];
                        overlapped.Offset = 0;
                        ReadFile(fileblocks[i].fileHandle, firstelement, 1, ref readedbyte, ref overlapped);
                        for (int j = 0; j < fileblocks[i].size; j++)
                        {
                            ReadFile(fileblocks[i].fileHandle, buf, 1, ref readedbyte, ref overlapped);

                            if (buf[0] == firstelement[0])
                            {
                                duplicates++;
                            }
                            overlapped.Offset++;
                        }


                        if (fileblocks[i].size == duplicates)
                        {
                            overlapped.Offset = 0;

                            for (int j = 0; j < fileblocks[i].size; j++)
                            {
                                overlapped.Offset = (uint)outfilePointer;
                                WriteFile(outfileHANDLE, firstelement, 1, out readedbyte, ref overlapped);
                                outfilePointer++;

                            }
                            CloseHandle(fileblocks[i].fileHandle);
                            DeleteFile(String.Format(fileblocks[i].filename, i));

                            //break;
                        }
                        else
                        {
                            DeleteFile(String.Format(InFileName, i));

                            RecursiveBlockSort(fileblocks[i].filename, OutFileName, sizeToRead, parts, RAMAviable, false);
                            CloseHandle(fileblocks[i].fileHandle);
                            DeleteFile(String.Format(fileblocks[i].filename, i));

                        }
                    }
                }
            }
            else
            {
                DialogResult result = System.Windows.Forms.MessageBox.Show(
                    "Для сортировки не достаточно свободной памяти на жёстком диске, освободите память и попробуйте запустить сортировку заново.",
                    "Ошибка!",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error,
                    MessageBoxDefaultButton.Button1
                    );
                Environment.Exit(0);
            }
        }

        //private void BlockSort(string InFileName, string OutFileName, int sizeToRead, ulong RAMAviable)
        //{

        //    outfileHANDLE = CreateFile(
        //     OutFileName,
        //     winapi.FileAccess.FILE_GENERIC_WRITE,
        //     winapi.FileShare.Write | winapi.FileShare.Read | winapi.FileShare.Delete,
        //     IntPtr.Zero,
        //     System.IO.FileMode.Create,
        //     winapi.FileAttributes.Overlapped,
        //     IntPtr.Zero
        //     );

        //    List<FileBlock> fileblocks = new List<FileBlock>();
        //    OVERLAPPED overlapped = new OVERLAPPED();

        //    long fileSize;
        //    bool result = GetFileSizeEx(infileHANDLE, out fileSize);
        //    int blocks_count = (int)Math.Ceiling((double)fileSize / (double)RAMAviable);

        //    int block_size = (int)Math.Ceiling((double)fileSize / blocks_count);

        //    for (int i = 0; i < blocks_count; i++)
        //    {
        //        Dispatcher.Invoke(() => logbox.Text += string.Format("Создание нового блока №{0}, объёмом = {1} байт;\r\n", i, block_size));

        //        fileblocks.Add(new FileBlock(CreateFile(
        //            String.Format(@"tmp{0}.txt", i),
        //            winapi.FileAccess.GenericAll,
        //            winapi.FileShare.Write | winapi.FileShare.Read | winapi.FileShare.Delete,
        //            IntPtr.Zero,
        //            System.IO.FileMode.Create,
        //            winapi.FileAttributes.Overlapped,
        //            IntPtr.Zero
        //            )));
        //    }

        //    byte[] buf = new byte[block_size];
        //    IntPtr myEventHandle = CreateEvent(IntPtr.Zero, false, true, "MyEvent");
        //    if (myEventHandle != IntPtr.Zero)
        //    {
        //        Dispatcher.Invoke(() => logbox.Text += string.Format("Объект синхронизации успешно создан;\r\n"));

        //        uint readedbyte = 0;
        //        overlapped.EventHandle = myEventHandle;


        //        overlapped.Offset = 0;
        //        ReadFile(infileHANDLE, buf, 1, ref readedbyte, ref overlapped);
        //        int MAXvalue = buf[0];

        //        overlapped.Offset = 0;
        //        for (overlapped.Offset = 0; overlapped.Offset < fileSize; overlapped.Offset += 1)
        //        {
        //            ReadFile(infileHANDLE, buf, 1, ref readedbyte, ref overlapped);

        //            if (buf[0] > MAXvalue) MAXvalue = buf[0];
        //        }

        //        float delta = (float)blocks_count / ((float)MAXvalue + 1);

        //        for (int i = 0; i < fileSize; i += 1)
        //        {
        //            overlapped.Offset = (uint)i;
        //            ReadFile(infileHANDLE, buf, 1, ref readedbyte, ref overlapped);

        //            //Console.WriteLine(buf[0] * delta);
        //            overlapped.Offset = (uint)fileblocks[(int)(buf[0] * delta)].size++;

        //            WriteFile(fileblocks[(int)(buf[0] * delta)].fileHandle, buf, 1, out readedbyte, ref overlapped);
        //        }


        //        int k = 0;
        //        for (int i = 0; i < fileblocks.Count; i += 1)
        //        {
        //            overlapped.Offset = 0;

        //            buf = new byte[fileblocks[i].size];

        //            ReadFile(fileblocks[i].fileHandle, buf, (uint)fileblocks[i].size, ref readedbyte, ref overlapped);
        //            Dispatcher.Invoke(() => logbox.Text += string.Format("Данные из {0}-го блока считаны в память ({1} байт)\r\n", i, fileblocks[i].size - 1));

        //            QuickSort(buf, 0, fileblocks[i].size - 1);
        //            Dispatcher.Invoke(() => logbox.Text += string.Format("Данные из {0}-го блока отсотртированны в памяти\r\n", i));

        //            overlapped.Offset = (uint)k;

        //            Dispatcher.Invoke(() => logbox.Text += string.Format("Данные из {0}-го блока записанны в конечный файл\r\n", i));
        //            WriteFile(outfileHANDLE, buf, (uint)buf.Length, out readedbyte, ref overlapped);
        //            k += buf.Length;
        //        }

        //        //diskStreamToRead.Read(buf, 0, 512);
        //        //try { diskStreamToRead.Close(); } catch { }
        //        //try { drive.Close(); } catch { }
        //    }



        //    //CloseHandle(myEventHandle);
        //    CloseHandle(infileHANDLE);
        //    CloseHandle(outfileHANDLE);

        //    for (int i = 0; i < blocks_count; i++)
        //    {
        //        CloseHandle(fileblocks[i].fileHandle);
        //        DeleteFile(String.Format(@"tmp{0}.txt", i));
        //    }

        //    Dispatcher.Invoke(() => logbox.Text += string.Format("Закрытие входного, выходного и всех временных файлов\r\n"));
        //    Dispatcher.Invoke(() => logbox.Text += string.Format("Удаление временных файлов\r\n"));



        //    outfileHANDLE = CreateFile(
        //     (string)outfileName,
        //     winapi.FileAccess.FILE_GENERIC_READ,
        //     winapi.FileShare.Read | winapi.FileShare.Delete,
        //     IntPtr.Zero,
        //     FileMode.Open,
        //     winapi.FileAttributes.Overlapped,
        //     IntPtr.Zero
        //     );

        //    buf = new byte[256];
        //    overlapped.Offset = 0;
        //    uint readedbytes = 0;
        //    ReadFile(outfileHANDLE, buf, 256, ref readedbytes, ref overlapped);

        //    Dispatcher.Invoke(() =>
        //    {
        //        for (int i = 0; i < Array.FindIndex<byte>(buf, (a) => a == 0); i++) listBox2.Items.Add(new ListBoxItem() { Content = buf[i].ToString() });
        //        if (Array.FindIndex<byte>(buf, (a) => a == 0) >= 254) listBox2.Items.Add(new ListBoxItem() { Content = "..." });
        //    }
        //    );
        //}


        async void task()
        {
            filecounter = 0;

            MEMORYSTATUSEX mEMORYSTATUSEX = new MEMORYSTATUSEX();
            GlobalMemoryStatusEx(mEMORYSTATUSEX);

            ulong RAMSize = 0;
            try
            {
                RAMSize = ulong.Parse(ReadRegKey(HKEY_LOCAL_MACHINE, @"SOFTWARE\lab5", "RAM_SIZE"));
                Dispatcher.Invoke(() => logbox.Text += string.Format("Искуственное ограничение оперативный памяти до {0} байт!\r\n", RAMSize));

            }
            catch (Exception) { }

            Dispatcher.Invoke(() => logbox.Text += string.Format("* Запуск алгоритма блочной сортировки *\r\n"));

            Task.Run(() =>
            {
                RecursiveBlockSort((string)infileName, (string)outfileName, 10, 2, (ulong)(RAMSize == 0 ? mEMORYSTATUSEX.ullAvailPhys : RAMSize));

                long fileSize;
                bool result = GetFileSizeEx(outfileHANDLE, out fileSize);
                OVERLAPPED overlapped = new OVERLAPPED();
                byte[] buf = new byte[fileSize];
                IntPtr myEventHandle = CreateEvent(IntPtr.Zero, false, true, "MyEvent");
                overlapped.EventHandle = myEventHandle;
                overlapped.Offset = 0;
                uint readedbytes = 0;
                ReadFile(outfileHANDLE, buf, (uint)fileSize, ref readedbytes, ref overlapped);

                Dispatcher.Invoke(() =>
                {
                    for (int i = 0; i < fileSize; i++) listBox2.Items.Add(new ListBoxItem() { Content = buf[i].ToString() });
                    if (fileSize >= 254) listBox2.Items.Add(new ListBoxItem() { Content = "..." });
                });
                CloseHandle(myEventHandle);

            });
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            DialogResult result = System.Windows.Forms.MessageBox.Show(
                "Очистить записи программы в реестре?",
                "Сообщение",
                MessageBoxButtons.YesNo,
                MessageBoxIcon.Information,
                MessageBoxDefaultButton.Button1
                );

            if (result == System.Windows.Forms.DialogResult.Yes)
            {
                RegDeleteKeyA(HKEY_LOCAL_MACHINE, @"SOFTWARE\lab5");
            }
        }

        ulong FreeBytesAvailable;
        ulong TotalNumberOfBytes;
        ulong TotalNumberOfFreeBytes;

        public MainWindow()
        {
            InitializeComponent();

            infileHANDLE = CreateFile(
             (string)infileName,
             winapi.FileAccess.FILE_GENERIC_READ,
             winapi.FileShare.Write | winapi.FileShare.Read | winapi.FileShare.Delete,
             IntPtr.Zero,
             System.IO.FileMode.Open,
             winapi.FileAttributes.Overlapped,
             IntPtr.Zero
             );

            outfileHANDLE = CreateFile(
             (string)outfileName,
             winapi.FileAccess.GenericRead | winapi.FileAccess.GenericWrite,
             winapi.FileShare.Write | winapi.FileShare.Read | winapi.FileShare.Delete,
             IntPtr.Zero,
             System.IO.FileMode.Create,
             winapi.FileAttributes.Overlapped,
             IntPtr.Zero
             );


            long fileSize;
            bool result = GetFileSizeEx(infileHANDLE, out fileSize);
            OVERLAPPED overlapped = new OVERLAPPED();
            byte[] buf = new byte[fileSize];
            IntPtr myEventHandle = CreateEvent(IntPtr.Zero, false, true, "MyEvent");
            overlapped.EventHandle = myEventHandle;
            overlapped.Offset = 0;
            uint readedbytes = 0;
            ReadFile(infileHANDLE, buf, (uint)fileSize, ref readedbytes, ref overlapped);
            for (int i = 0; i < fileSize; i++) listBox1.Items.Add(new ListBoxItem() { Content = buf[i].ToString() });
            if (fileSize >= 254) listBox1.Items.Add(new ListBoxItem() { Content = "..." });
            CloseHandle(myEventHandle);


            logbox.Text += "Входное имя файла = " + infileName+"\n";
            logbox.Text += "Выходное имя файла = " + outfileName + "\n";

            Task.Run(() =>
            {
                while (true)
                {
                    string tom = System.Reflection.Assembly.GetEntryAssembly().Location.Split("\\".ToCharArray())[0];

                    
                    Dispatcher.Invoke(() => logbox.Text += string.Format("Рабочий диск {0} \r\n", tom));
                    bool success = GetDiskFreeSpaceEx(tom + "\\", out FreeBytesAvailable, out TotalNumberOfBytes, out TotalNumberOfFreeBytes);
                    if (!success) throw new System.ComponentModel.Win32Exception();

                    Console.WriteLine((FreeBytesAvailable / TotalNumberOfBytes * 100));
                    Dispatcher.Invoke(() => progressbar.Value = (100 - (float)FreeBytesAvailable / (float)TotalNumberOfBytes * 100));
                    Dispatcher.Invoke(() => label2.Content = (100 - (float)FreeBytesAvailable / (float)TotalNumberOfBytes * 100).ToString()+"%");
                    
                    Dispatcher.Invoke(() => logbox.Text += string.Format("{0} кластеров оперативной памяти доступно!\r\n", FreeBytesAvailable));

                    if (FreeBytesAvailable < 5)
                    {
                        Dispatcher.Invoke(() => logbox.Text += "Недостаточно памяти!\r\n");
                        //Console.WriteLine("Недостаточно памяти!");
                    }
                    Thread.Sleep(1000);
                }
            });


        }

        private void button_Click(object sender, RoutedEventArgs e)
        {
            task();
        }
    }
}
