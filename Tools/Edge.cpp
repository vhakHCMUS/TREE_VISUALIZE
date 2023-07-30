#include "Edge.h"

Edge::Edge(Type type, string text,int data)
{
	line.setFillColor(Default_Color);
	line.setSize({ EDGE_THICKNESS,1 });
	line.setOrigin(Vector2f((float) 2.5, 0));
	line.setPosition(-100, -100);

	this->data = data;

	if (this->data != nothing)
	{
		string s = to_string(this->data);
		text = s;
	}

	this->text.setFont(ResourceManager::getFont(ResourceManager::Arial, "asset/fonts/ArialTh.ttf"));
	this->text.setCharacterSize(font_size);
	this->text.setFillColor(trans);
	this->text.setString(text);
	this->text.setPosition(line.getPosition().x + line.getSize().x / 2.f - this->text.getGlobalBounds().width / 2.f,
		line.getPosition().y + line.getSize().y / 2.f - this->text.getGlobalBounds().height / 2.f);

	mType = type;
}

void Edge::drawCurrent(RenderTarget& target, RenderStates states) const 
{
	target.draw(line);
	target.draw(text);
}

void Edge::updateCurrent(Event& event, Vector2f& MousePos) 
{
	//line.setPosition(Parent->getPosition());
}

void Edge::setPositionByNode(const Vector2f pos1, const Vector2f pos2) 
{
	Vector2f size(EDGE_THICKNESS, sqrt(pow(pos2.x - pos1.x, 2) + pow(pos2.y - pos1.y, 2)));
	Vector2f position = pos1;
	double angle = atan((pos2.x - pos1.x) / (pos2.y - pos1.y)) * 180 / acos(-1);
	this->pos1 = pos1;
	this->pos2 = pos2;
	this->angle = angle;

	make(position, size, -angle);
}

void Edge::make(const Vector2f& pos, const Vector2f& size, const double& angle) 
{
	line.setSize(size);
	line.setPosition(pos);
	line.setRotation(angle);
	this->angle = angle;

	if (abs(pos1.x - pos2.x)>abs((pos1.y - pos2.y)))
	text.setPosition((pos1.x+pos2.x)/2 - this->text.getGlobalBounds().width / 2.f, (pos1.y + pos2.y) / 2 - this->text.getGlobalBounds().height * 1.5);
	else
		text.setPosition((pos1.x + pos2.x) / 2 - this->text.getGlobalBounds().width*2, (pos1.y + pos2.y) / 2 - this->text.getGlobalBounds().height);
}