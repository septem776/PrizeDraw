
// PrizeDraw.cpp : ����Ӧ�ó��������Ϊ��
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


// CPrizeDrawApp ����

CPrizeDrawApp::CPrizeDrawApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
	_staff.clear();
	_department.clear();
	_deptype.clear();
	_candidate.clear();
}


// Ψһ��һ�� CPrizeDrawApp ����

CPrizeDrawApp theApp;


// CPrizeDrawApp ��ʼ��

BOOL CPrizeDrawApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	//LoadFile("smvicNameList.csv");
	LoadFileBlood("namelist.csv");

	CPrizeDrawDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

int CPrizeDrawApp::LoadFile(char * filename)
{
	locale lang("chs");
	wifstream fin(filename);
	if(!fin)
	{
		AfxMessageBox(_T("�����ļ���ʧ�ܣ�"));
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
		AfxMessageBox(_T("�����ļ���ʧ�ܣ�"));
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