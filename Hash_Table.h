#pragma once

#include <iostream>
#include <string>
#include "Tools/Tree.h"
#include "Animation/Hash_Anime.h"

using namespace std;

struct Hash_Table : public Tree
{
	//using Tree::Tree;
	Hash_Table();
	virtual ~Hash_Table();

	Hash_Anime* anime;

	bool is;
	float BeginPosX = 0;

	// update btn cmmmdume

	// Inheritance

	virtual void updateCurrent(Event& event, Vector2f& MousePos);
	virtual void takeTimeCurrent(Time& dt);

	void Disable() override;
	void Able() override;

	//function

	void CreateVisual(int Forced);
	void DestroyVisual();

	void PushLink(Hash_node*& node1, Hash_node*& node2);
	void PushAnime(Hash_Anime*& anime1);

	void Obliterate();
	void Forge(int n);

	//actual tree

	int cnt = 0;

	vector <Hash_node*> NodeVector;

	Hash_node* new_node(int data);

	int Hash(int data);

	void insertT(int data);

	void print_console();

	void Del(int data);

	int count_node();

	Hash_node* Search(int data);

	void DelAll();
};
