// BilateralfilterDlg.cpp: 实现文件
//

#include "imageProcessing.h"
#include "afxdialogex.h"
#include "BilateralfilterDlg.h"


// BilateralfilterDlg 对话框

IMPLEMENT_DYNAMIC(BilateralfilterDlg, CDialogEx)

BilateralfilterDlg::BilateralfilterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, sigma_d(0)
	, sigma_R(0)
{

}

BilateralfilterDlg::~BilateralfilterDlg()
{
}

void BilateralfilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, sigma_d);
	DDX_Text(pDX, IDC_EDIT2, sigma_R);
}


BEGIN_MESSAGE_MAP(BilateralfilterDlg, CDialogEx)
END_MESSAGE_MAP()


// BilateralfilterDlg 消息处理程序


