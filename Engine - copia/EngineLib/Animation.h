#ifndef ANIMATION_H
#define ANIMATION_H
//==============================================================================================
#include "pg1_timer.h"
#include "Frame.h"
#include <vector>
//==============================================================================================
#include "DLLExport.h"
//==============================================================================================
using namespace std;
//==============================================================================================
class Animation
{
public:
	DllExport Animation();
	DllExport ~Animation();

	DllExport void update(pg1::Timer& timer);

	DllExport void addFrame(float frameX, float frameY,
				  float frameWidth, float frameHeigth,
				  float textureWidth, float textureHeigth,
				  float durationInSecs);

	DllExport void addFrame(float frameX, float frameY,
				  float frameWidth, float frameHeigth,
				  float textureWidth, float textureHeigth,
				  float durationInSecs,
				  int frameCount);

	DllExport int currentFrame();

	DllExport vector<Frame>& getFrames();

private:
	int _currentFrame;
	float _currentTime;
	float _length;
	vector<Frame> _frames;
};
//==============================================================================================
#endif

