#include "pch.h"
#include "CGameControl.h"

//int CGameControl::s_nRows = 7;
//int CGameControl::s_nCols = 8;
//int CGameControl::s_nPicNum = 15;

CGameControl::CGameControl(void)
{
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COLOMN; ++j)
		{//为什么是m_dcMem
			m_anMap[i][j] = BLANK;
		}
	}
}

int CGameControl::GetElement(int nRow, int nCol)
{
	return m_anMap[nRow][nCol];
}

CGameControl::~CGameControl(void)
{
}

bool CGameControl::Link(Vertex avPath[2], Vertex aPath[4],int &vnum)
{
	if (gameLogic.IsLink(m_anMap, m_ptSelFirst, m_ptSelSec)) {
		avPath[0] = m_ptSelFirst;
		avPath[1] = m_ptSelSec;
		vnum = gameLogic.getPath(aPath);
		return true;
	}
	return false;
}

void CGameControl::ClearVex(Vertex aPath[2])
{
	gameLogic.Clear(m_anMap, aPath[0], aPath[1]);
}

void CGameControl::SetElement(int nRow, int nCol, int value)
{
	m_anMap[nRow][nCol] = value;
}

void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	m_ptSelFirst.row = nRow;
	m_ptSelFirst.col = nCol;
}

void CGameControl::SetSecPoint(int nRow, int nCol)
{
	m_ptSelSec.row = nRow;
	m_ptSelSec.col = nCol;
}

void CGameControl::StartGame(void)
{
	gameLogic.InitMap(m_anMap);
}

int CGameControl::is_win(int nTime)
{
	// TODO: 在此处添加实现代码.
	if (nTime <= 0)
	{
		ReleaseMap();
		return -1;
	}
	if (gameLogic.is_blank(m_anMap))
	{
		ReleaseMap();
		return 1;
	}
	return 0;
}


bool CGameControl::Help(Vertex aps[4],int &vnum)
{
	// TODO: 在此处添加实现代码.
	if (gameLogic.SearchValidPath(m_anMap, aps,vnum)) return true;
	return false;
}


void CGameControl::ResetMap()
{
	// TODO: 在此处添加实现代码.
	gameLogic.ResetMap(m_anMap);
}


void CGameControl::ReleaseMap()
{
	// TODO: 在此处添加实现代码.
	for (int i = 1; i < ROW-1 ; ++i)
		for (int j = 1; j < COLOMN-1; ++j)
			m_anMap[i][j] = BLANK;
}
