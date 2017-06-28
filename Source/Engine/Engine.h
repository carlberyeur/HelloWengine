#pragma once

namespace wendy
{
	class CBaseWindow;
	class CBaseFramework;
	class CBaseRenderer;

	class CScene;

	struct SEngineParameters
	{
		cu::CFunction<bool> updateCallback;
		cu::CFunction<void> renderCallback;
		
		cu::Vector2ui windowSize;
		
		//bool fullscreen : 1;
		//bool vsync : 1;
		bool threadedRendering : 1;
	};

	class CEngine
	{
	public:
		CEngine();
		CEngine(const CEngine& aCopy) = delete;
		~CEngine();

		bool Init(const SEngineParameters& aInitParameters);
		bool Run();
		bool Update();
		void Render();

		std::unique_ptr<CScene> CreateScene();

	private:
		bool DebugParameters(const SEngineParameters& aInitParameters);
		void AddRenderWork();

		cu::CFunction<bool> myUpdateCallback;
		cu::CFunction<void> myRenderCallback;

		std::unique_ptr<CBaseWindow> myWindow;
		std::unique_ptr<CBaseFramework> myFramework;
		std::unique_ptr<CBaseRenderer> myRenderer;

		std::atomic_bool myIsRunning;
		bool myThreadedRender;
	};
}
