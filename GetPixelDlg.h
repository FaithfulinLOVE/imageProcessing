#pragma once
#include "afxdialogex.h"


// GetPixelDlg 对话框

class GetPixelDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GetPixelDlg)

public:
	GetPixelDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~GetPixelDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = GET_PIXEL_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持


	DECLARE_MESSAGE_MAP()


public:
	int m_nX;
	int m_nY;
};
