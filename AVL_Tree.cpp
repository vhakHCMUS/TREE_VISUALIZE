#include "AVL_Tree.h"

AVL_node* AVL_Tree::new_node(int data)
{
	AVL_node* tmp = new AVL_node;

	tmp->data = data;
	tmp->height = 1;
	return tmp;
}

AVL_Tree::AVL_Tree() : Tree()
{
	txtUpdate = new TextBox(txtDelete->pos + Vector2f(txtDelete->size.y + txtDelete->btn_cofirm->size.y + OUTLINE_THICKNESS * 10, 0), btnDelete->size, "Replace with", "Go", cyan, black, black, black, white, { -50,0 }, { 40,40 }, 10, TextAlign::Middle);
	PushToObject(txtUpdate, btnDelete);

	DeleteGroup->adopt( txtUpdate->btn_cofirm,txtUpdate);

	anime = new AVL_Anime();

	PushAnime(anime);

	srand(time(NULL));
}

AVL_Tree::~AVL_Tree()
{

	DelAll(root);
	/*delete Buttones;
	delete TextBoxes;
	delete Linkes;
	delete Nodes;

	delete btnCreate;
	delete butt2;
	delete txtDelete;*/
}

void AVL_Tree::Disable()
{
	if (isDisable) return;

	Obliterate();
	anime->cleanUp();

	isDisable = true;
}

void AVL_Tree::Able()
{
	if (!isDisable) return;

	Forge(rand() % 5 + 8);

	isDisable = false;
}

void AVL_Tree::Forge(int n)
{
	cout << "Randomizing" << endl;

	DelAll(root);

	for (int i = 0; i < n; i++)
	{
		int a = rand() % 70 + 10;
		root=insertT(root, a, root, true);
	}
	CreateVisual(0);
	print_console();

	btnFunctionHub->ForceOff();
}

void AVL_Tree::Obliterate()
{
	DestroyVisual();
	DelAll(root);
}

void AVL_Tree::CreateVisual(int Forced)
{
	DestroyVisual();

	NodeVector.clear();

	int n = count_node(root);
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

	cnt = 0;

	if (!root) return;
	Push(root, cnt, root, true);
}

void AVL_Tree::DestroyVisual()
{
	Nodes->Children.clear();
	Linkes->Children.clear();
}

int AVL_Tree::count_node(AVL_node* cur)
{
	if (!cur) return 0;

	int res = (1 + count_node(cur->left) + count_node(cur->right));

	return res;
}

void AVL_Tree::Push(AVL_node*& Cur, int& cnt, AVL_node*& parent, bool isLeft)
{
	if (!Cur) return;

	if (parent != Cur)
	{
		Cur->par = parent;
		Cur->level = parent->level + 1;
	}
	else
	{
		Cur->par = NULL;
		Cur->level = 1;
	}

	Cur->isLeft = isLeft;

	// go left
	if (Cur->left) Push(Cur->left, cnt, Cur, true);

	TreeNode* tmp = new TreeNode(Type::AVL, "", Cur->data);

	tmp->setPosition({ BeginPosX + NODE_DISTANCE * 2 * cnt,NODE_POS_HEAD + ((NODE_DISTANCE)*Cur->level) });

	shared_ptr <TreeNode> here(tmp);
	Nodes->attachChild(here);

	// Vector dataing

	NodeVector.push_back(Cur);
	Cur->vectorPos = NodeVector.size() - 1;
	Cur->tVisual = here;
	cnt++;

	// go right
	if (Cur->right)	Push(Cur->right, cnt, Cur, false);

	if (Cur->left) PushLink(Cur, Cur->left);
	if (Cur->right) PushLink(Cur, Cur->right);

	return;
}

void AVL_Tree::PushLink(AVL_node*& node1, AVL_node*& node2)
{
	Edge* tmp = new Edge(Type::Link, "", nothing);

	tmp->setPositionByNode(node1->tVisual->getPosition(), node2->tVisual->getPosition());

	shared_ptr <Edge> here(tmp);
	Linkes->attachChild(here);
}

void AVL_Tree::PushAnime(AVL_Anime*& anime1)
{
	shared_ptr <SceneNode> here(anime1);
	Animes->attachChild(here);
}

