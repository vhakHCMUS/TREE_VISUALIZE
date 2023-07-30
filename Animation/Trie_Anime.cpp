#include "Trie_Anime.h"

Trie_Anime::Trie_Anime() : AnimeBase()
{

}

Trie_Anime::~Trie_Anime()
{
	cleanUp();
}

Trie_node::Trie_node(Trie_Anime* anime)
{
	isWord = false;
	data = (char)'#'; 

	for (int i = 0; i < N; i++) childs[i] = NULL, tVisual=NULL, Edgeid[i] = -1;
	Nodeid = -1;

	this->anime = anime;
}

void Trie_node::prepData()
{
	for (int i = 0; i < N; i++)	if (childs[i])
		{
			char c = (char)'a' + i;
			childs[i]->data = c;
			childs[i]->prepData();
		}
}

void Trie_node::printConsole(Trie_node* cur,string& S)
{	
	if (!cur) return;

	if (isWord) cout << S << endl;
	
	for (int i = 0; i < N; i++)
	{
		if (childs[i])
		{
			char c = (char)'a' + i; 
			childs[i]->data = c;

			S = S + c;
			childs[i]->printConsole(childs[i], S);
			S.pop_back();
		}
	}
}

void Trie_node::paintNode(Color color,bool HasPred)
{
	if (anime->isAnime)
	{
		if (HasPred) anime->CloneLastFrame(); else anime->MakeCurState();

		if (tVisual) tVisual->Cir.setOutlineColor(color);
	}
}

void Trie_node::paintLink(Color color, int i, bool HasPred)
{
	if (anime->isAnime)
	{
		if (HasPred) anime->CloneLastFrame(); else anime->MakeCurState();

		if (Edgeid[i]>=0 && Edgeid[i]<anime->AnimeFrameLink.back().size() && anime->AnimeFrameLink.back()[Edgeid[i]]) 
			anime->AnimeFrameLink.back()[Edgeid[i]]->line.setFillColor(color);
	}
}

// Btree

void Trie_Anime::InsTrie(Trie_node*& root,string data)
{
	if (!root) root = new Trie_node(this);
	insertTrie(root, data);
}

void Trie_Anime::insertTrie(Trie_node* root, string data)
{
	Trie_node*& pCrawl = root;

	for (int i = 0; i < data.length(); i++)
	{
		int index = data[i] - 'a';

		if (!pCrawl->childs[index]) pCrawl->childs[index] = new Trie_node(this);
		
		pCrawl->paintNode(Chosen_Color,0);
		pCrawl->paintLink(Chosen_Color,index,1);

		pCrawl = pCrawl->childs[index];
	}

	// mark last node as leaf
	pCrawl->isWord = true;
}

bool Trie_Anime::Search(Trie_node* cur, string data)
{
	Trie_node* pCrawl = root;

	for (int i = 0; i < data.length(); i++)
	{
		pCrawl->paintNode(Search_Color, 0);

		int index = data[i] - 'a';
		if (!pCrawl->childs[index]) return false;
				
		pCrawl->paintLink(Search_Color, index, 1);

		pCrawl = pCrawl->childs[index];
	}

	return (pCrawl->isWord);
}

bool Trie_Anime::isEmpty(Trie_node* root)
{
    for (int i = 0; i < N; i++) if (root->childs[i]) return false;

    return true;
}
 
Trie_node* Trie_Anime::DelTrie(Trie_node* root, string data, int depth=0)
{
    if (!root) return NULL;

	root->paintNode(Delete_Color, 0);
 
    // If last character of string is being processed
    if (depth == data.size()) 
	{
        if (root->isWord) root->isWord = false;
 
        // If given is not prefix of any other word
        if (isEmpty(root)) 
		{
            delete (root);
            root = NULL;
        }
 
        return root;
    }
 
    int index = data[depth] - 'a';
	if (root->childs[index]) root->paintLink(Delete_Color,index, 0);
    root->childs[index] = DelTrie(root->childs[index], data, depth + 1);
 
    if (isEmpty(root) && root->isWord == false) 
	{
		char c = 'a' + index; 
        delete root;
        root = NULL;
    }
 
    return root;
}

