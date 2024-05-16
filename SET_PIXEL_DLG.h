#pragma once
#include "afxdialogex.h"


// SET_PIXEL_DLG 对话框

class SET_PIXEL_DLG : public CDialogEx
{
	DECLARE_DYNAMIC(SET_PIXEL_DLG)

public:
	SET_PIXEL_DLG(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~SET_PIXEL_DLG();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int set_X;
	int set_Y;
	int set_Res;
	int set_R;
	int set_G;
	int set_B;
};
