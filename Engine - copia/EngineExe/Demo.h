#ifndef DEMO_H
#define DEMO_H

#include "Game.h"
#include "TileMap.h"
class Demo : public Game
{
public:
	bool init(Renderer& rkRenderer);
	void frame(Renderer& rkRenderer, Input& input, pg1::Timer& timer);
	void deinit();

	Sprite* _player;
	Animation* _runUp;
	Animation* _runDown;
	Animation* _runLeft;
	Animation* _runRight;
	Animation* _iddleDown;
	Animation* _iddleUp;
	Animation* _iddleRight;
	Animation* _iddleLeft;

	TileMap tile;

	ScreenText _score;
	ScreenText _userName;

	Quad* quad;
};

#endif

