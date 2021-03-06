#pragma once


// ShowDllDlg 对话框

class ShowDllDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ShowDllDlg)

public:
	ShowDllDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ShowDllDlg();
	CString m_processName;
	void ShowModuleFromEnumModules();	// 使用enumprocessmodules来实现
	void ShowModuleFromToolhelp();		// 使用toolhelp系列函数来实现
	DWORD m_processId;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_dllList;
};
