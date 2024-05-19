// SharpenDlg.cpp: 实现文件
//

#include "imageProcessing.h"
#include "afxdialogex.h"
#include "SharpenDlg.h"


// SharpenDlg 对话框

IMPLEMENT_DYNAMIC(SharpenDlg, CDialogEx)

SharpenDlg::SharpenDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(SHARPEN_DLG, pParent)
	, k1(0)
	, k2(0)
{

}

SharpenDlg::~SharpenDlg()
{
}

void SharpenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, SHARPEN_K1, k1);
	DDX_Text(pDX, SHARPEN_K2, k2);
}


BEGIN_MESSAGE_MAP(SharpenDlg, CDialogEx)
END_MESSAGE_MAP()


// SharpenDlg 消息处理程序