void Trie_Anime::DelAll(Trie_node* cur)
{
	if (!cur) return;

	Trie_node* tmp = cur;

	for (int i = 0; i < N; i++) if (cur->childs[i]) DelAll(cur->childs[i]);

	delete tmp;
	root = NULL;
}

int Trie_Anime::count_node(Trie_node* cur)
{
	if (!cur) return 0;

	int res = 1;

	for (auto &a : cur->childs) res += count_node(a);

	return res;
}

//draw

void Trie_Anime::drawFrame(RenderTarget& target, int id) const 
{
	if (id > -1 && AnimeFrameNode.size() > id)
	{
		for (auto &a : AnimeFrameLink[id]) if (a) target.draw(*a);

		for (auto &a : AnimeFrameNode[id]) if (a) target.draw(*a);		
	}
}

void Trie_Anime::makeTransition()
{	
	if (!isPlaying || curFrame > AnimeFrameNode.size()) return;

	for (auto &a : TransitionNode) delete a;
	for (auto &a : TransitionLink) delete a;

	TransitionNode.clear();
	TransitionLink.clear(); 

	int u = curFrame;
	int v = min(curFrame + 1, (int)AnimeFrameNode.size() - 1);

	for (int i = 0; i < n; i++) TransitionNode.push_back(InterpolateNode(AnimeFrameNode[u][i].get(), AnimeFrameNode[v][i].get(), transProgress));

	for (int i = 0; i < m; i++) TransitionLink.push_back(InterpolateEdge(AnimeFrameLink[u][i], AnimeFrameLink[v][i], transProgress));
}

//create a an empty frame
void Trie_Anime::MakeNewFrame()
{
	vector<shared_ptr<TreeNode>> tmp{};
	AnimeFrameNode.push_back(tmp);

	vector<Edge*> pmt{};
	AnimeFrameLink.push_back(pmt);
}

void Trie_Anime::PushCurNode(Trie_node*& Cur, Trie_node*& parent,string s)
{
	if (!Cur) return;

	if (parent != Cur)
	{
		Cur->level = parent->level + 1;
		if (parent == root) Cur->level++;
	}
	else Cur->level = 1;

	// go left

	string curS = ""; curS += Cur->data;
	TreeNode* tmp = new TreeNode(Type::AVL, curS, nothing);

	if (Cur->isWord) tmp->AdditionalText.setString(s);

	tmp->setPosition({ BeginPosX + NODE_DISTANCE * 2 *cnt,NODE_POS_HEAD + ((NODE_DISTANCE)*Cur->level * 1.1f) });

	shared_ptr <TreeNode> here(tmp);
	PushTreeNode(here,Cur->Nodeid);

	Cur->tVisual = here;
	cnt++;

	for (int i = 0; i < N; i++) if (Cur->childs[i])
	{
		PushCurNode(Cur->childs[i], Cur, s + Cur->childs[i]->data);
		PushCurLink(Cur->tVisual->getPosition(), Cur->childs[i]->tVisual->getPosition(),Cur->Edgeid[i]);
	}
}

void Trie_Anime::PushCurLink(Vector2f pos1, Vector2f pos2,int& id)
{
	Edge* tmp = new Edge(Type::Link, "", nothing);

	tmp->setPositionByNode(pos1, pos2);

	PushEdge(tmp, id);
}

void Trie_Anime::fillAllFrame()
{
	for (auto& a : AnimeFrameNode)
	{
		while (a.size() <= maxNodeCnt) a.push_back(NULL);

		for (int i = 0; i < maxNodeCnt; i++) if (!a[i])
			{
				TreeNode* tmp= new TreeNode(AVL, "", -1);
				tmp->Disable();
				shared_ptr <TreeNode> ttt(tmp);
				a[i] = ttt;
			}
	}
	n = maxNodeCnt;

	for (auto& a : AnimeFrameLink)
	{
		while (a.size() <= maxLinkCnt) a.push_back(NULL);

		for (int i = 0; i < maxLinkCnt; i++) if (!a[i])
		{
			Edge* tmp = new Edge(AVL,"",0);
			tmp->Disable();
			a[i] = tmp;
		}
	}
	m = maxLinkCnt;
}

