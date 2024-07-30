#pragma once
#include "RenderAlgorithm.h"
#include "GLTFModel.h"

namespace hiveEngine
{
	class CRenderManager
	{
	public:
		CRenderManager() = default;
		~CRenderManager() = default;

		void addRenderAlgorithm(const std::string& vName, const std::shared_ptr<IRenderAlgorithm>& vAlgorithm);
		void setUniformToShader(const std::string& vShaderName, const std::string& vUniformName, const std::function<std::any()>& vModifier);

		void render(const CGLTFModel& vModel);
		bool changeRenderAlgorithm(const std::string& vAlgorithmName);

	private:
		std::map<std::string, std::shared_ptr<IRenderAlgorithm>> m_RenderAlgorithms;
		std::shared_ptr<IRenderAlgorithm> m_pCurrentAlgorithm = nullptr;
	};
}