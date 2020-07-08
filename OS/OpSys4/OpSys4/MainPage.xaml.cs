using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System;
using System.Collections.Generic; 
… 
using System.Windows.Shapes;
using static WpfApp17.winapi;

namespace WpfApp17
{
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

        private void textBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            bool finded = false;
            listblock.Items.Clear();
            listblock.Items.Add(new ListBoxItem() { Content = String.Format("Начало страниц - конец страницы | размер | состояние | атрибут защиты | тип физической памяти") });
            try
            {
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

                                long address = 0;
                                MEMORY_BASIC_INFORMATION m = new MEMORY_BASIC_INFORMATION();

                                do
                                {
                                    int result = VirtualQueryEx(hProcess, (IntPtr)address, out m, (uint)Marshal.SizeOf(m));
                                    if (result == 0) break;

                                    StringBuilder Name = new StringBuilder(255);
                                    GetModuleFileNameEx(hProcess, m.BaseAddress, Name, (uint)Name.Capacity);

                                    string eltext = "";
                                    eltext += String.Format(" 0x{0:x8}-0x{1:x8} : {2:d8} ", (uint)m.BaseAddress, ((uint)m.BaseAddress + (uint)m.RegionSize - 1), (uint)m.RegionSize);

                                    if (Name.ToString().Length > 5 && Name.ToString().Contains("\\") && (uint)address != 0) listblock.Items.Add(new ListBoxItem() { Content = String.Format("({0})", Name.ToString().Split("\\".ToCharArray()).Last()) });

                                    eltext += " | ";
                                    if (m.State == 0x1000) eltext += "State=MEM_COMMIT ";
                                    if (m.State == 0x10000) eltext += "State=MEM_FREE ";
                                    if (m.State == 0x2000) eltext += "State=MEM_RESERVE ";
                                    if (m.Type == 0x1000000) eltext += "Type=MEM_IMAGE ";
                                    if (m.Type == 0x40000) eltext += "Type=MEM_MAPPED ";
                                    if (m.Type == 0x20000) eltext += "Type=MEM_PRIVATE ";

                                    eltext += "[ Protect : ";
                                    if (m.Protect == 0x10) eltext += "PAGE_EXECUTE ";
                                    if (m.Protect == 0x20) eltext += "PAGE_EXECUTE_READ ";
                                    if (m.Protect == 0x40) eltext += "PAGE_EXECUTE_READWRITE ";
                                    if (m.Protect == 0x80) eltext += "PAGE_EXECUTE_WRITECOPY ";
                                    if (m.Protect == 0x01) eltext += "PAGE_NOACCESS ";
                                    if (m.Protect == 0x02) eltext += "PAGE_READONLY ";
                                    if (m.Protect == 0x04) eltext += "PAGE_READWRITE ";
                                    if (m.Protect == 0x08) eltext += "PAGE_WRITECOPY ";
                                    if (m.Protect == 0x40000000) eltext += "PAGE_TARGETS_INVALID ";
                                    if (m.Protect == 0x40000000) eltext += "PAGE_TARGETS_NO_UPDATE ";
                                    if (m.Protect == 0x100) eltext += "PAGE_GUARD ";
                                    if (m.Protect == 0x200) eltext += "PAGE_NOCACHE ";
                                    if (m.Protect == 0x400) eltext += "PAGE_WRITECOMBINE ";
                                    eltext += "]";

                                    listblock.Items.Add(new ListBoxItem() { Content = eltext });

                                    address = (long)m.BaseAddress + (long)m.RegionSize;
                                } while (true);

                                GetLastError();
                                finded = true;
                                break;
                            }
                        } while (Process32Next(hSnapshot, ref pe32));
                    }
                }
            }
            catch (Exception)
            {
                throw;
            }
            if (!finded) label2.Content = "";
        }
    }
}