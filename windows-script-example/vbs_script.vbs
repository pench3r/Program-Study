'-----WScript.Shell------
CreateObject("WScript.Shell").Run("calc")	'1

set WshShell = WScript.CreateObject("WScript.Shell")

WshShell.Run "calc.exe"	'2

WshShell.exec("calc.exe") '3

'-----Shell.Application------
set objShellApp = CreateObject("Shell.Application")
set objFolder = objShellApp.NameSpace("C:\windows\system32\")

objFolder.Items().item("calc.exe").invokeverb	'4
objFolder.Items.item("calc.exe").invokeverbEx   '5

objShellApp.Open("C:\windows\system32\calc.exe")	'6

objShellApp.ShellExecute "calc.exe","","C:\windows\system32\","","1"	'7

set objFolderItem = objShellApp.NameSpace("C:\windows\system32").Items().item("calc.exe")
set objFIVs = objFolderItem.Verbs()

'-----MMC20.Application------
set oHttp = CreateObject("MMC20.Application")
a = oHttp.Document.ActiveView.ExecuteShellCommand("calc.exe","d:\", "", "Minimized") '8

'-----ShellWindows------
'由于没有对应的progid所以无法通过createobject来调用，只能直接调用classid调用

'<Job ID="myjob">
'<object id="ShellWindows" classiD="clsiD:9BA05972-F6A8-11CF-A442-00A0C90A8F39"/>
'<script language="VBScript">
'set obj =ShellWindows.item()
'obj.Document.Application.ShellExecute "cmd.exe","/c calc.exe","c:\windows\system32","",0
'</script>
'</Job>

'-----DDEInitiate & RegisterXL------
set obj = CreateObject("Excel.Application")
obj.DisplayAlerts = false
obj.DDEInitiate "cmd", "/c calc.exe"	'9

