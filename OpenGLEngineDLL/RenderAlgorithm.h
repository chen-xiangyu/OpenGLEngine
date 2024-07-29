#pragma once
#include "ShaderUnit.h"
#include "GLTFModel.h"

namespace hiveEngine
{
	enum class ERenderAlgorithmType
	{
		FORWARD_RENDER,
		DEFERRED_RENDER,
	};

	const std::map<std::string, ERenderAlgorithmType> RenderAlgorithmTypeMapping = {
		{"forward_render", ERenderAlgorithmType::FORWARD_RENDER},
		{"deferred_render", ERenderAlgorithmType::DEFERRED_RENDER},
	};

	class IRenderAlgorithm
	{
	public:
		IRenderAlgorithm() = default;
		~IRenderAlgorithm() = default;

		virtual void init() = 0;
		virtual void render(const CGLTFModel& vModel) = 0;
		bool isContainShader(const std::string& vShaderName);
		void setUniformToShader(const std::string& vShaderName, const std::string& vUniformName, const std::function<std::any()>& vModifier);

		void addShader(const std::string& vName, const std::string& vVertexFilename, const std::string& vFragmentFilename);
		size_t getNumShaders() const { return m_Shaders.size(); }

	protected:
		std::vector<CShaderUnit> m_Shaders;
	};
}