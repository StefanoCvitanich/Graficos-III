#ifndef SPRITE_H
#define SPRITE_H
//========================================================================================
#include "Entity2D.h"
#include "Animation.h"
#include <limits>
//========================================================================================
class Sprite : public Entity2D
{
public:
	DllExport Sprite(void);
	DllExport ~Sprite(void);
	DllExport void draw(Renderer& rkRenderer);
	DllExport void setTextureCoordinates(float u0, float v0,
								         float u1, float v1,
							             float u2, float v2,
							             float u3, float v3);
	DllExport void setTexture(const Texture& texture);
	DllExport void setAnimation(Animation* animation);
	DllExport void update(pg1::Timer& timer);

private:
	Texture _texture;
	TexturedVertex _texturedVertex[4];
	Animation* _animation;
	int _currentFrame, _previousFrame;
};
//========================================================================================
#endif

