#pragma once

namespace wendy
{
	class CBaseRenderer;

	class CScene
	{
	public:
		CScene(CBaseRenderer& aRenderer);
		~CScene();

		void Render();

	private:
		CBaseRenderer& myRenderer;
	};
}
