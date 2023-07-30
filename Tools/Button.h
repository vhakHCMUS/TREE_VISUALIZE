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

class Button : public SceneNode
{
private:
        
    states buttonState;

    float height = BUTTON_SIZE.x;
    float width = BUTTON_SIZE.y;

public:
    // Override the drawCurrent function from SceneNode
    virtual void drawCurrent(RenderTarget& target, RenderStates states) const  override;
    virtual void updateCurrent(Event& event, Vector2f& MousePos) override;

public:
    //attribute

    Color idleColor;
    Color hoverColor;
    Color activeColor;
    Color textColor;
    Color borderColor;

    RectangleShape shape;

    // Button text

    Text text;

    string FirstText = "";
    string SecondText = "";

    Color textOnColor;
    Color OnColor;

    //constructor

    Button(Vector2f pos, Vector2f size, string text, Color idleColor, Color hoverColor, Color activeColor,Color borderColor,TextAlign textAlign);

    //Accessors
    const bool isPressed() const;
    bool isOn = false;

    Event* event;

    //Function

    void ForceOn();
    void ForceOff();

    //void update(const Vector2f mousePos, Event* event);

    //void render(RenderTarget* target);


    // position &size
    Vector2f pos;
    Vector2f size;

    void reText();
    void reColorAll(Color color);

    virtual bool isLeftClicked(Event& event, Vector2f& MousePos) override;
    virtual bool isHovered(Event& event, Vector2f& MousePos) override;
};

