#include "Animation.h"
//==============================================================================================
Animation::Animation():
_currentTime(0),
_currentFrame(0),
_length(1000)
{
	//O w -
}
//==============================================================================================
Animation::~Animation(void){}
//==============================================================================================
void Animation::update(pg1::Timer& timer){
	_currentTime += timer.timeBetweenFrames();

	while(_currentTime > _length) {
		_currentTime -= _length;
	}

	float frameLength = _length / _frames.size();
	_currentFrame = static_cast<int>(_currentTime / frameLength);
}
//==============================================================================================
void Animation::addFrame(float frameX, float frameY,
						 float frameWidth, float frameHeigth,
						 float textureWidth, float textureHeigth,
						 float durationInSecs)
{
	_length = durationInSecs * 1000;
	//----------------------------------------------------------------
	Frame frame;

	frame.uvCoords[0].u = (frameX / textureWidth);
	frame.uvCoords[0].v = (frameY / textureHeigth);
	//----------------------------------------------------------------
	frame.uvCoords[1].u = ( (frameX + frameWidth) / textureWidth);
	frame.uvCoords[1].v = (frameY / textureHeigth);
	//----------------------------------------------------------------
	frame.uvCoords[2].u = (frameX / textureWidth);
	frame.uvCoords[2].v = ( (frameY + frameHeigth) / textureHeigth);
	//----------------------------------------------------------------
	frame.uvCoords[3].u = ( (frameX + frameWidth) / textureWidth);
	frame.uvCoords[3].v = ( (frameY + frameHeigth) / textureHeigth);
	//----------------------------------------------------------------
	_frames.push_back(frame);
}
//==============================================================================================
void Animation::addFrame(float frameX, float frameY,
						 float frameWidth, float frameHeigth,
						 float textureWidth, float textureHeigth,
						 float durationInSecs,
						 int frameCount)
{
	_length = durationInSecs * 1000;

	float frameXIndex = 0;

	for(int i = 0; i < frameCount; i++){
		Frame frame;

		frame.uvCoords[0].u = ((frameX + frameXIndex) / textureWidth);
		frame.uvCoords[0].v = (frameY / textureHeigth);
		//-----------------------------------------------------------------------------
		frame.uvCoords[1].u = ( ((frameX + frameXIndex) + frameWidth) / textureWidth);
		frame.uvCoords[1].v = (frameY / textureHeigth);
		//-----------------------------------------------------------------------------
		frame.uvCoords[2].u = ((frameX + frameXIndex) / textureWidth);
		frame.uvCoords[2].v = ( (frameY + frameHeigth) / textureHeigth);
		//-----------------------------------------------------------------------------
		frame.uvCoords[3].u = ( ((frameX + frameXIndex) + frameWidth) / textureWidth);
		frame.uvCoords[3].v = ( (frameY + frameHeigth) / textureHeigth);
		//-----------------------------------------------------------------------------
		_frames.push_back(frame);
		frameXIndex += frameWidth;
	}
}
//==============================================================================================
vector<Frame>& Animation::getFrames(){
	return _frames;
}
//==============================================================================================
int Animation::currentFrame(){
	return _currentFrame;
}
//==============================================================================================