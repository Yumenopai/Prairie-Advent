#pragma once

#include <map>
#include <filesystem>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include "Model.h"

class AssimpImporter
{
private:
	using MeshList = std::vector<Model::Mesh>;
	using MaterialList = std::vector<Model::Material>;
	using NodeList = std::vector<Model::Node>;
	using AnimationList = std::vector<Model::Animation>;

public:
	AssimpImporter(const char* filename);

	// ノードデータを読み込み
	void LoadNodes(NodeList& nodes);

	// メッシュデータを読み込み
	void LoadMeshes(MeshList& meshes, const NodeList& nodes);

	// マテリアルデータを読み込み
	void LoadMaterials(MaterialList& materials);

	// アニメーションデータを読み込み
	void LoadAnimations(AnimationList& animations, const NodeList& nodes);

private:
	// ノードデータを再帰読み込み
	void LoadNodes(NodeList& nodes, const aiNode* aNode, int parentIndex);

	// メッシュデータを読み込み
	void LoadMeshes(MeshList& meshes, const NodeList& nodes, const aiNode* aNode);

	// ノードインデックス取得
	static int GetNodeIndex(const NodeList& nodes, const char* name);

	// aiVector3D → XMFLOAT2
	static DirectX::XMFLOAT2 AssimpImporter::aiVector3DToXMFLOAT2(const aiVector3D& aValue);

	// aiVector3D → XMFLOAT3
	static DirectX::XMFLOAT3 AssimpImporter::aiVector3DToXMFLOAT3(const aiVector3D& aValue);

	// aiColor3D → XMFLOAT4
	static DirectX::XMFLOAT4 AssimpImporter::aiColor3DToXMFLOAT4(const aiColor3D& aValue);

	// aiQuaternion → XMFLOAT4
	static DirectX::XMFLOAT4 aiQuaternionToXMFLOAT4(const aiQuaternion& aValue);

	// aiMatrix4x4 → XMFLOAT4X4
	static DirectX::XMFLOAT4X4 aiMatrix4x4ToXMFLOAT4X4(const aiMatrix4x4& aValue);

private:
	std::filesystem::path			filepath;
	std::map<const aiNode*, int>	nodeIndexMap;
	Assimp::Importer				aImporter;
	const aiScene*					aScene = nullptr;
};
