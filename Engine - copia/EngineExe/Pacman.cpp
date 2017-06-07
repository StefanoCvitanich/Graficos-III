#include "Pacman.h"
#include "input.h"
#include <iostream>
//==================================================================================
Nodo* nodo1;
string userName;

unsigned short indices[] = { 0, 1, 2, 2, 1, 3, //front
4, 0, 6, 6, 0, 2, //right
7, 5, 6, 6, 5, 4, //back
3, 1, 7, 7, 1, 5, //left
4, 5, 0, 0, 5, 1, //upper
3, 7, 2, 2, 7, 6 }; //bottom

TexturedVertex _verts[8];
//==================================================================================
bool Pacman::init(Renderer& rkRenderer){
	_verts[0].x = -0.1f;	_verts[0].y = 0.1f;		_verts[0].z = -0.1f;	
	_verts[1].x = 0.1f;		_verts[1].y = 0.1f;		_verts[1].z = -0.1f;	
	_verts[2].x = -0.1f;	_verts[2].y = -0.1f;	_verts[2].z = -0.1f;	
	_verts[3].x = 0.1f;		_verts[3].y = -0.1f;	_verts[3].z = -0.1f;	
	_verts[4].x = -0.1f;	_verts[4].y = 0.1f;		_verts[4].z = 0.1f;		
	_verts[5].x = 0.1f;		_verts[5].y = 0.1f;		_verts[5].z = 0.1f;		
	_verts[6].x = -0.1f;	_verts[6].y = -0.1f;	_verts[6].z = 0.1f;		
	_verts[7].x = 0.1f;		_verts[7].y = -0.1f;	_verts[7].z = 0.1f;		

	camera = new Camera();
	
	arbol = new bspTree();

	camera->setPos(0, 0, -20);

	_importer = new Importer(rkRenderer);
	if (!_importer->importScene("Assets/Escena_BSP_Blender.dae", _root, *arbol))
		cout << "no se cargo escena";

	nodo1 = new Nodo();
	nodo1 = (Nodo*)_root.childs()[0];

	_screenText = new ScreenText();
	_screenText->create(0, 0, 200, 720, 15, "arial", "", true, rkRenderer);
	_text = "";
	
	_root.getNames(names);
	cout << _root.rotationX() <<" "<< _root.rotationY()<<" " << _root.rotationZ() << endl;
	return true;
}
//==================================================================================
float rotation = 0.0f;

