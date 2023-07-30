#pragma once

#include <iostream>
#include <string>
#include "Tools/Tree.h"
#include "Animation/Graph_Anime.h"

using namespace std;

struct Graphs : public Tree
{
	Graphs();
	virtual ~Graphs();

	TextBox* txtUpdate;

	Graph_Anime* anime;

	bool is;
	float BeginPosX = 0;

	// Inheritance

	virtual void updateCurrent(Event& event, Vector2f& MousePos);
	virtual void takeTimeCurrent(Time& dt);

	void Disable() override;
	void Able() override;

	//function

	void CreateVisual(int Forced);
	void DestroyVisual();

	void Push(int id);
	void PushLink(Vector2f pos1, Vector2f pos2,int data);
	void PushAnime(Graph_Anime*& anime1);

	void Obliterate();
	void Forge(int n);
};
