#include "Sound.h"
#include <Windows.h>
#include <mmsystem.h>
#include <mciapi.h>
#pragma comment(lib, "winmm.lib")

Sound::Sound():
_loop(false)
{
	_filePath = "";
}

Sound::~Sound(){
}

bool Sound::open(string filePath, bool loop){
	_filePath = filePath;
	_loop = loop;

	string command = "open \"" + _filePath + "\" type mpegvideo";
	mciSendString(command.c_str(), NULL, 0, 0);

	return true;
}

void Sound::play(){
	if (!_loop){
		string command = "play " + _filePath + " from 0";
		mciSendString(command.c_str(), NULL, 0, 0);
	}
	else{
		string command = "play " + _filePath + " repeat";
		mciSendString(command.c_str(), NULL, 0, 0);
	}
		
}

