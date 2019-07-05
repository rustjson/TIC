#include "stdafx.h"
#include "BoardDlg.h"
#include "Resource.h"

BEGIN_MESSAGE_MAP(CDrawTabDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CHK_ENABLE_DRAW, &CDrawTabDlg::OnBnClickedChkEnableDraw)
	ON_BN_CLICKED(IDC_BTN_UNDO, &CDrawTabDlg::OnBnClickedBtnUndo)
	ON_BN_CLICKED(IDC_BTN_REDO, &CDrawTabDlg::OnBnClickedBtnRedo)
	ON_BN_CLICKED(IDC_BTN_CLEAR_DRAW, &CDrawTabDlg::OnBnClickedBtnClearDraw)
	ON_BN_CLICKED(IDC_BTN_CLEAR_BOARD, &CDrawTabDlg::OnBnClickedBtnClearBoard)
	ON_BN_CLICKED(IDC_BTN_BK_IMAGE, &CDrawTabDlg::OnBnClickedBtnBkImage)
	ON_BN_CLICKED(IDC_BTN_BRUSH_COLOR, &CDrawTabDlg::OnBnClickedBtnBrushColor)
	ON_BN_CLICKED(IDC_BTN_BACK_COLOR, &CDrawTabDlg::OnBnClickedBtnBackColor)
	ON_BN_CLICKED(IDC_BTN_TEXT_COLOR, &CDrawTabDlg::OnBnClickedBtnTextColor)
	ON_CBN_SELCHANGE(IDC_COMBO_TOOL_TYPE, &CDrawTabDlg::OnCbnSelchangeComboToolType)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_BRUSH_THIN, &CDrawTabDlg::OnNMCustomdrawSliderBrushThin)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_TEXT_SIZE, &CDrawTabDlg::OnNMCustomdrawSliderTextSize)
	ON_BN_CLICKED(IDC_BTN_ADD_H5_PPT, &CDrawTabDlg::OnBnClickedBtnAddH5Ppt)
	ON_BN_CLICKED(IDC_BTN_ADD_H5_PPT, &CDrawTabDlg::OnBnClickedBtnAddH5Ppt)
	ON_BN_CLICKED(IDC_BTN_SET_BACK_H5, &CDrawTabDlg::OnBnClickedBtnSetBackH5)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_SCALE, &CDrawTabDlg::OnNMCustomdrawSliderScale)
END_MESSAGE_MAP()

CDrawTabDlg::CDrawTabDlg(CWnd* pParent /*= nullptr*/)
	: CDialogEx(IDD_BOARD_TAB_DRAW, pParent)
{

}

void CDrawTabDlg::Init()
{
	auto *boardCtrl = TICManager::GetInstance().GetBoardController();

	chkDrawEnable_.SetCheck(boardCtrl->IsDrawEnable() ? BST_CHECKED : BST_UNCHECKED);

	TEduBoardColor brushColor = boardCtrl->GetBrushColor();
	btnBrushColor_.SetFaceColor(RGB(brushColor.red, brushColor.green, brushColor.blue), true);
	TEduBoardColor backColor = boardCtrl->GetBackgroundColor();
	btnBackColor_.SetFaceColor(RGB(backColor.red, backColor.green, backColor.blue), true);
	TEduBoardColor textColor = boardCtrl->GetTextColor();
	btnTextColor_.SetFaceColor(RGB(textColor.red, textColor.green, textColor.blue), true);

	comboToolType_.SetCurSel(boardCtrl->GetToolType());

	uint32_t brushThin = boardCtrl->GetBrushThin();
	sliderBrushThin_.SetPos(brushThin);

	uint32_t textSize = boardCtrl->GetTextSize();
	sliderTextSize_.SetPos(textSize);
}

void CDrawTabDlg::UpdateUndoState(bool canUndo)
{
	btnUndo_.EnableWindow(canUndo);
}

