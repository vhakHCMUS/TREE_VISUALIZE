#include "Hash_Anime.h"

Hash_Anime::Hash_Anime() : AnimeBase()
{
	{	//setup code

		PushFakeCode("insert key to the back of this list i", 380);
		PushFakeCode("i = key%HT.length;", 380);
		PushFakeCode("insert key", 380);


		vector <CodeBox*> b;
		FakeCodes.push_back(b);

		PushFakeCode("	if (HT[i][j] == key) remove key from list i", 380);
		PushFakeCode("for j = 0 to HT[i].length  ", 380);
		PushFakeCode("i = key%HT.length;", 380);
		PushFakeCode("remove key", 380);
		

		vector <CodeBox*> c;
		FakeCodes.push_back(c);

		PushFakeCode("return not found", 380);
		PushFakeCode("	if (HT[i][j] == key) return found at index i number j", 380);
		PushFakeCode("for j = 0 to HT[i].length ", 380);
		PushFakeCode("i = key%HT.length;", 380);
		PushFakeCode("find key id", 380);
	}
}

Hash_Anime::~Hash_Anime()
{
	cleanUp();
}

//make a vector copy of the tree before the change
void Hash_Anime::copyFirstTree(vector <Hash_node*>& org)
{
	int cnt = 0;

	for (auto a : org)
	{
		Hash_node* b = a;
		Hash_node* par = a;

		keyHole.push_back(-1);

		while (b)
		{
			Hash_node* tmp = new Hash_node;
			tmp->data = b->data;
			tmp->vectorPos = cnt;

			if (par != b) NodeVectorFirst.back()->next = tmp; else keyHole.back() = cnt;

			NodeVectorFirst.push_back(tmp);
			
			par = b;
			b = b->next;
			cnt++;
		}
	}

	for (int i = 0; i < modulo; i++)
	{
		Hash_node* tmp = new Hash_node;
		tmp->data = i;
		tmp->vectorPos = cnt;

		NodeVectorFirst.push_back(tmp);
		cnt++;
	}

	n = cnt;

	cout << " con 1 " << endl;
	print_console();
	cout << endl;

	makeLinkLevel();
}

//create a display_node copy of the tree before change
void Hash_Anime::CloneFromTree(SceneNode*& Nodes)
{
	if (n >= 20) isBig = true; else isBig = false;

	cleanUp();

	MakeNewFrame();

	for (auto a : Nodes->Children)
	{
		shared_ptr<TreeNode> treeNode = dynamic_pointer_cast<TreeNode>(a);

		TreeNode* tmp = new TreeNode(noType, "", 0);
		tmp->Cir = treeNode->Cir;
		tmp->text = treeNode->text;
		tmp->data = treeNode->data;

		shared_ptr<TreeNode> ttt(tmp);

		AnimeFrameNode.back().push_back(ttt);
	}
}

// make Link between node for the last frame
void Hash_Anime::makeLinkLevel()
{
	for (int i=0;i<modulo;i++)
	{
		if (keyHole[i] != -1)
		{
			Hash_node* b = NodeVectorFirst[keyHole[i]];
			Hash_node* par = NodeVectorFirst[keyHole[i]];
			int cnt = keyHole[i];

			while (b)
			{
				if (par != b) changeLink(NodeVectorFirst[cnt - 1], NodeVectorFirst[cnt], Default_Color);
				//else changeLink(NodeVectorFirst[NodeVectorFirst.size()-modulo+i], NodeVectorFirst[cnt], Default_Color);

				par = b;
				b = b->next;
				cnt++;
			}
		}
	}
}

Edge* Hash_Anime::makeLink(Hash_node*& node1, Hash_node*& node2, Color color)
{
	if (!node1 || !node2) return NULL;

	if (node1 == node2) return NULL;
	Edge* tmp = new Edge(noType, "", nothing);
	tmp->setPositionByNode(AnimeFrameNode.back()[node1->vectorPos]->getPosition(), AnimeFrameNode.back()[node2->vectorPos]->getPosition());
	tmp->line.setFillColor(color);

	return tmp;
}

