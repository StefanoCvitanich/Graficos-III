#include "Mesh.h"
#include "pg2_indexbuffer.h"
#include "pg2_vertexbuffer.h"
#include "BoundingBox.h"
#include <algorithm>
#include <iostream>
//=====================================================
Mesh::Mesh(Renderer& renderer):
	_renderer (renderer),
	_texture (NoTexture)
{}
//=====================================================
Mesh::~Mesh(){
	delete _vertexBuffer;
	_vertexBuffer = NULL;
	delete _indexBuffer;
	_indexBuffer = NULL;
}
//=====================================================
void Mesh::setMeshData(const TexturedVertex* texVertex, 
					   Primitive ePrimitive, 
					   size_t uiVertexCount, 
					   const unsigned short* pusIndices, 
					   size_t uiIndexCount)
{
	_primitive = ePrimitive;
	_verts = texVertex;

	_indexBuffer = _renderer.createIndexBuffer();
	_vertexBuffer = _renderer.createVertexBuffer(sizeof(TexturedVertex), 0);

	_vertexBuffer->setVertexData(texVertex, uiVertexCount);
	_indexBuffer->setIndexData(pusIndices, uiIndexCount);

	_renderer.setCurrentIndexBuffer(_indexBuffer);
	_renderer.setCurrentVertexBuffer(_vertexBuffer);
}
//=====================================================
void Mesh::setMeshData(const Vertex* texVertex,
					   Primitive ePrimitive,
					   size_t uiVertexCount,
					   const unsigned short* pusIndices,
					   size_t uiIndexCount)
{
	_primitive = ePrimitive;

	_indexBuffer = _renderer.createIndexBuffer();
	_vertexBuffer = _renderer.createVertexBuffer(sizeof(Vertex), 1);

	_vertexBuffer->setVertexData(texVertex, uiVertexCount);
	_indexBuffer->setIndexData(pusIndices, uiIndexCount);

	_renderer.setCurrentIndexBuffer(_indexBuffer);
	_renderer.setCurrentVertexBuffer(_vertexBuffer);
}
//=====================================================
void Mesh::draw(Renderer& renderer, CollisionResult parentResult,
	const Frustum& frustum){
	if (parentResult != CollisionResult::AllOutside){
		_renderer.setCurrentTexture(_texture);
		_renderer.setMatrix(MatrixType::WORLD, _worldTransformationMatrix);

		_vertexBuffer->bind();
		_indexBuffer->bind();

		renderer.numPolygonsOnScreen += numPolygons;

		_renderer.drawCurrentBuffers(_primitive);
		_isDrawn = true;
	}
	else
		renderer.numPolygonsOnScreen -= numPolygons;
		_isDrawn = false;
}
//=====================================================
void Mesh::setTextureId(int iTextureId, Texture texture){
	_texture = texture;
}
//=====================================================
void Mesh::updateBV(){
	D3DXVECTOR3 pos, scale;
	D3DXQUATERNION rot;
	D3DXMatrixDecompose(&scale, &rot, &pos, _worldTransformationMatrix);

	float auxMaxX = (_aabb.maxPointX * scale.x) + pos.x;
	float auxMaxY = (_aabb.maxPointY * scale.y) + pos.y;
	float auxMaxZ = (_aabb.maxPointZ * scale.z) + pos.z;

	float auxMinX = (_aabb.minPointX * scale.x) + pos.x;
	float auxMinY = (_aabb.minPointY * scale.y) + pos.y;
	float auxMinZ = (_aabb.minPointZ * scale.z) + pos.z;

	_aabb.points[0]->x = auxMinX;		_aabb.points[0]->y = auxMaxY;		_aabb.points[0]->z = auxMinZ;
	_aabb.points[1]->x = auxMaxX;		_aabb.points[1]->y = auxMaxY;		_aabb.points[1]->z = auxMinZ;
	_aabb.points[2]->x = auxMinX;		_aabb.points[2]->y = auxMinY;		_aabb.points[2]->z = auxMinZ;
	_aabb.points[3]->x = auxMaxX;		_aabb.points[3]->y = auxMinY;		_aabb.points[3]->z = auxMinZ;
	_aabb.points[4]->x = auxMinX;		_aabb.points[4]->y = auxMaxY;		_aabb.points[4]->z = auxMaxZ;
	_aabb.points[5]->x = auxMaxX;		_aabb.points[5]->y = auxMaxY;		_aabb.points[5]->z = auxMaxZ;
	_aabb.points[6]->x = auxMinX;		_aabb.points[6]->y = auxMinY;		_aabb.points[6]->z = auxMaxZ;
	_aabb.points[7]->x = auxMaxX;		_aabb.points[7]->y = auxMinY;		_aabb.points[7]->z = auxMaxZ;

	_aabb.max[0] = auxMaxX;		_aabb.max[1] = auxMaxY;		_aabb.max[2] = auxMaxZ;
	_aabb.min[0] = auxMinX;		_aabb.min[1] = auxMinY;		_aabb.min[2] = auxMinZ;
}
//=====================================================
void Mesh::buildAABB(){
	_aabb.minPointX = _verts[0].x; _aabb.minPointY = _verts[0].y; _aabb.minPointZ = _verts[0].z;
	_aabb.maxPointX = _verts[0].x; _aabb.maxPointY = _verts[0].y; _aabb.maxPointZ = _verts[0].z;

	for (size_t i = 1; i < _vertexBuffer->vertexCount(); i++){
		if (_verts[i].x < _aabb.minPointX)
			_aabb.minPointX = _verts[i].x;
		if (_verts[i].y < _aabb.minPointY)
			_aabb.minPointY = _verts[i].y;
		if (_verts[i].z < _aabb.minPointZ)
			_aabb.minPointZ = _verts[i].z;

		if (_verts[i].x > _aabb.maxPointX)
			_aabb.maxPointX = _verts[i].x;
		if (_verts[i].y > _aabb.maxPointY)
			_aabb.maxPointY = _verts[i].y;
		if (_verts[i].z > _aabb.maxPointZ)
			_aabb.maxPointZ = _verts[i].z;
	}
}
//=====================================================
void Mesh::getNames(vector<string>& names){
	names.push_back(getName());
}
//=====================================================
void Mesh::updateNames(std::vector<std::string>& names, int& entityIndex){
	names[entityIndex] = getName();
}
//=====================================================
void Mesh::setNumPolygons(unsigned int polys){
	numPolygons = polys;
}
//=====================================================
bspPlane::bspPlane(){
}
//=====================================================
bspPlane::~bspPlane(){
}
//=====================================================
D3DXPLANE bspPlane::createPlane(D3DXVECTOR3 *p1, D3DXVECTOR3 *p2, D3DXVECTOR3 *p3) {

	D3DXPlaneFromPoints(plane, p1, p2, p3);

	D3DXPlaneNormalize(plane, plane);

	return *plane;
}