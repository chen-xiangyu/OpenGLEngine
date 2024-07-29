
#include "modelLoader.h"
#include "happly/happly.h"
#include "tinygltf/tiny_gltf.h"
#include "base/VertexArrayBuffer.h"
#include "HiveLogger.h"
#include "core/Scene.h"
#include "gizmos/AABBGizmo.h"
#include <glm/gtc/quaternion.hpp>


#define MODE_DEFAULT -1 
#define MODE_POINT 0
#define MODE_TRIANGLE 4 
#define COMPONETTYPE_UNSHORT 5123
#define COMPONETTYPE_UNINT   5125

namespace hiveGL::loader
{
	std::vector<float> computeColors(const std::vector<float>& vPoints, const std::vector<float>& vFeatures) {
		std::vector<float> colors(vPoints.size(), 0.5f); // 初始化为灰色
		float minZ = vPoints[0];
		float maxZ = vPoints[0];

		// 找到 特征值 的最小值和最大值
		for (size_t i = 0; i < vPoints.size(); i += 3) {
			minZ = std::min(minZ, vFeatures[i]);
			maxZ = std::max(maxZ, vFeatures[i]);
		}

		// 根据 特征值 计算颜色，使用 CloudCompare 的标准进行映射
		for (size_t i = 0; i < vPoints.size(); i += 3) {
			float f = vFeatures[i];
			float t = (f - minZ) / (maxZ - minZ);

			// 按照 CloudCompare 的标准颜色映射
			float r, g, b;
			if (t <= 0.25f) {
				r = 0;
				g = 4 * t;
				b = 1;
			}
			else if (t <= 0.5f) {
				r = 0;
				g = 1;
				b = 1 - 4 * (t - 0.25f);
			}
			else if (t <= 0.75f) {
				r = 4 * (t - 0.5f);
				g = 1;
				b = 0;
			}
			else {
				r = 1;
				g = 1 - 4 * (t - 0.75f);
				b = 0;
			}

			colors[i] = r;
			colors[i + 1] = g;
			colors[i + 2] = b;
		}

		return colors;
	}

	void readTxt(std::string vInputTxt, std::vector<float>& vPoints, std::vector<float>& vColors, std::vector<float>& vFeatures)
	{
		std::fstream modelRead;
		modelRead.open(vInputTxt, std::ios_base::in);
		float x, y, z, r, g, b;
		float featureA, featureB, featureC;
		float scalarA, scalarB, scalarC;
		while (!modelRead.eof())
		{
			modelRead >> x >> y >> z >> r >> g >> b >> featureA >> featureB >> featureC >> scalarA >> scalarB >> scalarC;
			vPoints.push_back(x);
			vPoints.push_back(y);
			vPoints.push_back(z);
			vColors.push_back(r / 255.0f);
			vColors.push_back(g / 255.0f);
			vColors.push_back(b / 255.0f);
			vFeatures.push_back(featureA);
			vFeatures.push_back(featureB);
			vFeatures.push_back(featureC);
		}
		modelRead.close();
		return;
	}

	void computeMinMaxVectors(const std::vector<float>& vVector, glm::vec3& vMinVec, glm::vec3& vMaxVec) {
		vMinVec = glm::vec3(vVector[0], vVector[1], vVector[2]);
		vMaxVec = glm::vec3(vVector[0], vVector[1], vVector[2]);

		for (size_t i = 0; i < vVector.size(); i += 3) {
			glm::vec3 point(vVector[i], vVector[i + 1], vVector[i + 2]);
			vMinVec = glm::min(vMinVec, point);
			vMaxVec = glm::max(vMaxVec, point);
		}
	}

