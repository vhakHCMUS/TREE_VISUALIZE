#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Core/Global.h"


using namespace sf;
using namespace std;
using namespace Colors;
using namespace Constants;


class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
    SceneNode();

    typedef std::shared_ptr<SceneNode> Ptr;
public:

    void attachChild(Ptr child);

    Ptr detachChild(const SceneNode& node);

    //private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {};

    void update(Event& event, Vector2f& MousePos);

    virtual void updateCurrent(Event& event, Vector2f& MousePos) {};

    void takeTime(Time& dt);

    virtual void takeTimeCurrent(Time& dt) {};

    //vector<shared_ptr<SceneNode>>& getChildren();
    TextAlign textAlign = TextAlign::Middle;
    void PushToObject(SceneNode* tmp, SceneNode* Father);

public:
    vector<Ptr> Children;
    vector<childType> ChildrenType;
    SceneNode* Parent;

    bool isDisable = false;
    virtual void Disable();
    virtual void Able();

public:
    virtual void setPosition(const sf::Vector2f& position) {}
    virtual void setPositionByNode(const sf::Vector2f& position1, const sf::Vector2f& position2) {}

public:
    virtual bool isLeftClicked(Event& event, Vector2f& MousePos) { return false; }
    virtual bool isRightClicked(Event& event, Vector2f& MousePos) { return false; }
    virtual bool isHovered(Event& event, Vector2f& MousePos) { return false; }
};