void CDrawTabDlg::UpdateRedoState(bool canRedo)
{
	btnRedo_.EnableWindow(canRedo);
}

void CDrawTabDlg::UpdateBackgroundColor()
{
	auto *boardCtrl = TICManager::GetInstance().GetBoardController();
	TEduBoardColor backColor = boardCtrl->GetBackgroundColor();
	btnBackColor_.SetFaceColor(RGB(backColor.red, backColor.green, backColor.blue), true);
}

void CDrawTabDlg::UpdateBoardScale()
{
	auto *boardCtrl = TICManager::GetInstance().GetBoardController();
	int scale = boardCtrl->GetBoardScale();
	sliderScale_.SetPos(scale);
}

BOOL CDrawTabDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//白板工具
	comboToolType_.AddString(L"鼠标");
	comboToolType_.AddString(L"画笔");
	comboToolType_.AddString(L"橡皮擦");
	comboToolType_.AddString(L"激光笔");
	comboToolType_.AddString(L"直线");
	comboToolType_.AddString(L"空心椭圆");
	comboToolType_.AddString(L"空心矩形");
	comboToolType_.AddString(L"实心椭圆");
	comboToolType_.AddString(L"实心矩形");
	comboToolType_.AddString(L"点选");
	comboToolType_.AddString(L"框选");
	comboToolType_.AddString(L"文本");
	comboToolType_.AddString(L"缩放移动");

	sliderBrushThin_.SetRange(1, 200);

	sliderTextSize_.SetRange(1, 1000);

	comboH5_.AddString(_T("https://test04-1257240443.cos.ap-shanghai.myqcloud.com/2019-05-08-15-38-54/index.html"));
	comboH5_.AddString(_T("https://test04-1257240443.cos.ap-shanghai.myqcloud.com/2019-05-08-15-18-25-0/index.html"));

	sliderScale_.SetRange(100, 300);

	return TRUE;
}

void CDrawTabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHK_ENABLE_DRAW, chkDrawEnable_);

	DDX_Control(pDX, IDC_BTN_UNDO, btnUndo_);
	DDX_Control(pDX, IDC_BTN_REDO, btnRedo_);

	DDX_Control(pDX, IDC_BTN_BRUSH_COLOR, btnBrushColor_);
	DDX_Control(pDX, IDC_BTN_BACK_COLOR, btnBackColor_);
	DDX_Control(pDX, IDC_BTN_TEXT_COLOR, btnTextColor_);

	DDX_Control(pDX, IDC_COMBO_TOOL_TYPE, comboToolType_);

	DDX_Control(pDX, IDC_SLIDER_BRUSH_THIN, sliderBrushThin_);
	DDX_Control(pDX, IDC_SLIDER_TEXT_SIZE, sliderTextSize_);

	DDX_Control(pDX, IDC_COMBO_H5, comboH5_);
	DDX_Control(pDX, IDC_EDIT_BACK_H5, editBackH5_);

	DDX_Control(pDX, IDC_SLIDER_SCALE, sliderScale_);
}

void CDrawTabDlg::OnBnClickedChkEnableDraw()
{
	auto *boardCtrl = TICManager::GetInstance().GetBoardController();
	if (boardCtrl)
	{
		boardCtrl->SetDrawEnable(chkDrawEnable_.GetCheck() == BST_CHECKED);
	}
}

void CDrawTabDlg::OnBnClickedBtnUndo()
{
	auto *boardCtrl = TICManager::GetInstance().GetBoardController();
	if (boardCtrl)
	{
		boardCtrl->Undo();
	}
}

void CDrawTabDlg::OnBnClickedBtnRedo()
{
	auto *boardCtrl = TICManager::GetInstance().GetBoardController();
	if (boardCtrl)
	{
		boardCtrl->Redo();
	}
}

