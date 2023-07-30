#pragma once

#include <iostream>
#include <string>
#include "Tools/Tree.h"
#include "Animation/AVL_Anime.h"

using namespace std;

struct AVL_Tree : public Tree
{
	//using Tree::Tree;
	AVL_Tree();
	virtual ~AVL_Tree();

	AVL_Anime* anime;

	bool is;
	float BeginPosX = 0;

	// update btn cmmmdume
	TextBox* txtUpdate;

	// Inheritance

	virtual void updateCurrent(Event& event, Vector2f& MousePos);
	virtual void takeTimeCurrent(Time& dt);

	void Disable() override;
	void Able() override;

	//function

	void CreateVisual(int Forced);
	void DestroyVisual();

	void Push(AVL_node*& Cur, int& cnt, AVL_node*&, bool isLeft);
	void PushLink(AVL_node*& node1, AVL_node*& node2);
	void PushAnime(AVL_Anime*& anime1);

	void Obliterate();
	void Forge(int n);

	//actual tree

	int cnt = 0;

	vector <AVL_node*> NodeVector;

	AVL_node* root = NULL;

	AVL_node* new_node(int data);

	int count_node(AVL_node* cur);

	AVL_node* rightRotate(AVL_node* cur);
	AVL_node* leftRotate(AVL_node* cur);

	int height(AVL_node* cur);
	void updateHeight(AVL_node*& cur);

	int GetBalance(AVL_node* cur);


	AVL_node* insertT(AVL_node*& cur, int data, AVL_node*& parent, bool Isleft);

	void print_console(AVL_node* cur, string prefix, bool isLeft);

	void print_console();

	AVL_node* Del(AVL_node*& cur, int data);

	AVL_node* Search(AVL_node*& cur, int data);

	void DelAll(AVL_node* cur);
};
