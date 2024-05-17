#pragma once
#include "afxdialogex.h"


// InterpolDlg 对话框

class InterpolDlg : public CDialogEx
{
	DECLARE_DYNAMIC(InterpolDlg)

public:
	InterpolDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~InterpolDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = INTERPOL_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int width;
	int height;
	BOOL nearest;
	BOOL double_linear;

	//初始化
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedLinear();
	afx_msg void OnBnClickedNearest();
};
