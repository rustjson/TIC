#include "stdafx.h"
#include "PushDlg.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CPushDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CHK_ENABLE_DRAW, &CPushDlg::OnBnClickedChkEnableDraw)
	ON_BN_CLICKED(IDC_CHECK_ENABLE_PUSH, &CPushDlg::OnBnClickedCheckEnablePush)
END_MESSAGE_MAP()

CPushDlg::CPushDlg(CWnd* pParent)
	: CDialogEx(IDD_PUSH_DIALOG, pParent)
{
	mLocalRecorder = TICLocalRecorder::GetInstance();
}

BOOL CPushDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	int appid = 1400162216;
	std::string user = "seven";
	std::string sig = "eJxlz01Pg0AQgOE7v4JwNrI7y0fwhqXEjW5jaW2rF4IwrQvhQ1gprfG-G7GJJM71eSeT*dR0XTfWD6vrJE3rj0rF6tSgod-oBjGu-rBpZBYnKmZt9g9xaGSLcbJX2I5IbdsGQqaNzLBSci8vRYc9VhPusiIeb-zuW4RQB4A600QeRhTz5xlfBgNAyML5orPNyIfHA3Bx3Ibvd*n5NZDcX1vwFKV5EK7ul-zNX4jZrtwUL3lSF7fbjpcpjfIdioFw5onENXt-45rijMFxclLJEi8POR7zLOrCRHtsO1lXYwCE2hQY*RlD*9K*AYzpXAs_";
	TEduRecordAuthParam auth(appid, user, sig);

	std::weak_ptr< CPushDlg> weakSelf = this->shared_from_this();
	mLocalRecorder->init(auth, [this, weakSelf](TICModule module, int code, const char *desc) {
		std::shared_ptr<CPushDlg> self = weakSelf.lock();
		if (!self)
		{
			return;
		}

		
	});



	return TRUE;
}

void CPushDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


void CPushDlg::OnBnClickedChkEnableDraw()
{
	

}


void CPushDlg::OnBnClickedCheckEnablePush()
{
	if (mLocalRecorder)
	{
		bool selected = true; //chkDrawEnable_.GetCheck() == BST_CHECKED;
		if (selected) {
			//mLocalRecorder->startPush();
		}
		else {
			//mLocalRecorder->stopPush();
		}
			

	}
	
}
