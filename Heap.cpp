#include "Heap.h"

Heap_node* Heap::new_node(int data)
{
	Heap_node* tmp = new Heap_node;

	tmp->data = data;
	return tmp;
}

Heap::Heap() : Tree()
{
	btnSearch->FirstText = "Get Top";
	btnSearch->text.setString(btnSearch->FirstText);

	txtSearch->shape.setScale({ 0,0 });
	txtSearch->text.setCharacterSize(0);

	txtSearch->btn_cofirm->shape.setPosition(btnSearch->shape.getPosition() + Vector2f(btnSearch->shape.getSize().x+OUTLINE_THICKNESS * 5, 0));
	txtSearch->btn_cofirm->shape.setSize(btnSearch->shape.getSize()-Vector2f(60,0));

	txtSearch->btn_cofirm->text.setPosition(txtSearch->btn_cofirm->shape.getPosition().x + txtSearch->btn_cofirm->shape.getSize().x / 2.f - txtSearch->btn_cofirm->text.getGlobalBounds().width / 2.f
		, txtSearch->btn_cofirm->shape.getPosition().y + txtSearch->btn_cofirm->shape.getSize().y / 2.f - txtSearch->btn_cofirm->text.getGlobalBounds().height / 2.f);

	btnChangeHeap = new Button({WINDOW_WIDTH-40-100.f,40.f+1}, {40.f,100.f}, "Max Heap", pink,grey, red, black, TextAlign::Middle);
	btnChangeHeap->SecondText = "Min Heap";

	btnChangeHeap->PushToObject(btnChangeHeap, Buttones);

	anime = new Heap_Anime();

	PushAnime(anime);

	srand(time(NULL));
}

Heap::~Heap()
{

	DelAll();
}

void Heap::Disable()
{
	if (isDisable) return;

	Obliterate();
	anime->cleanUp();

	isDisable = true;
}

void Heap::Able()
{
	if (!isDisable) return;

	Forge(rand() % 5 + 8);

	isDisable = false;
}

void Heap::Forge(int n)
{
	cout << "Randomizing" << endl;

	DelAll();

	for (int i = 0; i < n; i++)
	{
		int a = rand() % 70 + 10;
		insertT(a);
	}

	CreateVisual(0);
	print_console();

	btnFunctionHub->ForceOff();
}

void Heap::Obliterate()
{
	DestroyVisual();
	DelAll();
}

void Heap::CreateVisual(int Forced)
{
	DestroyVisual();

	int n = cnt;
	cout << "size " << n << endl;

	if (Forced > 0)
	{
		redoSize(Forced);
		if (checkSizeDiff(n,Forced)) BeginPosX = WINDOW_WIDTH / 2 - (NODE_DISTANCE * Forced);
	}
	else
	{
		redoSize(n);
		BeginPosX = WINDOW_WIDTH / 2 - (NODE_DISTANCE * n);
	}

	if (NodeVector.empty()) return;

	int pos = 0;
	
	Push(1, pos, true);

	for (int i = 0; i < cnt; i++) Nodes->attachChild(NodeVector[i]->tVisual);

}

void Heap::DestroyVisual()
{
	Nodes->Children.clear();
	Linkes->Children.clear();
}

int Heap::count_node()
{
	return cnt;
}

void Heap::Push(int id, int& pos, bool isLeft)
{
	if (id>cnt) return;

	Heap_node* Cur = NodeVector[id - 1];
	
	if (id>1) Cur->level = NodeVector[id/2-1]->level + 1;
	else Cur->level = 1;

	Cur->isLeft = isLeft;

	// go left
	if (id*2<=cnt) Push(id*2, pos, true);

	TreeNode* tmp = new TreeNode(Type::AVL, "", Cur->data);
	string s = to_string(id); 
	tmp->AdditionalText.setString(s);

	tmp->setPosition({ BeginPosX + NODE_DISTANCE * 2 * pos,NODE_POS_HEAD + ((NODE_DISTANCE)*Cur->level) });

	shared_ptr <TreeNode> here(tmp);

	// Vector dataing

	Cur->tVisual = here;
	pos++;

	// go right
	if (id*2+1 <= cnt)	Push(id*2+1, pos, false);

	if (id*2 <= cnt) PushLink(Cur, NodeVector[id*2-1]);
	if (id*2+1 <= cnt) PushLink(Cur, NodeVector[id*2]);

	return;
}

void Heap::PushLink(Heap_node*& node1, Heap_node*& node2)
{
	Edge* tmp = new Edge(Type::Link, "", nothing);

	tmp->setPositionByNode(node1->tVisual->getPosition(), node2->tVisual->getPosition());

	shared_ptr <Edge> here(tmp);
	Linkes->attachChild(here);
}

void Heap::PushAnime(Heap_Anime*& anime1)
{
	shared_ptr <SceneNode> here(anime1);
	Animes->attachChild(here);
}

