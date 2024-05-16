// GetPixelDlg.cpp: 实现文件
//

#include "imageProcessing.h"
#include "afxdialogex.h"
#include "GetPixelDlg.h"


// GetPixelDlg 对话框

IMPLEMENT_DYNAMIC(GetPixelDlg, CDialogEx)

GetPixelDlg::GetPixelDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(GET_PIXEL_DLG, pParent)
	, m_nX(0)
	, m_nY(0)
{

}

GetPixelDlg::~GetPixelDlg()
{
}

void GetPixelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, PixelX, m_nX);	//DDX（Dialog Data Exchange）
	DDX_Text(pDX, PixelY, m_nY);
	//DDV_MinMaxInt(pDX, m_nX, 0, INT_MAX); // 可选：添加验证，确保输入在有效范围内
	// DDV_MinMaxInt(pDX, m_nY, 0, INT_MAX); // 可选：添加验证，确保输入在有效范围内
}


BEGIN_MESSAGE_MAP(GetPixelDlg, CDialogEx)
END_MESSAGE_MAP()


