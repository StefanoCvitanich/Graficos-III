#include "ScreenText.h"
//=================================================
ScreenText::ScreenText():
	_font(NULL),
	_width(0),
	_height(0),
	_x(0),
	_y(0),
	_charSize(0),
	_italic(false)
{}
//=================================================
ScreenText::~ScreenText(){
}
//=================================================
void ScreenText::create(int x, int y, 
						int width, int height,
						int charSize,
						std::string textFont, std::string text,
						bool italic,
						Renderer& renderer)
{
	_font = renderer.createFont(charSize, textFont, italic);
	_rect = renderer.createRect(x, y, width, height);
	_text = text;
}
//=================================================
void ScreenText::display(Renderer& renderer){
	renderer.displayText(_font, _rect, _text);
}
//=================================================
void ScreenText::setText(std::string text){
	_text = text;
}
//=================================================