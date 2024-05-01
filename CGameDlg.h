#pragma once
#include "afxdialogex.h"
#include "global.h"
#include "CGameDlg.h"
#include "CGameLogic.h"
#include "pch.h"
#include "LLK.h"
#include "afxdialogex.h"
#include "CGameDlg.h"
#include "Resource.h"
#include "CGameControl.h"


// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameDlg();
	void UpdateWindow();
protected:
	void InitBackGround();
	void InitElement(void);
	void UpdateMap(void);
	void DrawTipFrame(int nRow, int nCol);
	void DrawTipLine(Vertex avPath[4], int vnum);
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	HICON m_hIcon;
	CDC m_dcMem;
	CDC m_dcBG;
	CDC m_dcElement;
	CDC m_dcMask;
	CDC m_dcPause;
	CPoint m_ptGameTop;
	CSize m_sizeElem;
	bool m_bFirstPoint;
	CGameLogic gmlogic;
	CRect m_rtGameRect;
	CGameControl m_GameC;
	bool m_bPlaying;
	bool m_bPause;
	DECLARE_MESSAGE_MAP()
public:
	BOOL PlaySound(LPCSTR pszSound, HMODULE hmod, DWORD fdwSound);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedBtnPause2();
	afx_msg void OnBnClickedBtnTip();
	afx_msg void OnBnClickedBtnRe();
	afx_msg void OnBnClickedBtnSetting();
	afx_msg void OnBnClickedBtnHelp();
	afx_msg void OnNMCustomdrawProgress1(NMHDR* pNMHDR, LRESULT* pResult);
	CProgressCtrl m_GameProgress;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void DrawGameTime();
	void JudgeWin();
};
