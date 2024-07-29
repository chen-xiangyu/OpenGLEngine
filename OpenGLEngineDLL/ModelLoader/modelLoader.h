#pragma once

#include <memory>
#include <string>
#include "core/Node.h"

namespace hiveGL::loader
{
	std::shared_ptr<hiveGL::CNode> loadModel(const std::string& vFileName, const std::shared_ptr<hiveGL::CMaterial>& vMaterial);
	std::shared_ptr<hiveGL::CNode> loadPointCloud(const std::string& vFileName, const std::shared_ptr<hiveGL::CMaterial>& vMaterial);
}