#include "CodeBox.h"

CodeBox::CodeBox(Vector2f pos, Vector2f size, string text, Color idleColor,Color onColor,TextAlign textAlign)
{
	this->height = size.y ? size.y : height;
	this->width = size.x ? size.x : width;

	shape.setSize(Vector2f(this->width, this->height));
	shape.setPosition(pos);

	setPosition(pos);

	this->textAlign = textAlign;

	this->size = { width, height};

	this->pos = pos;

	this->text.setFont(ResourceManager::getFont(ResourceManager::Arial,"asset/fonts/ArialTh.ttf"));
	this->text.setString(text);
	this->text.setCharacterSize(min((int) this->height/2, (int)this->width/ 5*4));
	this->text.setFillColor(white);

	if (this->textAlign==TextAlign::Middle)
	this->text.setPosition(this->shape.getPosition().x + this->shape.getSize().x / 2.f - this->text.getGlobalBounds().width/2.f
		,this->shape.getPosition().y + this->shape.getSize().y / 2.f - this->text.getGlobalBounds().height/2.f); else
		if (this->textAlign == TextAlign::Left)
			this->text.setPosition(this->shape.getPosition().x + this->shape.getSize().x / 10.f , this->shape.getPosition().y + this->shape.getSize().y / 2.f - this->text.getGlobalBounds().height / 2.f); 

	shape.setFillColor(idleColor);
}

void CodeBox::ForceOn()
{
	shape.setFillColor(onColor);
	text.setFillColor(idleColor);
}

void CodeBox::ForceOff()
{
	shape.setFillColor(idleColor);
	text.setFillColor(onColor);
}

void CodeBox::rePos(float t)
{
	shape.setPosition(Vector2f(pos.x+(1-t)*size.x,pos.y));

	if (this->textAlign == TextAlign::Middle)
		this->text.setPosition(this->shape.getPosition().x + this->shape.getSize().x / 2.f - this->text.getGlobalBounds().width / 2.f
			, this->shape.getPosition().y + this->shape.getSize().y / 2.f - this->text.getGlobalBounds().height / 2.f); else
		if (this->textAlign == TextAlign::Left)
			this->text.setPosition(this->shape.getPosition().x + this->shape.getSize().x / 10.f, this->shape.getPosition().y + this->shape.getSize().y / 2.f - this->text.getGlobalBounds().height / 2.f);

}

void CodeBox::drawCurrent(RenderTarget& target, RenderStates states) const
{
	target.draw(this->shape);
	target.draw(this->text);
}

void CodeBox::takeTimeCurrent(Time& dt)
{
	if (!isChangin)
	{
		timeCnt = sf::seconds(0.f);
		return;
	}

	timeCnt += dt;

	if (timeCnt >= TIME_PER_ANIME_FRAME) isChangin=0,timeCnt -= TIME_PER_ANIME_FRAME;

	transProgress = timeCnt / TIME_PER_ANIME_FRAME;

	if (AnimeOP == 1) rePos(transProgress); else
		if (AnimeOP == -1) rePos(1 - transProgress);
}
