#include "AnimeBase.h"
#include "../Tools/SceneNode.h"
#include "../Tools/TreeNode.h"
#include "../Tools/Edge.h"

#pragma once
using namespace std;

struct Heap_node
{
	int data = nothing;
	int level = 1;

	bool isLeft = 1;

	int vectorPos = -1;

	shared_ptr <TreeNode> tVisual = NULL;
};

class Heap_Anime : public AnimeBase
{
public:

	Heap_Anime();
	virtual ~Heap_Anime();

	vector<Heap_node*> NodeVectorFirst;

	int cnt = 0;

	//vector <[N][N]>

	//Functions

	bool compare(Heap_node* a, Heap_node* b);

	bool isMaxHeap = 1;

	void copyFirstTree(vector <Heap_node*>& org);

	void CloneFromTree(SceneNode*& Nodes);

	void makeLinkLevel(int id);
	void breakLinkLevel();
	Edge* makeLink(Heap_node*& node1, Heap_node*& node2, Color color);
	void changeLink(Heap_node*& node1, Heap_node*& node2, Color color);

	// Anime maker

	void MakeInsertAnime(int data, SceneNode*& Nodes, vector <Heap_node*>& org, int n);
	void MakeDeleteAnime(int data, SceneNode*& Nodes, vector <Heap_node*>& org, int n);
	void MakeSearchAnime(SceneNode*& Nodes, vector <Heap_node*>& org, int n);

	void print_console(int id, string prefix, bool isLeft);

	void ReposAfter(int id,int& nt,int level,bool isLeft);

	void cleanUp();
};

