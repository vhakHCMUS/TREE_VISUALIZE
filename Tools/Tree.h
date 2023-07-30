#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include "TreeNode.h"
#include "Edge.h"
#include "SceneNode.h"
#include "Button.h"
#include "GUIGroup.h"
#include "TextBox.h"

using namespace std;

struct Tree : public SceneNode
{
	Tree();
	virtual ~Tree();

	SceneNode* Buttones;
	SceneNode* Linkes;
	SceneNode* Nodes;
	SceneNode* Animes;

	//?? testing zone
	
	//Button* btnTest;

	//??
	
	Button* btnFunctionHub;

	
	GUIGroup* FunctionGroup;

	GUIGroup* CreateGroup;
	GUIGroup* InsertGroup;
	GUIGroup* DeleteGroup;
	GUIGroup* SearchGroup;


	Button* btnCreate;

	TextBox* txtCreateSize;
	Button* btnCreateRandom;
	Button* btnCreateLoad;

	Button* btnInsert;
	Button* btnDelete;
	Button* btnSearch;

	TextBox* txtDelete;
	TextBox* txtInsert;
	TextBox* txtSearch;

	float BeginPosX=0;

	//void Push(BST_node* &Cur,int& cnt,BST_node* &,bool isLeft);
	//void PushLink(BST_node*& node1, BST_node*& node2);

	//void PushToObject(SceneNode* tmp, SceneNode* Father);

	SceneNode* ButtonTranslate(Button* &btn);
	SceneNode* TextBoxTranslate(TextBox* &txt);
	SceneNode* GroupTranslate(GUIGroup* &grp);

	int cnt=0;
};