void Hash_Anime::changeLink(Hash_node*& node1, Hash_node*& node2, Color color)
{
	if (!node1 || !node2 || node1 == node2) return;  

	Edge* tmp = AnimeLinkMatrix.back()[node1->vectorPos][node2->vectorPos]; 
	Edge* pmt = AnimeLinkMatrix.back()[node2->vectorPos][node1->vectorPos]; 

	if (tmp == NULL)
	{
		if (color == trans)
		{
			AnimeLinkMatrix.back()[node2->vectorPos][node1->vectorPos] = NULL;
			delete pmt;
		}
		else
		{
			tmp = makeLink(node1, node2, color);
			AnimeLinkMatrix.back()[node1->vectorPos][node2->vectorPos] = tmp;

			AnimeLinkMatrix.back()[node2->vectorPos][node1->vectorPos] = NULL;
			delete pmt;
		}
	}
	else
	{
		if (color == trans)
		{
			AnimeLinkMatrix.back()[node1->vectorPos][node2->vectorPos] = NULL;
			delete tmp;

			AnimeLinkMatrix.back()[node2->vectorPos][node1->vectorPos] = NULL;
			delete pmt;
		}
		else
		{
			tmp->setPositionByNode(AnimeFrameNode.back()[node1->vectorPos]->getPosition(), AnimeFrameNode.back()[node2->vectorPos]->getPosition());
			tmp->line.setFillColor(color);

			AnimeLinkMatrix.back()[node1->vectorPos][node2->vectorPos] = tmp;
		}
	}
}

void Hash_Anime::breakLinkLevel()
{
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
	{
		if (AnimeLinkMatrix.back()[i][j]) delete AnimeLinkMatrix.back()[i][j];
		AnimeLinkMatrix.back()[i][j] = NULL;
	}
}

// making anima

void Hash_Anime::MakeInsertAnime(int data, SceneNode*& Nodes, vector <Hash_node*>& org, int key,int cnt)
{
	isPlaying = 1;
	isHavingAnime = 1;

	cout << "anime insert " << endl;

	n = cnt + modulo + 1;

	CloneFromTree(Nodes);

	TreeNode* tmp = new TreeNode(noType, "", data);
	tmp->Disable();
	shared_ptr<TreeNode> tt(tmp);
	AnimeFrameNode.back().insert(AnimeFrameNode.back().end()-modulo, tt);

	copyFirstTree(org); 
	CurAnime = aInsert;

	n++;

	Hash_node* ttt = new Hash_node;
	ttt->vectorPos = NodeVectorFirst.size() - modulo;
	ttt->data = data;

	NodeVectorFirst.insert(NodeVectorFirst.end() - modulo, ttt);

	for (int i = 0; i < modulo; i++) NodeVectorFirst[n - modulo + i]->vectorPos++;

	if (keyHole[key]!=-1)
	{
		Hash_node* cur = NodeVectorFirst[keyHole[key]];
		while (cur->next) cur = cur->next;

		CloneLastFrame();
		AnimeFrameNode.back()[cur->vectorPos]->Cir.setOutlineColor(Chosen_Color);
		AnimeFrameNode.back()[n - modulo - 1]->setPosition(AnimeFrameNode.back()[cur->vectorPos]->Cir.getPosition() + Vector2f(0, NODE_DISTANCE * 1.6f));

		CloneLastFrame();
		AnimeFrameNode.back()[n - modulo-1]->Able();
		AnimeFrameNode.back()[n - modulo-1]->Cir.setOutlineColor(Insert_Color);
		changeLink(NodeVectorFirst[cur->vectorPos], NodeVectorFirst[n - modulo - 1], Chosen_Color);
	}
	else
	{
		Hash_node* cur = NodeVectorFirst[n-modulo+key];

		CloneLastFrame();
		AnimeFrameNode.back()[n-modulo+key]->Cir.setOutlineColor(Chosen_Color);
		AnimeFrameNode.back()[n - modulo - 1]->setPosition(AnimeFrameNode.back()[cur->vectorPos]->Cir.getPosition() + Vector2f(NODE_DISTANCE/2 , NODE_DISTANCE * 1.2f));

		CloneLastFrame();
		AnimeFrameNode.back()[n - modulo - 1]->Able();
		AnimeFrameNode.back()[n - modulo - 1]->Cir.setOutlineColor(Insert_Color);
		changeLink(NodeVectorFirst[cur->vectorPos], NodeVectorFirst[n - modulo - 1], Chosen_Color);
	}
}

