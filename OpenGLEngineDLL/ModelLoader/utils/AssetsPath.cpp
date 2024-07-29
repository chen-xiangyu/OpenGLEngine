
#include "AssetsPath.h"
#include "HiveLogger.h"

namespace hiveGL
{
	std::string CAssetsPath::m_AssetsPath{};

	const std::string& CAssetsPath::getAssetsPath()
	{
		if (!m_AssetsPath.empty()) return m_AssetsPath;
		char* Buf = nullptr;
		size_t Size = 0;
		if (_dupenv_s(&Buf, &Size, "ASSETS_PATH") == 0 && Buf != nullptr)
		{
			m_AssetsPath = Buf;
			free(Buf);
			return m_AssetsPath;
		}
		HIVE_LOG_WARNING("environment variable ASSETS_PATH is not defined");
		return m_AssetsPath;
	}

	std::string CAssetsPath::extractFileName(const std::string& vFilePath)
	{
		size_t Pos = vFilePath.find_last_of("/\\");
		if (Pos == std::string::npos) return vFilePath;
		return vFilePath.substr(Pos + 1);
	}
}