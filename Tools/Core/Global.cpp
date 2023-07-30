#include "Global.h"

namespace Constants {
    int modulo = 10;

    const int T = 3;

    const double pi = 3.14159265;
    const double BASE_X = (double)(sf::VideoMode::getDesktopMode().width) ;
    const double BASE_Y = (double)(sf::VideoMode::getDesktopMode().height) ;
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);

    const int WINDOW_WIDTH = sf::VideoMode::getDesktopMode().width/3*2;
    const int WINDOW_HEIGHT = sf::VideoMode::getDesktopMode().height/3*2;

    const int font_size_small = BASE_X/90;
    const int font_size_medium = BASE_X/82 ;
    const int font_size_big = BASE_X/75 ;
    int font_size = font_size_medium;

    const sf::Vector2f LowStart = {(float) WINDOW_WIDTH / 6 * 5,(float)WINDOW_HEIGHT/ 6 * 5 };


    const float NODE_POS_HEAD=(float) 80;
    const sf::Vector2f MENU_POS_BOTTOM_LEFT = {(float) 0,(float) WINDOW_HEIGHT/4*3-21};

    const float OUTLINE_THICKNESS = (float)(2.5);
    const float BUTTON_THICKNESS = (float) 0;

    float NODE_RADIUS = 30.f;
    const float NODE_RADIUS_BIG = 30.f;
    const float NODE_RADIUS_MEDIUM = 20.f;
    const float NODE_RADIUS_SMALL = 15.f;
    const float EDGE_THICKNESS = 5.f;
    const sf::Vector2f BUTTON_SIZE = sf::Vector2f(50, 120);
    const sf::Vector2f TEXTBOX_SIZE = sf::Vector2f(50, 150);

    float NODE_DISTANCE = NODE_RADIUS * 3/2;
    const float NODE_DISTANCE_BIG = NODE_RADIUS_BIG * 3/2;
    const float NODE_DISTANCE_MEDIUM = NODE_RADIUS_MEDIUM * 3 / 2;
    const float NODE_DISTANCE_SMALL = NODE_RADIUS_SMALL* 3 / 2;


    const int nothing=-999999999;
    const std::string nothingText="-nothing";

    const sf::Time TIME_PER_ANIME_FRAME = sf::seconds(0.6f);
    const float FRAME_PER_FRAME=10;

    void loadMediumSize()
    {
        NODE_RADIUS = NODE_RADIUS_MEDIUM;
        NODE_DISTANCE = NODE_DISTANCE_MEDIUM;
        font_size = NODE_RADIUS;
    }

    void loadSmallSize()
    {
        NODE_RADIUS = NODE_RADIUS_SMALL;
        NODE_DISTANCE = NODE_DISTANCE_SMALL;
        font_size = NODE_RADIUS*100/96;
    }

    void loadBigSize()
    {
        NODE_RADIUS = NODE_RADIUS_BIG;
        NODE_DISTANCE = NODE_DISTANCE_BIG;
        font_size = NODE_RADIUS/8*7;
    }

    void redoSize(int n)
    {
        if (n < 14) loadBigSize(); else
            if (n < 20) loadMediumSize(); else
                loadSmallSize();

        if (n > 19) NODE_DISTANCE = (WINDOW_WIDTH - 100) / (2 * n);
    }

    bool checkSizeDiff(int a, int b)
    {
        if ((a == 13 && b==14) || (a == 14 && b == 13) || (a == 19 && b == 20) || (a == 20 && b == 19)) return true;

        return false;
    }
};

namespace Colors {
    sf::Color trans = sf::Color::Transparent;
    sf::Color white = sf::Color::White;
    sf::Color black = sf::Color::Black;
    sf::Color red = sf::Color::Red;
    sf::Color cyan = sf::Color::Cyan;
    sf::Color yellow = sf::Color::Yellow;
    sf::Color blue = sf::Color::Blue;
    sf::Color green = sf::Color::Green;
    sf::Color light_yellow = sf::Color(255,255,153);
    sf::Color orange = sf::Color(255, 83, 0);
    sf::Color grey = sf::Color(128,128,128);
    sf::Color light_grey = sf::Color(192, 192, 192);
    sf::Color pink = sf::Color(214, 87, 117);
    sf::Color purple = sf::Color(128, 0, 128);
    sf::Color Back_Ground_Color = white;
    sf::Color Chosen_Color = cyan;
    sf::Color Delete_Color = red;
    sf::Color Insert_Color = orange;
    sf::Color Search_Color = pink;
    sf::Color Default_Color = black;
};

namespace ResourceManager
{
    sf::Font& getFont(FontID  ID, const std::string& filename)
    {
        auto it = fonts.find(ID);

        if (it != fonts.end()) return it->second; else
        {
            sf::Font font;
            if (font.loadFromFile(filename))
            {
                fonts.emplace(ID, font);
                return fonts[ID];
            }
        }
    }

    struct FontDestructor
    {
        ~FontDestructor()
        {
            fonts.clear(); 
        }
    };

    static FontDestructor destructor; 
}
