#include "Graph_Anime.h"

Graph_Anime::Graph_Anime() : AnimeBase()
{
	srand(NULL);
}

Graph_Anime::~Graph_Anime()
{
	cleanUp();
}

Graph_node::Graph_node(Graph_Anime* anime)
{
	this->anime = anime;

	data = 0;

	Nodeid = -1;

	for (int i = 0; i < anime->n; i++) childs.push_back(0),Edgeid.push_back(-1);
}

void Graph_Anime::paintNode(int id,Color color)
{
	if (isAnime)
	{
		CloneLastFrame();

		if (NodeVector[id]->tVisual) NodeVector[id]->tVisual->Cir.setOutlineColor(color);
	}
}

void Graph_Anime::paintLink(int id1,int id2,Color color)
{
	if (isAnime)
	{
		CloneLastFrame(); 

		Graph_node*& a = NodeVector[id1];

		if (a->Edgeid[id2-1]!=-1 && AnimeFrameLink.back()[a->Edgeid[id2-1]])
			AnimeFrameLink.back()[a->Edgeid[id2-1]]->line.setFillColor(color);
	}
}

// Graph

void Graph_Anime::DelAll()
{
	n = 0;
	for (auto a : NodeVector) delete a;
	NodeVector.clear();
	Visited.clear();
}

void Graph_Anime::GenerateGraph(int n)
{
	DelAll();

	this->n = n;

	maxNodeCnt = maxLinkCnt = 0; 

	for (int i = 0; i < n; i++)
	{
		NodeVector.push_back(new Graph_node(this)); 
		Visited.push_back(0);

		NodeVector[i]->data = i+1; 
		NodeVector[i]->Nodeid = i;

		if (i)
		{
			int par = (i - 1) / 2;
			if (i % 2 == 0)
			{
				if (par % 2 && par+1<i) par++; else 
				if (par % 2 == 1 && par>=0) par--;
			}

			int data = rand() % 30 + 1;

			NodeVector[i]->childs[par] = data;
			NodeVector[par]->childs[i] = data;
		}
	}

	for (int i = 0; i < n/2-1; i++)
	{
		while (1)
		{
			int a = rand() % n;
			int b = rand() % n;
			if (a == b || NodeVector[a]->childs[b]) continue;
			else
			{
				int data = rand() % 30 + 1;

				NodeVector[a]->childs[b] = data;
				NodeVector[b]->childs[a] = data;

				break;
			}
		}
	}
}

void Graph_Anime::setVis()
{
	for (int i = 0; i < n;i++) Visited[i] = 0;
}

//draw

void Graph_Anime::drawFrame(RenderTarget& target, int id) const 
{
	if (id > -1 && AnimeFrameNode.size() > id)
	{
		for (auto a : AnimeFrameLink[id]) if (a) target.draw(*a);

		for (auto a : AnimeFrameNode[id]) if (a) target.draw(*a);		
	}
}

void Graph_Anime::makeTransition()
{	
	if (!isPlaying || curFrame > AnimeFrameNode.size()) return;

	for (auto a : TransitionNode) delete a;
	for (auto a : TransitionLink) delete a;

	TransitionNode.clear();
	TransitionLink.clear(); 

	int u = curFrame;
	int v = min(curFrame + 1, (int)AnimeFrameNode.size() - 1);

	for (int i = 0; i < n; i++) TransitionNode.push_back(InterpolateNode(AnimeFrameNode[u][i].get(), AnimeFrameNode[v][i].get(), transProgress));

	for (int i = 0; i < m; i++) TransitionLink.push_back(InterpolateEdge(AnimeFrameLink[u][i], AnimeFrameLink[v][i], transProgress));
}

//create a an empty frame
void Graph_Anime::MakeNewFrame()
{
	vector<shared_ptr<TreeNode>> tmp{};
	AnimeFrameNode.push_back(tmp);

	vector<Edge*> pmt{};
	AnimeFrameLink.push_back(pmt);
}

