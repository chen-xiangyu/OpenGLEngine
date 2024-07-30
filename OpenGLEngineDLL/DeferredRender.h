#pragma once
#include "RenderAlgorithm.h"

namespace hiveEngine
{
	class CDeferredRender : public IRenderAlgorithm
	{
	public:
		CDeferredRender() = default;
		~CDeferredRender() = default;

		void init() override;
		void render(const CGLTFModel& vModel) override;

	private:
		GLuint m_GBuffer = 0;
		GLuint m_GPosition = 0;
		GLuint m_GNormal = 0;
		GLuint m_GAlbedoSpec = 0;
		GLuint m_QuadVAO = 0;

		void __renderQuad();
	};
}
