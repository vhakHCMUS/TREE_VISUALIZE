#pragma once

#include <SFML/Graphics.hpp>
#include "SceneNode.h";

using namespace sf;

class Edge : public SceneNode // inherits  SceneNode
{
public:
	explicit Edge(Type type,string text,int data);
	virtual void drawCurrent(RenderTarget& target, RenderStates states) const ;
	virtual void updateCurrent(Event& event, Vector2f& MousePos);

	Vector2f pos1 = { 0,0 };
	Vector2f pos2 = { 0,0 };
	float angle = 0;

	void make(const Vector2f& pos,const Vector2f& size,const double& angle);

	void setPositionByNode(const Vector2f pos1, const Vector2f pos2);

	int data = 0;

	RectangleShape line;
	Text text;
private:
	Type mType;
	Sprite mSprite;

	
};

