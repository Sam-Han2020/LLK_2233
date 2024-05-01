#pragma once
#include "global.h"
//#include "CGameDlg.h"



class CGameLogic
{
private:
	Vertex m_avPath[4];
	int vnum = 0;
public:
	CGameLogic(void);
	~CGameLogic(void);
public:
	void InitMap(int an_Map[][COLOMN]);
	void Clear(int an_Map[][COLOMN], Vertex v1, Vertex v2);
	bool IsLink(int an_Map[][COLOMN], Vertex v1, Vertex v2);
	bool LinkInRow(int an_Map[][COLOMN], Vertex v1, Vertex v2);
	bool LinkInCol(int an_Map[][COLOMN], Vertex v1, Vertex v2);
	bool LineX(int an_Map[][COLOMN], int nRow, int nCol1, int nCol2);
	bool LineY(int an_Map[][COLOMN], int nCol, int nRow1, int nRow2);
	bool OneCornerLink(int an_Map[][COLOMN], Vertex v1, Vertex v2);
	bool twoCornerLink(int an_Map[][COLOMN], Vertex v1, Vertex v2);
	void PushVertex(Vertex v);
	void delVertex();
	int getPath(Vertex avPath[4]);
	bool is_blank(int an_map[][COLOMN]);
	bool SearchValidPath(int an_Map[][COLOMN], Vertex ap[4],int &vnum);
	void ResetMap(int an_Map[][COLOMN]);
};

