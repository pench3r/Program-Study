
// MyFirstMFCAppDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MyFirstMFCApp.h"
#include "MyFirstMFCAppDlg.h"
#include "afxdialogex.h"
#include "psapi.h"
#include "tlhelp32.h"  /* toolhelp系列函数 */
#include "ShowDllDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyFirstMFCAppDlg 对话框



CMyFirstMFCAppDlg::CMyFirstMFCAppDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYFIRSTMFCAPP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyFirstMFCAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST3, m_ProcessList);
}

BEGIN_MESSAGE_MAP(CMyFirstMFCAppDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST3, &CMyFirstMFCAppDlg::OnLvnItemchangedList3)
	ON_BN_CLICKED(IDOK, &CMyFirstMFCAppDlg::OnBnClickedOk)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_POPUP_DISPLAYDLL, &CMyFirstMFCAppDlg::OnPopupDisplaydll)
	ON_WM_SIZE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMyFirstMFCAppDlg 消息处理程序

BOOL CMyFirstMFCAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	// 保存相关的窗体相关的大小信息用于控件大小的缩放
	CRect mainRect;
	GetWindowRect(&mainRect);
	CRect buttonRect;
	GetDlgItem(IDOK)->GetWindowRect(&buttonRect);
	// 移动父窗口和子窗口都需要转化为窗口坐标
	ScreenToClient(&buttonRect);
	ScreenToClient(&mainRect);

	// 保存button控件到dlg边界的差值
	m_buttonRight2DlgDistance = mainRect.right - buttonRect.right;
	m_buttonBottom2DlgDistance = mainRect.bottom - buttonRect.bottom;

	CRect listRect;
	GetDlgItem(IDC_LIST3)->GetWindowRect(&listRect);
	ScreenToClient(&listRect);
	m_listBottom2DlgDistance = mainRect.bottom - listRect.bottom;
	m_listRight2DlgDistance = mainRect.right - listRect.right;

	CRect staticRect;
	ScreenToClient(&staticRect);
	GetDlgItem(IDC_STATIC)->GetWindowRect(&staticRect);
	m_staticTop2DlgDistance = mainRect.bottom - staticRect.bottom + 20;

	m_buttonSizeStoreFlag = TRUE;

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	// 开启list的内部双缓冲
	m_ProcessList.SetExtendedStyle(m_ProcessList.GetExtendedStyle() | LVS_EX_DOUBLEBUFFER);
	// init list columns
	LVCOLUMN m_ProcessListLvcol;
	m_ProcessListLvcol.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	m_ProcessListLvcol.fmt = LVCFMT_LEFT;
	m_ProcessListLvcol.cx = 240;
	m_ProcessListLvcol.pszText = L"Process Name";
	m_ProcessList.InsertColumn(0, &m_ProcessListLvcol);

	m_ProcessListLvcol.cx = 75;
	m_ProcessListLvcol.pszText = L"PID";
	m_ProcessList.InsertColumn(1, &m_ProcessListLvcol);

	m_ProcessListLvcol.cx = 240;
	m_ProcessListLvcol.pszText = L"Process Image Path";
	m_ProcessList.InsertColumn(2, &m_ProcessListLvcol);

	ShowProcessFromToolHelp();

	GetDlgItem(IDC_STATIC)->SetWindowTextW(L"hello world");
	// 使用EnumProcesss和GetProcessImageFileName遍历获取进程信息
	// ShowProcessFromEnumProcess();
	// ShowProcessFromNtQuerySystemInfo();

	// 设置定时器每一秒获取一次进程的列表信息
	SetTimer(123, 1000, NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMyFirstMFCAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMyFirstMFCAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMyFirstMFCAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyFirstMFCAppDlg::OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CMyFirstMFCAppDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CRect currentWinRect;
	GetDlgItem(IDC_STATIC)->GetWindowRect(&currentWinRect);
	ScreenToClient(&currentWinRect);
	CString rectStr;
	rectStr.Format(L"left: %d, top: %d, right: %d, bottom: %d", currentWinRect.left, currentWinRect.top,
		currentWinRect.right, currentWinRect.bottom);
	SetDlgItemText(IDC_STATIC, rectStr);

	// CDialogEx::OnOK();
}



