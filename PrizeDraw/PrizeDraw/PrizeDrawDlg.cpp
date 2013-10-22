
// PrizeDrawDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PrizeDraw.h"
#include "PrizeDrawDlg.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CPrizeDrawDlg �Ի���




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


// CPrizeDrawDlg ��Ϣ�������

BOOL CPrizeDrawDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	AddData();
	_chosen_dep = _chosen_deptype = L"ȫ��";
	srand((int)time(0));
	int seed = rand();
	srand(seed);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPrizeDrawDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPrizeDrawDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPrizeDrawDlg::OnCbnSetfocusComboDep()
{
	// TODO: Add your control notification handler code here
	CPrizeDrawApp *p = (CPrizeDrawApp*)AfxGetApp();
	_name.ResetContent();
	if(_chosen_deptype == L"ȫ��")
	{
		_name.AddString(_T("ȫ��"));
		map<wstring, wstring>::iterator it2 = p->_department.begin();
		for( ; it2 != p->_department.end(); ++it2)
		{
			LPCTSTR addline = (*it2).first.c_str();
			_name.AddString(addline);
		}
		return;
	}

	_name.AddString(_T("ȫ��"));
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
	_deptype.AddString(_T("ȫ��"));
	set<wstring>::iterator it = p->_deptype.begin();
	for( ; it != p->_deptype.end(); ++it)
	{
		LPCTSTR addline = (*it).c_str();
		_deptype.AddString(addline);
	}
	_name.AddString(_T("ȫ��"));
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPrizeDrawApp *p = (CPrizeDrawApp*)AfxGetApp();
	_list_result.ResetContent();
	int candidate_num = p->_candidate.size();
	if(candidate_num <= 0)
	{
		AfxMessageBox(_T("nobody"));
		return;
	}
	CString temp;
	_edit_num.GetWindowText(temp);
	int num = _ttoi(temp);
	if(num < 1 || num > 30)
	{
		AfxMessageBox(_T("too many people"));
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
		if((it->dep == _chosen_dep || _chosen_dep == L"ȫ��") && (it->dep_type == _chosen_deptype || _chosen_deptype == L"ȫ��"))
			p->_candidate.push_back(*it);
	}
}

void CPrizeDrawDlg::OnBnClickedButtonReset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CopyData();
}
