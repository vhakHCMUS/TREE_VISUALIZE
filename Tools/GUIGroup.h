#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <windows.h>
#include <iostream>
#include "Core/Global.h"
#include "SceneNode.h"
#include "Button.h"
#include "TextBox.h"

class GUIGroup : public SceneNode
{
private:
    
    //attribute

public:
    // Override the drawCurrent function from SceneNode
    //virtual void drawCurrent(RenderTarget& target, RenderStates states) const  override;
    virtual void updateCurrent(Event& event, Vector2f& MousePos) override;

public:

    // Button home

    Button* Father=NULL;

    vector <pair<Button*, SceneNode*>> House;

    //constructor

    //Accessors

    //Function

    void FatherBtn(Button* &Father);
    void adopt(Button* Btn, SceneNode* Txt) ;
};