void Hash_Anime::MakeDeleteAnime(int data, SceneNode*& Nodes, vector <Hash_node*>& org, int key, int cnt)
{
	isPlaying = 1;
	isHavingAnime = 1;

	cout << "anime Delete" << endl;

	n = cnt + modulo;

	CloneFromTree(Nodes);
	copyFirstTree(org);
	CurAnime = aDelete;

	if (keyHole[key] != -1)
	{
		Hash_node* cur = NodeVectorFirst[keyHole[key]];
		Hash_node* par = NodeVectorFirst[keyHole[key]];
		
		while (cur && cur->data!=data)
		{
			if (par != cur)
			{
				CloneLastFrame();
				changeLink(NodeVectorFirst[par->vectorPos], NodeVectorFirst[cur->vectorPos],Chosen_Color);
			}
			
			CloneLastFrame();
			AnimeFrameNode.back()[cur->vectorPos]->Cir.setOutlineColor(Chosen_Color);
			
			par = cur;
			cur = cur->next;
		}

		if (!cur) return;

		if (par != cur)
		{
			CloneLastFrame();
			changeLink(NodeVectorFirst[par->vectorPos], NodeVectorFirst[cur->vectorPos], Chosen_Color);
		}

		CloneLastFrame();
		AnimeFrameNode.back()[cur->vectorPos]->Cir.setOutlineColor(Chosen_Color);

		CloneLastFrame();
		AnimeFrameNode.back()[cur->vectorPos]->Cir.setOutlineColor(Delete_Color);

		CloneLastFrame();
		AnimeFrameNode.back()[cur->vectorPos]->Disable();
		if (cur->next) changeLink(NodeVectorFirst[cur->vectorPos], NodeVectorFirst[cur->next->vectorPos], trans);
		changeLink(NodeVectorFirst[par->vectorPos], NodeVectorFirst[cur->vectorPos], trans);

		if (par != cur)
		{
			if (cur->next) changeLink(NodeVectorFirst[par->vectorPos], NodeVectorFirst[cur->next->vectorPos], Chosen_Color);
		}

		while (cur->next)
		{
			AnimeFrameNode.back()[cur->next->vectorPos]->setPosition(AnimeFrameNode.back()[cur->next->vectorPos]->getPosition()-Vector2f(0,NODE_DISTANCE*1.6f));

			changeLink(NodeVectorFirst[cur->vectorPos], NodeVectorFirst[cur->next->vectorPos], Default_Color);
			cur = cur->next;
		}

	}
	else
	{
		Hash_node* cur = NodeVectorFirst[n - modulo + key];

		CloneLastFrame();
		AnimeFrameNode.back()[n - modulo + key]->Cir.setOutlineColor(Chosen_Color);
	}
}

void Hash_Anime::MakeSearchAnime(int data, SceneNode*& Nodes, vector <Hash_node*>& org, int key, int cnt)
{
	isPlaying = 1;
	isHavingAnime = 1;

	cout << "anime Search" << endl;

	n = cnt + modulo;

	CloneFromTree(Nodes);
	copyFirstTree(org);
	CurAnime = aSearch;

	if (keyHole[key] != -1)
	{
		Hash_node* cur = NodeVectorFirst[keyHole[key]];
		Hash_node* par = NodeVectorFirst[keyHole[key]];

		while (cur && cur->data != data)
		{
			if (par != cur)
			{
				CloneLastFrame();
				changeLink(NodeVectorFirst[par->vectorPos], NodeVectorFirst[cur->vectorPos], Chosen_Color);
			}

			CloneLastFrame();
			AnimeFrameNode.back()[cur->vectorPos]->Cir.setOutlineColor(Chosen_Color);

			par = cur;
			cur = cur->next;
		}

		if (!cur) return;

		if (par != cur)
		{
			CloneLastFrame();
			changeLink(NodeVectorFirst[par->vectorPos], NodeVectorFirst[cur->vectorPos], Chosen_Color);
		}

		CloneLastFrame();
		AnimeFrameNode.back()[cur->vectorPos]->Cir.setOutlineColor(Chosen_Color);

		CloneLastFrame();
		AnimeFrameNode.back()[cur->vectorPos]->Cir.setOutlineColor(Search_Color);
	}
	else
	{
		Hash_node* cur = NodeVectorFirst[n - modulo + key];

		CloneLastFrame();
		AnimeFrameNode.back()[n - modulo + key]->Cir.setOutlineColor(Chosen_Color);
	}
}

// misc

void Hash_Anime::print_console()
{
	for (int i = 0; i < modulo; i++)
	{
		if (keyHole[i]!=-1)
		{
			Hash_node* b = NodeVectorFirst[keyHole[i]];

			while (b)
			{
				cout << b->data << " ";
				b = b->next;
			}
		}
		cout << endl;
	}
}

void Hash_Anime::cleanUp()
{
	CurAnime = none;

	for (auto a : TransitionNode) delete a;
	for (auto a : TransitionLink) delete a;

	TransitionNode.clear();
	TransitionLink.clear();

	for (auto a : NodeVectorFirst) delete a;

	NodeVectorFirst.clear();

	for (auto a : AnimeFrameNode) a.clear();
	for (auto a : AnimeLinkMatrix) for (auto b : a) for (auto c : b) delete c;

	AnimeFrameNode.clear();
	AnimeLinkMatrix.clear();
	AnimeNodePos.clear();
	keyHole.clear();

	int n = 0;
	int FirstPos = 0;
	int SecondPos = 0;

	curFrame = 0;
	transProgress = 0;

	BeginPosX = 0;
}
