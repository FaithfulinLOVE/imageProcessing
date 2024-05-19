// CannyEdgeDlg.cpp: 实现文件
//

#include "imageProcessing.h"
#include "afxdialogex.h"
#include "CannyEdgeDlg.h"


// CannyEdgeDlg 对话框

IMPLEMENT_DYNAMIC(CannyEdgeDlg, CDialogEx)

CannyEdgeDlg::CannyEdgeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(CANNY_EDGE, pParent)
	, th1(0)
	, th2(0)
{

}

CannyEdgeDlg::~CannyEdgeDlg()
{
}

void CannyEdgeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, TH1, th1);
	DDX_Text(pDX, TH2, th2);
}


BEGIN_MESSAGE_MAP(CannyEdgeDlg, CDialogEx)
	ON_EN_CHANGE(TH1, &CannyEdgeDlg::OnEnChangeTh1)
END_MESSAGE_MAP()


// CannyEdgeDlg 消息处理程序


void CannyEdgeDlg::OnEnChangeTh1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