	bool generateGLTF(const std::string& vFilename, const std::vector<float>& vPoints, const std::vector<float>& vColors, const std::vector<float>& vNormals) {
		tinygltf::Model model;
		tinygltf::TinyGLTF gltf;
		tinygltf::Buffer buffer;
		tinygltf::Primitive primitive;
		glm::vec3 minVec, maxVec;

		buffer.data.resize(vPoints.size() * sizeof(float) + vColors.size() * sizeof(float) + vNormals.size() * sizeof(float));
		size_t offset = 0;

		memcpy(buffer.data.data() + offset, vPoints.data(), vPoints.size() * sizeof(float));
		offset += vPoints.size() * sizeof(float);

		tinygltf::BufferView posBufferView;
		posBufferView.buffer = 0;
		posBufferView.byteOffset = 0;
		posBufferView.byteLength = vPoints.size() * sizeof(float);
		posBufferView.target = TINYGLTF_TARGET_ARRAY_BUFFER;
		model.bufferViews.push_back(posBufferView);

		tinygltf::Accessor posAccessor;
		posAccessor.bufferView = 0;
		posAccessor.byteOffset = 0;
		posAccessor.componentType = TINYGLTF_COMPONENT_TYPE_FLOAT;
		posAccessor.count = vPoints.size() / 3;
		posAccessor.type = TINYGLTF_TYPE_VEC3;
		computeMinMaxVectors(vPoints, minVec, maxVec);
		posAccessor.minValues = std::vector<double>{ minVec.x, minVec.y, minVec.z };
		posAccessor.maxValues = std::vector<double>{ maxVec.x, maxVec.y, maxVec.z };
		model.accessors.push_back(posAccessor);

		primitive.attributes["POSITION"] = 0;

		memcpy(buffer.data.data() + offset, vColors.data(), vColors.size() * sizeof(float));
		offset += vColors.size() * sizeof(float);

		tinygltf::BufferView colorBufferView;
		colorBufferView.buffer = 0;
		colorBufferView.byteOffset = vPoints.size() * sizeof(float);
		colorBufferView.byteLength = vColors.size() * sizeof(float);
		colorBufferView.target = TINYGLTF_TARGET_ARRAY_BUFFER;
		model.bufferViews.push_back(colorBufferView);

		tinygltf::Accessor colorAccessor;
		colorAccessor.bufferView = 1;
		colorAccessor.byteOffset = 0;
		colorAccessor.componentType = TINYGLTF_COMPONENT_TYPE_FLOAT;
		colorAccessor.count = vColors.size() / 3;
		colorAccessor.type = TINYGLTF_TYPE_VEC3;
		computeMinMaxVectors(vColors, minVec, maxVec);
		colorAccessor.minValues = std::vector<double>{ minVec.x, minVec.y, minVec.z };
		colorAccessor.maxValues = std::vector<double>{ maxVec.x, maxVec.y, maxVec.z };
		model.accessors.push_back(colorAccessor);

		primitive.attributes["COLOR_0"] = 1;

		if (vNormals.size() != 0) {
			memcpy(buffer.data.data() + offset, vNormals.data(), vNormals.size() * sizeof(float));
			model.buffers.push_back(buffer);

			tinygltf::BufferView normalBufferView;
			normalBufferView.buffer = 0;
			normalBufferView.byteOffset = vPoints.size() * sizeof(float) + vColors.size() * sizeof(float);
			normalBufferView.byteLength = vNormals.size() * sizeof(float);
			normalBufferView.target = TINYGLTF_TARGET_ARRAY_BUFFER;
			model.bufferViews.push_back(normalBufferView);

			tinygltf::Accessor normalAccessor;
			normalAccessor.bufferView = 2;
			normalAccessor.byteOffset = 0;
			normalAccessor.componentType = TINYGLTF_COMPONENT_TYPE_FLOAT;
			normalAccessor.count = vNormals.size() / 3;
			normalAccessor.type = TINYGLTF_TYPE_VEC3;
			computeMinMaxVectors(vNormals, minVec, maxVec);
			normalAccessor.minValues = std::vector<double>{ minVec.x, minVec.y, minVec.z };
			normalAccessor.maxValues = std::vector<double>{ maxVec.x, maxVec.y, maxVec.z };
			model.accessors.push_back(normalAccessor);

			primitive.attributes["NORMAL"] = 2;
		}

		primitive.mode = TINYGLTF_MODE_POINTS;
		model.buffers.push_back(buffer);

		tinygltf::Mesh mesh;
		mesh.primitives.push_back(primitive);
		model.meshes.push_back(mesh);

		tinygltf::Node node;
		node.mesh = 0;
		model.nodes.push_back(node);

		tinygltf::Scene scene;
		scene.nodes.push_back(0);
		model.scenes.push_back(scene);
		model.defaultScene = 0;

		tinygltf::Asset asset;
		asset.version = "2.0";
		asset.generator = "tinygltf";
		model.asset = asset;

		return gltf.WriteGltfSceneToFile(&model, vFilename, true, true, true, false);
	}