void AVL_Tree::updateCurrent(Event& event, Vector2f& MousePos)
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
		ifstream fin("dataForLoad/AVL_Tree.in");
		int a;
		cout << "Loading..." << endl;

		DelAll(root);

		while (fin >> a) root=insertT(root, a, root, true);

		CreateVisual(0);
		print_console();

		btnFunctionHub->ForceOff();
	} else
		{
			if (txtDelete->data != nothing) // delete
			{
				if (txtUpdate->data != nothing)
				{
					cout << "update " << endl;

					int dataDel = txtDelete->getIntdata();
					int dataAdd = txtUpdate->getIntdata();

					if (root) anime->MakeUpdateAnime(dataDel,dataAdd, Nodes, NodeVector, root->vectorPos, count_node(root));

					int cnt = count_node(root);
					root = Del(root, dataDel);

					if (cnt != count_node(root))
					{
						if (root) anime->MakeUpdateAddin(dataAdd);
						root = insertT(root, dataAdd, root, false);
					}
				}
				else
				{
					cout << "delete " << endl;

					int data = txtDelete->getIntdata();

					if (root) anime->MakeDeleteAnime(data, Nodes, NodeVector, root->vectorPos, count_node(root));

					root = Del(root, data);
				}
				CreateVisual(0);

				btnFunctionHub->ForceOff();
			}
			else
				if (txtInsert->data != nothing) // delete
				{
					cout << "Insert " << endl;

					int data = txtInsert->getIntdata();

					if (root) anime->MakeInsertAnime(data, Nodes, NodeVector, root->vectorPos, count_node(root));

					root=insertT(root, data, root, false);
					CreateVisual(0);

					btnFunctionHub->ForceOff();
				}
				else
					if (txtSearch->data != nothing) // delete
					{
						cout << "Search " << endl;

						int data = txtSearch->getIntdata();

						if (root) anime->MakeSearchAnime(data, Nodes, NodeVector, root->vectorPos, count_node(root));

						Search(root, data); cout << endl;
						CreateVisual(0);

						btnFunctionHub->ForceOff();
					}
		}
}

void AVL_Tree::takeTimeCurrent(Time& dt)
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

int AVL_Tree::height(AVL_node* cur)
{
	if (!cur) return 0;
	return cur->height;
}

void AVL_Tree::updateHeight(AVL_node* &cur)
{
	if (!cur) return;
	cur->height = max(height(cur->left), height(cur->right)) + 1;
}

AVL_node* AVL_Tree::rightRotate(AVL_node* cur)
{
	AVL_node* x=cur->left;
	AVL_node* y = x->right;
	
	cur->left = y;
	x->right = cur;

	updateHeight(cur);
	updateHeight(x);	

	return x;
}

AVL_node* AVL_Tree::leftRotate(AVL_node* cur)
{
	AVL_node* x = cur->right;
	AVL_node* y = x->left;
	
	cur->right = y;
	x->left = cur;

	updateHeight(cur);
	updateHeight(x);	

	return x;
}

int AVL_Tree::GetBalance(AVL_node* cur)
{
	if (!cur) return 0;
	return height(cur->right) - height(cur->left);
}

AVL_node* AVL_Tree::insertT(AVL_node*& cur, int data, AVL_node*& parent, bool isLeft)
{
	if (cur == NULL)
	{
		cur = new_node(data);
		if (parent != cur)
		{
			cur->par = parent;
			cur->level = parent->level + 1;
		}
		cur->isLeft = isLeft;

		return cur;
	}

	if (cur->data > data) cur->left=insertT(cur->left, data, cur, true); else
		if (cur->data < data) cur->right=insertT(cur->right, data, cur, false); else
			return cur;

	updateHeight(cur);
	int balance = GetBalance(cur);

	if (balance > 1) //cur->data
	{
		if (data > cur->right->data)
		{
			if (anime->isHavingAnime) anime->makeRotation(anime->NodeVectorFirst[anime->FirstPos], anime->NodeVectorFirst[anime->FirstPos], cur->data, Left_Left);
			return leftRotate(cur); // left left
		}
		else 
		if (data < cur->right->data) // right left 
		{
			if (anime->isHavingAnime) anime->makeRotation(anime->NodeVectorFirst[anime->FirstPos], anime->NodeVectorFirst[anime->FirstPos], cur->right->data, Right_Right);
			cur->right=rightRotate(cur->right);
			if (anime->isHavingAnime) anime->makeRotation(anime->NodeVectorFirst[anime->FirstPos], anime->NodeVectorFirst[anime->FirstPos], cur->data, Left_Left);
			return leftRotate(cur);
		}
	} else
	
	if (balance < -1)
	{
		if (data < cur->left->data)
		{
			if (anime->isHavingAnime) anime->makeRotation(anime->NodeVectorFirst[anime->FirstPos], anime->NodeVectorFirst[anime->FirstPos], cur->data, Right_Right);
			return rightRotate(cur); // right right
		}
		else
		if (data > cur->left->data)  // left right
		{
			if (anime->isHavingAnime) anime->makeRotation(anime->NodeVectorFirst[anime->FirstPos], anime->NodeVectorFirst[anime->FirstPos], cur->left->data, Left_Left);
			cur->left=leftRotate(cur->left);
			if (anime->isHavingAnime) anime->makeRotation(anime->NodeVectorFirst[anime->FirstPos], anime->NodeVectorFirst[anime->FirstPos], cur->data, Right_Right);
			return rightRotate(cur);
		}
	}

	return cur;

}

