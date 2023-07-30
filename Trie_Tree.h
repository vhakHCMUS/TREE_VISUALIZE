#pragma once

#include <iostream>
#include <string>
#include "Tools/Tree.h"
#include "Animation/Trie_Anime.h"

using namespace std;

struct Trie_Tree : public Tree
{
	Trie_Tree();
	virtual ~Trie_Tree();

	Trie_Anime* anime;

	bool is;
	float BeginPosX = 0;

	string TrieString[41] = { "apple","apricot","apex","apostle","appliance","apricot","aperture","apathy","appendix","applause","apex","appetite","apparel",
		"apostrophe","apple","apricot","appendage","apricot","apprehend","apparatus","apathy","apostle","apartment","apple","apex","apostrophe",
		"appetite","aperture","appliance","apathy","apple","apricot","apex","apostle","appliance","apricot","aperture","apathy","appendix","applause","batman"};


	// Inheritance

	virtual void updateCurrent(Event& event, Vector2f& MousePos);
	virtual void takeTimeCurrent(Time& dt);

	void Disable() override;
	void Able() override;

	//function

	int count_node(Trie_node* cur);

	void CreateVisual(int Forced);
	void DestroyVisual();

	void Push(Trie_node*& Cur, Trie_node*& parent,string s);
	void PushLink(Trie_node*& node1, Trie_node*& node2);
	void PushAnime(Trie_Anime*& anime1);

	void Obliterate();
	void Forge(int n);
};
