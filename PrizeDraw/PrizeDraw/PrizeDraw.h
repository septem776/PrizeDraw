
// PrizeDraw.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <set>
using namespace std;


// CPrizeDrawApp:
// �йش����ʵ�֣������ PrizeDraw.cpp
//

struct Staff 
{
	wstring no;
	wstring e_name;
	wstring obj_no;
	wstring ch_name;
	wstring dep;
	wstring dep_type;
};

class CPrizeDrawApp : public CWinAppEx
{
public:
	CPrizeDrawApp();
	int LoadFile(char * filename);
	int roll(int total);

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()

public:
	vector<Staff> _staff;
	map<wstring, wstring> _department;
	set<wstring> _deptype;
	vector<Staff> _candidate;


};

extern CPrizeDrawApp theApp;