#pragma once
#include "ShaderUnit.h"

namespace hiveEngine
{
	class CShaderManager
	{
	public:
		CShaderManager() = default;
		~CShaderManager() = default;

		void addShader(const std::string& vVertexFilename, const std::string& vFragmentFilename);
		std::shared_ptr<CShaderUnit> getShader(unsigned int vID);
		size_t getNumShader() const;

	private:
		std::vector<std::shared_ptr<CShaderUnit>> m_ShaderList;
	};
}
