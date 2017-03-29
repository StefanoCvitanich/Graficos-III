#include "Demo.h"
#include "input.h"
#include <iostream>
string userName;
bool Demo::init(Renderer& rkRenderer){
	userName = "MatyX";
	string passWord = "None";

	if(!tile.importTileMap("assets/tilemap3.tmx", rkRenderer)){
		cout<<"algo fallo";
	}

	quad->setScale(132, 132);
	quad->setPosX(0);
	quad->setPosY(0);

	_score.create(0, 0, 1000, 100, 50, "Arial", "Hola", false, rkRenderer);
	_userName.create(0, 50, 1000, 200, 50, "Arial", "UserName: ", false, rkRenderer);

	_player = new Sprite();
	_player->setPosX(0);
	_player->setPosY(0);
	_player->setTexture(rkRenderer.loadTexture("assets/samurai.png", D3DCOLOR_XRGB(255,255,255)));
	_player->setScale(120, 120);

	_iddleDown = new Animation();
	_iddleDown->addFrame(0.0f, 0.0f, 64.0f, 64.0f, 1024.0f, 1024.0f, 0.6f, 4);
	_iddleLeft = new Animation();
	_iddleLeft->addFrame(0.0f, 64.0f, 64.0f, 64.0f, 1024.0f, 1024.0f, 0.6f, 4);

	_runDown = new Animation();
	_runDown->addFrame(256.0f, 0.0f, 64.0f, 64.0f, 1024.0f, 1024.0f, 0.7f, 7);
	_runLeft = new Animation();
	_runLeft->addFrame(256.0f, 64.0f, 64.0f, 64.0f, 1024.0f, 1024.0f, 0.66f, 8);
	_runRight = new Animation();
	_runRight->addFrame(256.0f, 128.0f, 64.0f, 64.0f, 1024.0f, 1024.0f, 0.66f, 8);
	_runRight = new Animation();
	_runRight->addFrame(256.0f, 128.0f, 64.0f, 64.0f, 1024.0f, 1024.0f, 0.66f, 8);
	_runUp = new Animation();
	_runUp->addFrame(256.0f, 192.0f, 64.0f, 64.0f, 1024.0f, 1024.0f, 0.7f, 6);
	_player->setAnimation(_iddleDown);

	return true;
}
int i = 0;
string score;
void Demo::frame(Renderer& rkRenderer, Input& input, pg1::Timer& timer){
	quad->draw(rkRenderer);
	if (input.keyDown(Input::KEY_D)){
		_player->setPosX(_player->posX() + 3.0f);
		_player->setAnimation(_runRight);
	}
	else if (input.keyDown(Input::KEY_A)){
		_player->setPosX(_player->posX() - 3.0f);
		_player->setAnimation(_runLeft);
	}

	if (input.keyDown(Input::KEY_W)){
		_player->setPosY(_player->posY() + 3.0f);
		_player->setAnimation(_runUp);
	}

	else if (input.keyDown(Input::KEY_S)) {
		_player->setPosY(_player->posY() - 3.0f);
		_player->setAnimation(_runDown);
	}

	if(input.keyUp(Input::KEY_S) && input.keyUp(Input::KEY_A) && input.keyUp(Input::KEY_D) && input.keyUp(Input::KEY_W)){
		_player->setAnimation(_iddleDown);
	}
	
	//tile.draw(rkRenderer);
	
	tile.checkCollision(*_player);
	
	_player->update(timer);
	_player->draw(rkRenderer);
	i++;
	score = "Score: " + std::to_string((long double)i);
	_score.setText(score);
	_score.display(rkRenderer);
	_userName.setText("Username: " + userName);
	_userName.display(rkRenderer);
	
	
}

void Demo::deinit(){
}