	bool loadGLTF(const std::string& vFilename, tinygltf::Model& vModelGLTF)
	{
		tinygltf::TinyGLTF loader;
		std::string err;
		std::string warn;

		bool res = loader.LoadASCIIFromFile(&vModelGLTF, &err, &warn, vFilename);

		if (!warn.empty()) {
			HIVE_LOG_WARNING("WARN: {}", warn);
		}

		if (!err.empty()) {
			HIVE_LOG_ERROR("ERR: {}", err);
		}

		if (!res) {
			HIVE_LOG_ERROR("Failed to load glTF: {}", vFilename);
		}
		else {
			HIVE_LOG_INFO("Loaded glTF: {}", vFilename);
		}

		return res;
	}

	void createIndiceBufferData(std::vector<unsigned int>& vIndices, const tinygltf::BufferView& vBufferView, const tinygltf::Buffer& vBuffer, const int& vComponentType) {
		unsigned short tempUShortIndice;
		unsigned int   tempUIntIndice;
		const int unShortByte = 2;
		const int unIntByte = 4;
		if (vComponentType == COMPONETTYPE_UNSHORT) {
			for (size_t i = vBufferView.byteOffset; i < vBufferView.byteOffset + vBufferView.byteLength; i += unShortByte) {
				std::memcpy(&tempUShortIndice, &vBuffer.data.at(i), sizeof(unsigned short));
				vIndices.push_back(tempUShortIndice);
			}
		}
		else if (vComponentType == COMPONETTYPE_UNINT) {
			for (size_t i = vBufferView.byteOffset; i < vBufferView.byteOffset + vBufferView.byteLength; i += unIntByte) {
				std::memcpy(&tempUIntIndice, &vBuffer.data.at(i), sizeof(unsigned int));
				vIndices.push_back(tempUIntIndice);
			}
		}
	}

	void createVertexBufferData(std::vector<float>& vVertices, const tinygltf::Buffer& vBuffer, const int vIndex) {
		float tempVertice;
		const int floatByte = 4;
		const int floatNum = 3;
		for (auto i = vIndex; i < vIndex + floatNum * floatByte; i += floatByte) {
			std::memcpy(&tempVertice, &vBuffer.data.at(i), sizeof(float));
			vVertices.push_back(tempVertice);
		}
	}

	void setCNodeTransform(std::shared_ptr<hiveGL::CNode> vPNode, const tinygltf::Node& vModelNode) {
		if (vModelNode.translation.size() == 3) {
			glm::vec3 tempPosition = glm::vec3((float)vModelNode.translation[0], (float)vModelNode.translation[1], (float)vModelNode.translation[2]);
			vPNode->setPosition(tempPosition);
		}
		if (vModelNode.rotation.size() == 4) {
			glm::quat tempRotationQuat = glm::quat((float)vModelNode.rotation[3], (float)vModelNode.rotation[0], (float)vModelNode.rotation[1], (float)vModelNode.rotation[2]);
			glm::vec3 euler = glm::eulerAngles(tempRotationQuat);
			glm::vec3 tempRotation = glm::degrees(euler);
			vPNode->setRotation(tempRotation);
		}
		if (vModelNode.scale.size() == 3) {
			glm::vec3 tempScale = glm::vec3((float)vModelNode.scale[0], (float)vModelNode.scale[1], (float)vModelNode.scale[2]);
			vPNode->setScale(tempScale);
		}
	}

