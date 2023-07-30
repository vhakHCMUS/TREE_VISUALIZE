#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <windows.h>
#include <iostream>
#include "Core/Global.h"
#include "SceneNode.h"
#include "StyleEditor.h"
#include "Button.h"
#include "GUIGroup.h"

using namespace sf;
using namespace std;
using namespace Colors;
using namespace ResourceManager;

class StyleEditor : public SceneNode
{
private:


public:
    // Override the drawCurrent function from SceneNode
    virtual void drawCurrent(RenderTarget& target, RenderStates states) const  override;
    virtual void updateCurrent(Event& event, Vector2f& MousePos) override;

public:
    //attribute

    RectangleShape ColorBox;
    /*RectangleShape SizeBox;*/

    // StyleEditor text

    Text ColorText;
    //Text SizeText;

    //constructor

    StyleEditor();
    ~StyleEditor() noexcept {};

    //stuff

    Button* btnRed;
    Button* btnYellow;
    Button* btnCyan;
    Button* btnOrange;
    Button* btnPink;
    Button* btnGrey;
    Button* btnBlue;
    Button* btnGreen;
    Button* btnBlack;
    Button* btnPurple;

    vector <Button*> ColBtn;

    Button* btnCurrent;

    Button* btnChosenNode;
    Button* btnInsertNode;
    Button* btnDeleteNode;
    Button* btnSearchNode;
    Button* btnDefaultNode;

    /*Button* btnBig;
    Button* btnSmall;*/

    GUIGroup* ColorGroup;
    /*GUIGroup* SizeGroup;*/

    Color* CurColor=&Chosen_Color;
};

