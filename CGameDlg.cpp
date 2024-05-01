// CGameDlg.cpp: 实现文件
//
#include "CGameDlg.h"
#include "CGameLogic.h"
#include "pch.h"
#include "LLK.h"
#include "afxdialogex.h"
#include "CGameDlg.h"
#include "Resource.h"
#include "CGameControl.h"
#include "global.h"
#include "resource.h"

// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_ptGameTop.x = 0;
	m_ptGameTop.y = 0;
	m_sizeElem.cx = 90;
	m_sizeElem.cy = 90;

	m_bFirstPoint = true;

	m_bPlaying = false;

	m_bPause = false;

	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElem.cx * COLOMN;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElem.cy * ROW;
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_GameProgress);
}

void CGameDlg::UpdateWindow()
{
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin); // 获得窗口大小
	this->GetClientRect(rtClient); // 获得客户区大小
	// 标题栏和外边框的大小
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	// 设置窗口大小
	MoveWindow(0, 0, 1200 + nSpanWidth, 900 + nSpanHeight);
	CenterWindow();
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_START, &CGameDlg::OnBnClickedBtnStart)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BTN_PAUSE2, &CGameDlg::OnBnClickedBtnPause2)
	ON_BN_CLICKED(IDC_BTN_TIP, &CGameDlg::OnBnClickedBtnTip)
	ON_BN_CLICKED(IDC_BTN_RE, &CGameDlg::OnBnClickedBtnRe)
	ON_BN_CLICKED(IDC_BTN_SETTING, &CGameDlg::OnBnClickedBtnSetting)
	ON_BN_CLICKED(IDC_BTN_HELP, &CGameDlg::OnBnClickedBtnHelp)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS1, &CGameDlg::OnNMCustomdrawProgress1)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CGameDlg 消息处理程序


BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	SetWindowText(_T("欢乐连连看—基本模式(=·ω·=)"));
	GetDlgItem(IDC_PROGRESS1)->ShowWindow(FALSE);
	InitBackGround();
	UpdateWindow();
	InitElement();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CGameDlg::InitBackGround()
{
	CClientDC dc(this);
	HANDLE bmp = ::LoadImageW(NULL, _T("theme\\picture\\game_bg.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
	);
	m_dcBG.CreateCompatibleDC(&dc);
	m_dcBG.SelectObject(bmp);
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc,1200,900);
	m_dcMem.SelectObject(&bmpMem);
	m_dcMem.BitBlt(0,0,1200,900,&m_dcBG,0,0,SRCCOPY);
}

void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	dc.BitBlt(0, 0, 1200, 900, &m_dcMem, 0, 0, SRCCOPY);
	if (m_bPause == true)
	{
		//绘制图片
		m_dcMem.BitBlt(30, 90, 871, 630, &m_dcPause, 0, 0, SRCCOPY);
		//GetDlgItem(IDC_BTN_TIP)->EnableWindow(false);
		//GetDlgItem(IDC_BTN_RE)->EnableWindow(false);
		InvalidateRect(m_rtGameRect, false); // 更新界面
		//更改提示文本
		this->GetDlgItem(IDC_BTN_PAUSE2)->SetWindowTextW(_T("继续游戏"));
		this->GetDlgItem(IDC_BTN_SETTING)->SetWindowTextW(_T("设置"));
		this->GetDlgItem(IDC_BTN_HELP)->SetWindowTextW(_T("帮助"));
	}
}

