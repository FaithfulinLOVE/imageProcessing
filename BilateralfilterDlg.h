#pragma once
#include "afxdialogex.h"


// BilateralfilterDlg 对话框

class BilateralfilterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(BilateralfilterDlg)

public:
	BilateralfilterDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~BilateralfilterDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double sigma_d;
	double sigma_R;
};
