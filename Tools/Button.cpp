#include "Button.h"

Button::Button(Vector2f pos, Vector2f size, string text, Color idleColor, Color hoverColor, Color activeColor,Color borderColor,TextAlign textAlign)
{
	this->height = size.x ? size.x : height;
	this->width = size.y ? size.y : width;

	shape.setSize(Vector2f(this->width, this->height));
	shape.setPosition(pos);

	setPosition(pos);

	this->textAlign = textAlign;

	this->size = { height, width};

	this->pos = pos;

	FirstText = text;

	this->text.setFont(ResourceManager::getFont(ResourceManager::Arial,"asset/fonts/ArialTh.ttf"));
	this->text.setString(text);
	this->text.setCharacterSize(min((int) this->height/2, (int)this->width/ 5*4));
	this->text.setFillColor(white);

	if (this->textAlign==TextAlign::Middle)
	this->text.setPosition(this->shape.getPosition().x + this->shape.getSize().x / 2.f - this->text.getGlobalBounds().width/2.f
		,this->shape.getPosition().y + this->shape.getSize().y / 2.f - this->text.getGlobalBounds().height/2.f); else
		if (this->textAlign == TextAlign::Left)
			this->text.setPosition(this->shape.getPosition().x + this->shape.getSize().x / 10.f , this->shape.getPosition().y + this->shape.getSize().y / 2.f - this->text.getGlobalBounds().height / 2.f); 

	buttonState = IDLE;

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;
	this->borderColor = borderColor;
	this->textColor = white;
	this->textOnColor = white;

	shape.setFillColor(idleColor);
	shape.setOutlineColor(borderColor);
	shape.setOutlineThickness(BUTTON_THICKNESS);

	this->event = event;
}

const bool Button::isPressed() const
{
	if (this->buttonState == PRESSED)
	{
		//Sleep(5);
		return 1;
	}
	return 0;
}

void Button::ForceOn()
{
	isOn = 1;
}

void Button::ForceOff()
{
	isOn = 0;
}

void Button::updateCurrent(Event& event, Vector2f& MousePos) 
{
	// update BTN_STATEs

	buttonState = IDLE;

	if (this->shape.getGlobalBounds().contains(MousePos))
	{
		if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) this->buttonState = PRESSED;
		else if (this->buttonState != PRESSED || event.mouseButton.button == Event::MouseButtonReleased) this->buttonState = HOVER;
	} else 
		if (this->buttonState != PRESSED || event.mouseButton.button == Event::MouseButtonReleased) this->buttonState = IDLE;

	switch (buttonState)
	{
	case IDLE:
		shape.setFillColor(idleColor);
		//text.setFillColor(activeColor);
		break;

	case HOVER:
		shape.setFillColor(hoverColor);
		//text.setFillColor(idleColor);
		break;

	case PRESSED:
		shape.setFillColor(activeColor);
		isOn=isOn ? 0 : 1;
		//text.setFillColor(hoverColor);
		break;
	}

	reText();

	//string s = text.getString();
	//cout << s << " isON: " << isOn << endl;
}

void Button::reText()
{
	if (SecondText == "") return;
	text.setString(isOn ? SecondText : FirstText);
	//text.setFillColor(isOn ? textColor : textOnColor);

	if (this->textAlign == TextAlign::Middle)
		this->text.setPosition(this->shape.getPosition().x + this->shape.getSize().x / 2.f - this->text.getGlobalBounds().width / 2.f
			, this->shape.getPosition().y + this->shape.getSize().y / 2.f - this->text.getGlobalBounds().height / 2.f); else
		if (this->textAlign == TextAlign::Left)
			this->text.setPosition(this->shape.getPosition().x + this->shape.getSize().x / 10.f, this->shape.getPosition().y + this->shape.getSize().y / 2.f - this->text.getGlobalBounds().height / 2.f); 

}

void Button::reColorAll(Color color)
{
	this->idleColor = color;
	this->hoverColor = color;
	this->activeColor = color;

	shape.setFillColor(idleColor);
}

void Button::drawCurrent(RenderTarget& target, RenderStates states) const 
{
	target.draw(this->shape);
	target.draw(this->text);
}

bool Button::isHovered(Event& event, Vector2f& MousePos) 
{
	return (this->shape.getGlobalBounds().contains(MousePos));
}

bool Button::isLeftClicked(Event& event, Vector2f& MousePos) {
	return (isHovered(event,MousePos) && Mouse::isButtonPressed(Mouse::Left) && event.type == Event::MouseButtonPressed);
}