void CGameDlg::InitElement(void)
{
	// 获得当前对话框的视频内存
	CClientDC dc(this);
	// 加载 BMP 图片资源
	HANDLE hBmpBG = ::LoadImageW(NULL, _T("theme\\picture\\2233_elements.bmp"),IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	// 创建与视频内存兼容的内存 DC 
	m_dcElement.CreateCompatibleDC(&dc);
	// 将位图资源选入 DC
	m_dcElement.SelectObject(hBmpBG);
	//// 加载掩码 BMP 图片资源
	//HANDLE hMask = ::LoadImageW(NULL, _T("theme\\picture\\game_bg.bmp"),
	//IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	////// 创建与视频内存兼容的内存 DC
	//m_dcMem.CreateCompatibleDC(&dc);
	////// 将位图资源选入 DC
	//m_dcMem.SelectObject(hMask);
	HANDLE hPause = ::LoadImageW(NULL, _T("theme\\picture\\pause.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcPause.CreateCompatibleDC(&dc);
	m_dcPause.SelectObject(hPause);
}


void CGameDlg::OnBnClickedBtnStart()
{
	// TODO: 在此添加控件通知处理程序代码
	//点击开始，绘制棋子
	m_GameC.StartGame();
	m_bPlaying = true;
	//显示进度条，开始按钮置为无效
	GetDlgItem(IDC_PROGRESS1)->ShowWindow(TRUE);
	this->GetDlgItem(IDC_BTN_START)->EnableWindow(FALSE);
	UpdateMap();
	Invalidate(FALSE);//这行代码的作用，在于重绘界面
	//启动计时
	m_GameProgress.SetRange(0, 100);
	m_GameProgress.SetStep(-1);
	m_GameProgress.SetPos(100);
	this->SetTimer(PLAY_TIMER_ID,1000,NULL);
	DrawGameTime();
}

void CGameDlg::UpdateMap(void)
{//根据二维数组重置棋子
	int nLeft = m_ptGameTop.x;
	int nTop = m_ptGameTop.y;
	int nElemW = m_sizeElem.cx;
	int nElemH = m_sizeElem.cy;
	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(), m_rtGameRect.Height(), &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COLOMN; ++j)
		{//为什么是m_dcMem
			if (m_GameC.GetElement(i, j) == BLANK) continue;
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElement, 0, m_GameC.GetElement(i, j) * nElemH, SRCAND);
		}
	}
}

void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bPause == true)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	if (point.x < m_ptGameTop.x || point.y < m_ptGameTop.y)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	//对鼠标点击的坐标取整，得到行列
	int nRow = (point.y - m_ptGameTop.y)/m_sizeElem.cy;
	int nCol = (point.x - m_ptGameTop.x) / m_sizeElem.cx;
	if (nRow > ROW-2 || nCol > COLOMN-2 || nRow < 1 || nCol < 1)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	if (m_GameC.GetElement(nRow, nCol) == BLANK)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	if (m_bFirstPoint)
	{
		m_GameC.SetFirstPoint(nRow,nCol);
		DrawTipFrame(nRow, nCol);
	}
	else
	{
		m_GameC.SetSecPoint(nRow, nCol);
		DrawTipFrame(nRow, nCol);
		Vertex av_Path[2];
		Vertex aPath[5];
		int vnum = 0;
		//判断是否是相同图片
		if (m_GameC.Link(av_Path,aPath,vnum))
		{
			aPath[0] = av_Path[0];
			aPath[vnum + 1] = av_Path[1];
			DrawTipLine(aPath,vnum);
			m_GameC.ClearVex(av_Path);
			m_GameProgress.SetPos(m_GameProgress.GetPos()+5);
			Sleep(500);
			UpdateMap();//只修改了背景的内容，但是没有做到重绘背景。
		}
		else {
			vnum = 0;
		}
		//Invalidate(FALSE);//这行代码会让程序对窗口按照新的背景进行重绘，但是没必要整个窗口
		InvalidateRect(m_rtGameRect, FALSE);//最好的解决方案，是定义一个矩形，包围游戏界面区域，重绘这个矩形区域
	}
	m_bFirstPoint = !m_bFirstPoint;
}

void CGameDlg::DrawTipFrame(int nRow,int nCol)
{
	CClientDC dc(this);
	CBrush brush(RGB(255,0,0));
	CRect rtTipFrame;
	rtTipFrame.left = m_ptGameTop.x + nCol * m_sizeElem.cx;
	rtTipFrame.top = m_ptGameTop.y + nRow * m_sizeElem.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElem.cy;
	dc.FrameRect(rtTipFrame, & brush);
}

