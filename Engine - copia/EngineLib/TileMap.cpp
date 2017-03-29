#include "TileMap.h"
#include "tinyxml2.h"
#include <iostream>
//=========================================================================================================
TileMap::TileMap(){}
//=========================================================================================================
TileMap::~TileMap(){}
//=========================================================================================================
const Tile& TileMap::tile(unsigned int id){
	Tile* NoTile = nullptr;

	for (size_t i = 0; i < tiles.size(); i++){
		if(id == tiles[i].getId()){
			return tiles[i];
		}
	}

	return *NoTile;
}
//=========================================================================================================
void TileMap::setTile(const Tile& tile){
	tiles.push_back(tile);
}
//=========================================================================================================
void TileMap::setMapTileId(int layer, unsigned int column, unsigned int row, unsigned int id){
	_tileMapGrid[layer][column][row] = tile(id);
}
//=========================================================================================================
void TileMap::setDimensions(unsigned int width, unsigned int heigth){
	_width = width;
	_height = heigth;

	//creo la grilla bidimensional para guardar la posicion de cada tile igual que en el editor
	Tile** tileMap;
		tileMap = new Tile*[_height];
		for (size_t i = 0; i < _height; i++){
		tileMap[i] = new Tile[_width];
	}
	_tileMapGrid.push_back(tileMap);
}
//=========================================================================================================
void TileMap::setTileDimensions(float tileWidth, float tileHeight){
	_tileWidth = tileWidth;
	_tileHeight = tileHeight;
}
//=========================================================================================================
void TileMap::setTexture(const Texture& texture){
	_texture = texture;
}
//=========================================================================================================
void TileMap::draw(Renderer& renderer) {
	renderer.setCurrentTexture(_texture);

	float mapWidth = -(_width * _tileWidth) / 2; 
	float mapHeight = (_height * _tileHeight) / 2;
	for (size_t i = 0; i < _tileMapGrid.size(); i++){
		for (size_t y = 0; y < _height; y++){
			for (size_t x = 0; x < _width; x++){
				if (_tileMapGrid[i][y][x].getId() != NULL){
					_tileMapGrid[i][y][x].setPosX(mapWidth + (_tileWidth * x));
					_tileMapGrid[i][y][x].setPosY(mapHeight - (_tileHeight * y));
					_tileMapGrid[i][y][x].draw(renderer);
				}
			}
		}
	}
	
}
//=========================================================================================================
bool TileMap::importTileMap(std::string filePath, Renderer& renderer){
	tinyxml2::XMLDocument doc; //guarda el documento
	tinyxml2::XMLError errorHandler; //guarda el resultado de las funciones

	errorHandler = doc.LoadFile(filePath.c_str()); //carga el archivo XML
	if(errorHandler == tinyxml2::XML_ERROR_FILE_NOT_FOUND || errorHandler == tinyxml2::XML_ERROR_FILE_COULD_NOT_BE_OPENED) return false;

	// Loading Map element and save Map width, heigth in tiles and width, heigth of Tiles in pixels
	tinyxml2::XMLElement* mapNode = doc.FirstChildElement("map");
	if (mapNode == nullptr)
		return false;
	setDimensions((unsigned int)mapNode->FloatAttribute("width"), (unsigned int)mapNode->FloatAttribute("height"));				// Get width and heigth for
	setTileDimensions(mapNode->FloatAttribute("tilewidth"), mapNode->FloatAttribute("tileheight")); // the map and the tiles

	// Loading Tilset element
	tinyxml2::XMLElement* pTileset = mapNode->FirstChildElement("tileset");
	if (pTileset == NULL)
		return false;
	
	int tileCount = pTileset->IntAttribute("tilecount"); // Number of Tiles in the Tileset
	unsigned int columns = pTileset->IntAttribute("columns");  // Columns of Tiles in the Tileset
	unsigned int rows = tileCount / columns;

	_imagePath = "Assets/";																//
	_imagePath += pTileset->FirstChildElement("image")->Attribute("source");			// Loading Textures
	setTexture(renderer.loadTexture(_imagePath.c_str(), D3DCOLOR_XRGB(255, 255, 255))); //

	// Save the Tiles in the TileMap
	_imageWidth = pTileset->FirstChildElement("image")->FloatAttribute("width");
	_imageHeight = pTileset->FirstChildElement("image")->FloatAttribute("height");
	float tileX = 0.0f, tileY = 0.0f;
	int _id = 1;
	for (size_t i = 0; i < rows; i++){
		for (size_t j = 0; j < columns; j++){
			Tile newTile;

			newTile.setId(_id);
			newTile.setTexture(_texture);
			newTile.setScale(_tileWidth, _tileHeight);

			newTile.setTextureCoordinates(tileX / _imageWidth, tileY / _imageHeight,
				(tileX + _tileWidth) / _imageWidth, tileY / _imageHeight,
				tileX / _imageWidth, (tileY + _tileHeight) / _imageHeight,
				(tileX + _tileWidth) / _imageWidth, (tileY + _tileHeight) / _imageHeight);

			tileX += _tileWidth;
			setTile(newTile);
			_id++;
		}
		tileX = 0;
		tileY += _tileHeight;
	}

	tinyxml2::XMLElement* pTile = pTileset->FirstChildElement("tile");

	while (pTile){
		unsigned int id = pTile->IntAttribute("id");
		tinyxml2::XMLElement* pProperty = pTile->FirstChildElement("properties")->FirstChildElement("property");
		std::string propertyName = pProperty->Attribute("value");
		if (propertyName == "true")
			tiles[id].makeSolid(true);

		pTile = pTile->NextSiblingElement("tile");
	}

	// Loading Layer element
	tinyxml2::XMLElement* pLayer = mapNode->FirstChildElement("layer");
	if (pLayer == NULL)
		return false;
	
	int layerCount = 0;
	while (pLayer){
		// Loading Data element
		tinyxml2::XMLElement* pData = pLayer->FirstChildElement("data");
		if (pData == NULL)
			return false;
		
		if (layerCount > 0){
			Tile** tileMap;
				tileMap = new Tile*[_height];
			for (size_t i = 0; i < _height; i++){
				tileMap[i] = new Tile[_width];
			}
			_tileMapGrid.push_back(tileMap);
		}

		while (pData){
			std::vector<int> tileGids;
			for (tinyxml2::XMLElement* pTile = pData->FirstChildElement("tile");
				pTile != NULL;
				pTile = pTile->NextSiblingElement("tile"))
			{
				unsigned int gid = std::atoi(pTile->Attribute("gid")); //guardo la id del tile
				tileGids.push_back(gid);
			}
			
			int gid = 0;
			for (size_t y = 0; y < _height; y++){
				for (size_t x = 0; x < _width; x++){
					if (tileGids[gid] != 0)
						setMapTileId(layerCount, y, x, tileGids[gid]);
					gid++;
				}
			}

			pData = pData->NextSiblingElement("data");
		}
		layerCount++;
		pLayer = pLayer->NextSiblingElement("layer");
	}
	
	return true;
}
//=========================================================================================================
void TileMap::checkCollision(Entity2D& object) {
	for(size_t y = 0; y < _height; y++){
		for (size_t x = 0; x < _width; x++){
			for (size_t i = 0; i < _tileMapGrid.size(); i++)
			{
				if (!_tileMapGrid[i][y][x].isWalkable()){

					if (_tileMapGrid[i][y][x].checkCollision(object) == CollisionHorizontalRight ||
						_tileMapGrid[i][y][x].checkCollision(object) == CollisionHorizontalLeft)
						object.returnToPreviusPosH();

					if (_tileMapGrid[i][y][x].checkCollision(object) == CollisionVerticalUp)
						object.returnToPreviusPos(object.posX(), object.previusPosY() + 0.2f);
					else if (_tileMapGrid[i][y][x].checkCollision(object) == CollisionVerticalDown)
						object.returnToPreviusPos(object.posX(), object.previusPosY() - 0.2f);
				}
			}
			
		}
	}
}
//=========================================================================================================