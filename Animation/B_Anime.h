#include "AnimeBase.h"
#include "../Tools/SceneNode.h"
#include "../Tools/TreeNode.h"
#include "../Tools/Edge.h"

#pragma once

class B_Anime;

struct B_node
{
	B_node(bool isLeaf,B_Anime* anime);

	int level = 0;
	int nKey = 0;

	vector <int> data;
	vector <B_node*> childs;

	vector <int> Nodeid;
	vector <int> Edgeid;
	
	bool isLeaf = 0;

	int vectorPos = -1;
	
	vector <shared_ptr <TreeNode>> tVisual;

	void splitChild(int i, B_node* y);

	void insertNonFull(int data);

	void printConsole(B_node* cur);

	Vector2f middlePos();

	//for Delete

	int findKey(int data);

	void remove(int data);

	void removeFromLeaf(int id);

	void removeFromInternal(int idx);

	int getPred(int idx);

	int getSucc(int idx);

	void fill(int idx);

	void borrowFromPrev(int idx);

	void borrowFromNext(int idx);

	void merge(int idx);

	B_Anime* anime;

	// custom
	void paintNode(Color color, int l, int r,bool HasPred);
	void paintLink(Color color, int l, int r, bool HasPred);
};

class B_Anime : public AnimeBase
{
public:

	B_Anime();
	virtual ~B_Anime();

	// shits
	int m=0;
	int cnt = 0;
	int maxNodeCnt = 0;
	int maxLinkCnt = 0;

	vector <vector <B_node*>> NodeVector;

	B_node* root = NULL;

	int count_node(B_node* cur);

	void insertT(int data,bool isAnime);

	void Del(int data,bool isAnime);

	B_node* Search(B_node*& cur, int data);

	void DelAll(B_node* cur);		

	//vector <[N][N]>

	void drawFrame(RenderTarget& target, int id) const override;

	void makeTransition() override;

	// TOOL for making anime

	void MakeCurState();
	void MakeNewFrame();

	void fillAllFrame();

	void CloneFromTree(SceneNode*& Nodes);
	void CloneLastFrame();

	void PushCurNode(B_node*& Cur, B_node*& parent);
	void PushCurLink(Vector2f pos1, Vector2f pos2,int& id);

	void PushTreeNode(shared_ptr <TreeNode>& tmp,int& id);
	void PushEdge(Edge* tmp,int& id);

	// Anime maker

	vector <vector<Edge*>> AnimeFrameLink;

	void MakeInsertAnime(int data,SceneNode*& Nodes);
	void MakeDeleteAnime(int data, SceneNode*& Nodes);
	void MakeUpdateAnime(int dataDel,int dataAdd, SceneNode*& Nodes);
	void MakeSearchAnime(int data, SceneNode*& Nodes);

	void ReposAfter(B_node* cur,int& cnt,int level,bool isLeft);

	void cleanUp();
};

