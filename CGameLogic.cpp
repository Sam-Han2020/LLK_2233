#include "pch.h"
#include "CGameLogic.h"
#include "CGameControl.h"
#include <random>
#include <unordered_map>
#include <vector>
#include <algorithm>  
#include <ctime>  
#include <cstdlib>

CGameLogic::CGameLogic(void)
{
}

CGameLogic::~CGameLogic(void)
{
}

void CGameLogic::InitMap(int an_Map[][COLOMN])
{
	std::vector<int> numbers = { 0, 0,0,0, 1, 1,1,1, 2, 2,2,2, 3, 3, 3, 3, 4, 4,4,4, 5, 5, 5, 5, 6, 6,6,6, 7, 7, 7, 7, 8, 8,8,8, 9, 9,9,9, 10, 10, 10, 10, 11, 11,11,11, 12, 12, 13, 13, 13, 13, 14, 14 };
	int count = 0;
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(numbers.begin(), numbers.end(), g);
	//int anMap[ROW][COLOMN] = 
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COLOMN; ++j)
		{
			if (i == 0 || j == 0 || i == ROW - 1 || j == COLOMN - 1) an_Map[i][j] = BLANK;
			else
			{
				an_Map[i][j] = numbers[count++];
			}
		}
	}
}

void CGameLogic::Clear(int an_Map[][COLOMN], Vertex v1, Vertex v2)
{
	an_Map[v1.row][v1.col] = BLANK;
	an_Map[v2.row][v2.col] = BLANK;
	delVertex();
}

bool CGameLogic::IsLink(int an_Map[][COLOMN], Vertex v1, Vertex v2)
{
	if ((v1.row == v2.row) && (v1.col == v2.col)) return false;
	if (an_Map[v1.row][v1.col] == -1) return false;
	//return an_Map[v1.row][v1.col] == an_Map[v2.row][v2.col];
	int nRow1 = v1.row;
	int nRow2 = v2.row;
	int nCol1 = v1.col;
	int nCol2 = v2.col;
	bool res = (an_Map[v1.row][v1.col] == an_Map[v2.row][v2.col]);
	if (res == false) return res;
	//一条直线联通
	if (nRow1 == nRow2) if (LinkInRow(an_Map, v1, v2)) return res;
	if (nCol1 == nCol2) if(LinkInCol(an_Map, v1, v2)) return res;
	//两条直线联通
	if (OneCornerLink(an_Map, v1, v2)) return res;
	//三条直线联通
	if (twoCornerLink(an_Map, v1, v2)) return res;
	delVertex();
	return false;
}

void swit(int& a, int& b)
{
	int t = a;
	a = b;
	b = t;
}

bool CGameLogic::LineX(int an_Map[][COLOMN],int nRow, int nCol1, int nCol2)
{
	if (nCol1 > nCol2)
		swit(nCol1, nCol2);
	for (int i = nCol1 + 1; i <= nCol2; ++i)
	{
		if (i == nCol2) return true;
		if (an_Map[nRow][i] != -1) break;
	}
	return false;
}

bool CGameLogic::LineY(int an_Map[][COLOMN], int nCol, int nRow1, int nRow2)
{
	if (nRow1 > nRow2)
		swit(nRow1, nRow2);
	for (int i = nRow1 + 1; i <= nRow2; ++i)
	{
		if (i == nRow2) return true;
		if (an_Map[i][nCol] != -1) break;
	}
	return false;
}

bool CGameLogic::LinkInRow(int an_Map[][COLOMN], Vertex v1, Vertex v2)
{
	int nRow = v1.row;
	int nCol1 = v1.col;
	int nCol2 = v2.col;
	return LineX(an_Map, nRow, nCol1, nCol2);
}

bool CGameLogic::LinkInCol(int an_Map[][COLOMN], Vertex v1, Vertex v2)
{
	int nCol = v1.col;
	int nRow1 = v1.row;
	int nRow2 = v2.row;
	return LineY(an_Map, nCol, nRow1, nRow2);
}

