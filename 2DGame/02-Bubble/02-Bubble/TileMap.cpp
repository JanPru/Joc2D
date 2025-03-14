#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "TileMap.h"


using namespace std;


TileMap *TileMap::createTileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program)
{
	TileMap *map = new TileMap(levelFile, minCoords, program);
	
	return map;
}


TileMap::TileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program)
{
	loadLevel(levelFile);
	prepareArrays(minCoords, program);
}

TileMap::~TileMap()
{
	if(map != NULL)
		delete map;
}


void TileMap::render() const
{
	glEnable(GL_TEXTURE_2D);
	tilesheet.use();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6 * nTiles);
	glDisable(GL_TEXTURE_2D);
}

void TileMap::free()
{
	glDeleteBuffers(1, &vbo);
}

bool TileMap::loadLevel(const string &levelFile)
{
	ifstream fin;
	string line, tilesheetFile;
	stringstream sstream;
	char tile;
	
	fin.open(levelFile.c_str());
	if(!fin.is_open())
		return false;
	getline(fin, line);
	if(line.compare(0, 7, "TILEMAP") != 0)
		return false;
	getline(fin, line);
	sstream.str(line);
	sstream >> mapSize.x >> mapSize.y;
	getline(fin, line);
	sstream.str(line);
	sstream >> tileSize >> blockSize;
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetFile;
	tilesheet.loadFromFile(tilesheetFile, TEXTURE_PIXEL_FORMAT_RGBA);
	tilesheet.setWrapS(GL_CLAMP_TO_EDGE);
	tilesheet.setWrapT(GL_CLAMP_TO_EDGE);
	tilesheet.setMinFilter(GL_NEAREST);
	tilesheet.setMagFilter(GL_NEAREST);
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetSize.x >> tilesheetSize.y;
	tileTexSize = glm::vec2(1.f / tilesheetSize.x, 1.f / tilesheetSize.y);
	
	map = new int[mapSize.x * mapSize.y];
	for(int j=0; j<mapSize.y; j++)
	{
		getline(fin, line);
		sstream.clear();
		sstream.str(line);
		for(int i=0; i<mapSize.x; i++)
		{
			string tile;
			getline(sstream, tile, ',');
			if (tile == " ")
				map[j * mapSize.x + i] = 0;
			else 
				map[j * mapSize.x + i] = stoi(tile);
		}
	}
	fin.close();
	
	return true;
}

void TileMap::definirCoordTile(glm::vec2 (&texCoordTile)[2], int tile) {
	if (tile == 1) {
		texCoordTile[0] = glm::vec2(0,0.5);
		texCoordTile[1] = texCoordTile[0] + tileTexSize;
	}
	if (tile == 2) {
		texCoordTile[0] = glm::vec2(0.125, 0.5);
		texCoordTile[1] = texCoordTile[0] + tileTexSize;
	}
	if (tile == 3) {
		texCoordTile[0] = glm::vec2(0, 0);
		texCoordTile[1] = texCoordTile[0] + tileTexSize;
	}
	if (tile == 4) {
		texCoordTile[0] = glm::vec2(0.125, 0);
		texCoordTile[1] = texCoordTile[0] + tileTexSize;
	}
	if (tile == 5) {
		texCoordTile[0] = glm::vec2(0.25, 0);
		texCoordTile[1] = texCoordTile[0] + tileTexSize;
	}
	if (tile == 6) {
		texCoordTile[0] = glm::vec2(0.375, 0);
		texCoordTile[1] = texCoordTile[0] + tileTexSize;
	}
	if (tile == 7) {
		texCoordTile[0] = glm::vec2(0.5, 0);
		texCoordTile[1] = texCoordTile[0] + tileTexSize;
	}
	if (tile == 8) {
		texCoordTile[0] = glm::vec2(0.625, 0);
		texCoordTile[1] = texCoordTile[0] + tileTexSize;
	}
	if (tile == 9) {
		texCoordTile[0] = glm::vec2(0.75, 0);
		texCoordTile[1] = texCoordTile[0] + tileTexSize;
	}
	if (tile == 10) {
		texCoordTile[0] = glm::vec2(0.875, 0);
		texCoordTile[1] = texCoordTile[0] + tileTexSize;
	}
	if (tile == 11) {
		texCoordTile[0] = glm::vec2(0.25, 0.5);
		texCoordTile[1] = texCoordTile[0] + tileTexSize;
	}
	if (tile == 17) {
		texCoordTile[0] = glm::vec2(0.375, 0.5);
		texCoordTile[1] = texCoordTile[0] + tileTexSize;
	}
	if (tile == 18) {
		texCoordTile[0] = glm::vec2(0.5, 0.5);
		texCoordTile[1] = texCoordTile[0] + tileTexSize;
	}
	if (tile == 19) {
		texCoordTile[0] = glm::vec2(0.625, 0.5);
		texCoordTile[1] = texCoordTile[0] + tileTexSize;
	}
	if (tile == 20) {
		texCoordTile[0] = glm::vec2(0.75, 0.5);
		texCoordTile[1] = texCoordTile[0] + tileTexSize;
	}
	if (tile == 21) {
		texCoordTile[0] = glm::vec2(0.875, 0.5);
		texCoordTile[1] = texCoordTile[0] + tileTexSize;
	}

}