void AVL_Tree::print_console(AVL_node* cur, string prefix, bool isLeft)
{
	if (!cur) return;

	if (isLeft) cout << "|--"; else cout << "`--";

	cout << cur->data << endl;

	if (cur->left) cout << "   " + prefix;
	print_console(cur->left, cur->right ? prefix + "|  " : prefix + "   ", 1);

	if (cur->right) cout << "   " + prefix;
	print_console(cur->right, prefix + "   ", 0);
}

void AVL_Tree::print_console()
{
	print_console(root, "", 1);
}

AVL_node* AVL_Tree::Del(AVL_node*& cur, int data)
{
	if (!cur) return NULL;

	if (cur->data > data) cur->left = Del(cur->left, data); else 
		if (cur->data < data) cur->right = Del(cur->right, data); else
		{	//delete this node

			if (!cur->left && !cur->right) // delete leave node
			{
				delete cur;
				return NULL;
			} else

			if (cur->left && cur->right) // delete node that have 2 children
			{
				AVL_node* tmp = cur->left;

				while (tmp->right) tmp = tmp->right;

				cur->data = tmp->data;
				cur->left = Del(cur->left, tmp->data);
			}
			else //have one child
			{
				AVL_node* tmp = cur->left ? cur->left : cur->right;
				AVL_node* del = cur;
				cur = tmp;

				delete del;
			}
		}

	updateHeight(cur);
	int balance = GetBalance(cur);

	if (balance > 1)
	{
		if (GetBalance(cur->right) >= 0)
		{
			if (anime->isHavingAnime) anime->makeRotation(anime->NodeVectorFirst[anime->FirstPos], anime->NodeVectorFirst[anime->FirstPos], cur->data, Left_Left);
			return leftRotate(cur);
		}
		else 
		{
			if (anime->isHavingAnime) anime->makeRotation(anime->NodeVectorFirst[anime->FirstPos], anime->NodeVectorFirst[anime->FirstPos], cur->right->data, Right_Right);
			cur->right=rightRotate(cur->right);
			if (anime->isHavingAnime) anime->makeRotation(anime->NodeVectorFirst[anime->FirstPos], anime->NodeVectorFirst[anime->FirstPos], cur->data, Left_Left);
			return leftRotate(cur);
		}
	} else
		if (balance < -1)
		{
			if (GetBalance(cur->right) <= 0)
			{
				if (anime->isHavingAnime) anime->makeRotation(anime->NodeVectorFirst[anime->FirstPos], anime->NodeVectorFirst[anime->FirstPos], cur->data, Right_Right);
				return rightRotate(cur);
			}
			else
			{
				if (anime->isHavingAnime) anime->makeRotation(anime->NodeVectorFirst[anime->FirstPos], anime->NodeVectorFirst[anime->FirstPos], cur->left->data, Left_Left);
				cur->left = leftRotate(cur->left);
				if (anime->isHavingAnime) anime->makeRotation(anime->NodeVectorFirst[anime->FirstPos], anime->NodeVectorFirst[anime->FirstPos], cur->data, Right_Right);
				return rightRotate(cur);
			}
		}	

	return cur;
}

AVL_node* AVL_Tree::Search(AVL_node*& cur, int data)
{
	if (!cur) return NULL;

	//cout << cur->data << "-> ";

	if (cur->data > data) return Search(cur->left, data);
	if (cur->data < data) return Search(cur->right, data);

	return cur;
}

void AVL_Tree::DelAll(AVL_node* cur)
{
	if (!cur) return;

	AVL_node* tmp = cur;

	DelAll(cur->left);
	DelAll(cur->right);

	delete tmp;
	root = NULL;
}