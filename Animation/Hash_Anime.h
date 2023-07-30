#include "AnimeBase.h"
#include "../Tools/SceneNode.h"
#include "../Tools/TreeNode.h"
#include "../Tools/Edge.h"

#pragma once

struct Hash_node
{
	int data = nothing;
	int level = 1;

	Hash_node* next = NULL;

	int vectorPos = -1;

	shared_ptr <TreeNode> tVisual = NULL;
};

class Hash_Anime : public AnimeBase
{
public:

	Hash_Anime();
	virtual ~Hash_Anime();

	vector<Hash_node*> NodeVectorFirst;
	vector<int> keyHole;

	//vector <[N][N]>

	//Functions

	void copyFirstTree(vector <Hash_node*>& org);

	void CloneFromTree(SceneNode*& Nodes);

	void makeLinkLevel();
	void breakLinkLevel();
	Edge* makeLink(Hash_node*& node1, Hash_node*& node2, Color color);
	void changeLink(Hash_node*& node1, Hash_node*& node2, Color color);

	// Anime maker

	void MakeInsertAnime(int data, SceneNode*& Nodes, vector <Hash_node*>& org, int key,int cnt);
	void MakeDeleteAnime(int data, SceneNode*& Nodes, vector <Hash_node*>& org, int key,int cnt);
	void MakeSearchAnime(int data, SceneNode*& Nodes, vector <Hash_node*>& org, int key,int cnt);

	void print_console();

	void cleanUp();
};