void Graph_Anime::PushCurNode(Graph_node*& Cur, Graph_node*& parent)
{
	
}

void Graph_Anime::PushCurLink(Vector2f pos1, Vector2f pos2,int& id)
{
	Edge* tmp = new Edge(Type::Link, "", nothing);

	tmp->setPositionByNode(pos1, pos2);

	PushEdge(tmp, id);
}

void Graph_Anime::fillAllFrame()
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

//create a display_node copy of the tree and setup
void Graph_Anime::CloneFromTree(SceneNode*& Nodes, SceneNode*& Linkes)
{
	if (n >= 40) isBig = true; else isBig = false; 

	cleanUp();

	MakeNewFrame();
	
	for (auto a : Nodes->Children)
	{
		shared_ptr<TreeNode> treeNode = dynamic_pointer_cast<TreeNode>(a);

		TreeNode* tmp = new TreeNode(noType, "", 0);
		tmp->Cir = treeNode->Cir;
		tmp->text = treeNode->text;
		tmp->data = treeNode->data;
		tmp->CanBeDrag = treeNode->CanBeDrag;

		shared_ptr<TreeNode> ttt(tmp);
		AnimeFrameNode.back().push_back(ttt);
	}

	for (auto a : Linkes->Children)
	{
		shared_ptr<Edge> link = dynamic_pointer_cast<Edge>(a);

		Edge* tmp = new Edge(noType, "", 0);
		tmp->line = link->line;
		tmp->text = link->text;
		tmp->isDisable = link->isDisable;
		tmp->data = link->data;

		tmp->pos1 = link->pos1;
		tmp->pos2 = link->pos2;

		AnimeFrameLink.back().push_back(tmp);
	}
}

