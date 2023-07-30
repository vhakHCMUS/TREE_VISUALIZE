#include "Tree.h"

Tree::Tree()
{
	Buttones = new SceneNode();
	Linkes = new SceneNode();
	Nodes = new SceneNode();
	Animes = new SceneNode();

	FunctionGroup = new GUIGroup();

	CreateGroup = new GUIGroup();
	InsertGroup = new GUIGroup();
	DeleteGroup = new GUIGroup();
	SearchGroup = new GUIGroup();

	// testies
	//btnTest = new Button(Vector2f(21, 10), Vector2f(30.f, 110), "test", cyan, black, red, black, TextAlign::Middle);
	//PushToObject(ButtonTranslate(btnTest),Buttones);
	// testies

	btnCreate = new Button(MENU_POS_BOTTOM_LEFT + Vector2f(31, 0), Vector2f(40.f, 130.f), "Generate", cyan, black, red, black, TextAlign::Left);
	btnInsert = new Button(btnCreate->pos + Vector2f(0, btnCreate->size.x + BUTTON_THICKNESS * 2), btnCreate->size, "Insert", cyan, black, red, black, TextAlign::Left);
	btnDelete = new Button(btnInsert->pos + Vector2f(0, btnInsert->size.x + BUTTON_THICKNESS * 2), btnCreate->size, "Delete", cyan, black, red, black, TextAlign::Left);
	btnSearch = new Button(btnDelete->pos + Vector2f(0, btnDelete->size.x + BUTTON_THICKNESS * 2), btnCreate->size, "Search", cyan, black, red, black, TextAlign::Left);
	btnFunctionHub = new Button(MENU_POS_BOTTOM_LEFT, Vector2f(btnCreate->size.x*4, 30), ">", cyan, cyan, cyan+Color(30,0,0), black, TextAlign::Middle);
	btnFunctionHub->SecondText = "<";

	txtCreateSize = new TextBox(btnCreate->pos + Vector2f(btnInsert->size.y + OUTLINE_THICKNESS * 5, 0), {40.f,70.f}, "Size", "Go", cyan, black, black, black, white, {75,0}, {40,40}, 10, TextAlign::Middle);
	btnCreateRandom = new Button(btnCreate->pos + Vector2f(btnInsert->size.y + txtCreateSize->size.y + OUTLINE_THICKNESS * 8+45, 0), Vector2f(40.f, 70), "Random", cyan, black, red, black, TextAlign::Middle);
	btnCreateLoad = new Button(btnCreate->pos + Vector2f(btnInsert->size.y + btnCreateRandom->size.y * 2 + OUTLINE_THICKNESS * 10 + 47, 0), Vector2f(40.f, 70), "From File", cyan, black, red, black, TextAlign::Middle);

	txtInsert = new TextBox(btnInsert->pos + Vector2f(btnInsert->size.y + OUTLINE_THICKNESS * 5, 0), btnInsert->size, "Input", "Go", cyan, black, black, black, white, {145,0 }, { 40,40 }, 10, TextAlign::Middle);
	txtDelete = new TextBox(btnDelete->pos + Vector2f(btnDelete->size.y + OUTLINE_THICKNESS * 5, 0), btnDelete->size, "Input", "Go", cyan, black, black, black, white, {145,0 }, { 40,40 }, 10, TextAlign::Middle);
	txtSearch = new TextBox(btnSearch->pos + Vector2f(btnSearch->size.y + OUTLINE_THICKNESS * 5, 0), btnSearch->size, "Input", "Go", cyan, black, black, black, white, {145,0 }, { 40,40 }, 10, TextAlign::Middle);

	shared_ptr <SceneNode> FirstLayer(Buttones);
	shared_ptr <SceneNode> SecondLayer(Linkes);
	shared_ptr <SceneNode> ThirdLayer(Nodes);
	shared_ptr <SceneNode> FourthLayer(Animes);

	this->attachChild(FirstLayer);
	this->attachChild(SecondLayer);
	this->attachChild(ThirdLayer);
	this->attachChild(FourthLayer);

	PushToObject(TextBoxTranslate(txtCreateSize), ButtonTranslate(btnCreate));
	PushToObject(ButtonTranslate(btnCreateRandom), ButtonTranslate(btnCreate));
	PushToObject(ButtonTranslate(btnCreateLoad), ButtonTranslate(btnCreate));

	PushToObject(TextBoxTranslate(txtInsert), ButtonTranslate(btnInsert));
	PushToObject(TextBoxTranslate(txtDelete), ButtonTranslate(btnDelete));
	PushToObject(TextBoxTranslate(txtSearch), ButtonTranslate(btnSearch));
	

	PushToObject(ButtonTranslate(btnFunctionHub), Buttones);
	PushToObject(ButtonTranslate(btnCreate), Buttones);
	PushToObject(ButtonTranslate(btnInsert), Buttones);
	PushToObject(ButtonTranslate(btnDelete), Buttones);
	PushToObject(ButtonTranslate(btnSearch), Buttones);

	PushToObject(GroupTranslate(FunctionGroup), Buttones);
	PushToObject(GroupTranslate(CreateGroup), Buttones);
	PushToObject(GroupTranslate(InsertGroup), Buttones);
	PushToObject(GroupTranslate(DeleteGroup), Buttones);
	PushToObject(GroupTranslate(SearchGroup), Buttones);

	FunctionGroup->FatherBtn(btnFunctionHub);

	FunctionGroup->adopt(btnCreate, nullptr);
	FunctionGroup->adopt(btnInsert, nullptr);
	FunctionGroup->adopt(btnDelete, nullptr);
	FunctionGroup->adopt(btnSearch, nullptr);

	CreateGroup->FatherBtn(btnCreate);
	CreateGroup->adopt(txtCreateSize->btn_cofirm, txtCreateSize);
	CreateGroup->adopt(btnCreateRandom, nullptr);
	CreateGroup->adopt(btnCreateLoad, nullptr);

	DeleteGroup->FatherBtn(btnDelete);
	DeleteGroup->adopt(txtDelete->btn_cofirm,txtDelete);

	InsertGroup->FatherBtn(btnInsert);
	InsertGroup->adopt(txtInsert->btn_cofirm, txtInsert);

	SearchGroup->FatherBtn(btnSearch);
	SearchGroup->adopt(txtSearch->btn_cofirm, txtSearch);

	Disable();
}

Tree::~Tree()
{
}

//void Tree::PushToObject(SceneNode* tmp, SceneNode* Father)
//{
//	shared_ptr <SceneNode> here(tmp);
//	Father->attachChild(here);
//}

SceneNode* Tree::ButtonTranslate(Button*& btn)
{
	SceneNode* tmp = static_cast<SceneNode*>(btn);
	return tmp;
}

SceneNode* Tree::TextBoxTranslate(TextBox*& txt)
{
	SceneNode* tmp = static_cast<SceneNode*>(txt);
	return tmp;
}

SceneNode* Tree::GroupTranslate(GUIGroup*& grp)
{
	SceneNode* tmp = static_cast<SceneNode*>(grp);
	return tmp;
}
