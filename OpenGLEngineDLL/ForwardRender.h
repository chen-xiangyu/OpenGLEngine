#pragma once
#include "RenderAlgorithm.h"

namespace hiveEngine
{
	class CForwardRender : public IRenderAlgorithm
	{
	public:
		CForwardRender() = default;
		~CForwardRender() = default;

		void init() override;
		void render(const CGLTFModel& vModel) override;

	private:

	};
}