void TileMap::prepareArrays(const glm::vec2 &minCoords, ShaderProgram &program)
{
	int tile;
	glm::vec2 posTile, texCoordTile[2], halfTexel;
	vector<float> vertices;
	
	nTiles = 0;
	halfTexel = glm::vec2(0.5f / tilesheet.width(), 0.5f / tilesheet.height());
	for(int j=0; j<mapSize.y; j++)
	{
		for(int i=0; i<mapSize.x; i++)
		{
			tile = map[j * mapSize.x + i];
			if(tile != 0)
			{
				// Non-empty tile
				nTiles++;
				posTile = glm::vec2(minCoords.x + i * tileSize, minCoords.y + j * tileSize);
				definirCoordTile(texCoordTile, tile);
				/*texCoordTile[0] = glm::vec2(float((tile - 1) % tilesheetSize.x) / tilesheetSize.x, float((tile - 1) / tilesheetSize.x) / tilesheetSize.y);
				texCoordTile[1] = texCoordTile[0] + tileTexSize;*/
				//texCoordTile[0] += halfTexel;
				texCoordTile[1] -= halfTexel;
				// First triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				// Second triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				vertices.push_back(posTile.x); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[1].y);
			}
		}
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * nTiles * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	posLocation = program.bindVertexAttribute("position", 2, 4*sizeof(float), 0);
	texCoordLocation = program.bindVertexAttribute("texCoord", 2, 4*sizeof(float), (void *)(2*sizeof(float)));
}

// Collision tests for axis aligned bounding boxes.
// Method collisionMoveDown also corrects Y coordinate if the box is
// already intersecting a tile below.

bool TileMap::collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) const
{
	int x, y0, y1;
	
	x = pos.x / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for(int y=y0; y<=y1; y++)
	{
		if(map[y*mapSize.x+x] != 0)
			return true;
	}
	
	return false;
}

bool TileMap::collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size) const
{
	int x, y0, y1;
	
	x = (pos.x + size.x - 1) / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for(int y=y0; y<=y1; y++)
	{
		if(map[y*mapSize.x+x] != 0)
			return true;
	}
	
	return false;
}

bool TileMap::collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) const
{
	int x0, x1, y;

	//std::cout << "POS X " << pos.x << "POS Y " << pos.y << "SIZE X , Y " << size.x << size.y << "POS_YYYY " << *posY << std::endl;
	
	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = (pos.y + size.y - 1) / tileSize;
	for(int x=x0; x<=x1; x++)
	{
		if(map[y*mapSize.x+x] != 0)
		{
			if(*posY - tileSize * y + size.y <= 4)
			{
				*posY = tileSize * y - size.y;
				return true;
			}
		}
	}
	
	return false;
}

glm::vec2 TileMap::getMapSize() const {
	return mapSize;
}




























