#ifndef MESH_H
#define MESH_H
//========================================================================================
#include "Entity3D.h"
//========================================================================================
using namespace std;
//========================================================================================
struct bspPlane
{
public:
	DllExport bspPlane();
	DllExport ~bspPlane();

	DllExport D3DXPLANE createPlane(D3DXVECTOR3 *p1, D3DXVECTOR3 *p2, D3DXVECTOR3 *p3);

	D3DXPLANE *plane;
};
//========================================================================================
class Mesh : public Entity3D
{
public:
	DllExport Mesh(Renderer& renderer);
	DllExport ~Mesh();

public:
	DllExport void setMeshData(const TexturedVertex* texVertex, 
							   Primitive ePrimitive, 
							   size_t uiVertexCount, 
							   const unsigned short* pusIndices, 
							   size_t uiIndexCount);

	DllExport void setMeshData(const Vertex* texVertex,
								Primitive ePrimitive,
								size_t uiVertexCount,
								const unsigned short* pusIndices,
								size_t uiIndexCount);

	DllExport void draw(Renderer& renderer, CollisionResult parentResult,
						const Frustum& frustum);

	DllExport void updateBV();
	DllExport void setTextureId(int iTextureId, Texture texture);
	DllExport void buildAABB();
	DllExport void getNames(vector<std::string>& names);
	DllExport void updateNames(std::vector<std::string>& names, int& entityIndex);

	DllExport void setNumPolygons(unsigned int polys);

private:
	Renderer& _renderer;
	Primitive _primitive;
	pg2::IndexBuffer* _indexBuffer;
	pg2::VertexBuffer* _vertexBuffer;
	Texture _texture;
	const TexturedVertex* _verts;
	unsigned int numPolygons;
};
//========================================================================================
#endif