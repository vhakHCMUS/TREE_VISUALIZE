#include "Hash_Table.h"

Hash_node* Hash_Table::new_node(int data)
{
	Hash_node* tmp = new Hash_node;

	tmp->data = data;
	return tmp;
}

Hash_Table::Hash_Table() : Tree()
{
	anime = new Hash_Anime();

	PushAnime(anime);

	srand(time(NULL));
}

Hash_Table::~Hash_Table()
{

	DelAll();
}

void Hash_Table::Disable()
{
	if (isDisable) return;

	Obliterate();
	anime->cleanUp();

	isDisable = true;
}

void Hash_Table::Able()
{
	if (!isDisable) return;

	Forge(rand() % 5 + 8); 

	isDisable = false;
}

void Hash_Table::Forge(int n)
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

void Hash_Table::Obliterate()
{
	DestroyVisual();
	DelAll();
}

void Hash_Table::CreateVisual(int Forced)
{
	DestroyVisual();

	int n = modulo;

	redoSize(n);
	BeginPosX = WINDOW_WIDTH / 2 - (NODE_DISTANCE * n);

	for (int i = 0; i < modulo; i++)
	{
		Hash_node* a = NodeVector[i];
		Hash_node* par = NodeVector[i];

		int cnt = 0;

		while (a)
		{
			TreeNode* tmp = new TreeNode(Type::AVL, "", a->data);

			tmp->setPosition({ BeginPosX + NODE_DISTANCE * 2 * i,NODE_POS_HEAD + NODE_DISTANCE*1.6f*cnt+ NODE_DISTANCE*1.2f });

			shared_ptr <TreeNode> here(tmp);
			Nodes->attachChild(here);

			a->tVisual = here;

			if (par != a) PushLink(par, a);

			par = a;
			a = a->next;
			cnt++;
		}
	}

	for (int i = 0; i < modulo; i++)
	{
		TreeNode* head = new TreeNode(Type::AVL, "", i);
		head->setPosition({ BeginPosX + NODE_DISTANCE * 2 * i - NODE_DISTANCE / 2,NODE_POS_HEAD });
		PushToObject(head, Nodes);

		if (NodeVector[i]) //connecto head
		{
			Edge* tmp = new Edge(Type::Link, "", nothing);

			tmp->setPositionByNode(head->getPosition(), NodeVector[i]->tVisual->getPosition());

			PushToObject(tmp, Linkes);
		}
	}


	cnt = 0;
}

void Hash_Table::DestroyVisual()
{
	Nodes->Children.clear();
	Linkes->Children.clear();
}

void Hash_Table::PushLink(Hash_node*& node1, Hash_node*& node2)
{
	Edge* tmp = new Edge(Type::Link, "", nothing);

	tmp->setPositionByNode(node1->tVisual->getPosition(), node2->tVisual->getPosition());

	shared_ptr <Edge> here(tmp);
	Linkes->attachChild(here);
}

void Hash_Table::PushAnime(Hash_Anime*& anime1)
{
	shared_ptr <SceneNode> here(anime1);
	Animes->attachChild(here);
}

void Hash_Table::updateCurrent(Event& event, Vector2f& MousePos)
{
	if (txtCreateSize->data != nothing)
	{
		int data = txtCreateSize->getIntdata();
		if (data<1 || data > 30) return; 

		modulo = data;

		Forge(data);
	}else
		if (btnCreateRandom->isPressed()) Forge(modulo);
		else
			if (btnCreateLoad->isPressed())
	{
		ifstream fin("dataForLoad/Hash_Table.in");
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

				anime->MakeDeleteAnime(data, Nodes, NodeVector, Hash(data), count_node());

				Del(data);
				
				CreateVisual(0);
				print_console();

				btnFunctionHub->ForceOff();
			}
			else
				if (txtInsert->data != nothing) // delete
				{
					cout << "Insert " << endl;

					int data = txtInsert->getIntdata();

					anime->MakeInsertAnime(data,Nodes,NodeVector,Hash(data),count_node());

					insertT(data);
					CreateVisual(0);
					print_console();

					btnFunctionHub->ForceOff();
				}
				else
					if (txtSearch->data != nothing) // delete
					{
						cout << "Search " << endl;

						int data = txtSearch->getIntdata();

						anime->MakeSearchAnime(data, Nodes, NodeVector, Hash(data), count_node());

						Search(data); 
						CreateVisual(0);
						print_console();

						btnFunctionHub->ForceOff();
					}
		}
}

void Hash_Table::takeTimeCurrent(Time& dt)
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

int Hash_Table::Hash(int data)
{
	return data % modulo;
}

void Hash_Table::insertT(int data)
{
	int key = Hash(data);

	Hash_node* a = NodeVector[key];

	while (a && a->next) a = a->next;

	if (a) a->next = new_node(data); else NodeVector[key] = new_node(data);
}

void Hash_Table::print_console()
{
	for (int i=0;i<modulo;i++) 
	{
		{
			Hash_node* b = NodeVector[i];

			while (b)
			{
				cout << b->data << " ";
				b = b->next;
			}
		}
		cout << endl;
	}
}
	
void Hash_Table::Del(int data)
{
	int key = Hash(data);

	Hash_node* a = NodeVector[key];
	Hash_node* par = NodeVector[key];

	while (a && a->data != data)
	{
		par = a; 
		a = a->next;
	}

	if (a)
	{
		if (a == par)
		{
			NodeVector[key] = a->next;
			delete a;
		}
		else
		{
			par->next = a->next;
			delete a;
		}
	}
	else return;
}

Hash_node* Hash_Table::Search(int data)
{
	int key = Hash(data);

	Hash_node* a = NodeVector[key];

	while (a && a->data != data) a = a->next;

	return a;
}

void Hash_Table::DelAll()
{
	for (Hash_node* &a : NodeVector)
	{
		Hash_node* b = a; 

		while (b!=NULL)
		{
			Hash_node* c = b->next;
			delete b;
			b = c;
		}

		a = NULL;
	}

	while (NodeVector.size() < modulo) NodeVector.push_back(NULL);

	while (NodeVector.size() > modulo) NodeVector.pop_back();
}

int Hash_Table::count_node()
{
	int cnt = 0;

	for (int i=0;i<modulo;i++)	if (NodeVector[i])
		{
			auto a = NodeVector[i];
			while (a)
			{
				cnt++;
				a = a->next;
			}
		}

	return cnt;
}