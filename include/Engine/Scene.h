//////////////////////////////////////////////////
//	Copyright © Severin Fürbringer 2014
//
//	Author: Severin Fürbringer
//	Jahr:	2014
//	Datei:	Scene.h
//////////////////////////////////////////////////

#ifndef SCENE_H
#define SCENE_H

#include "MsgBox.h"
#include "Transition.h"
#include "EngineExport.h"

namespace se
{
class SEVENGINEDLL_API Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void loadContent();
	virtual void unloadContent();
	virtual void update();
	virtual void update(sf::RenderWindow& window);
	virtual void draw(sf::RenderWindow& window);

private:
	virtual void initialize();
};
}

#endif // SCENE_H
