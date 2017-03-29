#ifndef IMPORTER_H
#define IMPORTER_H
//=============================================================
#include "Mesh.h"
#include "Nodo.h"
#include <string>

struct aiNode;
struct aiScene;
struct aiMesh;
//=============================================================
class Importer
{
public:
	DllExport Importer(Renderer& renderer);
	DllExport ~Importer();

	DllExport bool importScene(const std::string& fileName, Nodo& rootNode);

private:
	bool processNode(Nodo& childNode, aiNode& assimpNode, const aiScene& scene);
	Mesh& processMesh(aiMesh& assimpMesh, aiNode& assimpNode, const aiScene& scene);
	void showNodeNames(aiNode& assimpNode, const aiScene& scene);
	void showMeshNames(aiMesh& assimpMesh, const aiScene& scene);
	Renderer& _renderer;
};
//=============================================================
#endif

