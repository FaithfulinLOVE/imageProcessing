// GaussianFilterDlg.cpp: 实现文件
//

#include "imageProcessing.h"
#include "afxdialogex.h"
#include "GaussianFilterDlg.h"


// GaussianFilterDlg 对话框

IMPLEMENT_DYNAMIC(GaussianFilterDlg, CDialogEx)

GaussianFilterDlg::GaussianFilterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(GAUSS_FIL_DLG, pParent)
	, sigma(0)
{

}

GaussianFilterDlg::~GaussianFilterDlg()
{
}

void GaussianFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, GUASSFIL_SIGMA, sigma);
}


BEGIN_MESSAGE_MAP(GaussianFilterDlg, CDialogEx)
END_MESSAGE_MAP()


// GaussianFilterDlg 消息处理程序


