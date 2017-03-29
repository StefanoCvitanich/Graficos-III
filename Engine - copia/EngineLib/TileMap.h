#ifndef TILEMAP_H
#define TILEMAP_H
//===================================================================
#include "Tile.h"
#include <string>
//===================================================================
class TileMap{
public:
	DllExport TileMap();
	DllExport ~TileMap();

	DllExport const Tile& tile(unsigned int id);
	DllExport void setTile(const Tile& tile);
	DllExport void setMapTileId(int layer, unsigned int column, unsigned int row, unsigned int id);

	DllExport void setDimensions(unsigned int width, unsigned int heigth);
	DllExport void setTileDimensions(float tileWidth, float tileHeigth);

	DllExport void setTexture(const Texture& texture);
	DllExport void draw(Renderer& renderer);

	DllExport bool importTileMap(std::string filePath, Renderer& renderer);
	DllExport void checkCollision(Entity2D& object);
private:
	std::vector<Tile> tiles;
	std::vector<Tile**> _tileMapGrid;
	//Tile** _tileMapGrid;
	Texture _texture;
	unsigned int _width;
	unsigned int _height;
	float _tileWidth;
	float _tileHeight;
	float _imageWidth;
	float _imageHeight;
	std::string _imagePath;
};
#endif