// 使用ToolHelp系列函数获取进程pid、exename等信息
void CMyFirstMFCAppDlg::ShowProcessFromToolHelp()
{
	PROCESSENTRY32 processEntry32 = { 0 };
	processEntry32.dwSize = sizeof(PROCESSENTRY32);  // 关键需要设置process结构体的大小
	DWORD processId;
	HANDLE th32Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);	// all process snapprocess
	if (th32Snapshot == INVALID_HANDLE_VALUE) {
		return;
	}
	Process32First(th32Snapshot, &processEntry32);
	DWORD itemIndex = 0;
	HMODULE hMods[1024] = { 0 };
	DWORD needBytes;
	CString numStr;
	TCHAR fullPathName[MAX_PATH] = L"not found!";
	// 清空列表的内容重新更新
	m_ProcessList.DeleteAllItems();
	do {
		processId = processEntry32.th32ProcessID;
		numStr.Format(L"%d", processId);
		HANDLE processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId);
		if (processHandle == NULL) {
			continue;
		}
		m_ProcessList.InsertItem(itemIndex, processEntry32.szExeFile);
		m_ProcessList.SetItemText(itemIndex, 1, numStr);
		if (EnumProcessModules(processHandle, hMods, sizeof(hMods), &needBytes)) {
			if (GetModuleFileNameEx(processHandle, hMods[0], fullPathName, sizeof(fullPathName))) {
				m_ProcessList.SetItemText(itemIndex, 2, fullPathName);
			}
		}
		CloseHandle(processHandle);
		itemIndex++;
	} while (Process32Next(th32Snapshot, &processEntry32));


	CloseHandle(th32Snapshot);
}

// 使用EnumProcesss和GetProcessImageFileName遍历获取进程信息
void CMyFirstMFCAppDlg::ShowProcessFromEnumProcess()
{
	DWORD m_processArray[1024], recvProcessNum, recvProcessBytes, processId, res;
	if (!EnumProcesses(m_processArray, sizeof(m_processArray), &recvProcessBytes)) {
		return;
	}
	recvProcessNum = recvProcessBytes / sizeof(DWORD);

	TCHAR sProcessName[MAX_PATH];
	CString tmpStr;

	for (DWORD proc_index = 0; proc_index < recvProcessNum; proc_index++) {
		processId = m_processArray[proc_index];
		// get pid
		tmpStr.Format(L"%d", processId);

		if (processId == 0) {
			m_ProcessList.InsertItem(proc_index, L"System Idle Process");
			m_ProcessList.SetItemText(proc_index, 1, tmpStr);
			continue;
		}
		if (processId == 4) {
			m_ProcessList.InsertItem(proc_index, L"System");
			m_ProcessList.SetItemText(proc_index, 1, tmpStr);
			continue;
		}

		// get process name and process full name
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
			FALSE, processId);
		if (hProcess != NULL) {
			res = GetProcessImageFileName(hProcess, sProcessName, sizeof(sProcessName));
			if (res == NULL) {
				break;
			}
		}
		m_ProcessList.InsertItem(proc_index, sProcessName);
		m_ProcessList.SetItemText(proc_index, 1, tmpStr);
	}
}

