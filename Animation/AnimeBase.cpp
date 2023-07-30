#include "AnimeBase.h"

AnimeBase::AnimeBase() {
	btnBack = new Button(Vector2f(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT - 39), { 38,100 }, "", white, grey, white, Color::Transparent, Middle);
	btnPlay = new Button(btnBack->pos + Vector2f(btnBack->size.y + 1,0), btnBack->size, "", white, grey, white, Color::Transparent, Middle);
	btnPlay->SecondText = "";
	btnForw = new Button(btnPlay->pos + Vector2f(btnBack->size.y + 1, 0), btnBack->size, "", white, grey, white, Color::Transparent, Middle);
	btnStart = new Button(btnBack->pos - Vector2f(btnBack->size.y + 1, 0), btnBack->size, "", white, grey, white, Color::Transparent, Middle);
	btnEnd = new Button(btnForw->pos + Vector2f(btnBack->size.y + 1, 0), btnBack->size, "", white, grey, white, Color::Transparent, Middle);

	PushToObject(btnBack, this);
	PushToObject(btnForw, this);
	PushToObject(btnPlay, this);
	PushToObject(btnStart, this);
	PushToObject(btnEnd, this);

	CurAnime = none;
}

AnimeBase::~AnimeBase()
{
	cleanUp();
}

void AnimeBase::ChooseFrame(int i)
{
	if (isHavingAnime)
	{
		if ((curFrame == 0 && i == 1) ) OpenCode(1); else
			if ((curFrame == 1 && i == -1)) OpenCode(-1);
	}

	curFrame += i;
	curFrame = min((int)AnimeFrameNode.size(), max(0, curFrame));
	isPlaying = 0;
	transProgress = 0;
	timeCnt = sf::seconds(0.f);
	isHavingAnime = (curFrame < (int)AnimeFrameNode.size()) ? 1 : 0;
}

//drawin'
void AnimeBase::drawFrame(RenderTarget& target, int id) const
{
	if (id > -1 && AnimeFrameNode.size() > id)
	{
		for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
			if (AnimeLinkMatrix[id][i][j] != nullptr)
				target.draw(*AnimeLinkMatrix[id][i][j]);

		for (auto a : AnimeFrameNode[id]) target.draw(*a);
	}
	//cout << "adu " << endl;
}

void AnimeBase::drawTrans(RenderTarget& target) const
{
	for (auto a : TransitionLink) target.draw(*a);

	for (auto a : TransitionNode) target.draw(*a);
}

//create a an empty frame

void AnimeBase::MakeNewFrame()
{
	vector<shared_ptr<TreeNode>> tmp{};
	AnimeFrameNode.push_back(tmp);

	vector<vector<Edge*>> pmt{};
	AnimeLinkMatrix.push_back(pmt);

	for (int i = 0; i < n; i++)
	{
		vector<Edge*> vvv;
		AnimeLinkMatrix.back().push_back(vvv);

		for (int j = 0; j < n; j++)
			AnimeLinkMatrix.back().back().push_back(NULL);
	}
}

//create a display_node copy of the tree before change

void AnimeBase::drawCurrent(RenderTarget& target, RenderStates states) const
{
	if (!isHavingAnime || curFrame >= AnimeFrameNode.size()) ;
	else
	{
		if (!isPlaying || isBig) drawFrame(target, curFrame);
		else drawTrans(target);
	}
}

void AnimeBase::updateCurrent(Event& event, Vector2f& MousePos)
{
}

void AnimeBase::takeTimeCurrent(Time& dt)
{
	isHavingAnime = (curFrame < (int)AnimeFrameNode.size()) ? 1 : 0;

	if (!isHavingAnime) isPlaying = 0;

	if (!isPlaying)	timeCnt = sf::seconds(0.f);
	else
	{
		transProgress = timeCnt / TIME_PER_ANIME_FRAME;

		if (!isBig) makeTransition();

		timeCnt += dt;

		if (timeCnt >= TIME_PER_ANIME_FRAME) curFrame = min((int)AnimeFrameNode.size(), curFrame + 1), timeCnt -= TIME_PER_ANIME_FRAME;
	}
	
	if (isHavingAnime && CurAnime != none)
	{
		if (isPlaying)
		{
			if (curFrame == 0) OpenCode(1); else
				if (curFrame == AnimeFrameNode.size() - 1) OpenCode(-1); else
					StableCode();
		}
		//else if (curFrame >= AnimeFrameNode.size()) StableCode();

		for (auto a : FakeCodes[CurAnime])
		{
			a->rePos(1);
			a->takeTime(dt);
		}
	}
}

