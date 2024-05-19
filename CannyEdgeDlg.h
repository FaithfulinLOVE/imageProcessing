#pragma once
#include "afxdialogex.h"


// CannyEdgeDlg 对话框

class CannyEdgeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CannyEdgeDlg)

public:
	CannyEdgeDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CannyEdgeDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = CANNY_EDGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeTh1();
	double th1;
	double th2;
};
