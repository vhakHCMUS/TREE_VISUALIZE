#include "TextBox.h"

TextBox::TextBox(Vector2f pos, Vector2f size, string text, string btnText, Color idleColor, Color hoverColor, Color activeColor, Color borderColor, Color textColor, Vector2f btnDiff, Vector2f btnSize,int textLim, TextAlign textAlign)
{
	this->height = size.x ? size.x : height;
	this->width = size.y ? size.y : width;

	shape.setSize(Vector2f(this->width, this->height));
	shape.setPosition(pos);

	setPosition(pos);

	this->size = size;
	this->pos = pos;

	this->textAlign = textAlign;

	default_S = text;

	this->btn_cofirm = new Button(pos+btnDiff,btnSize, btnText, idleColor, hoverColor, activeColor, textColor,TextAlign::Middle);
	shared_ptr <Button> here(btn_cofirm);
	attachChild(here);

	box_Stat = IDLE;

	this->text.setFont(ResourceManager::getFont(ResourceManager::Arial, "asset/fonts/ArialTh.ttf"));
	this->text.setString(text);
	this->text.setCharacterSize((int)this->height / 2);
	this->text.setFillColor(textColor);

	if (this->textAlign == TextAlign::Middle)
		this->text.setPosition(this->shape.getPosition().x + this->shape.getSize().x / 2.f - this->text.getGlobalBounds().width / 2.f,
			this->shape.getPosition().y + this->shape.getSize().y / 2.f - this->text.getGlobalBounds().height / 2.f); else
				if (this->textAlign == TextAlign::Left)
					this->text.setPosition(this->shape.getPosition().x + this->shape.getSize().x / 10.f, this->shape.getPosition().y + this->shape.getSize().y / 2.f - this->text.getGlobalBounds().height / 2.f); 


	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;
	this->borderColor = borderColor;
	this->textColor = textColor;

	shape.setFillColor(idleColor);
	shape.setOutlineColor(borderColor);
	shape.setOutlineThickness(BUTTON_THICKNESS);

	target = NULL;
	this->event = event;

	data = 0;
	this->textLim = textLim;
	data = nothing;
}

TextBox::~TextBox()
{
	//delete btn_cofirm;
}

void TextBox::updateCurrent(Event& event, Vector2f& MousePos)
{
	// update Box_STATEs

	//btn_cofirm->update(MousePos,event);
	data = 0;

	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
	{
		isHover = 0;
		if (this->shape.getGlobalBounds().contains(MousePos))box_Stat = ACTIVE;
		else box_Stat = IDLE;
	}
	else if (this->shape.getGlobalBounds().contains(MousePos)) isHover = 1; else isHover = 0;

	if (box_Stat == ACTIVE || isToggle)
	{
		shape.setFillColor(activeColor);
		//text.setFillColor(idleColor);

		if (box_Stat == ACTIVE)
		{
			if (event.type == Event::TextEntered)
			{
				if (isprint(event.text.unicode) && input_text.size() < textLim)
					input_text += event.text.unicode;
			}
			else
				if (event.type == Event::KeyPressed)
				{
					if (event.key.code == Keyboard::BackSpace)
					{
						if (!input_text.empty())
							input_text.pop_back();
					}
				}
		}
	}
	else
	{
		shape.setFillColor(idleColor);
		//text.setFillColor(activeColor);
		text.setString(default_S);
		if (isHover) shape.setFillColor(hoverColor);
	}

	if (btn_cofirm->isPressed() || (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter))
		confirm(input_text); else data = nothing,dataText=nothingText;

	outputRecal();
}

void TextBox::takeTimeCurrent(Time& dt)
{
	if (box_Stat == ACTIVE)
	{
		text_effect_time += clock.restart();

		if (text_effect_time >= sf::seconds(0.5f))
		{
			show_cursor = !show_cursor;
			text_effect_time = sf::Time::Zero;
		}
		text.setString(output_text + (show_cursor ? '_' : ' '));
	}
}

void TextBox::outputRecal()
{
	if (input_text.size() > 10)
	{
		output_text = "";
		for (int i = 1; i <= 10; i++)
			output_text = input_text[input_text.size() - i] + output_text;
		output_text = "..." + output_text;
	}
	else output_text = input_text;

	if (input_text != "" || box_Stat == ACTIVE)
	{
		if (box_Stat == ACTIVE)
		{
			text_effect_time += clock.restart();

			if (text_effect_time >= sf::seconds(0.5f))
			{
				show_cursor = !show_cursor;
				text_effect_time = sf::Time::Zero;
			}
			text.setString(output_text + (show_cursor ? '_' : ' '));
		}
		else text.setString(output_text);

		this->text.setPosition(this->shape.getPosition().x + this->shape.getSize().x / 10.f,this->text.getPosition().y);
	}
	else
	{
		text.setString(default_S);
		if (this->textAlign == TextAlign::Middle)
			this->text.setPosition(this->shape.getPosition().x + this->shape.getSize().x / 2.f - this->text.getGlobalBounds().width / 2.f,
				this->shape.getPosition().y + this->shape.getSize().y / 2.f - this->text.getGlobalBounds().height / 2.f); else
			if (this->textAlign == TextAlign::Left)
				this->text.setPosition(this->shape.getPosition().x + this->shape.getSize().x / 10.f, this->shape.getPosition().y + this->shape.getSize().y / 2.f - this->text.getGlobalBounds().height / 2.f); 
	}

}

void TextBox::drawCurrent(RenderTarget& target, RenderStates states) const 
{
	target.draw(shape);
	target.draw(text);
}

int TextBox::getIntdata()
{
	if (data != nothing)
	{
		int tmp = data;
		data = nothing;
		return tmp;
	}
	else return nothing;
}

string TextBox::getTextdata()
{
	if (dataText != nothingText)
	{
		string s = dataText;
		dataText = nothingText;
		return s;
	}
	else return nothingText;
}

bool TextBox::is_number(string& s)
{
	isNeg = 0;
	if (s[0] == '-') { isNeg = 1; s.erase(s.begin(), s.begin()+1);	}

	return !s.empty() && s.size()<9 && find_if(s.begin(),	s.end(), [](unsigned char c) { return !isdigit(c); }) == s.end();
}

bool TextBox::is_text(string& s)
{
	if (s.empty() || s.size() > 12) return 0;

	for (int i = 0; i < s.size(); i++) if (s[i] < 'a' || s[i]>'z') return 0;

	return 1;
}

void TextBox::confirm(string& s)
{
	if (!canText)
	{
		data = nothing;
		if (is_number(s)) data = stoi(s) * (isNeg ? -1 : 1);
		cout << "data  " << data << endl;
	}
	else
	{
		dataText = nothingText;
		if (is_text(s)) dataText = s;
		cout << "dataTexxt  " << dataText << endl;
	}

	input_text = "";
}