	void createCNode(tinygltf::Model& vGLTFModel, std::shared_ptr<hiveGL::CNode> vParentNode, const std::shared_ptr<hiveGL::CMaterial>& vMaterial)
	{
		std::vector<float> Vertices;
		std::vector<unsigned int> Indices;
		for (auto& node : vGLTFModel.nodes) {
			if (node.mesh == -1) continue;
			const auto& mesh = vGLTFModel.meshes[node.mesh];
			std::string MeshName = mesh.name;
			HIVE_LOG_INFO("MeshName : {}", MeshName);
			const auto& pChildNode = std::make_shared<hiveGL::CNode>(MeshName);

			for (auto& primitive : mesh.primitives) {
				Vertices.clear();
				if (primitive.mode == MODE_POINT) {
					const tinygltf::Accessor& accessorPos = vGLTFModel.accessors[primitive.attributes.at("POSITION")];
					const tinygltf::BufferView& bufferViewPos = vGLTFModel.bufferViews[accessorPos.bufferView];
					const tinygltf::Buffer& bufferPos = vGLTFModel.buffers[bufferViewPos.buffer];
					const tinygltf::Accessor& accessorCol = vGLTFModel.accessors[primitive.attributes.at("COLOR_0")];
					const tinygltf::BufferView& bufferViewCol = vGLTFModel.bufferViews[accessorCol.bufferView];
					const tinygltf::Buffer& bufferCol = vGLTFModel.buffers[bufferViewCol.buffer];
					glm::vec3 MinPos(accessorPos.minValues[0], accessorPos.minValues[1], accessorPos.minValues[2]);
					glm::vec3 MaxPos(accessorPos.maxValues[0], accessorPos.maxValues[1], accessorPos.maxValues[2]);

					const int vec3Byte = 12;
					for (size_t i = bufferViewPos.byteOffset, k = bufferViewCol.byteOffset;
						(i < bufferViewPos.byteOffset + bufferViewPos.byteLength && k < bufferViewCol.byteOffset + bufferViewCol.byteLength);
						i += vec3Byte, k += vec3Byte) {
						createVertexBufferData(Vertices, bufferPos, (int)i);
						createVertexBufferData(Vertices, bufferCol, (int)k);
					}
					
					HIVE_LOG_INFO("Vertices.size : {}", Vertices.size());
					assert(Vertices.size() == vGLTFModel.accessors[primitive.attributes.at("POSITION")].count * 3 * 2);

					const auto& pVAO = std::make_shared<hiveGL::CVertexArrayBuffer>(Vertices, std::vector<int>{3, 3}, GL_POINTS);
					const auto& pModel = std::make_shared<hiveGL::CModel>(pVAO, vMaterial);
					pChildNode->setPosition(-(MinPos + MaxPos) / 2.0f);
					pChildNode->addModel(pModel);
				}
				else if (primitive.mode == MODE_TRIANGLE or primitive.mode == MODE_DEFAULT) {
					Vertices.clear();
					Indices.clear();
					const tinygltf::BufferView& bufferViewInd = vGLTFModel.bufferViews[vGLTFModel.accessors[primitive.indices].bufferView];
					const tinygltf::Buffer& bufferInd = vGLTFModel.buffers[bufferViewInd.buffer];
					const int indiceComponentType = vGLTFModel.accessors[primitive.indices].componentType;

					createIndiceBufferData(Indices, bufferViewInd, bufferInd, indiceComponentType);
					HIVE_LOG_INFO("indice.size : {}", Indices.size());
					assert(Indices.size() == vGLTFModel.accessors[primitive.indices].count);

					const tinygltf::BufferView& bufferViewPos = vGLTFModel.bufferViews[vGLTFModel.accessors[primitive.attributes.at("POSITION")].bufferView];
					const tinygltf::Buffer& bufferPos = vGLTFModel.buffers[bufferViewPos.buffer];
					const tinygltf::BufferView& bufferViewNor = vGLTFModel.bufferViews[vGLTFModel.accessors[primitive.attributes.at("NORMAL")].bufferView];
					const tinygltf::Buffer& bufferNor = vGLTFModel.buffers[bufferViewNor.buffer];

					assert(bufferViewPos.byteLength == bufferViewNor.byteLength);

					const int vec3Byte = 12;
					for (size_t i = bufferViewPos.byteOffset, k = bufferViewNor.byteOffset;
						(i < bufferViewPos.byteOffset + bufferViewPos.byteLength && k < bufferViewNor.byteOffset + bufferViewNor.byteLength);
						i += vec3Byte, k += vec3Byte) {

						createVertexBufferData(Vertices, bufferPos, (int)i);
						createVertexBufferData(Vertices, bufferNor, (int)k);
					}
					HIVE_LOG_INFO("Vertices.size : {}", Vertices.size());
					assert(Vertices.size() == vGLTFModel.accessors[primitive.attributes.at("POSITION")].count * 6);
					const auto& pVAO = std::make_shared<hiveGL::CVertexArrayBuffer>(Vertices, Indices, std::vector<int>{3, 3});
					const auto& pModel = std::make_shared<hiveGL::CModel>(pVAO, vMaterial);
					pChildNode->addModel(pModel);
					setCNodeTransform(pChildNode, node);
				}
			}
			vParentNode->addChild(pChildNode);
		}
		return;
	}