void Graph_Anime::CloneLastFrame()
{
	MakeNewFrame(); 
	for (auto& a : AnimeFrameNode[AnimeFrameNode.size() - 2])
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

void Graph_Anime::MakeDijsktraAnime(SceneNode* Nodes, SceneNode* Linkes,int id1, int id2)
{
	//isPlaying = 1;
	id1--; id2--;
	isHavingAnime = 1;
	isAnime = 1;
	curFrame = 0;

	vector <int> NodeCurVal;
	vector <int> LastNode;

	CloneFromTree(Nodes,Linkes);	

	for (int i = 0; i < n; i++) Visited.push_back(0), NodeCurVal.push_back(9999), LastNode.push_back(-1);

	NodeCurVal[id1] = 0;

	priority_queue<pair <int,int>,vector <pair <int,int>>,greater <pair<int,int>>> pq;

	pq.push({ NodeCurVal[id1],id1});

	while (!pq.empty())
	{
		int u = pq.top().second;
		pq.pop();

		if (Visited[u]) continue;
		Visited[u] = 1;
		
		for (int v = 0; v < n; v++) if (v!=u && NodeVector[u]->childs[v] && !Visited[v] && NodeCurVal[v]>NodeCurVal[u]+NodeVector[u]->childs[v])
		{
			NodeCurVal[v] = NodeCurVal[u] + NodeVector[u]->childs[v];
			LastNode[v] = u;
			pq.push({NodeCurVal[v] ,v});
		}
	}

	if (Visited[id2])
	{
		int cur = id2;

		//string s = to_string(NodeCurVal[cur]);
		//AnimeFrameNode.back()[NodeVector[cur]->Nodeid]->AdditionalText.setString(s);

		while (LastNode[cur]!=-1)
		{
			AnimeFrameNode.back()[NodeVector[cur]->Nodeid]->Cir.setOutlineColor(Chosen_Color);

			AnimeFrameLink.back()[NodeVector[cur]->Edgeid[LastNode[cur]]]->line.setFillColor(Chosen_Color);

			cur = LastNode[cur];
			if (LastNode[cur]==-1) break;
		}
	}

	cout << " froom " << id1+1 << " to " << id2+1 << " is " << NodeCurVal[id2] << endl;
}

void Graph_Anime::MakeMinSpanAnime(SceneNode* Nodes, SceneNode* Linkes,int id)
{
	//isPlaying = 1;
	id--; 
	isHavingAnime = 1;
	isAnime = 1;
	curFrame = 0;

	vector <int> NodeCurVal;
	vector <int> LastNode;

	CloneFromTree(Nodes, Linkes);

	for (int i = 0; i < n; i++) Visited.push_back(0), NodeCurVal.push_back(9999), LastNode.push_back(-1);

	NodeCurVal[id] = 0;

	priority_queue<pair <int, int>, vector <pair <int, int>>, greater <pair<int, int>>> pq;

	pq.push({ NodeCurVal[id],id });

	int MinSpanNum = 0;

	while (!pq.empty())
	{
		int u = pq.top().second;
		int data = pq.top().first;
		pq.pop();

		if (Visited[u]) continue;
		Visited[u] = 1;

		MinSpanNum += data;

		for (int v = 0; v < n; v++) if (v != u && NodeVector[u]->childs[v] && !Visited[v] && NodeCurVal[v] > NodeVector[u]->childs[v])
		{
			NodeCurVal[v] = NodeVector[u]->childs[v];
			LastNode[v] = u;
			pq.push({ NodeCurVal[v] ,v });
		}
	}

	

	for (int i = 0; i < n; i++) 
	{
		if (Visited[i]) AnimeFrameNode.back()[NodeVector[i]->Nodeid]->Cir.setOutlineColor(Chosen_Color);
		if (LastNode[i]!=-1) AnimeFrameLink.back()[NodeVector[i]->Edgeid[LastNode[i]]]->line.setFillColor(Chosen_Color);
	}

	cout << " mimn " << id + 1 << " is " << MinSpanNum << endl;
}

void Graph_Anime::MakeConnectedComponent(SceneNode* Nodes, SceneNode* Linkes,int id)
{
	id--;
	isHavingAnime = 1;
	isAnime = 1;
	curFrame = 0;

	CloneFromTree(Nodes, Linkes);

	for (int i = 0; i < n; i++) Visited.push_back(0);

	queue<int> q;

	q.push(id);

	while (!q.empty())
	{
		int u = q.front();
		q.pop();

		if (Visited[u]) continue;
		Visited[u] = 1;

		for (int v = 0; v < n; v++) if (v != u && NodeVector[u]->childs[v] && !Visited[v])	q.push(v);
	}

	for (int i = 0; i < n; i++) if (Visited[i])
	{
		AnimeFrameNode.back()[NodeVector[i]->Nodeid]->Cir.setOutlineColor(Chosen_Color);

		//for (int j=0;i<n;j++) if (NodeVector[i]->Edgeid[j]>-1) AnimeFrameLink.back()[NodeVector[i]->Edgeid[j]]->line.setFillColor(Chosen_Color);
	}

	cout << " con " << id + 1 << " is " << endl;
}

void Graph_Anime::PushTreeNode(shared_ptr <TreeNode> &tmp, int& id)
{
	if (id == -1) id = maxNodeCnt++;

	while (AnimeFrameNode.back().size() <= id) AnimeFrameNode.back().push_back(NULL);

	AnimeFrameNode.back()[id] = tmp;
}

void Graph_Anime::PushEdge(Edge* tmp, int& id)
{
	if (id == -1) id = maxLinkCnt++;

	while (AnimeFrameLink.back().size() <= id) AnimeFrameLink.back().push_back(NULL);	

	AnimeFrameLink.back()[id] = tmp;
}

// misc

void Graph_Anime::cleanUp()
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
	Visited.clear();

	curFrame = 0;
	transProgress = 0;

	BeginPosX = 0;

	isAnime = 0;
}
