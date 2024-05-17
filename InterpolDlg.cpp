// InterpolDlg.cpp: 实现文件
//

#include "imageProcessing.h"
#include "afxdialogex.h"
#include "InterpolDlg.h"


// InterpolDlg 对话框

IMPLEMENT_DYNAMIC(InterpolDlg, CDialogEx)

InterpolDlg::InterpolDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(INTERPOL_DLG, pParent)
	, width(0)
	, height(0)
	, nearest(FALSE)
	, double_linear(FALSE)
{

}

InterpolDlg::~InterpolDlg()
{
}

void InterpolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, INTER_WIDTH, width);
	DDX_Text(pDX, INTER_HEIGHT, height);
	DDX_Radio(pDX, NEAREST, nearest);
	DDX_Radio(pDX, DOUBLE_LINEAR, double_linear);
}


BEGIN_MESSAGE_MAP(InterpolDlg, CDialogEx)
	ON_BN_CLICKED(DOUBLE_LINEAR, &InterpolDlg::OnBnClickedLinear)
	ON_BN_CLICKED(NEAREST, &InterpolDlg::OnBnClickedNearest)
END_MESSAGE_MAP()

BOOL InterpolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置Radio Button初始状态
	CButton* pRadioButton = (CButton*)GetDlgItem(NEAREST);
	pRadioButton->SetCheck(BST_CHECKED);
	pRadioButton = (CButton*)GetDlgItem(DOUBLE_LINEAR);
	pRadioButton->SetCheck(BST_UNCHECKED);

	return TRUE;
}

// InterpolDlg 消息处理程序


void InterpolDlg::OnBnClickedLinear()
{
	CButton* pRadioButton = (CButton*)GetDlgItem(NEAREST);
	pRadioButton->SetCheck(BST_UNCHECKED);
	pRadioButton = (CButton*)GetDlgItem(DOUBLE_LINEAR);
	pRadioButton->SetCheck(BST_CHECKED);
}


void InterpolDlg::OnBnClickedNearest()
{
	// TODO: 在此添加控件通知处理程序代码
	CButton* pRadioButton = (CButton*)GetDlgItem(DOUBLE_LINEAR);
	pRadioButton->SetCheck(BST_UNCHECKED);
	pRadioButton = (CButton*)GetDlgItem(NEAREST);
	pRadioButton->SetCheck(BST_CHECKED);
}
