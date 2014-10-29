
// PrizeDraw.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <set>
using namespace std;


// CPrizeDrawApp:
// 有关此类的实现，请参阅 PrizeDraw.cpp
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

struct StaffBlood
{
	int id;
	wstring dep;
	wstring dep_type;
};

class CPrizeDrawApp : public CWinAppEx
{
public:
	CPrizeDrawApp();
	int LoadFile(char * filename);
	int LoadFileBlood(char * filename);
	int roll(int total);

// 重写
	public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()

public:
	vector<Staff> _staff;
	map<wstring, wstring> _department;
	set<wstring> _deptype;
	vector<Staff> _candidate;

	map<int, wstring> _mapId2Info;
	vector<StaffBlood> _vecIdDep;
	vector<int> _toRoll;
};

extern CPrizeDrawApp theApp;