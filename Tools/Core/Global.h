#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#define ff first
#define ss second

#define null NULL

namespace Constants
{
    extern int modulo;
    extern const int T;

    extern const double pi;
    extern const double BASE_X;
    extern const double BASE_Y;
    extern const sf::Time TIME_PER_FRAME;
    extern const int WINDOW_WIDTH;
    extern const int WINDOW_HEIGHT;

    extern int font_size;
    extern const int font_size_small;
    extern const int font_size_medium;
    extern const int font_size_large;

    extern void loadSmallSize();
    extern void loadMediumSize();
    extern void loadBigSize();
    
    extern void redoSize(int n);
    extern bool checkSizeDiff(int a,int b);

    extern const sf::Vector2f LowStart;

    extern const sf::Vector2f MENU_POS_BOTTOM_LEFT;
    extern const float OUTLINE_THICKNESS;
    extern const float BUTTON_THICKNESS;
    extern const float NODE_POS_HEAD;

    extern float NODE_RADIUS;
    extern const float NODE_RADIUS_SMALL;
    extern const float NODE_RADIUS_MEDIUM;
    extern const float NODE_RADIUS_BIG;
    extern const float EDGE_THICKNESS;
    extern const sf::Vector2f BUTTON_SIZE;
    extern const sf::Vector2f TEXTBOX_SIZE;

    extern float NODE_DISTANCE;
    extern const float NODE_DISTANCE_BIG;
    extern const float NODE_DISTANCE_MEDIUM;
    extern const float NODE_DISTANCE_SMALL;
    extern const int nothing;
    extern const std::string nothingText;

    extern const sf::Time TIME_PER_ANIME_FRAME;
    extern const float FRAME_PER_FRAME;

    enum Type
    {
        BST, AVL, Graph, Link, noType , Left_Left, Right_Left, Right_Right, Left_Right
    };

    enum AnimeType
    {
        aInsert = 0, aDelete = 1, aSearch = 2, aUpdate = 3, none = -1
    };

    enum childType
    {
        cFirst,cSecond,cThird,cFour,cNone,sSmall,sMedium,sBig
    };

    enum states { IDLE, HOVER , PRESSED , ACTIVE};

    enum TextAlign {Left,Middle,Right};
};

namespace Colors
{
    extern sf::Color trans;
    extern sf::Color white;
    extern sf::Color black;
    extern sf::Color red;
    extern sf::Color blue;
    extern sf::Color green;
    extern sf::Color cyan;
    extern sf::Color yellow;
    extern sf::Color orange;
    extern sf::Color light_yellow;
    extern sf::Color grey;
    extern sf::Color pink;
    extern sf::Color purple;
    extern sf::Color Back_Ground_Color;
    extern sf::Color Default_Color;
    extern sf::Color Chosen_Color;
    extern sf::Color Delete_Color;
    extern sf::Color Insert_Color;
    extern sf::Color Search_Color;
};

namespace ResourceManager
{
    enum FontID { Arial };

    static std::map<FontID, sf::Font> fonts;

    sf::Font& getFont(FontID ID,const std::string& filename);

    // Add a similar namespace for textures
}
