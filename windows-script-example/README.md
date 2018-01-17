windows script example in penetration
----

#### 1.	powershell ####

	powershell -executionpolicy bypass ./powershell_script.ps1

#### 2. VBS ####

默认可以直接在机器上运行，命令行下可以通过`cscript.exe`执行

	cscript.exe vbs_script.vbs
	vbs_script.vbs

#### 3. csc(.cs c#) ####

首先通过`csc.exe`进行编译c#为`exe`，然后通过`InstallUtil.exe`进行程序执行

	C:\Windows\Microsoft.NET\Framework64\v4.0.30319\csc.exe /unsafe /out:PEL.exe InstallUtilBypass.cs

	InstallUtil.exe /logfile= /LogToConsole=false /U PEL.exe