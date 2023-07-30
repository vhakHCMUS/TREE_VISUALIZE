#include "GUIGroup.h"

void GUIGroup::FatherBtn(Button*& Father)
{
	this->Father = Father;
}

void GUIGroup::adopt(Button* Btn, SceneNode* Txt)
{
	House.push_back(make_pair(Btn, Txt));
}

void GUIGroup::updateCurrent(Event& event, Vector2f& MousePos)
{
	// update BTN_STATEs

	if (Father)
	{
		for (auto a : House)
			if (!Father->isOn)
			{
				a.ff->ForceOff();
				a.ff->Able();
				if (a.ss) a.ss->Able();
			}
			else
			{
				a.ff->Able();
				if (a.ss) a.ss->Able();
			}

		if (!Father->isOn) return;

		for (auto a : House)
		{
			if (a.ff->isPressed())
			{
				bool wasOn = a.ff->isOn;
				for (auto b : House) b.ff->ForceOff();
				if (wasOn) a.ff->ForceOn();
				break;
			}
		}
	}
	else
		for (auto a : House)
		{
			if (a.ff->isPressed())
			{
				for (auto b : House) b.ff->ForceOff();
				a.ff->ForceOn();
				break;
			}
		}

}