void CDrawTabDlg::OnBnClickedBtnClearDraw()
{
	auto *boardCtrl = TICManager::GetInstance().GetBoardController();
	if (boardCtrl)
	{
		boardCtrl->Clear(); //仅清空涂鸦
	}
}

void CDrawTabDlg::OnBnClickedBtnClearBoard()
{
	auto *boardCtrl = TICManager::GetInstance().GetBoardController();
	if (boardCtrl)
	{
		boardCtrl->Clear(true); //清空涂鸦，同时清空背景色和背景图片
	}
}

void CDrawTabDlg::OnBnClickedBtnBkImage()
{
	auto *boardCtrl = TICManager::GetInstance().GetBoardController();
	if (boardCtrl)
	{
		CFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("All Files (*.*)|*.*||"), NULL);

		if (dlgFile.DoModal() == IDOK)
		{
			boardCtrl->SetBackgroundImage(w2a(dlgFile.GetPathName().GetString(), CP_UTF8).c_str(), TEDU_BOARD_IMAGE_FIT_MODE_CENTER);
		}
	}
}

void CDrawTabDlg::OnBnClickedBtnBrushColor()
{
	auto *boardCtrl = TICManager::GetInstance().GetBoardController();
	if (boardCtrl)
	{
		CColorDialog dlg;
		if (dlg.DoModal() == IDOK)
		{
			COLORREF color = dlg.GetColor();
			btnBrushColor_.SetFaceColor(color, true);

			TEduBoardColor brushColor;
			brushColor.red = GetRValue(color);
			brushColor.green = GetGValue(color);
			brushColor.blue = GetBValue(color);
			brushColor.alpha = 255;
			boardCtrl->SetBrushColor(brushColor);
		}
	}
}

void CDrawTabDlg::OnBnClickedBtnBackColor()
{
	auto *boardCtrl = TICManager::GetInstance().GetBoardController();
	if (boardCtrl)
	{
		CColorDialog dlg;
		if (dlg.DoModal() == IDOK)
		{
			COLORREF color = dlg.GetColor();
			btnBackColor_.SetFaceColor(color, true);
			btnBackColor_.SetFaceColor(color, true);

			TEduBoardColor backColor;
			backColor.red = GetRValue(color);
			backColor.green = GetGValue(color);
			backColor.blue = GetBValue(color);
			backColor.alpha = 255;
			boardCtrl->SetBackgroundColor(backColor);
		}
	}
}

void CDrawTabDlg::OnBnClickedBtnTextColor()
{
	auto *boardCtrl = TICManager::GetInstance().GetBoardController();
	if (boardCtrl)
	{
		CColorDialog dlg;
		if (dlg.DoModal() == IDOK)
		{
			COLORREF color = dlg.GetColor();
			btnTextColor_.SetFaceColor(color, true);
			btnTextColor_.SetFaceColor(color, true);

			TEduBoardColor textColor;
			textColor.red = GetRValue(color);
			textColor.green = GetGValue(color);
			textColor.blue = GetBValue(color);
			textColor.alpha = 255;
			boardCtrl->SetTextColor(textColor);
		}
	}
}

void CDrawTabDlg::OnCbnSelchangeComboToolType()
{
	auto *boardCtrl = TICManager::GetInstance().GetBoardController();
	if (boardCtrl)
	{
		boardCtrl->SetToolType((TEduBoardToolType)(comboToolType_.GetCurSel()));
	}
}

void CDrawTabDlg::OnNMCustomdrawSliderBrushThin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	auto *boardCtrl = TICManager::GetInstance().GetBoardController();
	if (boardCtrl)
	{
		boardCtrl->SetBrushThin(sliderBrushThin_.GetPos());
	}
	*pResult = 0;
}

void CDrawTabDlg::OnNMCustomdrawSliderTextSize(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	auto *boardCtrl = TICManager::GetInstance().GetBoardController();
	if (boardCtrl)
	{
		boardCtrl->SetTextSize(sliderTextSize_.GetPos());
	}
	*pResult = 0;
}

