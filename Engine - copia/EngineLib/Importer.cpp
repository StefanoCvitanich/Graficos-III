#include "Importer.h"
#include "Utility.h"
#include "assimp\Importer.hpp"
#include "assimp\scene.h"
#include "assimp\postprocess.h"
#include <d3dx9math.h>
#include <stack>
#include <iostream>
//=============================================================================================================
Importer::Importer(Renderer& renderer):
_renderer(renderer){}
//=============================================================================================================
Importer::~Importer(){}
//=============================================================================================================
bool Importer::importScene(const std::string& fileName, Nodo& rootNode, bspTree &tree){
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) return false;

	processNode(rootNode, *scene->mRootNode, *scene, tree);
	rootNode.setRotation(0, rootNode.rotationY(), rootNode.rotationZ());
	return true;
}
//=============================================================================================================
bool Importer::processNode(Nodo& nodo, aiNode& assimpNode, const aiScene& scene, bspTree &tree){
	nodo.setName(assimpNode.mName.C_Str());
	cout << nodo.getName() << endl;

	aiVector3t<float> position, scaling, rotInEulerAngles;
	aiQuaterniont<float> rotation;
	assimpNode.mTransformation.Decompose(scaling, rotation, position);
	
	float xsqr = rotation.x * rotation.x;
	float ysqr = rotation.y * rotation.y;
	float zsqr = rotation.z * rotation.z;

	// roll (x-axis rotation)
	float t0 = +2.0 * (rotation.w * rotation.x + rotation.y * rotation.z);
	float t1 = +1.0 - 2.0 * (xsqr + ysqr);
	rotInEulerAngles.x = std::atan2(t0, t1);

	// pitch (y-axis rotation)
	float t2 = +2.0 * (rotation.w * rotation.y - rotation.z * rotation.x);
	t2 = t2 > 1.0 ? 1.0 : t2;
	t2 = t2 < -1.0 ? -1.0 : t2;
	rotInEulerAngles.y = std::asin(t2);

	// yaw (z-axis rotation)
	float t3 = +2.0 * (rotation.w * rotation.z + rotation.x * rotation.y);
	float t4 = +1.0 - 2.0 * (ysqr + zsqr);
	rotInEulerAngles.z = std::atan2(t3, t4);

	nodo.setPosX(position.x);
	nodo.setPosY(position.y);
	nodo.setPosZ(position.z);
	nodo.setScale(scaling.x, scaling.y, scaling.z);
	nodo.setRotation(rotInEulerAngles.x, rotInEulerAngles.y, rotInEulerAngles.z);

	for (size_t j = 0; j < assimpNode.mNumMeshes; j++){
		Mesh& mesh = processMesh(*scene.mMeshes[assimpNode.mMeshes[j]], assimpNode, scene, tree);
		mesh.setParent(&nodo);
		nodo.addChild(mesh);
	}
	
	for (size_t i = 0; i < assimpNode.mNumChildren; i++)
	{
		Nodo* nodoHijo = new Nodo();

		nodo.addChild(*nodoHijo);
		nodoHijo->setParent(&nodo);

		processNode(*nodoHijo, *assimpNode.mChildren[i], scene, tree);
	}

	return true;
}
//=============================================================================================================
Mesh& Importer::processMesh(aiMesh& assimpMesh, aiNode& assimpNode, const aiScene& scene, bspTree &tree){
	Mesh* mesh = new Mesh(_renderer);
	string name = assimpNode.mName.C_Str();
	mesh->setName(name + "_mesh");
	cout << mesh->getName() << endl;
	TexturedVertex* verts = new TexturedVertex[assimpMesh.mNumVertices];
	if (assimpMesh.HasTextureCoords(0)){
		for (size_t i = 0; i < assimpMesh.mNumVertices; i++)
		{
			verts[i] = { assimpMesh.mVertices[i].x,
				assimpMesh.mVertices[i].y,
				assimpMesh.mVertices[i].z,
				assimpMesh.mTextureCoords[0][i].x,
				assimpMesh.mTextureCoords[0][i].y
			};
		}
	}

	else{
		for (size_t i = 0; i < assimpMesh.mNumVertices; i++){
			verts[i] = { assimpMesh.mVertices[i].x,
				assimpMesh.mVertices[i].y,
				assimpMesh.mVertices[i].z,
			};
		}
	}

	unsigned int faces = assimpMesh.mNumFaces;

	unsigned int numIndices = assimpMesh.mNumFaces * 3;
	unsigned short* indices = new unsigned short[numIndices];
	int index = 0;

	for (unsigned int i = 0; i < assimpMesh.mNumFaces; i++)
	{
		indices[i * 3 + 0] = assimpMesh.mFaces[i].mIndices[0];
		indices[i * 3 + 1] = assimpMesh.mFaces[i].mIndices[1];
		indices[i * 3 + 2] = assimpMesh.mFaces[i].mIndices[2];
	}

	mesh->setMeshData(verts, TRIANGLELIST, assimpMesh.mNumVertices, indices, numIndices);
	mesh->buildAABB();
	aiVector3t<float> position, scaling;
	aiQuaterniont<float> rotation;
	assimpNode.mTransformation.Decompose(scaling, rotation, position);

	mesh->setNumPolygons(faces);
	
	mesh->setPosX(position.x);
	mesh->setPosY(position.y);
	mesh->setPosZ(position.z);
	mesh->setScale(scaling.x, scaling.y, scaling.z);
	mesh->setRotation(rotation.x, rotation.y, rotation.z);
	cout << mesh->posX() << " " << mesh->posY() << " " << mesh->posZ() << endl;
	
	mesh->updateWorldTransformation();
	mesh->updateBV();

	aiString path;
	std::stack<char> _stack;
	if (scene.mMaterials[assimpMesh.mMaterialIndex]->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
	{
		string fullPath = path.data;
		for (size_t i = fullPath.length(); i > 0; i--){
			if (fullPath[i] == '/')
				break;

			_stack.push(fullPath[i - 1]);
		}

		fullPath.clear();
		while (!_stack.empty()){
			fullPath += _stack.top();
			_stack.pop();
		}
		mesh->setTextureId(0, _renderer.loadTexture("Assets/" + fullPath, D3DCOLOR_XRGB(255, 0, 255)));
	}

	size_t buscar = mesh->getName().find("Plane");

	if (buscar != string::npos)
	{
		D3DXVECTOR3 *pV1 = new D3DXVECTOR3(mesh->getAABB().minPointX, mesh->getAABB().minPointY, mesh->getAABB().minPointZ);
		D3DXVECTOR3 *pV2 = new D3DXVECTOR3(mesh->getAABB().maxPointX, mesh->getAABB().minPointY, mesh->getAABB().minPointZ);
		D3DXVECTOR3 *pV3 = new D3DXVECTOR3(mesh->getAABB().maxPointX, mesh->getAABB().maxPointY, mesh->getAABB().minPointZ);

		bspPlane *BSP = new bspPlane();
		BSP->createPlane(pV1, pV2, pV3);
		
		tree.addPlaneToVector(*BSP);
	}
	else
	{
		tree.addMeshToVector(mesh);
	}

	return *mesh;
}
//=============================================================================================================
void Importer::showNodeNames(aiNode& assimpNode, const aiScene& scene){
	cout << assimpNode.mName.C_Str() << endl;
	for (size_t i = 0; i < assimpNode.mNumMeshes; i++)
	{
		showMeshNames(*scene.mMeshes[assimpNode.mMeshes[i]], scene);
	}

	for (size_t i = 0; i < assimpNode.mNumChildren; i++)
	{
		showNodeNames(*assimpNode.mChildren[i], scene);
	}
}
//=============================================================================================================
void Importer::showMeshNames(aiMesh& assimpMesh, const aiScene& scene){
	cout << assimpMesh.mName.C_Str()<<endl;
}
//=============================================================================================================