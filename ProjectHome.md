Being a linux programmer, we often feel the need of the powerful memory leak detection tool similar to Valgrind on Windows environment also.

**WinValgrind** is a resource leak tracking tool which will offer complete detection of Handle leaks, GDI objects leak & Memory leaks, with a simple to use command line user interface.

**WinValgrind** takes inspiration from Valgrind and enables the user to track down memory issues without changing a single line of code.

[Download x86 Binaries](https://docs.google.com/file/d/0BwPKVN0q8_4_Si1YWnRZZEVNXzA/edit?usp=sharing)


# **How to build** #

**Before building the tool you need to have some prerequisite on your computer.**
  * Visual studio 2k10 to latest... ( I have built in vs 2k12).
  * Debugging tools for windows.
  * SVN client like tortoisesvn.


To build the tool from source, check out the source in some local directory.
Open WinValgrind.sln and hit build solution.. Now you are ready to go :)

In the output folder you will get:
  * WinValgrind.exe --> command line interface utility to inject the parasite into a process.
  * parasite.dll --> Spy DLL which hook the windows API's.

```
Enable logging for the tool by setting the value of "WINVAL_LOG" environment variable as 1.
```

# **How to use the tool** #


Note : Tool is currently at initial stage of development, therefore I have yet not decided whether to go with the GUI.

Tool is very simple to use, just follow the below steps to get started..

Execute winvalgrind.exe on windows command prompt to see all command line options.

```
usage: winvalgrind [-gc] | [-sm <PID>]

        -gc     Generate the config file template.
        -sm     start monitoring the process.
```

  * ### **First you need to generate the default config.xml template.** ###

  * --> Execute "winvalgrind.exe -gc"
    * ----> This command will generate the default config.xml file into the winvalgrind.exe directory.

```
*------------ Config.xml default template-------------------*

<?xml version="1.0"?>
<WinValgrind>
	<!-- Type of HOOK -->
	<MonitorType>HANDLE</MonitorType>
	<!-- PDB Path -->
	<PDBInfo>
		<!-- Do not remove PDB path 1 & 2 -->
		<PDBInfo1 path="C:\Users\win-valgrind\WinValgrind\Debug\" />
		<PDBInfo2 path="C:\Windows\system32" />
		<!-- microsoft symbol server -->
		<PDBInfo3 path="SRV*c:\Windows\Symbols*http://msdl.microsoft.com/download/symbols" />
		<!-- Add Monitored process symbol path -->
	</PDBInfo>
</WinValgrind>
```


  * --> Config.xml, serves as configuration file which will be read/loaded to set the initialisation parameters for parasite.dll.
```
--> MonitorType tag's value define type of tracing user want to enable.
-----> MEMORY : Memory leak detection.
-----> GDI : GDI object leak detection.
-----> HANDLE: Handle leak detection.

--> PDBInfo tags define the path to the symbol file.
----> 1st pdbinfo is the path to the directory of parasite.dll.
----> 2nd is the system DLL path.

Note: path 1 & 2 are compulsory, do not remove them.

----> 3rd is the Microsoft symbol server path, which is optional.
```

  * ### **Edit the generated config.xml.** ###

  * --> Set the monitor type.
```
"HANDLE", "MEMORY" or "GDI"
```
  * --> Add the symbol path of the application you want to monitor.


  * ### **Start the application you want to monitor.** ###
  * ### **Execute "winvalgrind.exe -sm <PID of the process to be monitored>".** ###

```
Once the monitoring starts you will see below internal command line which you can use to control the application.

--------------------------------------
Monitoring started for pid <PID>

Command options

-d  Dump the leak trace.
-c  Clear leaks.
-e  Exit.

> 

---------------------------------------

```

# **Internals of tool** #

Basically this application works by hooking all the windows API's which are used to allocate and de-allocate memory.

Now, after the hooking is complete, For each allocation of memory I save its stack in stl map with address keys.
Map entry for a address is only cleared if, respective de-allocation function is called on that address.

at-last, all the remaining entries in map are treated as leaked once, and there stack is dumped to file.