void CGameDlg::DrawTipLine(Vertex avPath[4],int vnum)
{
	CClientDC dc(this);
	CPen penLine(PS_SOLID, 5, RGB(160, 226, 252));
	CPen* pOldPen = dc.SelectObject(&penLine);
	for (int i = 1; i < vnum+2; ++i)
	{
		dc.MoveTo(m_ptGameTop.x + avPath[i-1].col * m_sizeElem.cx + m_sizeElem.cx / 2, m_ptGameTop.y + avPath[i-1].row * m_sizeElem.cy + m_sizeElem.cy / 2);
		dc.LineTo(m_ptGameTop.x + avPath[i].col * m_sizeElem.cx + m_sizeElem.cx / 2, m_ptGameTop.y + avPath[i].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	}
	
	dc.SelectObject(pOldPen);
}




void CGameDlg::OnBnClickedBtnPause2()
{
	// TODO: 在此添加控件通知处理程序代码
	CClientDC dc(this);

	// 游戏未正在进行，直接返回
	if (m_bPlaying == false)
	{
		return;
	}

	// 如果游戏不是暂停状态
	if (m_bPause == false)
	{
		//绘制图片
		m_dcMem.BitBlt(30,90 , 871, 630, &m_dcPause, 0, 0, SRCCOPY);
		GetDlgItem(IDC_BTN_TIP)->EnableWindow(false);
		GetDlgItem(IDC_BTN_RE)->EnableWindow(false);
		InvalidateRect(m_rtGameRect, false); // 更新界面
		//更改提示文本
		this->GetDlgItem(IDC_BTN_PAUSE2)->SetWindowTextW(_T("继续游戏"));
	}

	// 如果游戏暂停,则恢复游戏状态
	if (m_bPause == true)
	{
		UpdateMap();
		GetDlgItem(IDC_BTN_TIP)->EnableWindow(1);
		GetDlgItem(IDC_BTN_RE)->EnableWindow(1);
		InvalidateRect(m_rtGameRect, FALSE); // 局部矩形更新
		//更改提示文本
		this->GetDlgItem(IDC_BTN_PAUSE2)->SetWindowTextW(_T("暂停游戏"));
	}
	m_bPause = !m_bPause;
}


void CGameDlg::OnBnClickedBtnTip()
{
	// TODO: 在此添加控件通知处理程序代码
	Vertex ap[4];
	int vnum=0;
	if (m_GameC.Help(ap,vnum))
	{
		DrawTipFrame(ap[0].row,ap[0].col);
		DrawTipFrame(ap[vnum+1].row, ap[vnum+1].col);
		//CString str;
		//str.Format(_T("%d"), vnum);
		//AfxMessageBox(str);
		DrawTipLine(ap, vnum);
		Sleep(1000);
		UpdateMap();
		InvalidateRect(m_rtGameRect, FALSE);
	}
}


void CGameDlg::OnBnClickedBtnRe()
{
	// TODO: 在此添加控件通知处理程序代码
	m_GameC.ResetMap();
	UpdateMap();
	InvalidateRect(m_rtGameRect, FALSE);
}


void CGameDlg::OnBnClickedBtnSetting()
{

}


void CGameDlg::OnBnClickedBtnHelp()
{
	// TODO: 在此添加控件通知处理程序代码
	//CHelpDialog dlg;
	//dlg.DoModal();
}


void CGameDlg::OnNMCustomdrawProgress1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == PLAY_TIMER_ID && m_bPlaying && !m_bPause)
	{
		m_GameProgress.StepIt();
	}
	DrawGameTime();
	JudgeWin();
	CDialogEx::OnTimer(nIDEvent);
}


void CGameDlg::DrawGameTime()
{
	// TODO: 在此处添加实现代码.
	CClientDC dc(this);
	CString num;
	CSize size = 10; // 文本内容大小
	int nPos; // 进度条值
	//  创建字体
	CFont myFont;
	myFont.CreatePointFont(320, _T("微软雅黑"));
	//  将字体选入设备描述表，并保存原来的字体
	CFont* oldFont = dc.SelectObject(&myFont);

	//  设置字体颜色和背景
	dc.SetTextColor(RGB(254, 198, 224));
	//dc.SetBkColor(TRANSPARENT);

	//  获取文本内容
	nPos = m_GameProgress.GetPos();

	//  获取文本内容大小
	size = dc.GetTextExtent(num, nPos);

	num.Format(_T("%d"), nPos);

	//  设置文本输出区域，绘制文本
	dc.TextOut(830, 730, num);
	//  还原字体
	dc.SelectObject(oldFont);

	//  更新界面
	UpdateMap();
}


void CGameDlg::JudgeWin()
{
	int game_status = m_GameC.is_win(m_GameProgress.GetPos());
	if (game_status == 0) return;
	else
	{
		m_bPlaying = false;
		KillTimer(PLAY_TIMER_ID);
		CString strTitle;
		this->GetWindowTextW(strTitle);
		if (game_status == 1)
		{
			UpdateMap();
			MessageBox(_T("你赢啦!"));
		}
		else if (game_status == -1)
		{
			UpdateMap();
			MessageBox(_T("很遗憾，时间到啦!"), strTitle);
		}
		GetDlgItem(IDC_PROGRESS1)->ShowWindow(FALSE);
		this->GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
		Invalidate(FALSE);
	}
}
