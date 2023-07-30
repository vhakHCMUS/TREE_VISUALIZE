#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Button.h"
#include "SceneNode.h"

using namespace std;
using namespace sf;

class TextBox : public SceneNode
{    
       public:

        string input_text;
        string default_S,current_S;
        Text text;

        int data=nothing;
        string dataText = nothingText;
        
        states box_Stat;
        short unsigned isHover = 0;

        bool canText=0;

        //constructor

        TextBox(Vector2f pos, Vector2f size, string text,string btnText, Color idleColor, Color hoverColor, Color activeColor,Color borderColor, Color textColor, Vector2f btnDiff,Vector2f btnSize,int textLim,TextAlign textAlign);

        //destructor
        virtual~TextBox();

        //Function

        int getIntdata();
        string getTextdata();

public:
    // Override the drawCurrent function from SceneNode
        virtual void drawCurrent(RenderTarget& target, RenderStates states) const  override;
        virtual void updateCurrent(Event& event, Vector2f& MousePos) override;
        virtual void takeTimeCurrent(Time& dt) override;

        void outputRecal();

        void confirm(string& s);

        // position &size
        Vector2f pos;
        Vector2f size;

        //accessor
        
        Button* btn_cofirm;
        bool isToggle = 0;

        RenderTarget* target;
        RectangleShape shape;

   private:
        

        //attribute

        Font font;
        Color idleColor;
        Color hoverColor;
        Color activeColor;
        Color borderColor;
        Color textColor;
        float height = TEXTBOX_SIZE.x;
        float width = TEXTBOX_SIZE.y;

        int textLim=0;

        //event & clock
        

        Event* event;

        Clock clock;

        sf::Time text_effect_time;
        bool show_cursor;

        // input accept?

        bool isNeg = 0;
        bool TextGet = 0;
        bool is_number(string& s);

        bool is_text(string& s);

        string output_text;
};