void CDrawTabDlg::OnBnClickedBtnAddH5Ppt()
{
	auto *boardCtrl = TICManager::GetInstance().GetBoardController();
	if (boardCtrl)
	{
		CString h5Url;
		comboH5_.GetWindowText(h5Url);
		std::string url = w2a(h5Url.GetString());
		boardCtrl->AddH5PPTFile(url.c_str());
	}
}

void CDrawTabDlg::OnBnClickedBtnSetBackH5()
{
	auto *boardCtrl = TICManager::GetInstance().GetBoardController();
	if (boardCtrl)
	{
		CString h5Url;
		editBackH5_.GetWindowText(h5Url);
		std::string url = w2a(h5Url.GetString());
		boardCtrl->SetBackgroundH5(url.c_str());
	}
}

void CDrawTabDlg::OnNMCustomdrawSliderScale(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	auto *boardCtrl = TICManager::GetInstance().GetBoardController();
	if (boardCtrl)
	{
		boardCtrl->SetBoardScale(sliderScale_.GetPos());
	}
	*pResult = 0;
}

BEGIN_MESSAGE_MAP(CBoardTabDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_PREV_BOARD, &CBoardTabDlg::OnBnClickedBtnPrevBoard)
	ON_BN_CLICKED(IDC_BTN_NEXT_BOARD, &CBoardTabDlg::OnBnClickedBtnNextBoard)
	ON_BN_CLICKED(IDC_BTN_PREV_STEP, &CBoardTabDlg::OnBnClickedBtnPrevStep)
	ON_BN_CLICKED(IDC_BTN_NEXT_STEP, &CBoardTabDlg::OnBnClickedBtnNextStep)
	ON_BN_CLICKED(IDC_BTN_ADD_BOARD, &CBoardTabDlg::OnBnClickedBtnAddBoard)
	ON_BN_CLICKED(IDC_BTN_DEL_BOARD, &CBoardTabDlg::OnBnClickedBtnDelBoard)
	ON_LBN_SELCHANGE(IDC_LIST_BOARD, &CBoardTabDlg::OnLbnSelchangeListBoard)
END_MESSAGE_MAP()

CBoardTabDlg::CBoardTabDlg(CWnd* pParent /*= nullptr*/)
	: CDialogEx(IDD_BOARD_TAB_BOARD, pParent)
{

}

void CBoardTabDlg::UpdateBoardList()
{
	auto *boardCtrl = TICManager::GetInstance().GetBoardController();
	if (boardCtrl)
	{
		listBoard_.SetRedraw(FALSE);
		listBoard_.ResetContent();
		auto* boardList = boardCtrl->GetFileBoardList(boardCtrl->GetCurrentFile());
		if (!boardList) return;
		std::string curBoardId = boardCtrl->GetCurrentBoard();
		for (uint32_t i = 0; i < boardList->GetCount(); ++i)
		{
			std::string boardId = boardList->GetBoard(i);
			listBoard_.InsertString(i, a2w(boardId, CP_UTF8).c_str());
			if (curBoardId == boardId) listBoard_.SetCurSel(i);
		}
		boardList->Release();
		listBoard_.SetRedraw(TRUE);
	}
}

BOOL CBoardTabDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return TRUE;
}

void CBoardTabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHK_REST_STEP, chkResetStep_);
	DDX_Control(pDX, IDC_LIST_BOARD, listBoard_);
}

void CBoardTabDlg::OnBnClickedBtnPrevBoard()
{
	auto *boardCtrl = TICManager::GetInstance().GetBoardController();
	if (boardCtrl)
	{
		bool resetStep = (chkResetStep_.GetCheck() == BST_CHECKED);
		boardCtrl->PrevBoard(resetStep);
	}
}

