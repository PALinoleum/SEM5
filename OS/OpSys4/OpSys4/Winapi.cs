using System;
using System.Runtime.InteropServices;
using System.Text;
namespace WpfApp17
{
    static class winapi
    {
        [Flags]
        public enum ProcessAccessFlags : uint
        {
            All = 0x001F0FFF,
            Terminate = 0x00000001, CreateThread = 0x00000002, VirtualMemoryOperation = 0x00000008, VirtualMemoryRead = 0x00000010,
            VirtualMemoryWrite = 0x00000020, DuplicateHandle = 0x00000040, CreateProcess = 0x000000080, SetQuota = 0x00000100,
            SetInformation = 0x00000200, QueryInformation = 0x00000400, QueryLimitedInformation = 0x00001000, Synchronize = 0x00100000
        }
        [Flags]
        public enum SnapshotFlags : uint
        {
            HeapList = 0x00000001, Process = 0x00000002, Thread = 0x00000004, Module = 0x00000008, Module32 = 0x00000010, Inherit = 0x80000000,
            All = 0x0000001F, NoHeaps = 0x40000000
        }
        [StructLayout(LayoutKind.Sequential)]
        public struct MEMORY_BASIC_INFORMATION
        {
            public IntPtr BaseAddress, AllocationBase; public uint AllocationProtect; public IntPtr RegionSize; public uint State, Protect, Type;
        }
        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]
        public struct PROCESSENTRY32
        {
            const int MAX_PATH = 260;
            internal UInt32 dwSize; internal UInt32 cntUsage; internal UInt32 th32ProcessID; internal IntPtr th32DefaultHeapID; internal UInt32 th32ModuleID;
            internal UInt32 cntThreads; internal UInt32 th32ParentProcessID; internal Int32 pcPriClassBase; internal UInt32 dwFlags;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = MAX_PATH)]
            internal string szExeFile;
        }

        public enum ProcessorArchitecture { 86 = 0, Arm = 5, Itanium = 6, X64 = 9, ARM64 = 12, Unknown = 0xFFFF, }

        [StructLayout(LayoutKind.Sequential)]
        public struct SYSTEM_INFO
        {
            public ProcessorArchitecture ProcessorArchitecture; // WORD 
            public uint PageSize; // DWORD 
            public IntPtr MinimumApplicationAddress; // (long)void* 
            public IntPtr MaximumApplicationAddress; // (long)void* 
            public IntPtr ActiveProcessorMask; // DWORD* 
            public uint NumberOfProcessors; // DWORD (WTF) 
            public uint ProcessorType; // DWORD 
            public uint AllocationGranularity; // DWORD 
            public ushort ProcessorLevel; // WORD 
            public ushort ProcessorRevision; // WORD 
        }

        [DllImport("kernel32.dll", SetLastError = false)]
        public static extern void GetSystemInfo(out SYSTEM_INFO Info);
        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]
        public class MEMORYSTATUSEX
        {
            public uint Length, MemoryLoad;
            public ulong TotalPhys, AvailPhys, TotalPageFile, AvailPageFile, TotalVirtual, AvailVirtual, AvailExtendedVirtual;
            public MEMORYSTATUSEX() { this.Length = (uint)Marshal.SizeOf(typeof(MEMORYSTATUSEX)); }
        }

        [return: MarshalAs(UnmanagedType.Bool)]
        [DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        public static extern bool GlobalMemoryStatusEx([In, Out] MEMORYSTATUSEX lpBuffer);
        [DllImport("kernel32.dll")]
        public static extern int VirtualQueryEx(IntPtr hProcess, IntPtr lpAddress, out MEMORY_BASIC_INFORMATION lpBuffer, uint dwLength);
        [DllImport("kernel32.dll", SetLastError = true)]
        public static extern IntPtr OpenProcess(ProcessAccessFlags processAccess, bool bInheritHandle, int processId);
        [DllImport("kernel32.dll", SetLastError = true)]
        public static extern IntPtr CreateToolhelp32Snapshot(SnapshotFlags dwFlags, uint th32ProcessID);
        [DllImport("kernel32", SetLastError = true, CharSet = CharSet.Auto)]
        public static extern bool Process32First([In]IntPtr hSnapshot, ref PROCESSENTRY32 lppe);
        [DllImport("kernel32", SetLastError = true, CharSet = CharSet.Auto)]
        public static extern bool Process32Next([In]IntPtr hSnapshot, ref PROCESSENTRY32 lppe);
        internal const ushort PROCESSOR_ARCHITECTURE_INTEL = 0; internal const ushort PROCESSOR_ARCHITECTURE_IA64 = 6;
        internal const ushort PROCESSOR_ARCHITECTURE_AMD64 = 9; internal const ushort PROCESSOR_ARCHITECTURE_UNKNOWN = 0xFFFF;
        [DllImport("kernel32.dll")]
        public static extern void GetNativeSystemInfo(ref SYSTEM_INFO lpSystemInfo);
        [DllImport("kernel32.dll")]
        public static extern uint GetLastError();
        [DllImport("psapi.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
        public static extern uint GetModuleFileNameEx(IntPtr hProcess, IntPtr hModule, [Out] StringBuilder lpBaseName, uint nSize);
    }
}