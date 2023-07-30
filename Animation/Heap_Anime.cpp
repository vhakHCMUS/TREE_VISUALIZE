#include "Heap_Anime.h"

Heap_Anime::Heap_Anime() : AnimeBase()
{
	{	//setup code
		
		PushFakeCode("	swap(A[i], A[parent(i)]); i = parent(i)", 380);
		PushFakeCode("while ((i > 1) && (A[i] > A[parent(i)]))", 380);
		PushFakeCode("A[A.length-1] = v, i = A.length++", 380);
		PushFakeCode("insert v", 380);


		vector <CodeBox*> b;
		FakeCodes.push_back(b);

		PushFakeCode("Delete 0'th() then shifting;", 380);
		PushFakeCode("A[i] = A[1]+1; shiftup(i); ", 380);
		PushFakeCode("remove i'th node", 380);


		vector <CodeBox*> c;
		FakeCodes.push_back(c);

		PushFakeCode("return 0'th node", 380);
		PushFakeCode("get 0'th node", 380);
	}
}

Heap_Anime::~Heap_Anime()
{
	cleanUp();
}

bool Heap_Anime::compare(Heap_node* a, Heap_node* b)
{
	if (isMaxHeap) return a->data > b->data; else
		return a->data < b->data;
}

//make a vector copy of the tree before the change
void Heap_Anime::copyFirstTree(vector <Heap_node*>& org)
{
	for (auto a : org)
	{
		Heap_node* tmp = new Heap_node;
		tmp->data = a->data;
		tmp->vectorPos = a->vectorPos;
		tmp->isLeft = a->isLeft;
		NodeVectorFirst.push_back(tmp);
	}

	cout << " con 1 " << endl;
	//print_console(1,"",1);
	cout << endl;

	makeLinkLevel(1);
}

//create a display_node copy of the tree before change
void Heap_Anime::CloneFromTree(SceneNode*& Nodes)
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
		tmp->AdditionalText = treeNode->AdditionalText;

		shared_ptr<TreeNode> ttt(tmp);

		AnimeFrameNode.back().push_back(ttt);
	}
}

// make Link between node for the last frame
void Heap_Anime::makeLinkLevel(int id)
{
	if (id>cnt) return;

	Heap_node* Cur = NodeVectorFirst[id - 1];

	if (id*2<cnt && NodeVectorFirst[id*2-1]->data!=nothing)
	{
		changeLink(Cur, NodeVectorFirst[id*2 - 1], Default_Color);
		makeLinkLevel(id * 2);
	}

	if (id*2+1<cnt && NodeVectorFirst[id * 2]->data != nothing)
	{
		changeLink(Cur, NodeVectorFirst[id*2], Default_Color);
		makeLinkLevel(id * 2 + 1);
	}
}

Edge* Heap_Anime::makeLink(Heap_node*& node1, Heap_node*& node2, Color color)
{
	if (!node1 || !node2) return NULL;

	if (node1 == node2) return NULL;
	Edge* tmp = new Edge(noType, "", nothing);
	tmp->setPositionByNode(AnimeFrameNode.back()[node1->vectorPos]->getPosition(), AnimeFrameNode.back()[node2->vectorPos]->getPosition());
	tmp->line.setFillColor(color);

	return tmp;
}

void Heap_Anime::changeLink(Heap_node*& node1, Heap_node*& node2, Color color)
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

void Heap_Anime::breakLinkLevel()
{
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
	{
		if (AnimeLinkMatrix.back()[i][j]) delete AnimeLinkMatrix.back()[i][j];
		AnimeLinkMatrix.back()[i][j] = NULL;
	}
}

// Anime Making 