// 使用NtQuerySystemInformation来获取进程信息
void CMyFirstMFCAppDlg::ShowProcessFromNtQuerySystemInfo()
{

	HMODULE hDllModule = LoadLibrary(L"Ntdll.dll");
	NtQueryFunc NtQuerySystemInformation = (NtQueryFunc)GetProcAddress(hDllModule, "NtQuerySystemInformation");
	ULONG needBytes = 0;
	int res = NtQuerySystemInformation(SystemProcessesAndThreadsInformation, NULL, 0, &needBytes);
	BYTE *pSystemInfoBuf = new BYTE[needBytes];
	NtQuerySystemInformation(SystemProcessesAndThreadsInformation,(PVOID)pSystemInfoBuf, needBytes, NULL);
	PSYSTEM_PROCESS_INFORMATION pSystemInfo = (PSYSTEM_PROCESS_INFORMATION)pSystemInfoBuf;
	CString numStr;
	DWORD itemIndex = 0;
	do {
		numStr.Format(L"%d", pSystemInfo->ProcessId);
		m_ProcessList.InsertItem(itemIndex, pSystemInfo->ProcessName.Buffer);
		m_ProcessList.SetItemText(itemIndex, 1, numStr);
		itemIndex++;
		pSystemInfo = (PSYSTEM_PROCESS_INFORMATION)((size_t)pSystemInfo + pSystemInfo->NextEntryDelta);
	} while (pSystemInfo->NextEntryDelta != 0);
	numStr.Format(L"Total Process Num: %d.", itemIndex);
	SetDlgItemText(IDC_STATIC, numStr);
}

void CMyFirstMFCAppDlg::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	// TODO: 在此处添加消息处理程序代码
	// 获取list中选中的内容
	int selectedMark = m_ProcessList.GetSelectionMark();
	CString selectedItemData = m_ProcessList.GetItemText(selectedMark, 0);
	SetDlgItemText(IDC_STATIC, selectedItemData);
	m_selectListItem = selectedItemData;
	selectedItemData = m_ProcessList.GetItemText(selectedMark, 1);
	m_selectListPid = _wtoi(selectedItemData);

	// Load The desired menu
	CMenu listItemPopMenu;
	VERIFY(listItemPopMenu.LoadMenuW(IDR_MENU1));

	CRect currentRect;
	GetDlgItem(IDC_LIST3)->GetWindowRect(&currentRect);

	CMenu *pPopMenu = listItemPopMenu.GetSubMenu(0);
	ASSERT(pPopMenu != NULL);

	if (currentRect.PtInRect(point) && selectedMark != -1) {
		pPopMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
}


void CMyFirstMFCAppDlg::OnPopupDisplaydll()
{
	// TODO: 在此添加命令处理程序代码
	ShowDllDlg sDllDlg;
	sDllDlg.m_processName = m_selectListItem;
	sDllDlg.m_processId = m_selectListPid;
	size_t resFlag = sDllDlg.DoModal();
	if (IDCANCEL == resFlag) {
		return;
	}
}

void CMyFirstMFCAppDlg::AutoSize(int nId, int cx, int cy) {
	// 获取指定控件的rect
	CRect currentRect;
	GetDlgItem(nId)->GetWindowRect(&currentRect);
	ScreenToClient(&currentRect);
	// 获取主窗体的rect
	CRect mainRect;
	GetWindowRect(&mainRect);
	ScreenToClient(&mainRect);

	// 更新控件rect的right和bottom的值
	long nWidth = currentRect.right - currentRect.left;
	long nHeight = currentRect.bottom - currentRect.top;


	currentRect.bottom = mainRect.bottom - cy;
	if (nId == IDC_STATIC) {
		currentRect.top = currentRect.bottom - nHeight;
		GetDlgItem(nId)->MoveWindow(&currentRect, TRUE);
		return;
	}
	
	currentRect.right = mainRect.right - cx;

	if (nId == IDOK) {
		currentRect.left = currentRect.right - nWidth;
		currentRect.top = currentRect.bottom - nHeight;
	}

	// 更新控件的rect
	GetDlgItem(nId)->MoveWindow(&currentRect, TRUE);
}



void CMyFirstMFCAppDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (m_buttonSizeStoreFlag) {
		AutoSize(IDOK, m_buttonRight2DlgDistance, m_buttonBottom2DlgDistance);
		AutoSize(IDC_LIST3, m_listRight2DlgDistance, m_listBottom2DlgDistance);
		AutoSize(IDC_STATIC, 0, m_staticTop2DlgDistance);
	}
}

void CMyFirstMFCAppDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent) {
		case 123:
			ShowProcessFromToolHelp();
			break;
		default:
			break;
	}
	CDialogEx::OnTimer(nIDEvent);
}