void Trie_Anime::MakeCurState()
{
	MakeNewFrame(); 

	string S = "";

	int n = count_node(root);
	root->prepData();

	redoSize(n);
	BeginPosX = WINDOW_WIDTH / 2 - (NODE_DISTANCE * n);

	cnt = 0;
	PushCurNode(root, root, "");	
}

//create a display_node copy of the tree and setup
void Trie_Anime::CloneFromTree(SceneNode*& Nodes)
{
	if (n >= 40) isBig = true; else isBig = false; 

	cleanUp();
	isAnime = 1;
	MakeCurState();
}

void Trie_Anime::CloneLastFrame()
{
	MakeNewFrame(); 
	for (auto &a : AnimeFrameNode[AnimeFrameNode.size() - 2])
	{
		TreeNode* tmp = new TreeNode(noType, "", 0);
		
		if (a)
		{
			tmp->Cir = a->Cir;
			tmp->text = a->text;
			tmp->AdditionalText = a->AdditionalText;
			tmp->isDisable = a->isDisable;
			tmp->data = a->data;
		}

		shared_ptr<TreeNode> ttt(tmp);
		AnimeFrameNode.back().push_back(ttt);
	}

	for (auto &a : AnimeFrameLink[AnimeFrameLink.size() - 2])
	{
		Edge* tmp = new Edge(noType, "", 0);

		if (a)
		{
			tmp->line = a->line;
			tmp->text = a->text;
			tmp->isDisable = a->isDisable;
			tmp->data = a->data;

			tmp->pos1 = a->pos1;
			tmp->pos2 = a->pos2;
		}

		AnimeFrameLink.back().push_back(tmp);
	}
}

// Anime Making  

void Trie_Anime::MakeInsertAnime(string data, SceneNode*& Nodes)
{
	isPlaying = 1;
	isHavingAnime = 1;
	curFrame = 0;

	CloneFromTree(Nodes);

	InsTrie(root,data);

	MakeCurState();

	fillAllFrame();
}

void Trie_Anime::MakeDeleteAnime(string data, SceneNode*& Nodes)
{
	isPlaying = 1;
	isHavingAnime = 1;
	curFrame = 0;
	bool k = 0;

	CloneFromTree(Nodes); 

	DelTrie(root, data);  
	MakeCurState(); 

	fillAllFrame();
}

void Trie_Anime::MakeSearchAnime(string data, SceneNode*& Nodes)
{
	isPlaying = 1;
	isHavingAnime = 1;
	curFrame = 0;

	CloneFromTree(Nodes); 
	Search(root, data);
	MakeCurState();

	fillAllFrame();
}

void Trie_Anime::PushTreeNode(shared_ptr <TreeNode> &tmp, int& id)
{
	//if (id == -1) cout << "-1  cc " << endl;
	if (id == -1) id = maxNodeCnt++;
	//cout << maxNodeCnt << endl;

	while (AnimeFrameNode.back().size() <= id) AnimeFrameNode.back().push_back(NULL);

	AnimeFrameNode.back()[id] = tmp;
}

void Trie_Anime::PushEdge(Edge* tmp, int& id)
{
	if (id == -1) id = maxLinkCnt++;

	while (AnimeFrameLink.back().size() <= id) AnimeFrameLink.back().push_back(NULL);

	AnimeFrameLink.back()[id] = tmp;
}

// misc

void Trie_Anime::cleanUp()
{
	CurAnime = none;
	for (auto& a : TransitionNode) delete a;
	for (auto& a : TransitionLink) delete a;

	TransitionNode.clear();
	TransitionLink.clear();

	for (auto& a : AnimeFrameNode) a.clear();
	for (auto& a : AnimeFrameLink) for (auto& b : a) delete b;

	AnimeFrameNode.clear();
	AnimeFrameLink.clear();

	//n = 0;
	//m = 0;

	curFrame = 0;
	transProgress = 0;

	BeginPosX = 0;

	isAnime = 0;
}