void Heap::updateCurrent(Event& event, Vector2f& MousePos)
{
	if (txtCreateSize->data != nothing)
	{
		int data = txtCreateSize->getIntdata();
		if (data<0 || data > 50) return;
		Forge(data);
	}else
		if (btnCreateRandom->isPressed()) Forge(rand() % 5 + 10); else 
			if (btnCreateLoad->isPressed())
	{
		ifstream fin("dataForLoad/Heap.in");
		int a;
		cout << "Loading..." << endl;

		DelAll();

		while (fin >> a) insertT(a);

		CreateVisual(0);
		print_console();

		btnFunctionHub->ForceOff();
	} else
		{
			if (txtDelete->data != nothing) // delete
			{				
				cout << "delete " << endl;

				int data = txtDelete->getIntdata();
				if (data<1 || data>cnt) return;

				if (NodeVector.size()) anime->MakeDeleteAnime(data, Nodes, NodeVector, cnt);

				Del(data);
			
				CreateVisual(0);

				btnFunctionHub->ForceOff();
			}
			else
				if (txtInsert->data != nothing) // delete
				{
					cout << "Insert " << endl;

					int data = txtInsert->getIntdata();

					if (NodeVector.size()) anime->MakeInsertAnime(data, Nodes, NodeVector, cnt);
		
					insertT(data); 

					CreateVisual(0);		

					btnFunctionHub->ForceOff();
				}
				else
					if (txtSearch->btn_cofirm->isPressed()) // delete
					{
						cout << "Search " << endl;

						int data = txtSearch->getIntdata();

						if (NodeVector.size()) anime->MakeSearchAnime(Nodes, NodeVector, cnt);

						Search(); 
						CreateVisual(0);

						btnFunctionHub->ForceOff();
					}
		}

	if (btnChangeHeap->isPressed())
	{
		anime->isMaxHeap = btnChangeHeap->isOn ? 0 : 1;

		Forge(rand() % 5 + 10);
	}
}

void Heap::takeTimeCurrent(Time& dt)
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

Heap_node* Heap::insertT(int data)
{
	Heap_node* cur = new_node(data);
	cur->vectorPos = cnt;
	cnt++;
	
	NodeVector.push_back(cur);
	
	int id = cnt;

	while (id>1)
	{
		int par = id / 2 - 1;

		//if (NodeVector[par]->data < NodeVector[id-1]->data) swap(NodeVector[par]->data, NodeVector[id-1]->data); else break;
		if (anime->compare(NodeVector[id - 1],NodeVector[par])) swap(NodeVector[par]->data, NodeVector[id - 1]->data); else break;

		id = id / 2;
	}	
	
	return cur;

}

void Heap::print_console(int id, string prefix, bool isLeft)
{
	if (id > cnt) return; 

	if (isLeft) cout << "|--"; else cout << "`--";

	Heap_node* cur = NodeVector[id-1];

	cout << cur->data << endl;

	if ((id*2)<=cnt) cout << "   " + prefix;
	print_console(id*2, (id*2+1)<=cnt ? prefix + "|  " : prefix + "   ", 1);

	if ((id*2+1)<=cnt) cout << "   " + prefix;
	print_console(id*2+1, prefix + "   ", 0);
}

void Heap::print_console()
{
	if (!NodeVector.empty()) print_console(1, "", 1);
}

Heap_node* Heap::Del(int id)
{
	if (id > cnt) return NULL;
	
	NodeVector[id-1]->data = NodeVector[0]->data + 1;

	while (id > 1)
	{
		int par = id / 2 - 1; 

		swap(NodeVector[par]->data, NodeVector[id - 1]->data); 

		id = id / 2;
	}

	NodeVector[0]->data = NodeVector.back()->data; 

	cnt--;
	delete NodeVector.back();
	NodeVector.pop_back(); 

	id = 1; 

	while (id * 2 <= cnt)
	{
		int next = id * 2 - 1;

		//if (id * 2 < cnt && NodeVector[id * 2]->data > NodeVector[next]->data) next=id*2;
		if (id * 2 < cnt && anime->compare(NodeVector[id * 2],NodeVector[next])) next = id * 2;

		//if (NodeVector[next]->data > NodeVector[id - 1]->data) swap(NodeVector[next]->data, NodeVector[id - 1]->data);
		if (anime->compare(NodeVector[next],NodeVector[id - 1])) swap(NodeVector[next]->data, NodeVector[id - 1]->data);
		else break;
		
		id = next+1;
	}

	return NULL;
}

Heap_node* Heap::Search()
{
	Heap_node* cur = NodeVector[0];

	return cur;
}

void Heap::DelAll()
{
	cnt=0;

	while (!NodeVector.empty())
	{
		delete NodeVector.back();
		NodeVector.pop_back();
	}
}