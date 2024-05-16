// SET_PIXEL_DLG.cpp: 实现文件
//

#include "imageProcessing.h"
#include "afxdialogex.h"
#include "SET_PIXEL_DLG.h"


// SET_PIXEL_DLG 对话框

IMPLEMENT_DYNAMIC(SET_PIXEL_DLG, CDialogEx)

SET_PIXEL_DLG::SET_PIXEL_DLG(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, set_X(0)
	, set_Y(0)
	, set_Res(0)
	, set_R(0)
	, set_G(0)
	, set_B(0)
{

}

SET_PIXEL_DLG::~SET_PIXEL_DLG()
{
}

void SET_PIXEL_DLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, set_X);
	DDX_Text(pDX, IDC_EDIT2, set_Y);

	DDX_Text(pDX, IDC_EDIT3, set_Res);
	DDX_Text(pDX, IDC_EDIT4, set_R);
	DDX_Text(pDX, IDC_EDIT5, set_G);
	DDX_Text(pDX, IDC_EDIT6, set_B);
}


BEGIN_MESSAGE_MAP(SET_PIXEL_DLG, CDialogEx)
END_MESSAGE_MAP()


// SET_PIXEL_DLG 消息处理程序
