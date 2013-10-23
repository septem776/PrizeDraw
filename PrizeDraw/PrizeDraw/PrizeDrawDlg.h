
// PrizeDrawDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CPrizeDrawDlg 对话框
class CPrizeDrawDlg : public CDialog
{
// 构造
public:
	CPrizeDrawDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PRIZEDRAW_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox _name;
	afx_msg void OnCbnSetfocusComboDep();
	afx_msg void OnCbnSelchangeComboDep();
	CComboBox _deptype;
	afx_msg void OnCbnSetfocusComboType();
	void AddData();

private:
	wstring _chosen_deptype;
	wstring _chosen_dep;
	int _chosen_num;

public:
	afx_msg void OnCbnSelchangeComboType();
	CEdit _edit_num;
	afx_msg void OnBnClickedButtonGo();
	void CopyData();
	CListBox _list_result;
	afx_msg void OnBnClickedButtonReset();
	void OnOK();
	BOOL PreTranslateMessage(MSG* pMsg);
};
