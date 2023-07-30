#include "AnimeBase.h"
#include "../Tools/SceneNode.h"
#include "../Tools/TreeNode.h"
#include "../Tools/Edge.h"

#pragma once

struct AVL_node
{
	int data = nothing;
	int level = 1;

	int height = 0;
	int BalanceFactor = 0;

	AVL_node* left = NULL;
	AVL_node* right = NULL;
	AVL_node* par = NULL;

	bool isLeft = true;

	int vectorPos = -1;

	shared_ptr <TreeNode> tVisual = NULL;
};

class AVL_Anime : public AnimeBase
{
public:

	AVL_Anime();
	virtual ~AVL_Anime();

	vector<AVL_node*> NodeVectorFirst;

	int FirstPos = 0;
	

	//vector <[N][N]>

	//Functions

	void copyFirstTree(vector <AVL_node*>& org, int pos);

	void CloneFromTree(SceneNode*& Nodes);

	void makeLinkLevel(AVL_node*& Cur);
	void breakLinkLevel();
	Edge* makeLink(AVL_node*& node1, AVL_node*& node2, Color color);
	void changeLink(AVL_node*& node1, AVL_node*& node2, Color color);

	// Anime maker

	void MakeInsertAnime(int data, SceneNode*& Nodes, vector <AVL_node*>& org, int pos, int n);
	void MakeDeleteAnime(int data, SceneNode*& Nodes, vector <AVL_node*>& org, int pos, int n);
	void MakeUpdateAnime(int dataDel,int dataAdd, SceneNode*& Nodes, vector <AVL_node*>& org, int pos, int n);
	void MakeUpdateAddin(int data);
	void MakeSearchAnime(int data, SceneNode*& Nodes, vector <AVL_node*>& org, int pos, int n);

	void makeRotation(AVL_node* cur, AVL_node* par, int data, Type type);

	void print_console(AVL_node* cur, string prefix, bool isLeft);

	void ReposAfter(AVL_node* cur,int& cnt,int level,bool isLeft);

	void cleanUp();
};

