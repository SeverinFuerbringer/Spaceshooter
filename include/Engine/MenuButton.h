//////////////////////////////////////////////////
//	Copyright © Severin Fürbringer 2014
//
//	Author: Severin Fürbringer
//	Jahr:	2014
//	Datei:	MenuButton.h
//////////////////////////////////////////////////

#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include "MenuElement.h"
#include "EngineExport.h"

namespace se
{
class SEVENGINEDLL_API MenuButton : public MenuElement
{
public:
	MenuButton();
	MenuButton(se::vec2u pos, se::vec2u size);
	~MenuButton();
};
} // namespace SevEngine

#endif // MENUBUTTON_H
