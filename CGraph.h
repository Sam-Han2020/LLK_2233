#pragma once
class CGraph
{
public:
	CGraph();
	~CGraph();
public:
	void InitGraph();
#define MAX_VERTEX_NUM 56
	typedef int Vertices[MAX_VERTEX_NUM];
	typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
protected:
	Vertices m_Vertices;
	int n_nVexnum;
	AdjMatrix m_AdjMatrix;
	int m_nArcnum;
};