void CBoardTabDlg::OnBnClickedBtnNextBoard()
{
	auto *boardCtrl = TICManager::GetInstance().GetBoardController();
	if (boardCtrl)
	{
		bool resetStep = (chkResetStep_.GetCheck() == BST_CHECKED);
		boardCtrl->NextBoard(resetStep);
	}
}

void CBoardTabDlg::OnBnClickedBtnPrevStep()
{
	auto *boardCtrl = TICManager::GetInstance().GetBoardController();
	if (boardCtrl)
	{
		boardCtrl->PrevStep();
	}
}

void CBoardTabDlg::OnBnClickedBtnNextStep()
{
	auto *boardCtrl = TICManager::GetInstance().GetBoardController();
	if (boardCtrl)
	{
		boardCtrl->NextStep();
	}
}

void CBoardTabDlg::OnBnClickedBtnAddBoard()
{
	auto *boardCtrl = TICManager::GetInstance().GetBoardController();
	if (boardCtrl)
	{
		boardCtrl->AddBoard();
	}
}

void CBoardTabDlg::OnBnClickedBtnDelBoard()
{
	auto *boardCtrl = TICManager::GetInstance().GetBoardController();
	if (boardCtrl)
	{
		auto *boardList = boardCtrl->GetFileBoardList(boardCtrl->GetCurrentFile());
		if (!boardList) return;
		boardCtrl->DeleteBoard(boardList->GetBoard(listBoard_.GetCurSel()));
		boardList->Release();
	}
}

void CBoardTabDlg::OnLbnSelchangeListBoard()
{
	auto *boardCtrl = TICManager::GetInstance().GetBoardController();
	if (boardCtrl)
	{
		CString text;
		listBoard_.GetText(listBoard_.GetCurSel(), text);
		boardCtrl->GotoBoard(w2a(text.GetString()).c_str());
	}
}

BEGIN_MESSAGE_MAP(CFileTabDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_ADD_FILE, &CFileTabDlg::OnBnClickedBtnAddFile)
	ON_BN_CLICKED(IDC_BTN_DEL_FILE, &CFileTabDlg::OnBnClickedBtnDelFile)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_FILE, &CFileTabDlg::OnNMDbClkListFile)
END_MESSAGE_MAP()

CFileTabDlg::CFileTabDlg(CWnd* pParent /*= nullptr*/)
	: CDialogEx(IDD_BOARD_TAB_FILE, pParent)
{

}

void CFileTabDlg::UpdateFileList()
{
	auto *boardCtrl = TICManager::GetInstance().GetBoardController();
	if (boardCtrl)
	{
		listFile_.SetRedraw(FALSE);
		listFile_.DeleteAllItems();
		auto* fileList = boardCtrl->GetFileInfoList();
		if (!fileList) return;
		std::string curFileId = boardCtrl->GetCurrentFile();
		for (uint32_t i = 0; i < fileList->GetCount(); ++i)
		{
			TEduBoardFileInfo fileInfo = fileList->GetFileInfo(i);
			listFile_.InsertItem(i, _T(""));
			listFile_.SetItemText(i, 0, a2w(fileInfo.fileId, CP_UTF8).c_str());
			listFile_.SetItemText(i, 1, a2w(fileInfo.title, CP_UTF8).c_str());
			listFile_.SetItemText(i, 2, (std::to_wstring(fileInfo.pageIndex + 1) + _T("/") + std::to_wstring(fileInfo.pageCount)).c_str());
			if (curFileId == fileInfo.fileId) // 选中当前文件
			{
				listFile_.SetItemState(i, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
				listFile_.SetFocus();
			}
		}
		fileList->Release();
		listFile_.SetRedraw(TRUE);
	}
}

BOOL CFileTabDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	listFile_.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 80);
	listFile_.InsertColumn(1, _T("文件名"), LVCFMT_LEFT, 100);
	listFile_.InsertColumn(2, _T("页码"), LVCFMT_LEFT, 72);

	return TRUE;
}

void CFileTabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_FILE, listFile_);
}

void CFileTabDlg::OnBnClickedBtnAddFile()
{
	auto *boardCtrl = TICManager::GetInstance().GetBoardController();
	if (boardCtrl)
	{
		CFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("All Files (*.*)|*.*||"), NULL);
		if (dlgFile.DoModal() == IDOK)
		{
			boardCtrl->AddFile(w2a(dlgFile.GetPathName().GetString(), CP_UTF8).c_str());
		}
	}
}

void CFileTabDlg::OnBnClickedBtnDelFile()
{
	auto *boardCtrl = TICManager::GetInstance().GetBoardController();
	if (boardCtrl)
	{
		POSITION pos = listFile_.GetFirstSelectedItemPosition();
		int index = listFile_.GetNextSelectedItem(pos);
		CString text = listFile_.GetItemText(index, 0);
		boardCtrl->DeleteFile(w2a(text.GetString()).c_str());
	}
}

void CFileTabDlg::OnNMDbClkListFile(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	auto *boardCtrl = TICManager::GetInstance().GetBoardController();
	if (boardCtrl)
	{
		POSITION pos = listFile_.GetFirstSelectedItemPosition();
		int index = listFile_.GetNextSelectedItem(pos);
		CString text = listFile_.GetItemText(index, 0);
		boardCtrl->SwitchFile(w2a(text.GetString()).c_str());
	}
	*pResult = 0;
}

BEGIN_MESSAGE_MAP(CBoardDlg, CDialogEx)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_BOARD, &CBoardDlg::OnTabSelChange)
	ON_CBN_SELCHANGE(IDC_COMBO_RATIO, &CBoardDlg::OnCbnSelchangeComboRatio)
	ON_CBN_SELCHANGE(IDC_COMBO_FIT_MODE, &CBoardDlg::OnCbnSelchangeComboFitMode)
END_MESSAGE_MAP()

CBoardDlg::CBoardDlg(CWnd* pParent)
	: CDialogEx(IDD_BOARD_DIALOG, pParent)
	, histroySync_(false)
{

}

void CBoardDlg::Init()
{
	Uninit();

	auto *boardCtrl = TICManager::GetInstance().GetBoardController();
	if (boardCtrl)
	{
		comboFitMode_.SetCurSel(boardCtrl->GetBoardContentFitMode());

		drawTabDlg_.Init();

		RECT clientRect;
		staticBoard_.GetClientRect(&clientRect);
		// 设置白板为子窗口
		::SetParent(boardCtrl->GetBoardRenderView(), staticBoard_.m_hWnd);
		// 更改白板大小和位置
		boardCtrl->SetBoardRenderViewPos(0, 0, clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
		::ShowWindow(boardCtrl->GetBoardRenderView(), SW_SHOW);

		boardState_ = BoardState::Inited;
		UpdateUI();
	}
}

void CBoardDlg::Uninit()
{
	histroySync_ = false;
	auto *boardCtrl = TICManager::GetInstance().GetBoardController();
	if (boardCtrl)
	{
		boardState_ = BoardState::NotInit;
		UpdateUI();
	}
}

void CBoardDlg::UpdateUI()
{
	switch (boardState_)
	{
	case BoardState::NotInit:
	{
		staticBoard_.SetWindowText(_T("进房后可使用白板"));
		EnableWindow(FALSE);
		break;
	}
	case BoardState::Inited:
	{
		staticBoard_.SetWindowText(_T(""));
		EnableWindow(TRUE);
		break;
	}
	default: break;
	}
}

BOOL CBoardDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//插入TAB页
	tabBoardCtrl_.InsertItem(0, _T("涂鸦"));
	tabBoardCtrl_.InsertItem(1, _T("白板"));
	tabBoardCtrl_.InsertItem(2, _T("文件"));

	drawTabDlg_.Create(IDD_BOARD_TAB_DRAW, &tabBoardCtrl_);
	boardTabDlg_.Create(IDD_BOARD_TAB_BOARD, &tabBoardCtrl_);
	fileTabDlg_.Create(IDD_BOARD_TAB_FILE, &tabBoardCtrl_);

	//获取标签高度
	CRect itemRect;
	tabBoardCtrl_.GetItemRect(0, &itemRect);

	//获取并计算标签页工作区大小
	CRect clientRect;
	tabBoardCtrl_.GetClientRect(clientRect);
	clientRect.top += itemRect.Height() + 2;
	clientRect.bottom -= 2;
	clientRect.left += 2;
	clientRect.right -= 2;

	drawTabDlg_.MoveWindow(&clientRect);
	drawTabDlg_.ShowWindow(SW_SHOW);

	boardTabDlg_.MoveWindow(&clientRect);
	boardTabDlg_.ShowWindow(SW_HIDE);

	fileTabDlg_.MoveWindow(&clientRect);
	fileTabDlg_.ShowWindow(SW_HIDE);

	comboRatio_.AddString(_T("16:9"));
	comboRatio_.AddString(_T("4:3"));
	comboRatio_.SetCurSel(0);

	comboFitMode_.AddString(_T("填满白板"));
	comboFitMode_.AddString(_T("填满容器"));
	comboFitMode_.AddString(_T("覆盖容器"));

	UpdateUI();

	return TRUE;
}

void CBoardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_TAB_BOARD, tabBoardCtrl_);

	DDX_Control(pDX, IDC_BOARD, staticBoard_);

	DDX_Control(pDX, IDC_COMBO_FIT_MODE, comboFitMode_);
	DDX_Control(pDX, IDC_COMBO_RATIO, comboRatio_);
}

void CBoardDlg::UpdateBoardPos()
{
	auto *boardCtrl = TICManager::GetInstance().GetBoardController();
	if (boardCtrl)
	{
		RECT clientRect;
		staticBoard_.GetClientRect(&clientRect);
		// 更改白板大小和位置
		boardCtrl->SetBoardRenderViewPos(0, 0, clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
	}
}

void CBoardDlg::UpdateBoardRatio()
{
	auto *boardCtrl = TICManager::GetInstance().GetBoardController();
	std::string ratio = boardCtrl->GetBoardRatio();
	if (ratio == "16:9") {
		comboRatio_.SetCurSel(0);
	}
	else {
		comboRatio_.SetCurSel(1);
	}
}

void CBoardDlg::OnSize(UINT nType, int cx, int cy)
{
	UpdateBoardPos();

	if (tabBoardCtrl_.m_hWnd) {
		//获取标签高度
		CRect itemRect;
		tabBoardCtrl_.GetItemRect(0, &itemRect);

		//获取并计算标签页工作区大小
		CRect clientRect;
		tabBoardCtrl_.GetClientRect(clientRect);
		clientRect.top += itemRect.Height() + 2;
		clientRect.bottom -= 2;
		clientRect.left += 2;
		clientRect.right -= 2;

		drawTabDlg_.MoveWindow(&clientRect);
		boardTabDlg_.MoveWindow(&clientRect);
		fileTabDlg_.MoveWindow(&clientRect);
	}

	CDialogEx::OnSize(nType, cx, cy);
}

HBRUSH CBoardDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	int nCtrlId = pWnd->GetDlgCtrlID();
	if (nCtrlId == IDC_BOARD)
	{

		pDC->SetTextColor(RGB(188, 0, 0));
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)GetStockObject(WHITE_BRUSH);
	}

	return __super::OnCtlColor(pDC, pWnd, nCtlColor);
}

