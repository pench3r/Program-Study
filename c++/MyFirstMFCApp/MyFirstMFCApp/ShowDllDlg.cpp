// ShowDllDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MyFirstMFCApp.h"
#include "ShowDllDlg.h"
#include "afxdialogex.h"
#include "psapi.h"
#include "tlhelp32.h"


// ShowDllDlg 对话框

IMPLEMENT_DYNAMIC(ShowDllDlg, CDialogEx)

ShowDllDlg::ShowDllDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

ShowDllDlg::~ShowDllDlg()
{
}

void ShowDllDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_dllList);
}


BEGIN_MESSAGE_MAP(ShowDllDlg, CDialogEx)
END_MESSAGE_MAP()


// ShowDllDlg 消息处理程序


BOOL ShowDllDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	// init dlllist columns
	LVCOLUMN m_dllListLvcol;
	m_dllListLvcol.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	m_dllListLvcol.fmt = LVCFMT_LEFT;
	m_dllListLvcol.cx = 75;
	m_dllListLvcol.pszText = L"Dll Name";
	m_dllList.InsertColumn(0, &m_dllListLvcol);

	m_dllListLvcol.pszText = L"Path";
	m_dllListLvcol.cx = 300;
	m_dllList.InsertColumn(1, &m_dllListLvcol);
	SetDlgItemText(IDC_STATIC, m_processName);

	ShowModuleFromToolhelp();
	// ShowDllViaEnumModules();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void ShowDllDlg::ShowModuleFromToolhelp() {
	HANDLE th32snapshoot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE32 | TH32CS_SNAPMODULE, m_processId);
	if (th32snapshoot == INVALID_HANDLE_VALUE) {
		CString errStr;
		errStr.Format(L"%d", GetLastError());
		AfxMessageBox(errStr);
		return;
	}
	MODULEENTRY32 moduleEntry32 = { 0 };
	moduleEntry32.dwSize = sizeof(MODULEENTRY32);
	BOOL res = Module32First(th32snapshoot, &moduleEntry32);
	int index = 0;
	while (res) {
		if (wcscmp(moduleEntry32.szModule, m_processName) == 0) {
			res = Module32Next(th32snapshoot, &moduleEntry32);
			continue;
		}
		m_dllList.InsertItem(index, moduleEntry32.szModule);
		m_dllList.SetItemText(index, 1, moduleEntry32.szExePath);
		index++;
		res = Module32Next(th32snapshoot, &moduleEntry32);
	}
	CloseHandle(th32snapshoot);
}

// 实现后的功能对于某些进程打开是错误299 ERROR_PARTIAL_COPY; 后续再尝试解决
// 299产生的原因：系统为64位，而生成的程序为32位，重新配置生成64位即可正常运行
void ShowDllDlg::ShowModuleFromEnumModules() {
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, m_processId);
	if (NULL == hProcess) {
		return;
	}
	HMODULE hMods[1024];
	DWORD needBytes;
	TCHAR szModName[MAX_PATH];
	if (EnumProcessModulesEx(hProcess, hMods, sizeof(hMods), &needBytes, LIST_MODULES_ALL)) {
		for (unsigned int modIndex = 0; modIndex < (needBytes / sizeof(HMODULE)); ++modIndex) {
			if (GetModuleBaseName(hProcess, hMods[modIndex], szModName, sizeof(szModName) / sizeof(TCHAR))) {
				if (wcscmp(szModName, m_processName) == 0) {
					continue;
				}
				m_dllList.InsertItem(modIndex, szModName);
			}

			if (GetModuleFileNameEx(hProcess, hMods[modIndex], szModName, sizeof(szModName) / sizeof(TCHAR))) {
				m_dllList.SetItemText(modIndex, 1, szModName);
			}
		}
	} else {
		CString errStr;
		errStr.Format(L"%d", GetLastError());
		AfxMessageBox(errStr);
	}
	CloseHandle(hProcess);
}