// the Transition

void AnimeBase::makeTransition()
{
	if (!isPlaying || curFrame > AnimeFrameNode.size()) return;

	for (auto a : TransitionNode) delete a;
	for (auto a : TransitionLink) delete a;

	TransitionNode.clear();
	TransitionLink.clear();

	int u = curFrame;
	int v = min(curFrame + 1, (int)AnimeFrameNode.size() - 1);

	for (int i = 0; i < n; i++)	TransitionNode.push_back(InterpolateNode(AnimeFrameNode[u][i].get(), AnimeFrameNode[v][i].get(), transProgress));

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			Edge* a = AnimeLinkMatrix[u][i][j] ? AnimeLinkMatrix[u][i][j] : AnimeLinkMatrix[u][j][i];
			Edge* b = AnimeLinkMatrix[v][i][j] ? AnimeLinkMatrix[v][i][j] : AnimeLinkMatrix[v][j][i];

			TransitionLink.push_back(InterpolateEdge(a, b, transProgress));
		}
	}
}

TreeNode* AnimeBase::InterpolateNode(TreeNode* a, TreeNode* b, float t)
{
	TreeNode* res = new TreeNode(noType, "", 0);

	bool noA = 0,noB = 0;
	if (!a)
	{
		a = new TreeNode(noType, "", 0);
		a->Disable(); noA = 1;
	}

	if (!b)
	{
		b = new TreeNode(noType, "", 0);
		b->Disable(); noB = 1;
	}

	res->Cir = a->Cir;
	res->text = a->text;
	res->AdditionalText = a->AdditionalText;

	int r_diff = b->Cir.getOutlineColor().r - a->Cir.getOutlineColor().r;
	int g_diff = b->Cir.getOutlineColor().g - a->Cir.getOutlineColor().g;
	int b_diff = b->Cir.getOutlineColor().b - a->Cir.getOutlineColor().b;

	int red = a->Cir.getOutlineColor().r + t * r_diff;
	int green = a->Cir.getOutlineColor().g + t * g_diff;
	int blue = a->Cir.getOutlineColor().b + t * b_diff;
	int alpha = 255;

	if (b->isDisable)
	{
		if (a->isDisable) res->Disable();
		else alpha = 255 - (255 * t);
	}
	else if (a->isDisable) alpha = 0 + 255 * t; else
	{
		float size_diff = b->Cir.getRadius() - a->Cir.getRadius();

		res->Cir.setRadius(a->Cir.getRadius()+ size_diff*t);

		int char_diff = b->text.getCharacterSize() - a->text.getCharacterSize();

		res->text.setCharacterSize((int) (a->text.getCharacterSize() + char_diff * t));
	}


	res->Cir.setOutlineColor(Color(red, green, blue, alpha));

	res->Cir.setPosition((1 - t) * a->Cir.getPosition() + t * b->Cir.getPosition());
	res->text.setPosition(res->Cir.getPosition().x - res->text.getGlobalBounds().width / 2.f, res->Cir.getPosition().y - res->text.getGlobalBounds().height / 2.f);
	res->AdditionalText.setPosition(res->Cir.getPosition().x - res->AdditionalText.getGlobalBounds().width / 2.f, res->Cir.getPosition().y - res->AdditionalText.getGlobalBounds().height / 2.f+NODE_DISTANCE*0.9f);

	if (b->Cir.getFillColor()!= a->Cir.getFillColor() || b->isDisable || a->isDisable)
	{
		r_diff = b->Cir.getFillColor().r - a->Cir.getFillColor().r;
		g_diff = b->Cir.getFillColor().g - a->Cir.getFillColor().g;
		b_diff = b->Cir.getFillColor().b - a->Cir.getFillColor().b;

		red = a->Cir.getFillColor().r + t * r_diff;
		green = a->Cir.getFillColor().g + t * g_diff;
		blue = a->Cir.getFillColor().b + t * b_diff;

		res->Cir.setFillColor(Color(red, green, blue, alpha));
	}

	if (b->text.getFillColor() != a->text.getFillColor())
	{
		r_diff = b->text.getFillColor().r - a->text.getFillColor().r;
		g_diff = b->text.getFillColor().g - a->text.getFillColor().g;
		b_diff = b->text.getFillColor().b - a->text.getFillColor().b;

		red = a->text.getFillColor().r + t * r_diff;
		green = a->text.getFillColor().g + t * g_diff;
		blue = a->Cir.getFillColor().b + t * b_diff;

		res->text.setFillColor(Color(red, green, blue, alpha));
	}

	if (noA) a = NULL, delete a;
	if (noB) b = NULL, delete b;

	return res;
}

