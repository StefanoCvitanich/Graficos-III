#ifndef IMPORTER_H
#define IMPORTER_H
//=============================================================
#include "Mesh.h"
#include "Nodo.h"
#include <string>
#include "bspTree.h"
#include "bspPlane.h"
//============================================================
using namespace std;
//============================================================
struct aiNode;
struct aiScene;
struct aiMesh;
//=============================================================
class Importer
{
public:
	DllExport Importer(Renderer& renderer);
	DllExport ~Importer();

	DllExport bool importScene(const std::string& fileName, Nodo& rootNode, bspTree &tree);

private:
	bool processNode(Nodo& childNode, aiNode& assimpNode, const aiScene& scene, bspTree &tree);
	Mesh& processMesh(aiMesh& assimpMesh, aiNode& assimpNode, const aiScene& scene, bspTree &tree);
	void showNodeNames(aiNode& assimpNode, const aiScene& scene);
	void showMeshNames(aiMesh& assimpMesh, const aiScene& scene);
	Renderer& _renderer;
};
//=============================================================
#endif