void Heap_Anime::MakeInsertAnime(int data, SceneNode* &Nodes, vector <Heap_node*> &org, int n)
{
	isPlaying = 1;
	isHavingAnime = 1;

	this->n = n + 1;
	n++;

	cout << "anime insert " << endl; 

	CloneFromTree(Nodes); 

	this->n = n;  
	
	TreeNode* tmp = new TreeNode(noType, "", data); 
	string s = to_string(n);
	tmp->AdditionalText.setString(s);
	shared_ptr<TreeNode> tt(tmp);

	AnimeFrameNode.back().push_back(tt);
	AnimeFrameNode.back().back()->Disable();

	if (n > 1) AnimeFrameNode.back().back()->setPosition(AnimeFrameNode.back()[n / 2 - 1]->getPosition() + Vector2f(NODE_DISTANCE * 2 * ((n & 1) ? 1 : -1), NODE_DISTANCE));
	
	cnt = n;
	copyFirstTree(org); 
	
	Heap_node* ttt = new Heap_node;
	ttt->vectorPos = n-1;
	ttt->data = data;

	NodeVectorFirst.push_back(ttt);

	CurAnime = aInsert;

	int id = n;
	cnt = n + 1;

	if (id > 1)
	{
		CloneLastFrame();
		AnimeFrameNode.back().back()->Able();
		AnimeFrameNode.back().back()->Cir.setOutlineColor(Insert_Color);
		changeLink(NodeVectorFirst[id/2 - 1], NodeVectorFirst[n - 1], Chosen_Color);
	}

	
	while (id>1)
	{
		int par = id / 2 - 1; 
		CloneLastFrame();
		AnimeFrameNode.back()[id-1]->Cir.setOutlineColor(Chosen_Color);
		AnimeFrameNode.back()[par]->Cir.setOutlineColor(Chosen_Color);

		//if (NodeVectorFirst[par]->data < NodeVectorFirst[id - 1]->data)
		if (compare(NodeVectorFirst[id - 1],NodeVectorFirst[par]))
		{
			CloneLastFrame();

			AnimeFrameNode.back()[id-1]->Cir.setOutlineColor(Insert_Color);
			AnimeFrameNode.back()[par]->Cir.setOutlineColor(Insert_Color);
			
			swap(NodeVectorFirst[par]->data, NodeVectorFirst[id - 1]->data);
			
			string s = AnimeFrameNode.back()[id-1]->text.getString();

			AnimeFrameNode.back()[id-1]->make(AnimeFrameNode.back()[id-1]->getPosition(), AnimeFrameNode.back()[par]->text.getString());
			AnimeFrameNode.back()[par]->make(AnimeFrameNode.back()[par]->getPosition(), s);
		}
		
		else break;

		CloneLastFrame();
		AnimeFrameNode.back()[id-1]->Cir.setOutlineColor(Default_Color);
		AnimeFrameNode.back()[par]->Cir.setOutlineColor(Default_Color);
		changeLink(NodeVectorFirst[par], NodeVectorFirst[id - 1], Default_Color);

		id = id / 2;
	}
	CloneLastFrame();

	BeginPosX = WINDOW_WIDTH / 2 - (NODE_DISTANCE * n);

	int pos = 0;
	ReposAfter(1, pos, 1, false); 
	makeLinkLevel(1);
	curFrame = 0;
}

void Heap_Anime::MakeDeleteAnime(int data, SceneNode* &Nodes, vector <Heap_node*> &org, int n)
{
	isPlaying = 1;
	isHavingAnime = 1;

	this->n = n ;

	cout << "anime Delete " << endl;

	CloneFromTree(Nodes); 

	this->n = n;

	cnt = n+1;
	copyFirstTree(org);
	CurAnime = aDelete;
	int id = data;

	CloneLastFrame();

	if (isMaxHeap) NodeVectorFirst[id - 1]->data = NodeVectorFirst[0]->data + 1;
	else NodeVectorFirst[id - 1]->data = NodeVectorFirst[0]->data - 1;

	if (isMaxHeap) AnimeFrameNode.back()[id - 1]->text.setString("Big");
	else AnimeFrameNode.back()[id - 1]->text.setString("Smol");

	while (id > 1)
	{
		int par = id / 2 - 1;

		//if (NodeVectorFirst[par]->data < NodeVectorFirst[id - 1]->data)
		if (compare(NodeVectorFirst[id - 1],NodeVectorFirst[par]))
		{
			CloneLastFrame();

			AnimeFrameNode.back()[id - 1]->Cir.setOutlineColor(Insert_Color);
			AnimeFrameNode.back()[par]->Cir.setOutlineColor(Insert_Color);

			swap(NodeVectorFirst[par]->data, NodeVectorFirst[id - 1]->data);

			string s = AnimeFrameNode.back()[id - 1]->text.getString();

			AnimeFrameNode.back()[id - 1]->make(AnimeFrameNode.back()[id - 1]->getPosition(), AnimeFrameNode.back()[par]->text.getString());
			AnimeFrameNode.back()[par]->make(AnimeFrameNode.back()[par]->getPosition(), s);
		}

		else break;

		CloneLastFrame();
		AnimeFrameNode.back()[id - 1]->Cir.setOutlineColor(Default_Color);
		AnimeFrameNode.back()[par]->Cir.setOutlineColor(Default_Color);
		changeLink(NodeVectorFirst[par], NodeVectorFirst[id - 1], Default_Color);

		id = id / 2;
	}

	CloneLastFrame();
	NodeVectorFirst[0]->data = NodeVectorFirst[n - 1]->data;

	AnimeFrameNode.back()[0]->data = AnimeFrameNode.back()[n - 1]->data;
	AnimeFrameNode.back()[0]->text.setString(AnimeFrameNode.back()[n-1]->text.getString());
	AnimeFrameNode.back()[n - 1]->data = nothing;
	AnimeFrameNode.back()[n - 1]->Disable();
	NodeVectorFirst.back()->data = nothing;

	if (n > 1) changeLink(NodeVectorFirst[n - 1], NodeVectorFirst[n / 2 - 1], trans);

	id = 1; 

	while (id*2 < n)
	{
		int next = id * 2 - 1;

		if (id * 2 < cnt)
		{
			CloneLastFrame();
			AnimeFrameNode.back()[id*2]->Cir.setOutlineColor(Chosen_Color);
			AnimeFrameNode.back()[id*2-1]->Cir.setOutlineColor(Chosen_Color);
			CloneLastFrame();

			//if (NodeVectorFirst[id * 2]->data > NodeVectorFirst[next]->data)
			if (compare(NodeVectorFirst[id * 2],NodeVectorFirst[next]))
			{
				next = id * 2;
				AnimeFrameNode.back()[id * 2 - 1]->Cir.setOutlineColor(Default_Color);
			}
			else
			{
				AnimeFrameNode.back()[id * 2]->Cir.setOutlineColor(Default_Color);
			}
		}

		CloneLastFrame();
		AnimeFrameNode.back()[id-1]->Cir.setOutlineColor(Chosen_Color);
		AnimeFrameNode.back()[next]->Cir.setOutlineColor(Chosen_Color);

		//if (NodeVectorFirst[next]->data > NodeVectorFirst[id - 1]->data)

		if (compare(NodeVectorFirst[next],NodeVectorFirst[id - 1]))
		{
			CloneLastFrame();
			swap(NodeVectorFirst[next]->data, NodeVectorFirst[id - 1]->data);

			string s = AnimeFrameNode.back()[next]->text.getString();
			AnimeFrameNode.back()[next]->make(AnimeFrameNode.back()[next]->getPosition(), AnimeFrameNode.back()[id-1]->text.getString());
			AnimeFrameNode.back()[id-1]->make(AnimeFrameNode.back()[id-1]->getPosition(), s);
		}
		else break;

		CloneLastFrame();
		AnimeFrameNode.back()[id - 1]->Cir.setOutlineColor(Default_Color);
		AnimeFrameNode.back()[next]->Cir.setOutlineColor(Default_Color);
		id = next+1;
	}

	/*CloneLastFrame();*/

	BeginPosX = WINDOW_WIDTH / 2 - (NODE_DISTANCE * (n-1));

	int pos = 0;
	cnt--;
	/*ReposAfter(1, pos, 1, false);
	makeLinkLevel(1);*/
	curFrame = 0;
}

