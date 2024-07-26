#pragma once
#include "Shader.h"

namespace hiveEngine
{
	class CShaderManager
	{
	public:
		CShaderManager() = default;
		~CShaderManager() = default;

		void addShader(const std::string& vVertexFilename, const std::string& vFragmentFilename);
		std::shared_ptr<CShader> getShader(unsigned int vID);
		int getNumShader() const;

	private:
		std::vector<std::shared_ptr<CShader>> m_ShaderList;
	};
}
