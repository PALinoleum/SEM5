using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using static WpfApp17.winapi;

namespace WpfApp17
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>

    public static class BinaryExt
    {
        public static string ToBinary(this int number, int bitsLength = 32)
        {
            return NumberToBinary(number, bitsLength);
        }

        public static string NumberToBinary(int number, int bitsLength = 32)
        {
            string result = Convert.ToString(number, 2).PadLeft(bitsLength, '0');

            return result;
        }

        public static int FromBinaryToInt(this string binary)
        {
            return BinaryToInt(binary);
        }

        public static int BinaryToInt(string binary)
        {
            return Convert.ToInt32(binary, 2);
        }
    }


    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            SYSTEM_INFO iNFO;
            GetSystemInfo(out iNFO);
            infolabel1.Content = iNFO.ProcessorArchitecture;
            infolabel2.Content = iNFO.PageSize;
            infolabel3.Content = iNFO.MinimumApplicationAddress.ToString("x") + "h";
            infolabel4.Content = iNFO.MaximumApplicationAddress.ToString("x") + "h";
            infolabel5.Content = BinaryExt.ToBinary(iNFO.ActiveProcessorMask.ToInt32()).ToString();
            infolabel6.Content = iNFO.NumberOfProcessors;
            infolabel7.Content = iNFO.ProcessorType;
            infolabel8.Content = iNFO.AllocationGranularity;
            infolabel9.Content = iNFO.ProcessorLevel;
            infolabel10.Content = iNFO.ProcessorRevision;

            task2();

            //chartvalue = 0;
        }

        int chartvalue = 0;

        public async void task2()
        {
            await Task.Run(() =>
            {

                while (true)
                {
                    MEMORYSTATUSEX mEMORYSTATUSEX = new MEMORYSTATUSEX();
                    GlobalMemoryStatusEx(mEMORYSTATUSEX);

                    chartvalue += 10;
                    Dispatcher.Invoke(() =>
                    {
                        textBlock_Copy19.Text = "TotalPhys: " + mEMORYSTATUSEX.TotalPhys.ToString();
                        textBlock_Copy20.Text = "AvailPhys: " + mEMORYSTATUSEX.AvailPhys.ToString();
                        textBlock_Copy21.Text = "TotalPageFile: " + mEMORYSTATUSEX.TotalPageFile.ToString();
                        textBlock_Copy22.Text = "AvailPageFile: " + mEMORYSTATUSEX.AvailPageFile.ToString();
                        textBlock_Copy23.Text = "TotalVirtual: " + mEMORYSTATUSEX.TotalVirtual.ToString();
                        textBlock_Copy24.Text = "AvailVirtual: " + mEMORYSTATUSEX.AvailVirtual.ToString();
                        textBlock_Copy25.Text = "AvailExtendedVirtual: " + mEMORYSTATUSEX.AvailExtendedVirtual;

                        Resources["GaugeValue1"] = Math.Round(Math.Abs((Double)mEMORYSTATUSEX.AvailPhys / mEMORYSTATUSEX.TotalPhys * 100 - 100), 2);
                        Resources["GaugeValue2"] = Math.Round(Math.Abs((Double)mEMORYSTATUSEX.AvailVirtual / mEMORYSTATUSEX.TotalVirtual * 100 - 100), 2);
                        Resources["GaugeValue3"] = Math.Round(Math.Abs((Double)mEMORYSTATUSEX.AvailPageFile / mEMORYSTATUSEX.TotalPageFile * 100 - 100), 2);
                        Resources["GaugeValue4"] = Math.Round((double)mEMORYSTATUSEX.MemoryLoad, 2);

                    });

                    Thread.Sleep(1000);

                }

            });
        }

        private void button_Click(object sender, RoutedEventArgs e)
        {

            //chartvalue += 5;
        }

        private void Window_Initialized(object sender, EventArgs e)
        {


        }


        public class mapelement
        {
            public string _ModuleName;
            public string _BaseAddress;
            public string _EndAddress;
            public string _Size;
            public string _State;
            public string _Protection;
            public string _MemoryType;

            public string ModuleName
            {
                get { return _ModuleName; }
                set { _ModuleName = value; }
            }
            public string BaseAddress
            {
                get { return _BaseAddress; }
                set { _BaseAddress = value; }
            }
            public string EndAddress
            {
                get { return _EndAddress; }
                set { _EndAddress = value; }
            }
            public string Size
            {
                get { return _Size; }
                set { _Size = value; }
            }
            public string State
            {
                get { return _State; }
                set { _State = value; }
            }
            public string Protection
            {
                get { return _Protection; }
                set { _Protection = value; }
            }
            public string MemoryType
            {
                get { return _MemoryType; }
                set { _MemoryType = value; }
            }
        }

        public ObservableCollection<mapelement> processmap { get; set; }

        private void textBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            processmap = new ObservableCollection<mapelement>();

            bool finded = false;
            listblock.Items.Clear();
            listblock.Items.Add(new ListBoxItem() { Content = String.Format("Начало страниц - конец страницы | размер | состояние | атрибут защиты | тип физической памяти") });
            //try
            //{
                IntPtr hSnapshot = CreateToolhelp32Snapshot(SnapshotFlags.Process, 0);
                if (hSnapshot.ToInt32() != 0)
                {
                    PROCESSENTRY32 pe32 = new PROCESSENTRY32();
                    pe32.dwSize = (uint)Marshal.SizeOf(pe32);
                    if (Process32First(hSnapshot, ref pe32))
                    {
                        do
                        {
                            if (pe32.szExeFile.Contains(textBox.Text))
                            {
                                SYSTEM_INFO sysInfo = new SYSTEM_INFO();
                                GetNativeSystemInfo(ref sysInfo);


                                IntPtr hProcess = OpenProcess(ProcessAccessFlags.All, false, (int)pe32.th32ProcessID);
                                if ((int)pe32.th32ProcessID != 0)
                                {
                                    label2.Content = String.Format("(PID = {0})", (int)pe32.th32ProcessID);
                                }
                                else
                                {
                                    label2.Content = "";
                                }

                                long MaxAddress = 0x7fffffff;
                                //long address = (long)System.Diagnostics.Process.GetProcessesByName("Adguard_6.X_Setup_Online_Ml_Rus")[0].MainModule.BaseAddress;

                                //if ((long)System.Diagnostics.Process.GetProcessesByName("uTorrent.exe").Length == 0) break;
                                //long address = (long)System.Diagnostics.Process.GetProcessesByName("uTorrent.exe")[0].MainModule.BaseAddress;
                                long address = 0;
                                MEMORY_BASIC_INFORMATION m = new MEMORY_BASIC_INFORMATION();//GetCurrentProcess, System.Diagnostics.Process.GetProcessesByName("Adguard_6.X_Setup_Online_Ml_Rus")[0].Handle

                                do
                                {

                                    int result = VirtualQueryEx(hProcess, (IntPtr)address, out m, (uint)Marshal.SizeOf(m));//System.Diagnostics.Process.GetCurrentProcess().Handle
                                    if (result == 0) break;

                                    if ((uint)m.BaseAddress == 0x6a200000)
                                    {
                                        ;
                                    }

                                    StringBuilder Name = new StringBuilder(255);
                                    //GetModuleFileName(m.BaseAddress, Name, Name.Capacity);
                                    GetModuleFileNameEx(hProcess, m.BaseAddress, Name, (uint)Name.Capacity);
                                    //string convertedUtf8 = Encoding.UTF8.GetString(Encoding.Unicode.GetBytes(Name.ToString()));



                                    string Statetext = "", ProtectText = "", MemoryTypeText = "";
                                    //eltext += String.Format("      0x{0:x8}-0x{1:x8} : {2:d8} ", (uint)m.BaseAddress, ((uint)m.BaseAddress + (uint)m.RegionSize - 1), (uint)m.RegionSize); uTorrent
                                    
                                    

                                    if (Name.ToString().Length > 5 && Name.ToString().Contains("\\") && (uint)address != 0) listblock.Items.Add(new ListBoxItem() { Content = String.Format("({0})", Name.ToString().Split("\\".ToCharArray()).Last()) });

                                    //eltext += " | ";
                                    if (m.State == 0x1000) Statetext += "MEM_COMMIT ";
                                    if (m.State == 0x10000) Statetext += "MEM_FREE ";
                                    if (m.State == 0x2000) Statetext += "MEM_RESERVE ";

                                    if (m.Type == 0x1000000) MemoryTypeText += "MEM_IMAGE ";
                                    if (m.Type == 0x40000) MemoryTypeText += "MEM_MAPPED ";
                                    if (m.Type == 0x20000) MemoryTypeText += "MEM_PRIVATE ";

                                    //eltext += "[ Protect : ";
                                    if (m.Protect == 0x10) ProtectText += "PAGE_EXECUTE ";
                                    if (m.Protect == 0x20) ProtectText += "PAGE_EXECUTE_READ ";
                                    if (m.Protect == 0x40) ProtectText += "PAGE_EXECUTE_READWRITE ";
                                    if (m.Protect == 0x80) ProtectText += "PAGE_EXECUTE_WRITECOPY ";
                                    if (m.Protect == 0x01) ProtectText += "PAGE_NOACCESS ";
                                    if (m.Protect == 0x02) ProtectText += "PAGE_READONLY ";
                                    if (m.Protect == 0x04) ProtectText += "PAGE_READWRITE ";
                                    if (m.Protect == 0x08) ProtectText += "PAGE_WRITECOPY ";
                                    if (m.Protect == 0x40000000) ProtectText += "PAGE_TARGETS_INVALID ";
                                    if (m.Protect == 0x40000000) ProtectText += "PAGE_TARGETS_NO_UPDATE ";
                                    if (m.Protect == 0x100) ProtectText += "PAGE_GUARD ";
                                    if (m.Protect == 0x200) ProtectText += "PAGE_NOCACHE ";
                                    if (m.Protect == 0x400) ProtectText += "PAGE_WRITECOMBINE ";
                                //eltext += "]";

                                //string a = m.GetType().Name;
                                //listblock.Items.Add(new ListBoxItem() { Content = eltext });
                                string ModuleName = "";
                                if (Name.ToString().Length > 5 && Name.ToString().Contains("\\") && (uint)address != 0 && Name.ToString().Split("\\".ToCharArray()).Last().IndexOf(".")>1) ModuleName = String.Format("({0})", Name.ToString().Split("\\".ToCharArray()).Last());

                                processmap.Add(new mapelement() { ModuleName = ModuleName, BaseAddress = String.Format("0x{0:x8}", (uint)m.BaseAddress), EndAddress = String.Format("0x{0:x8}", ((uint)m.BaseAddress + (uint)m.RegionSize - 1)), Size = String.Format("{0:d8}", (uint)m.RegionSize), State = Statetext, Protection = ProtectText, MemoryType = MemoryTypeText });

                                address = (long)m.BaseAddress + (long)m.RegionSize;
                                    //} while (address < (long)(System.Diagnostics.Process.GetProcessesByName("Adguard_6.X_Setup_Online_Ml_Rus")[0].MainModule.BaseAddress.ToInt32()+sysInfo..ToInt32()));
                                } while (true);//(address < 0x7FFE7000);

                                GetLastError();
                                finded = true;
                                if (processmap != null)
                                {
                                    dataGrid.ItemsSource = processmap;
                                }
                                else
                                {
                                    dataGrid.Items.Clear();
                                }
                                break;
                            }
                            //ListBoxItem lbi = new ListBoxItem();
                            //lbi.Content = "pid : " + pe32.th32ProcessID + " | " + pe32.szExeFile;
                            //lbi.Tag = pe32.th32ProcessID;
                            //processeslst.Items.Add(lbi);
                            //printf("pid %d %s\n", pe32.th32ProcessID, pe32.szExeFile);
                        } while (Process32Next(hSnapshot, ref pe32));
                    }
                    //CloseHandle(hSnapshot);
                }

            //}
            //catch (Exception)
            //{
                //throw;

            //}
            if (!finded) label2.Content = "";

        }
    }
}