#### **Currently supported API hooks** ####
```
Handle allocation APIs			GDI object allocation APIs	Memory allocation APIs
----------------------      		--------------------------      ----------------------

LoadLibraryA				LoadBitmapA			HeapAlloc
LoadLibraryW				LoadBitmapW			HeapFree
LoadLibraryExA				LoadImageA			HeapReAlloc
LoadLibraryExW				LoadImageW			VirtualAlloc
GetProcAddress				CreateBitmap			VirtualFree
CreateEventA				CreateBitmapIndirect		VirtualAllocEx
CreateEventW				CreateCompatibleBitmap		VirtualFreeEx
CreateEventExA				CreateDIBitmap			GlobalAlloc
CreateEventExW				CreateDIBSection		GlobalReAlloc
OpenEventA				CreateDiscardableBitmap		GlobalFree
OpenEventW				CopyImage			LocalAlloc
CreateMutexA				GetIconInfo			LocalReAlloc
CreateMutexW				GetIconInfoExA			LocalFree
CreateMutexExA				GetIconInfoExA			MapViewOfFile
CreateMutexExW				DeleteObject			MapViewOfFileEx
OpenMutexA				CopyIcon			UnmapViewOfFile
OpenMutexW				CreateIcon			CoTaskMemAlloc
CreateSemaphoreA			CreateIconFromResource		CoTaskMemRealloc
CreateSemaphoreW			CreateIconFromResourceEx	CoTaskMemFree
CreateSemaphoreExA			CreateIconIndirect	
CreateSemaphoreExW			DestroyIcon	
OpenSemaphoreA				DuplicateIcon	
OpenSemaphoreW				ExtractAssociatedIconA	
CreateWaitableTimerA			ExtractAssociatedIconW	
CreateWaitableTimerW			ExtractAssociatedIconExA	
CreateWaitableTimerExA			ExtractAssociatedIconExW	
CreateWaitableTimerExW			ExtractIconA	
OpenWaitableTimerA			ExtractIconW	
OpenWaitableTimerW			ExtractIconExA	
CreateFileA				ExtractIconExW	
CreateFileW				LoadIconA	
CreateFileTransactedA			LoadIconW	
CreateFileTransactedW			PrivateExtractIconsA	
FindFirstFileA				PrivateExtractIconsW	
FindFirstFileW				CreateCursor	
FindFirstFileExA			LoadCursorA	
FindFirstFileExW			LoadCursorW	
FindFirstFileExW			LoadCursorFromFileA	
FindFirstFileNameW			LoadCursorFromFileW	
FindFirstFileTransactedA		DestroyCursor	
FindFirstFileTransactedW		CreateBrushIndirect	
FindFirstStreamTransactedW		CreateSolidBrush	
FindFirstStreamW			CreatePatternBrush	
FindClose				CreateDIBPatternBrush	
OpenFileById				CreateDIBPatternBrushPt	
ReOpenFile				CreateHatchBrush	
CreateIoCompletionPort			CreateCompatibleDC	
CreateRestrictedToken			CreateDCA	
DuplicateToken				CreateDCW	
DuplicateTokenEx			CreateICA	
OpenProcessToken			CreateICW	
OpenThreadToken				GetDC	
FindFirstChangeNotificationA		GetDCEx	
FindFirstChangeNotificationW		GetWindowDC	
FindCloseChangeNotification		ReleaseDC	
CreateMemoryResourceNotification	DeleteDC	
CreateFileMappingA			CreateFontA	
CreateFileMappingW			CreateFontW	
CreateFileMappingNumaA			CreateFontIndirectA	
CreateFileMappingNumaW			CreateFontIndirectW	
OpenFileMappingA			CreateMetaFileA	
OpenFileMappingW			CreateMetaFileW	
HeapCreate				CreateEnhMetaFileA	
HeapDestroy				CreateEnhMetaFileW	
GlobalAlloc				GetEnhMetaFileA	
GlobalReAlloc				GetEnhMetaFileW	
GlobalFree				GetMetaFileA	
LocalAlloc				GetMetaFileW	
LocalReAlloc				DeleteMetaFile	
LocalFree				DeleteEnhMetaFile	
CreateProcessA				CopyEnhMetaFileA	
CreateProcessW				CopyEnhMetaFileW	
CreateProcessAsUserA			CloseEnhMetaFile	
CreateProcessAsUserW			CloseMetaFile	
CreateProcessWithLogonW			CreatePen	
CreateProcessWithTokenW			CreatePenIndirect	
OpenProcess				ExtCreatePen	
CreateThread				PathToRegion	
CreateRemoteThread			CreateEllipticRgn	
OpenThread				CreateEllipticRgnIndirect	
CreateJobObjectA			CreatePolygonRgn	
CreateJobObjectW			CreatePolyPolygonRgn	
CreateMailslotA				CreateRectRgn	
CreateMailslotW				CreateRectRgnIndirect	
CreatePipe				CreateRoundRectRgn	
CreateNamedPipeA			ExtCreateRegion	
CreateNamedPipeW			CreateHalftonePalette	
RegCreateKeyExA				CreatePalette	
RegCreateKeyExW		
RegCreateKeyTransactedA		
RegCreateKeyTransactedW		
RegOpenCurrentUser		
RegOpenKeyA		
RegOpenKeyW		
RegOpenKeyExA		
RegOpenKeyExW		
RegOpenKeyTransactedA		
RegOpenKeyTransactedW		
RegOpenUserClassesRoot		
RegCreateKeyA		
RegCreateKeyW		
RegCloseKey		
DuplicateHandle		
CloseHandle		

```

# **What is coming up?** #
  * GUI
  * Overall performance improvements.

# **Contact me** #
Do you want to participate?
if yes, then contact me at anshulgoel27@gmail.com