void Heap_Anime::MakeSearchAnime( SceneNode* &Nodes, vector <Heap_node*> &org, int n)
{
	isPlaying = 1;
	isHavingAnime = 1;
	isPlaying = 1;
	isHavingAnime = 1;

	this->n = n;

	cout << "anime Delete " << endl;

	CloneFromTree(Nodes);

	this->n = n;

	cnt = n + 1;
	copyFirstTree(org);
	CurAnime = aSearch;

	CloneLastFrame();
	AnimeFrameNode.back()[0]->Cir.setOutlineColor(Search_Color);
}

void Heap_Anime::ReposAfter(int id, int& nt, int level, bool isLeft)
{
	if (id>n) return;

	Heap_node* cur = NodeVectorFirst[id - 1];

	cur->isLeft = isLeft;

	// go left
	ReposAfter(id*2, nt, level + 1, true);

	//reposing

	TreeNode* tmp = AnimeFrameNode.back()[cur->vectorPos].get();

	if (tmp->data != nothing)
	{
		cout << "cc " << id << endl;
		tmp->setPosition({ BeginPosX + NODE_DISTANCE * 2 * nt,NODE_POS_HEAD + ((NODE_DISTANCE)*level) });
		tmp->Cir.setOutlineColor(Default_Color);
		nt++;
	}
		

	// go right
	ReposAfter(id*2+1, nt, level + 1, false);
}

// misc

void Heap_Anime::print_console(int id, string prefix, bool isLeft)
{
	if (id > cnt) return;

	if (isLeft) cout << "|--"; else cout << "`--";

	Heap_node* cur = NodeVectorFirst[id - 1];

	cout << cur->data << endl;

	if ((id * 2) <= cnt) cout << "   " + prefix;
	print_console(id * 2, (id * 2 + 1) <= cnt ? prefix + "|  " : prefix + "   ", 1);

	if ((id * 2 + 1) <= cnt) cout << "   " + prefix;
	print_console(id * 2 + 1, prefix + "   ", 0);
}

void Heap_Anime::cleanUp()
{
	CurAnime = none;

	for (auto a : TransitionNode) delete a;
	for (auto a : TransitionLink) delete a;

	TransitionNode.clear();
	TransitionLink.clear(); 
	
	//for (auto a : NodeVectorFirst) delete a;

	NodeVectorFirst.clear(); 

	for (auto a : AnimeFrameNode) a.clear();
	for (auto a : AnimeLinkMatrix) for (auto b : a) for (auto c : b) delete c;

	AnimeFrameNode.clear();
	AnimeLinkMatrix.clear(); 

	int n = 0;
	curFrame = 0;
	transProgress = 0;

	BeginPosX = 0;
}
