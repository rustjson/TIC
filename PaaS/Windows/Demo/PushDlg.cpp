#include "stdafx.h"
#include "PushDlg.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CPushDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CHK_ENABLE_DRAW, &CPushDlg::OnBnClickedChkEnableDraw)
END_MESSAGE_MAP()

CPushDlg::CPushDlg(CWnd* pParent)
	: CDialogEx(IDD_PUSH_DIALOG, pParent)
{

}

BOOL CPushDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return TRUE;
}

void CPushDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHECK_ENABLE_PUSH, chkPushEnable_);
}


void CPushDlg::OnBnClickedChkEnableDraw()
{
	
}


