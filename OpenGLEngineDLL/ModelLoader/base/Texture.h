#pragma once

#include <glad/glad.h>

namespace hiveGL
{
	class CTexture
	{
	public:
		virtual GLuint getID() const = 0;
		virtual void bind() const = 0;
	};
}
