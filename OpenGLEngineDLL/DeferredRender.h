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

	};
}
