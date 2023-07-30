#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <windows.h>
#include <iostream>
#include "Core/Global.h"
#include "SceneNode.h"

using namespace sf;
using namespace std;
using namespace Colors;
using namespace ResourceManager;

class CodeBox : public SceneNode
{
private:
        
    float width = BUTTON_SIZE.x;
    float height = BUTTON_SIZE.y;

public:
    // Override the drawCurrent function from SceneNode
    virtual void drawCurrent(RenderTarget& target, RenderStates states) const  override;

public:
    //attribute

    RectangleShape shape;

    Time timeCnt = sf::seconds(0.f);
    float transProgress=0;

    // CodeBox text

    Text text;

    Color onColor;
    Color idleColor;

    //constructor

    CodeBox(Vector2f pos, Vector2f size, string text, Color idleColor,Color onColor,TextAlign textAlign);

    //Accessors

    void ForceOn();
    void ForceOff();

    void rePos(float t);

    // position &size
    Vector2f pos;
    Vector2f size;

    bool isChangin = 0;
    int AnimeOP = 0;

    void takeTimeCurrent(Time& dt);
};