void CBoardDlg::OnTabSelChange(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	int nCurSel = tabBoardCtrl_.GetCurSel();
	switch (nCurSel)
	{
	case 0:
		drawTabDlg_.ShowWindow(SW_SHOW);
		boardTabDlg_.ShowWindow(SW_HIDE);
		fileTabDlg_.ShowWindow(SW_HIDE);
		break;
	case 1:
		drawTabDlg_.ShowWindow(SW_HIDE);
		boardTabDlg_.ShowWindow(SW_SHOW);
		fileTabDlg_.ShowWindow(SW_HIDE);
		break;
	case 2:
		drawTabDlg_.ShowWindow(SW_HIDE);
		boardTabDlg_.ShowWindow(SW_HIDE);
		fileTabDlg_.ShowWindow(SW_SHOW);
		break;
	default:
		break;
	}
}

void CBoardDlg::OnCbnSelchangeComboRatio()
{
	auto *boardCtrl = TICManager::GetInstance().GetBoardController();
	if (boardCtrl)
	{
		if (comboRatio_.GetCurSel() == 0) {
			boardCtrl->SetBoardRatio("16:9");
		}
		else {
			boardCtrl->SetBoardRatio("4:3");
		}
	}
}

void CBoardDlg::OnCbnSelchangeComboFitMode()
{
	auto *boardCtrl = TICManager::GetInstance().GetBoardController();
	if (boardCtrl)
	{
		boardCtrl->SetBoardContentFitMode((TEduBoardContentFitMode)(comboFitMode_.GetCurSel()));
	}
}

void CBoardDlg::onTEBError(TEduBoardErrorCode code, const char * msg)
{
	printf("-----------onTEBError(%d, %s)------------\n", (int)code, msg);
}

void CBoardDlg::onTEBWarning(TEduBoardWarningCode code, const char * msg)
{
	printf("-----------onTEBWarning(%d, %s)------------\n", (int)code, msg);
}

void CBoardDlg::onTEBInit()
{
	
}

void CBoardDlg::onTEBHistroyDataSyncCompleted()
{
	histroySync_ = true;
	fileTabDlg_.UpdateFileList();
	boardTabDlg_.UpdateBoardList();
}

void CBoardDlg::onTEBSyncData(const char * data)
{

}

void CBoardDlg::onTEBUndoStatusChanged(bool canUndo)
{
	drawTabDlg_.UpdateUndoState(canUndo);
}

void CBoardDlg::onTEBRedoStatusChanged(bool canRedo)
{
	drawTabDlg_.UpdateRedoState(canRedo);
}

void CBoardDlg::onTEBAddBoard(const TEduBoardList *boardList, const char * fileId)
{
	if (histroySync_) boardTabDlg_.UpdateBoardList();
}

void CBoardDlg::onTEBDeleteBoard(const TEduBoardList *boardList, const char * fileId)
{
	if (histroySync_) boardTabDlg_.UpdateBoardList();
}

void CBoardDlg::onTEBGotoBoard(const char * boardId, const char * fileId)
{	
	if (!histroySync_) return;

	auto *boardCtrl = TICManager::GetInstance().GetBoardController();
	if (boardCtrl)
	{
		UpdateBoardRatio();

		drawTabDlg_.UpdateBackgroundColor();
		drawTabDlg_.UpdateBoardScale();

		fileTabDlg_.UpdateFileList();

		boardTabDlg_.UpdateBoardList();
	}
}

void CBoardDlg::onTEBAddFile(const char * fileId)
{
	if (histroySync_) fileTabDlg_.UpdateFileList();
}

void CBoardDlg::onTEBAddH5PPTFile(const char * fileId)
{
	if (histroySync_) fileTabDlg_.UpdateFileList();
}

void CBoardDlg::onTEBDeleteFile(const char * fileId)
{
	if (histroySync_) fileTabDlg_.UpdateFileList();
}

void CBoardDlg::onTEBSwitchFile(const char * fileId)
{
	if (histroySync_)
	{
		fileTabDlg_.UpdateFileList();
		boardTabDlg_.UpdateBoardList();
	}
}