	std::shared_ptr<hiveGL::CNode> loadModel(const std::string& vFileName, const std::shared_ptr<hiveGL::CMaterial>& vMaterial)
	{
		tinygltf::Model GLTFModel;
		const auto& pParentNode = std::make_shared<hiveGL::CNode>("ParentNode");
		if (!loadGLTF(vFileName, GLTFModel)) return nullptr;
		createCNode(GLTFModel, pParentNode, vMaterial);
		return pParentNode;
	}

	std::shared_ptr<hiveGL::CNode> loadPointCloud(const std::string& vFileName, const std::shared_ptr<hiveGL::CMaterial>& vMaterial)
	{
		happly::PLYData PlyIn(vFileName, true);
		std::vector<double> PosX = PlyIn.getElement("vertex").getProperty<double>("x");
		std::vector<double> PosY = PlyIn.getElement("vertex").getProperty<double>("y");
		std::vector<double> PosZ = PlyIn.getElement("vertex").getProperty<double>("z");
		std::vector<unsigned char> ColorR = PlyIn.getElement("vertex").getProperty<unsigned char>("red");
		std::vector<unsigned char> ColorG = PlyIn.getElement("vertex").getProperty<unsigned char>("green");
		std::vector<unsigned char> ColorB = PlyIn.getElement("vertex").getProperty<unsigned char>("blue");
		std::vector<float> Vertices;
		if (PosX.size() == 0) HIVE_LOG_WARNING("point cloud: {} is empty!", vFileName);
		glm::vec3 MinPos(PosX[0], PosY[0], PosZ[0]);
		glm::vec3 MaxPos(MinPos);
		for (size_t i = 0; i < PosX.size(); ++i)
		{
			Vertices.push_back(static_cast<float>(PosX[i]));
			Vertices.push_back(static_cast<float>(PosY[i]));
			Vertices.push_back(static_cast<float>(PosZ[i]));
			Vertices.push_back(ColorR[i] / 255.0f);
			Vertices.push_back(ColorG[i] / 255.0f);
			Vertices.push_back(ColorB[i] / 255.0f);
			MinPos.x = std::min((float)PosX[i], MinPos.x);
			MinPos.y = std::min((float)PosY[i], MinPos.y);
			MinPos.z = std::min((float)PosZ[i], MinPos.z);
			MaxPos.x = std::max((float)PosX[i], MaxPos.x);
			MaxPos.y = std::max((float)PosY[i], MaxPos.y);
			MaxPos.z = std::max((float)PosZ[i], MaxPos.z);
		}
		const auto& pVAO = std::make_shared<hiveGL::CVertexArrayBuffer>(Vertices, std::vector<int>{3, 3}, GL_POINTS);
		const auto& pModel = std::make_shared<hiveGL::CModel>(pVAO, vMaterial);
		const auto& pNode = std::make_shared<hiveGL::CNode>(vFileName);
		pNode->addModel(pModel);
		const auto& pAABB = std::make_shared<hiveGL::CAABB>(MinPos, MaxPos);
		pNode->addChild(std::make_shared<hiveGL::CAABBGizmo>(pAABB));
		pNode->setPosition(-(MinPos + MaxPos) / 2.0f);
		return pNode;
	}
}