bool CGameLogic::OneCornerLink(int an_Map[][COLOMN], Vertex v1, Vertex v2)
{
	int nRow1 = v1.row;
	int nRow2 = v2.row;
	int nCol1 = v1.col;
	int nCol2 = v2.col;
	if (nRow1 > nRow2)
	{
		swit(nRow1, nRow2);
		swit(nCol1, nCol2);
	}
	if (an_Map[nRow1][nCol2] == BLANK)
	{
		//先向下，在向左
		if (LineY(an_Map, nCol2, nRow1, nRow2) && LineX(an_Map, nRow1, nCol1, nCol2))
		{
			Vertex v = { nRow1,nCol2,BLANK };
			PushVertex(v);//一开始写程序的时候，因为一直往里面塞顶点，导致溢出了，画面上出现了很多新的图标
			return true;
		}
	}
	if (an_Map[nRow2][nCol1] == BLANK)
	{
		//先向左，再向下
		if (LineY(an_Map, nCol1, nRow1, nRow2) && LineX(an_Map, nRow2, nCol1, nCol2))
		{
			Vertex v = { nRow2,nCol1,BLANK };
			PushVertex(v);
			return true;
		}
	}
	return false;
}

bool CGameLogic::twoCornerLink(int an_Map[][COLOMN], Vertex v1, Vertex v2)
{
	int nRow1 = v1.row;
	int nRow2 = v2.row;
	int nCol1 = v1.col;
	int nCol2 = v2.col;
	for (int i = 0; i < COLOMN; ++i)
	{
		if (an_Map[nRow1][i] == BLANK && an_Map[nRow2][i] == BLANK)
		{
			if (LineY(an_Map, i, nRow1, nRow2))
			{
				if (LineX(an_Map, nRow1, nCol1, i) && LineX(an_Map, nRow2, nCol2, i))
				{
					Vertex vx1 = {nRow1,i,BLANK};
					Vertex vx2 = {nRow2,i,BLANK};
					PushVertex(vx1);
					PushVertex(vx2);
					return true;
				}
			}
		}
	}
	for (int i = 0; i < ROW; ++i)
	{
		if (an_Map[i][nCol1] == BLANK && an_Map[i][nCol2] == BLANK)
		{
			if (LineX(an_Map, i, nCol1, nCol2))
			{
				if (LineY(an_Map, nCol1, i, nRow1) && LineY(an_Map, nCol2, i, nRow2))
				{
					Vertex vx1 = { i,nCol1,BLANK };
					Vertex vx2 = { i,nCol2,BLANK };
					PushVertex(vx1);
					PushVertex(vx2);
					return true;
				}
			}
		}
	}
	return false;
}

void CGameLogic::PushVertex(Vertex v)
{
	if (vnum == 4) return;
	m_avPath[vnum++] = v;
}

void CGameLogic::delVertex()
{
	vnum = 0;
}

int CGameLogic::getPath(Vertex avPath[4])
{
	for (int i = 1; i < vnum+2; ++i) avPath[i] = m_avPath[i-1];
	int res = vnum;
	delVertex();
	return res;
}


bool CGameLogic::is_blank(int an_map[][COLOMN] )
{
	// TODO: 在此处添加实现代码.
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COLOMN; ++j)
		{
			if (an_map[i][j] != BLANK) return false;
		}
	}
	return true;
}


bool CGameLogic::SearchValidPath(int an_Map[][COLOMN],Vertex ap[4],int &vnum)
{
	// TODO: 在此处添加实现代码.
	Vertex v1, v2;
	for (int i = 1; i < ROW-1; ++i)
	{
		for (int j = 1; j < COLOMN-1; ++j)
		{
			if (an_Map[i][j] != BLANK)
			{
				v1 = { i,j,BLANK };
				for (int k = 1; k < ROW-1; ++k)
				{
					for (int l = 1; l < COLOMN-1; ++l)
					{
						if (an_Map[k][l] != BLANK)
						{
							v2 = {k,l,BLANK};
							if (IsLink(an_Map, v1, v2))
							{
								vnum = getPath(ap);
								ap[0] = v1;
								ap[vnum+1] = v2;
								return true;
							}
							delVertex();
						}
					}
				}
			}
		}
	}
	return false;
}


void CGameLogic::ResetMap(int an_Map[][COLOMN])
{
	// TODO: 在此处添加实现代码.
	srand(time(0));
	for (int i = 0; i < 100; ++i)
	{
		int row1 = (rand() % (ROW - 2)) + 1;
		int col1 = (rand() % (COLOMN - 2)) + 1;
		int row2 = (rand() % (ROW - 2)) + 1;
		int col2 = (rand() % (COLOMN - 2)) + 1;
		swit(an_Map[row1][col1],an_Map[row2][col2]);
	}
}
