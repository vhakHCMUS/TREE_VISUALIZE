#include "Trie_Tree.h"

Trie_Tree::Trie_Tree() : Tree()
{
	txtInsert->canText = 1;
	txtDelete->canText = 1;
	txtSearch->canText = 1;

	anime = new Trie_Anime();

	PushAnime(anime);

	srand(time(NULL));
}

Trie_Tree::~Trie_Tree()
{

	anime->DelAll(anime->root);
}

void Trie_Tree::Disable()
{
	if (isDisable) return;

	Obliterate();
	anime->cleanUp();

	isDisable = true;
}

void Trie_Tree::Able()
{
	if (!isDisable) return;

	Forge(rand() % 3+1);

	isDisable = false;
}

void Trie_Tree::Forge(int n)
{
	cout << "Randomizing " << n << endl;

	anime->DelAll(anime->root); 

	for (int i = 0; i < n; i++)
	{
		int a = rand() % 41; 

		anime->InsTrie(anime->root,TrieString[a]);
	}
	
	CreateVisual(0);
	
	btnFunctionHub->ForceOff();
}

void Trie_Tree::Obliterate()
{
	DestroyVisual(); 
	anime->DelAll(anime->root); 
}

void Trie_Tree::CreateVisual(int Forced)
{
	DestroyVisual();

	anime->NodeVector.clear(); 

	if (!anime->root) return;

	string S = ""; 

	int n = count_node(anime->root);

	if (!n) return;
	anime->root->printConsole(anime->root, S);

	redoSize(n);
	BeginPosX = WINDOW_WIDTH / 2 - (NODE_DISTANCE * n);
	
	cnt = 0;
	anime->maxNodeCnt = anime->maxLinkCnt = 0;
	Push(anime->root, anime->root,"");
}

void Trie_Tree::DestroyVisual()
{
	Nodes->Children.clear();
	Linkes->Children.clear();
}

void Trie_Tree::Push(Trie_node*& Cur, Trie_node*& parent,string s)
{
	if (!Cur) return;

	if (parent != Cur)
	{
		Cur->level = parent->level + 1;
		if (parent == anime->root) Cur->level++;
	}
	else Cur->level = 1;

	// go left

	string curS = "";curS+= Cur->data; 
	TreeNode* tmp = new TreeNode(Type::AVL, curS, nothing);

	if (Cur->isWord) tmp->AdditionalText.setString(s);

	tmp->setPosition({ BeginPosX + NODE_DISTANCE*2 * anime->maxNodeCnt,NODE_POS_HEAD + ((NODE_DISTANCE)*Cur->level*1.1f) });

	shared_ptr <TreeNode> here(tmp);
	Nodes->attachChild(here);

	Cur->Nodeid = anime->maxNodeCnt++;
	Cur->tVisual = here;
	cnt++;

	for (int i = 0; i < N; i++) if (Cur->childs[i])
	{
		Push(Cur->childs[i],Cur,s + Cur->childs[i]->data);
		PushLink(Cur, Cur->childs[i]);
		Cur->Edgeid[i] = anime->maxLinkCnt++;
	}
}

void Trie_Tree::PushLink(Trie_node*& node1, Trie_node*& node2)
{
	Edge* tmp = new Edge(Type::Link, "", nothing);

	tmp->setPositionByNode(node1->tVisual->getPosition(), node2->tVisual->getPosition());

	shared_ptr <Edge> here(tmp);
	Linkes->attachChild(here);
}

void Trie_Tree::PushAnime(Trie_Anime*& anime1)
{
	shared_ptr <SceneNode> here(anime1);
	Animes->attachChild(here);
}

void Trie_Tree::updateCurrent(Event& event, Vector2f& MousePos)
{
	if (txtCreateSize->data != nothing)
	{
		int data = txtCreateSize->getIntdata();
		if (data<0 || data > 15) return;
		Forge(data);
	}else
		if (btnCreateRandom->isPressed()) Forge(rand() % 3 + 2); else 
			if (btnCreateLoad->isPressed())
	{
		ifstream fin("dataForLoad/Trie_Tree.in");
		string a;
		cout << "Loading..." << endl;

		anime->DelAll(anime->root);

		while (fin >> a) anime->InsTrie(anime->root,a);

		CreateVisual(0);

		btnFunctionHub->ForceOff();
	} else
				//if (anime->root)
		{
			if (txtDelete->dataText != nothingText) // delete
			{
				cout << "delete " << endl;

				string data = txtDelete->getTextdata();

				anime->MakeDeleteAnime(data, Nodes);
				
				CreateVisual(0);

				btnFunctionHub->ForceOff();
			}
			else
				if (txtInsert->dataText != nothingText) // delete
				{
					cout << "Insert " << endl;

					string data = txtInsert->getTextdata();

					anime->MakeInsertAnime(data,Nodes);

					CreateVisual(0);

					btnFunctionHub->ForceOff();
				}
				else
					if (txtSearch->dataText != nothingText) // Search
					{
						cout << "Search " << endl;

						string data = txtSearch->getTextdata();

						anime->MakeSearchAnime(data, Nodes);

						CreateVisual(0);

						btnFunctionHub->ForceOff();
					}
		}
}

int Trie_Tree::count_node(Trie_node* cur)
{
	if (!cur) return 0;

	int cnt = 1;

	for (int i = 0; i < N; i++) if (cur->childs[i])
		cnt+=count_node(cur->childs[i]);

	return cnt;
}

void Trie_Tree::takeTimeCurrent(Time& dt)
{
	if (anime->isHavingAnime)
	{
		Nodes->Disable();
		Linkes->Disable();
	}
	else
	{
		Nodes->Able();
		Linkes->Able();
	}
}