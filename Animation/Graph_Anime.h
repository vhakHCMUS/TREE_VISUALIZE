#include "AnimeBase.h"
#include "../Tools/SceneNode.h"
#include "../Tools/TreeNode.h"
#include "../Tools/Edge.h"
#include <queue>

#pragma once

class Graph_Anime;

struct Graph_node
{
	Graph_node(Graph_Anime* anime);

	int data;

	int Nodeid;

	int childsCnt = 0;

	vector<int> childs;

	vector<int> Edgeid;

	Graph_Anime* anime;

	// custom

	shared_ptr <TreeNode> tVisual;
};

class Graph_Anime : public AnimeBase
{
public:

	Graph_Anime();
	virtual ~Graph_Anime();

	// shits
	int m=0;
	int cnt = 0;
	int maxNodeCnt = 0;
	int maxLinkCnt = 0;

	vector <bool> Visited;

	vector <Graph_node*> NodeVector;

	void DelAll();		

	//vector <[N][N]>

	void GenerateGraph(int n);

	void paintNode(int id,Color color);
	void paintLink(int id1,int id2,Color color);

	void drawFrame(RenderTarget& target, int id) const override;

	void makeTransition() override;

	// TOOL for making anime

	void setVis();

	void MakeNewFrame();

	void fillAllFrame();

	void CloneFromTree(SceneNode*& Nodes, SceneNode*& Linkes);
	void CloneLastFrame();

	void PushCurNode(Graph_node*& Cur, Graph_node*& parent);
	void PushCurLink(Vector2f pos1, Vector2f pos2,int& id);

	void PushTreeNode(shared_ptr <TreeNode>& tmp,int& id);
	void PushEdge(Edge* tmp,int& id);

	// Anime maker

	vector <vector<Edge*>> AnimeFrameLink; 

	void MakeDijsktraAnime(SceneNode* Nodes, SceneNode* Linkes,int StartId,int EndId);
	void MakeMinSpanAnime(SceneNode* Nodes, SceneNode* Linkes,int id);
	void MakeConnectedComponent(SceneNode* Nodes, SceneNode* Linkes,int id);

	void cleanUp();
};

