#pragma once

#include <iostream>
#include <string>
#include "Tools/Tree.h"
#include "Animation/Heap_Anime.h"

using namespace std;

struct Heap : public Tree
{
	//using Tree::Tree;
	Heap();
	virtual ~Heap();

	Heap_Anime* anime;

	float BeginPosX = 0;

	// update btn cmmmdume
	Button* btnChangeHeap;

	// Inheritance

	virtual void updateCurrent(Event& event, Vector2f& MousePos);
	virtual void takeTimeCurrent(Time& dt);

	void Disable() override;
	void Able() override;

	//function

	void CreateVisual(int Forced);
	void DestroyVisual();

	void Push(int id, int& pos, bool isLeft);
	void PushLink(Heap_node*& node1, Heap_node*& node2);
	void PushAnime(Heap_Anime*& anime1);

	void Obliterate();
	void Forge(int n);

	//actual tree

	int cnt = 0;

	vector <Heap_node*> NodeVector;

	Heap_node* new_node(int data);

	int count_node();

	Heap_node* insertT(int data);

	void print_console(int id, string prefix, bool isLeft);

	void print_console();

	Heap_node* Del(int id);

	Heap_node* Search();

	void DelAll();
};