void Pacman::frame(Renderer& rkRenderer, Input& input, pg1::Timer& timer){
	_text = "";

	//Movimiento de la camara
	if (input.keyDown(Input::KEY_H)){
		camera->strafe(10.0f * (timer.timeBetweenFrames() / 1000.0f));
	}
	else if (input.keyDown(Input::KEY_F)){
		camera->strafe(-10.0f * (timer.timeBetweenFrames() / 1000.0f));
	}

	if (input.keyDown(Input::KEY_T)){
		camera->walk(10.0f * (timer.timeBetweenFrames() / 1000.0f));
	}
	else if (input.keyDown(Input::KEY_G)) {
		camera->walk(-10.0f * (timer.timeBetweenFrames() / 1000.0f));
	}

	camera->yaw(input.mouseRelPosX() * (timer.timeBetweenFrames() / 1000.0f));
	camera->pitch(input.mouseRelPosY() * (timer.timeBetweenFrames() / 1000.0f));
	camera->roll(input.mouseRelPosZ() * 0.1f * (timer.timeBetweenFrames() / 1000.0f));

	camera->update(rkRenderer);

	//Transformaciones Nodo1
	if (input.keyDown(Input::KEY_A)){
		nodo1->setPosX(nodo1->posX() - 2.0f * (timer.timeBetweenFrames() / 1000.0f));
	}
	else if (input.keyDown(Input::KEY_D)){
		nodo1->setPosX(nodo1->posX() + 2.0f * (timer.timeBetweenFrames() / 1000.0f));
	}

	if (input.keyDown(Input::KEY_S)){
		nodo1->setPosZ(nodo1->posZ() - 2.0f * (timer.timeBetweenFrames() / 1000.0f));
	}
	else if (input.keyDown(Input::KEY_W)){
		nodo1->setPosZ(nodo1->posZ() + 2.0f * (timer.timeBetweenFrames() / 1000.0f));
	}

	if (input.keyDown(Input::KEY_K))
		nodo1->setScale(nodo1->scaleX() + 1.01f * (timer.timeBetweenFrames() / 1000.0f), nodo1->scaleY() + 1.01f * (timer.timeBetweenFrames() / 1000.0f), nodo1->scaleZ() + 1.01f * (timer.timeBetweenFrames() / 1000.0f));
	if (input.keyDown(Input::KEY_L))
		nodo1->setScale(nodo1->scaleX() - 1.01f * (timer.timeBetweenFrames() / 1000.0f), nodo1->scaleY() - 1.01f * (timer.timeBetweenFrames() / 1000.0f), nodo1->scaleZ() - 1.01f * (timer.timeBetweenFrames() / 1000.0f));

	if (input.keyDown(Input::KEY_R))
		//nodo1->childs()[0]->setRotation(nodo1->rotationX(),nodo1->rotationY() - 1.01f * (timer.timeBetweenFrames() / 1000.0f), nodo1->rotationZ());
	
	//Transformaciones Teapot
	if (input.keyDown(Input::KEY_UP)){
		nodo1->childs()[0]->setScale(nodo1->childs()[0]->scaleX() + 1.01f * (timer.timeBetweenFrames() / 1000.0f), nodo1->childs()[0]->scaleY() + 1.01f * (timer.timeBetweenFrames() / 1000.0f), nodo1->childs()[0]->scaleZ() + 1.01f * (timer.timeBetweenFrames() / 1000.0f));
	}
	else if (input.keyDown(Input::KEY_DOWN)){
		nodo1->childs()[0]->setScale(nodo1->childs()[0]->scaleX() - 1.01f * (timer.timeBetweenFrames() / 1000.0f), nodo1->childs()[0]->scaleY() - 1.01f * (timer.timeBetweenFrames() / 1000.0f), nodo1->childs()[0]->scaleZ() - 1.01f * (timer.timeBetweenFrames() / 1000.0f));
	}

	if (input.keyDown(Input::KEY_LEFT)){
		nodo1->childs()[0]->setPosX(nodo1->childs()[0]->posX() - 1.01f * (timer.timeBetweenFrames() / 1000.0f));
	}
	else if (input.keyDown(Input::KEY_RIGHT)){
		nodo1->childs()[0]->setPosX(nodo1->childs()[0]->posX() + 1.01f * (timer.timeBetweenFrames() / 1000.0f));
	}

	_root.updateBV();
	CollisionResult col = camera->getFrustum().aabbVsFrustum(_root.getAABB());

	arbol->checkTree(camera->getPos());

	_root.draw(rkRenderer, col, camera->getFrustum());

	int index = 0;
	_root.updateNames(names, index);
	for (size_t i = 0; i < names.size(); i++)
	{
		_text += names[i]+"\n";
	}

	/*
	char buff[33];
	string polysOnScreen = itoa(rkRenderer.numPolygonsOnScreen, buff, 10);
	_text += polysOnScreen + "\n";
	*/
	_screenText->setText(_text);
	_screenText->display(rkRenderer);
}
//==================================================================================
void Pacman::deinit(){
	delete camera;
	delete _importer;
	delete nodo1;
	delete _screenText;
}
//==================================================================================
void Pacman::moveNode1(Input& input){
	//_root.childs()[1]->setRotation(0, _root.childs()[1]->rotationY() + 1.0f * -0.001f, 0);
}
//==================================================================================
void Pacman::moveMesh(Input& input){
	//nodo1->childs()[0]->setRotation(nodo1->childs()[0]->rotationX() + 1.0f * 0.001f, 0, 0);
}
//==================================================================================
void Pacman::moveRoot(Input& input){
	//_root.setRotation(0, 0, _root.rotationZ() + 1.0f * 0.001f);
}
//==================================================================================