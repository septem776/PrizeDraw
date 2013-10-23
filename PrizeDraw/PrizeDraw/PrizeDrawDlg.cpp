
// PrizeDrawDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PrizeDraw.h"
#include "PrizeDrawDlg.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CPrizeDrawDlg 对话框




CPrizeDrawDlg::CPrizeDrawDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPrizeDrawDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPrizeDrawDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DEP, _name);
	DDX_Control(pDX, IDC_COMBO_TYPE, _deptype);
	DDX_Control(pDX, IDC_EDIT_NUM, _edit_num);
	DDX_Control(pDX, IDC_LIST_RESULT, _list_result);
}

BEGIN_MESSAGE_MAP(CPrizeDrawDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_CBN_SETFOCUS(IDC_COMBO_DEP, &CPrizeDrawDlg::OnCbnSetfocusComboDep)
	ON_CBN_SELCHANGE(IDC_COMBO_DEP, &CPrizeDrawDlg::OnCbnSelchangeComboDep)
	ON_CBN_SETFOCUS(IDC_COMBO_TYPE, &CPrizeDrawDlg::OnCbnSetfocusComboType)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, &CPrizeDrawDlg::OnCbnSelchangeComboType)

	ON_BN_CLICKED(IDC_BUTTON_GO, &CPrizeDrawDlg::OnBnClickedButtonGo)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CPrizeDrawDlg::OnBnClickedButtonReset)
END_MESSAGE_MAP()


// CPrizeDrawDlg 消息处理程序

BOOL CPrizeDrawDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	AddData();
	_chosen_dep = _chosen_deptype = L"全部";
	srand((int)time(0));
	int seed = rand();
	srand(seed);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPrizeDrawDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPrizeDrawDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPrizeDrawDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPrizeDrawDlg::OnCbnSetfocusComboDep()
{
	// TODO: Add your control notification handler code here
	CPrizeDrawApp *p = (CPrizeDrawApp*)AfxGetApp();
	_name.ResetContent();
	if(_chosen_deptype == L"全部")
	{
		_name.AddString(_T("全部"));
		map<wstring, wstring>::iterator it2 = p->_department.begin();
		for( ; it2 != p->_department.end(); ++it2)
		{
			LPCTSTR addline = (*it2).first.c_str();
			_name.AddString(addline);
		}
		return;
	}

	_name.AddString(_T("全部"));
	map<wstring, wstring>::iterator it = p->_department.begin();
	for( ; it != p->_department.end(); ++it)
	{
		if(it->second.c_str() == _chosen_deptype)
		{
			LPCTSTR addline = it->first.c_str();
			_name.AddString(addline);
		}
	}
}

void CPrizeDrawDlg::OnCbnSelchangeComboDep()
{
	// TODO: Add your control notification handler code here
	CString text;
	_name.GetLBText(_name.GetCurSel(), text);
	//AfxMessageBox(text);
	_chosen_dep = text;
	CopyData();
}

void CPrizeDrawDlg::OnCbnSetfocusComboType()
{
	// TODO: Add your control notification handler code here
}

void CPrizeDrawDlg::AddData()
{
	_deptype.ResetContent();
	_name.ResetContent();
	CPrizeDrawApp *p = (CPrizeDrawApp*)AfxGetApp();
	_deptype.AddString(_T("全部"));
	set<wstring>::iterator it = p->_deptype.begin();
	for( ; it != p->_deptype.end(); ++it)
	{
		LPCTSTR addline = (*it).c_str();
		_deptype.AddString(addline);
	}
	_name.AddString(_T("全部"));
	map<wstring, wstring>::iterator it2 = p->_department.begin();
	for( ; it2 != p->_department.end(); ++it2)
	{
		LPCTSTR addline = (*it2).first.c_str();
		_name.AddString(addline);
	}

}
void CPrizeDrawDlg::OnCbnSelchangeComboType()
{
	// TODO: Add your control notification handler code here
	CString text;
	_deptype.GetLBText(_deptype.GetCurSel(), text);
	_chosen_deptype = text;
	CopyData();
}

void CPrizeDrawDlg::OnBnClickedButtonGo()
{
	// TODO: 在此添加控件通知处理程序代码
	CPrizeDrawApp *p = (CPrizeDrawApp*)AfxGetApp();
	_list_result.ResetContent();
	int candidate_num = p->_candidate.size();
	if(candidate_num <= 0)
	{
		AfxMessageBox(_T("没人了哟"));
		return;
	}
	CString temp;
	_edit_num.GetWindowText(temp);
	int num = _ttoi(temp);
	if(num > 50)
	{
		AfxMessageBox(_T("人太多哟"));
		return;
	}
	while(num--)
	{
		int win = p->roll(candidate_num);
		CString text = p->_candidate[win].ch_name.c_str();
		text += " ";
		text += p->_candidate[win].obj_no.c_str();
		text += " ";
		text += p->_candidate[win].dep.c_str();
		_list_result.AddString(text);
		p->_candidate.erase(p->_candidate.begin()+win);
		candidate_num = p->_candidate.size();
		
		if(candidate_num < 1)
			break;
	}
}

void CPrizeDrawDlg::CopyData()
{
	CPrizeDrawApp *p = (CPrizeDrawApp*)AfxGetApp();
	p->_candidate.clear();
	vector<Staff>::iterator it = p->_staff.begin();
	for(; it != p->_staff.end(); ++it)
	{
		if((it->dep == _chosen_dep || _chosen_dep == L"全部") && (it->dep_type == _chosen_deptype || _chosen_deptype == L"全部"))
			p->_candidate.push_back(*it);
	}
}

void CPrizeDrawDlg::OnBnClickedButtonReset()
{
	// TODO: 在此添加控件通知处理程序代码
	CopyData();
}

void CPrizeDrawDlg::OnOK()
{
	// do nothing, for don't close dialog when hit Enter
}

BOOL CPrizeDrawDlg::PreTranslateMessage(MSG* pMsg)
{
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_NUM);
	if(pMsg->message == WM_KEYDOWN && pEdit->GetSafeHwnd() == pMsg->hwnd)
	{
		if((pMsg->wParam < _T('0') || pMsg->wParam > _T('9'))
			&& pMsg->wParam != VK_DELETE && pMsg->wParam != VK_BACK
			&& pMsg->wParam != VK_LEFT && pMsg->wParam != VK_RIGHT
			&& pMsg->wParam != VK_UP && pMsg->wParam != VK_DOWN
			&& (pMsg->wParam < VK_NUMPAD0 || pMsg->wParam > VK_NUMPAD9))
			return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}
