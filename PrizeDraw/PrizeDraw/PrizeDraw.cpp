
// PrizeDraw.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "PrizeDraw.h"
#include "PrizeDrawDlg.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPrizeDrawApp

BEGIN_MESSAGE_MAP(CPrizeDrawApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CPrizeDrawApp 构造

CPrizeDrawApp::CPrizeDrawApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
	_staff.clear();
	_department.clear();
	_deptype.clear();
	_candidate.clear();
}


// 唯一的一个 CPrizeDrawApp 对象

CPrizeDrawApp theApp;


// CPrizeDrawApp 初始化

BOOL CPrizeDrawApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	//LoadFile("smvicNameList.csv");
	LoadFileBlood("namelist.csv");

	CPrizeDrawDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

int CPrizeDrawApp::LoadFile(char * filename)
{
	locale lang("chs");
	wifstream fin(filename);
	if(!fin)
	{
		AfxMessageBox(_T("数据文件打开失败！"));
		return -1;
	}
	wstring line;
	fin.imbue(lang);
	while(getline(fin, line))
	{
		Staff onestaff;
		int index1 = 0;
		int index2 = line.find(',');
		if(index2 > index1)
			onestaff.no = line.substr(index1, index2-index1);
		index1 = index2+1;
		index2 = line.find(',', index1);
		if(index2 > index1)
			onestaff.e_name = line.substr(index1, index2-index1);
		index1 = index2+1;
		index2 = line.find(',', index1);
		if(index2 > index1)
			onestaff.obj_no = line.substr(index1, index2-index1);
		index1 = index2+1;
		index2 = line.find(',', index1);
		if(index2 > index1)
			onestaff.ch_name = line.substr(index1, index2-index1);
		index1 = index2+1;
		index2 = line.find(',', index1);
		if(index2 > index1)
			onestaff.dep = line.substr(index1, index2-index1);
		index1 = index2+1;
		onestaff.dep_type = line.substr(index1);
		_staff.push_back(onestaff);
		if(_department.find(onestaff.dep) == _department.end())
		{
			_department.insert(make_pair(onestaff.dep, onestaff.dep_type));
		}
		if(_deptype.find(onestaff.dep_type) == _deptype.end())
			_deptype.insert(onestaff.dep_type);
	}
	fin.close();
	return 0;
}

int CPrizeDrawApp::LoadFileBlood(char * filename)
{
	locale lang("chs");
	wifstream fin(filename);
	if(!fin)
	{
		AfxMessageBox(_T("数据文件打开失败！"));
		return -1;
	}
	wstring line;
	fin.imbue(lang);
	int staffid = 0;
	while(getline(fin, line))
	{
		wstring flag;
		int index1 = line.find(',');
		int index2 = line.find(',', index1+1);
		int index3 = line.find(',', index2+1);

		wstring deptype = line.substr(index1+1, index2-index1-1);
		wstring dep = line.substr(index2+1, index3-index2-1);
		if(_department.find(dep) == _department.end())
		{
			_department.insert(make_pair(dep, deptype));
		}
		if(_deptype.find(deptype) == _deptype.end())
			_deptype.insert(deptype);

		int indexlast = line.rfind(',');
		if(indexlast > 0)
		{
			flag = line.substr(indexlast+1);
		}
		if(_wtoi(flag.c_str()) == 1)
			continue;

		line = line.substr(0, indexlast);
		staffid++;
		_mapId2Info.insert((make_pair(staffid, line)));
		StaffBlood sb;
		sb.id = staffid;
		sb.dep = dep;
		sb.dep_type = deptype;
		_vecIdDep.push_back(sb);
	}
	fin.close();
	return 0;
}

int CPrizeDrawApp::roll(int total)
{
	return rand() % total;
}