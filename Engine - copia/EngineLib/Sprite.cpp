#include "Sprite.h"
//===========================================================================================================================================
Sprite::Sprite(void):
_texture(NoTexture)
{
	_texturedVertex[0].x = -0.5;	_texturedVertex[0].y = 0.5;		_texturedVertex[0].z = 0.0f;
	_texturedVertex[1].x = 0.5;		_texturedVertex[1].y = 0.5;		_texturedVertex[1].z = 0.0f;
	_texturedVertex[2].x = -0.5;	_texturedVertex[2].y = -0.5;	_texturedVertex[2].z = 0.0f;
	_texturedVertex[3].x = 0.5;		_texturedVertex[3].y = -0.5;	_texturedVertex[3].z = 0.0f;

	_texturedVertex[0].u = 0.0;		_texturedVertex[0].v = 0.0f;
	_texturedVertex[1].u = 1.0;		_texturedVertex[1].v = 0.0;	
	_texturedVertex[2].u = 0.0;		_texturedVertex[2].v = 1.0;
	_texturedVertex[3].u = 1.0;		_texturedVertex[3].v = 1.0;
}
//===========================================================================================================================================
Sprite::~Sprite(void){
}
//===========================================================================================================================================
void Sprite::setTextureCoordinates(float u0, float v0,
								   float u1, float v1,
							       float u2, float v2,
								   float u3, float v3)
{
	_texturedVertex[0].u = u0;		_texturedVertex[0].v = v0;
	_texturedVertex[1].u = u1;		_texturedVertex[1].v = v1;	
	_texturedVertex[2].u = u2;		_texturedVertex[2].v = v2;
	_texturedVertex[3].u = u3;		_texturedVertex[3].v = v3;
}
//===========================================================================================================================================
void Sprite::setTexture(const Texture& texture){
	_texture = texture;
}
//===========================================================================================================================================
void Sprite::draw(Renderer& rkRenderer){
	rkRenderer.setCurrentTexture(_texture);
	rkRenderer.setMatrix(WORLD, _transformationMatrix);
	rkRenderer.draw(_texturedVertex, TRIANGLESTRIP, ARRAY_SIZE(_texturedVertex));
}
//===========================================================================================================================================
void Sprite::setAnimation(Animation* animation){
	_animation = animation;
	_previousFrame = std::numeric_limits<unsigned int>::max_digits10;
}
//===========================================================================================================================================
void Sprite::update(pg1::Timer& timer){
	if(!_animation)
		return;

	_animation->update(timer);

	_currentFrame = _animation->currentFrame();
	if(_currentFrame != _previousFrame){
		setTextureCoordinates(_animation->getFrames()[_currentFrame].uvCoords[0].u, _animation->getFrames()[_currentFrame].uvCoords[0].v,
							  _animation->getFrames()[_currentFrame].uvCoords[1].u, _animation->getFrames()[_currentFrame].uvCoords[1].v,
							  _animation->getFrames()[_currentFrame].uvCoords[2].u, _animation->getFrames()[_currentFrame].uvCoords[2].v,
							  _animation->getFrames()[_currentFrame].uvCoords[3].u, _animation->getFrames()[_currentFrame].uvCoords[3].v);

		_previousFrame = _currentFrame;
	}
}
//===========================================================================================================================================