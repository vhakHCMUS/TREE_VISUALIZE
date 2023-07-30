#pragma once

#include <SFML/Graphics.hpp>
#include "SceneNode.h";
#include "Edge.h"

using namespace sf;


class TreeNode : public SceneNode // inherits  SceneNode
{
public:

	explicit TreeNode(Type type,string text,int data);
	virtual void drawCurrent(RenderTarget& target, RenderStates states) const ;
	virtual void setPosition(const Vector2f& position);
	void updateCurrent(Event& event, Vector2f& MousePos) override;
	virtual Vector2f getPosition();

	void Highlight(Color color);
	void unHighlight();

	bool CanBeDrag = 0;
	bool isDraggin = 0;

	Vector2f offset;

	void make(const Vector2f& pos, const string& s);
	void setSize();

	int data = nothing;
	
	CircleShape Cir;
	Text text;
	
	Text AdditionalText;
private:
	Type mType;
	Sprite mSprite;
};

