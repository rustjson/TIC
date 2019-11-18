#pragma once

#include <memory>
#include <Live/ITXLivePlayer.h>

class CPushDlg
	: public CDialogEx
	, public std::enable_shared_from_this<CPushDlg>
{
	DECLARE_MESSAGE_MAP()
public:
	CPushDlg(CWnd* pParent = nullptr);

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PUSH_DIALOG };
#endif

private:
	virtual BOOL OnInitDialog() override;
	virtual void DoDataExchange(CDataExchange* pDX) override;

public:
	ITXLivePlayer* mLivePlayer;
	CButton chkPushEnable_;
public:
	afx_msg void OnBnClickedChkEnableDraw();

};