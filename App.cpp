#include "App.h"

App::App()
{
	videoMode.height = WINDOW_HEIGHT;
	videoMode.width = WINDOW_WIDTH;
	ContextSettings settings;
	settings.antialiasingLevel = 10.0;

	window = new RenderWindow(videoMode, "data Visual", Style::Default, settings);

	window->setFramerateLimit(60);

	mAVL = new AVL_Tree();
	mHash = new Hash_Table();
	mHeap = new Heap();
	mTrie = new Trie_Tree();

	MasterDisplay.PushToObject(mAVL, &MasterDisplay);
	MasterDisplay.PushToObject(mHash, &MasterDisplay);
	MasterDisplay.PushToObject(mHeap, &MasterDisplay);
	MasterDisplay.PushToObject(mTrie, &MasterDisplay);

	btnMenu = new Button(Vector2f(30, 1), Vector2f(38.f, 110), "Menu", cyan, grey, cyan, black, TextAlign::Middle);
	btnMenu->SecondText = "[>"+btnMenu->FirstText+"<]";
	btnMenu->isOn = true;
	MasterDisplay.PushToObject(btnMenu, &MasterDisplay);

	btnAVL = new Button(btnMenu->pos + Vector2f(0, btnMenu->size.x + 1), btnMenu->size, "AVL tree", cyan, grey, cyan, black, TextAlign::Middle);
	btnAVL->SecondText = "[>" + btnAVL->FirstText + "<]";
	MasterDisplay.PushToObject(btnAVL, &MasterDisplay);

	btnHash = new Button(btnAVL->pos + Vector2f(0, btnAVL->size.x + 1), btnAVL->size, "Hash Table", cyan, grey, cyan, black, TextAlign::Middle);
	btnHash->SecondText = "[>" + btnHash->FirstText + "<]";
	MasterDisplay.PushToObject(btnHash, &MasterDisplay);

	btnHeap = new Button(btnHash->pos + Vector2f(0, btnHash->size.x + 1), btnAVL->size, "Heap", cyan, grey, cyan, black, TextAlign::Middle);
	btnHeap->SecondText = "[>" + btnHeap->FirstText + "<]";
	MasterDisplay.PushToObject(btnHeap, &MasterDisplay);

	btnTrie = new Button(btnHeap->pos + Vector2f(0, btnHeap->size.x + 1), btnAVL->size, "Trie", cyan, grey, cyan, black, TextAlign::Middle);
	btnTrie->SecondText = "[>" + btnTrie->FirstText + "<]";
	MasterDisplay.PushToObject(btnTrie, &MasterDisplay);

	dataStucture.push_back(mAVL);
	dataStucture.push_back(mHash);
	dataStucture.push_back(mHeap);
	dataStucture.push_back(mTrie);

	MenuGroup = new GUIGroup;
	StyleGroup = new GUIGroup;

	MenuGroup->adopt(btnMenu, NULL);
	MenuGroup->adopt(btnAVL, NULL);
	MenuGroup->adopt(btnHash, NULL);
	MenuGroup->adopt(btnHeap, NULL);
	MenuGroup->adopt(btnTrie, NULL);

	MasterDisplay.PushToObject(MenuGroup, &MasterDisplay);


	srand(time(NULL));
}

App::~App()
{
	delete window;
}

void App::pollEvents()
{
	timeSinceLastUpdate = Time::Zero;

	while (window->isOpen()) {
		
		ProcessInput();
		
		if (!isPaused)
		{
			timeSinceLastUpdate += clock.restart();

			while (timeSinceLastUpdate > TIME_PER_FRAME)
			{
				timeSinceLastUpdate -= TIME_PER_FRAME;
					//update with frame

				takeTime(TIME_PER_FRAME);
			}
		}
		
		Render();
	}
}

void App::ProcessInput()
{
	MousePos = this->window->mapPixelToCoords(Mouse::getPosition(*this->window));

	while (window->pollEvent(event))
	{
		update();

		if (event.type == Event::Closed) {
			window->close();
		}

		if (event.type == sf::Event::GainedFocus)
			isPaused = false; else
			if (event.type == sf::Event::LostFocus)
				isPaused = true;
	}
}

void App::takeTime(Time dt)
{
	MasterDisplay.takeTime(dt);
}

void App::update()
{
	MasterDisplay.update(event, MousePos);

	if (btnMenu->isOn)
	{
		for (int i = 0; i < dataStucture.size();i++) dataStucture[i]->Disable();
	}
	else if (btnAVL->isOn)
	{
		for (int i = 0; i < dataStucture.size(); i++) if (i != 0) dataStucture[i]->Disable();

		mAVL->Able();
	} 
	else if (btnHash->isOn)
	{
		for (int i = 0; i < dataStucture.size(); i++) if (i != 1) dataStucture[i]->Disable();

		mHash->Able();
	}
	else if (btnHeap->isOn)
	{
		for (int i = 0; i < dataStucture.size(); i++) if (i != 2) dataStucture[i]->Disable();

		mHeap->Able();
	}
	else if (btnTrie->isOn)
	{
		for (int i = 0; i < dataStucture.size(); i++) if (i != 3) dataStucture[i]->Disable();

		mTrie->Able();
	}
}

void App::Render()
{	
	window->clear(white);
	MasterDisplay.draw(*window, a);

	window->display();
}