Edge* AnimeBase::InterpolateEdge(Edge* a, Edge* b, float t)
{
	Edge* res = new Edge(noType, "", 0);

	int alpha = 255;

	if (!b)
	{
		if (!a) res->Disable();
		else
		{
			res->line = a->line;

			int r_diff = 255 - a->line.getFillColor().r;
			int g_diff = 255 - a->line.getFillColor().g;
			int b_diff = 255 - a->line.getFillColor().b;

			int red = a->line.getFillColor().r + t * r_diff;
			int green = a->line.getFillColor().g + t * g_diff;
			int blue = a->line.getFillColor().b + t * b_diff;

			alpha = 255 - (255 * t);

			res->line.setFillColor(Color(red, green, blue, alpha));
			res->setPositionByNode(a->pos1, a->pos2);
		}
	}
	else
	{
		if (!a)
		{
			int r_diff = b->line.getFillColor().r - 255;
			int g_diff = b->line.getFillColor().g - 255;
			int b_diff = b->line.getFillColor().b - 255;

			int red = 255 + t * r_diff;
			int green = 255 + t * g_diff;
			int blue = 255 + t * b_diff;

			alpha = 0 + 255 * t;

			res->line.setFillColor(Color(red, green, blue, alpha));
			res->setPositionByNode(b->pos1, b->pos2);
		}
		else
		{
			int r_diff = b->line.getFillColor().r - a->line.getFillColor().r;
			int g_diff = b->line.getFillColor().g - a->line.getFillColor().g;
			int b_diff = b->line.getFillColor().b - a->line.getFillColor().b;

			int red = a->line.getFillColor().r + t * r_diff;
			int green = a->line.getFillColor().g + t * g_diff;
			int blue = a->line.getFillColor().b + t * b_diff;
			alpha = 255;

			res->line.setFillColor(Color(red, green, blue, alpha));

			Vector2f pos1Diff = b->pos1 - a->pos1;
			Vector2f pos2Diff = b->pos2 - a->pos2;

			res->setPositionByNode(Vector2f(a->pos1.x + pos1Diff.x * t, a->pos1.y + pos1Diff.y * t), Vector2f(a->pos2.x + pos2Diff.x * t, a->pos2.y + pos2Diff.y * t));
		}
	}

	return res;
}

// misc

void AnimeBase::OpenCode(int i)
{
}

void AnimeBase::StableCode()
{
}

void AnimeBase::CloneLastFrame()
{
	MakeNewFrame();

	for (auto a : AnimeFrameNode[AnimeFrameNode.size() - 2])
	{
		TreeNode* tmp = new TreeNode(noType, "", 0);
		tmp->Cir = a->Cir;
		tmp->text = a->text;
		tmp->AdditionalText = a->AdditionalText;
		tmp->isDisable = a->isDisable;
		tmp->data = a->data;

		shared_ptr<TreeNode> ttt(tmp);
		AnimeFrameNode.back().push_back(ttt);
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			Edge* tmp = nullptr;
			if (AnimeLinkMatrix[AnimeLinkMatrix.size() - 2][i][j] != nullptr)
			{
				auto a = AnimeLinkMatrix[AnimeLinkMatrix.size() - 2][i][j];
				tmp = new Edge(noType, "", 0);

				tmp->line = a->line;
				tmp->text = a->text;
				tmp->isDisable = a->isDisable;

				tmp->pos1 = a->pos1;
				tmp->pos2 = a->pos2;
			}

			AnimeLinkMatrix.back()[i][j] = tmp;
		}
}

void AnimeBase::PushFakeCode(string s,float width)
{

}