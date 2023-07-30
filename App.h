#pragma once

#include "SFML/Graphics.hpp"
#include "Tools/Button.h"
#include "Tools/GUIGroup.h"
#include "Tools/Core/Global.h"
#include "Tools/SceneNode.h"
#include "Tools/TreeNode.h"
#include "Tools/Edge.h"
#include "Tools/StyleEditor.h"
#include "AVL_Tree.h"
#include "Hash_Table.h"
#include "Heap.h"
#include "B_tree.h"
#include "Trie_Tree.h"
#include "Graph.h"

using namespace sf;
using namespace std;
using namespace Constants;
using namespace Colors;

class App
{
public:
	App();                     //Constructor

	virtual ~App();            // Destructor

	//Event & Window

	RenderWindow* window;
	VideoMode videoMode;
	Event event{};

	RenderStates a;

	void pollEvents();

	void update();
	void Render();
	void ProcessInput();
	void takeTime(Time dt);

	Vector2f MousePos;

	//var

	enum ScreenState { BST_Menu,AVL_Menu };

	bool isPaused = false;

	// stuff
	
	SceneNode MasterDisplay;
	AVL_Tree* mAVL;
	Hash_Table* mHash;
	Heap* mHeap;

	RectangleShape BG1;

	Button* btnMenu;
	Button* btnAVL;
	Button* btnHash;
	Button* btnHeap;

	GUIGroup* MenuGroup;
	GUIGroup* StyleGroup;

	vector <SceneNode*> dataStucture;

	// Timer
	
	Clock clock;
	Time timeSinceLastUpdate = Time::Zero;

	//
};

