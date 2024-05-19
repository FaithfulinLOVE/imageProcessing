#pragma once
#include "afxdialogex.h"


// SharpenDlg 对话框

class SharpenDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SharpenDlg)

public:
	SharpenDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~SharpenDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = SHARPEN_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double k1;
	double k2;
};
