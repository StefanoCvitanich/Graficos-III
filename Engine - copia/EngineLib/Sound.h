#ifndef SOUND_H
#define SOUND_H
//===================================================================
#include <string>
//===================================================================
#include "DLLExport.h"
//===================================================================
using namespace std;
class Sound
{
public:
	DllExport Sound();
	DllExport ~Sound();

	DllExport bool open(std::string filePath, bool loop);
	DllExport void play();
private:
	string _filePath;
	bool _loop;
};

#endif

