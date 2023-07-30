#include "AnimeBase.h"
#include "../Tools/SceneNode.h"
#include "../Tools/TreeNode.h"
#include "../Tools/Edge.h"

#pragma once
const int N = 26;

class Trie_Anime;

struct Trie_node
{
	Trie_node(Trie_Anime* anime);

	int level = 0;

	char data;
	Trie_node* childs[N];

	int Edgeid[N];
	
	bool isWord = false;

	int Nodeid = -1;
	
	shared_ptr <TreeNode> tVisual;

	void printConsole(Trie_node* cur,string& S);
	void prepData();

	Trie_Anime* anime;

	// custom
	void paintNode(Color color,bool HasPred);
	void paintLink(Color color, int i, bool HasPred);
};

class Trie_Anime : public AnimeBase
{
public:

	Trie_Anime();
	virtual ~Trie_Anime();

	// shits
	int m=0;
	int cnt = 0;
	int maxNodeCnt = 0;
	int maxLinkCnt = 0;

	vector <vector <Trie_node*>> NodeVector;

	Trie_node* root = NULL;

	int count_node(Trie_node* cur);

	void insertTrie(Trie_node* root, string data);

	Trie_node* DelTrie(Trie_node* root, string data, int depth);

	void InsTrie(Trie_node*& root,string data);

	bool Search(Trie_node* cur, string data);

	void DelAll(Trie_node* cur);		

	bool isEmpty(Trie_node* root);

	//vector <[N][N]>

	void drawFrame(RenderTarget& target, int id) const override;

	void makeTransition() override;

	// TOOL for making anime

	void MakeCurState();
	void MakeNewFrame();

	void fillAllFrame();

	void CloneFromTree(SceneNode*& Nodes);
	void CloneLastFrame();

	void PushCurNode(Trie_node*& Cur, Trie_node*& parent,string s);
	void PushCurLink(Vector2f pos1, Vector2f pos2,int& id);

	void PushTreeNode(shared_ptr <TreeNode>& tmp,int& id);
	void PushEdge(Edge* tmp,int& id);

	// Anime maker

	vector <vector<Edge*>> AnimeFrameLink;

	void MakeInsertAnime(string data,SceneNode*& Nodes);
	void MakeDeleteAnime(string data, SceneNode*& Nodes);
	void MakeSearchAnime(string data, SceneNode*& Nodes);

	void cleanUp();
};

