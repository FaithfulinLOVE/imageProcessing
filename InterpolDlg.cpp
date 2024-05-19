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
	, nearest(1)
	, double_linear(0)
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
	CButton* pRadioButton = (CButton*)GetDlgItem(DOUBLE_LINEAR);
	pRadioButton->SetCheck(BST_CHECKED);
	pRadioButton = (CButton*)GetDlgItem(NEAREST);
	pRadioButton->SetCheck(BST_UNCHECKED);
	nearest = 1;
	double_linear = 0;
}


void InterpolDlg::OnBnClickedNearest()
{
	CButton* pRadioButton = (CButton*)GetDlgItem(NEAREST);
	pRadioButton->SetCheck(BST_CHECKED);
	pRadioButton = (CButton*)GetDlgItem(DOUBLE_LINEAR);
	pRadioButton->SetCheck(BST_UNCHECKED);
	nearest = 0;
	double_linear = 1;
}
