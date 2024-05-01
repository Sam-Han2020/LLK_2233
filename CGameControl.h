#pragma once
#include "CGameLogic.h"
#include "global.h"
#include "CGraph.h"
class CGameControl
{
public:
	static int s_nRows;
	static int s_nCols;
	static int s_nPicNum;
private:
	//int** m_pGameMap;
	CGameLogic gameLogic;
public:
	CGameControl(void);
	~CGameControl(void);
	void StartGame(void);
	int GetElement(int nRow, int nCol);
	void SetFirstPoint(int nRow, int nCol);
	void SetSecPoint(int nRow, int nCol);
	bool Link(Vertex avPath[2], Vertex aPath[4], int& vnum);
	void ClearVex(Vertex aPath[2]);
	void SetElement(int nRow, int nCol, int value);

protected:
	int m_anMap[ROW][COLOMN];
	Vertex m_ptSelFirst;
	Vertex m_ptSelSec;
public:
	int is_win(int nTime);
	bool Help(Vertex ap[4],int &vnum);
	void ResetMap();
	void ReleaseMap();
};

