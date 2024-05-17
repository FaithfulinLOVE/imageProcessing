// MedianFilterDlg.cpp: 实现文件
//

#include "imageProcessing.h"
#include "afxdialogex.h"
#include "MedianFilterDlg.h"


// MedianFilterDlg 对话框

IMPLEMENT_DYNAMIC(MedianFilterDlg, CDialogEx)

MedianFilterDlg::MedianFilterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(MED_FIL_DLG, pParent)
	, winSize(0)
{

}

MedianFilterDlg::~MedianFilterDlg()
{
}

void MedianFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, MEDFIL_WIN_SIZE, winSize);
}


BEGIN_MESSAGE_MAP(MedianFilterDlg, CDialogEx)
END_MESSAGE_MAP()


// MedianFilterDlg 消息处理程序


