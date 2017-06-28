#include "stdafx.h"
#include "Engine.h"

#include "BaseWindow.h"
#include "BaseFramework.h"
#include "BaseRenderer.h"

#include "Scene.h"

#include "../CommonUtilities/WorkPool.h"
#include "../CommonUtilities/Work.h"

#include "GLFWWindow.h"
#include "Direct3DFramework.h"
#include "OpenGLFramework.h"
#include "OpenGLRenderer.h"
#include "TestSprite2.h"

#ifdef _DEBUG
#define DEBUG_INIT_PARAMETERS() if (!DebugParameters(aInitParameters)) return false;
#else
#define DEBUG_INIT_PARAMETERS()
#endif // _DEBUG


namespace wendy
{
	CEngine::CEngine()
		: myWindow(nullptr)
		, myFramework(nullptr)
		, myRenderer(nullptr)
		, myIsRunning(false)
		, myThreadedRender(false)
	{
	}

	CEngine::~CEngine()
	{
	}

	TestSprite2* testSprite = nullptr;

	bool CEngine::Init(const SEngineParameters& aInitParameters)
	{
		DEBUG_INIT_PARAMETERS();

		myWindow = std::make_unique<CGLFWWindow>();
		if (!myWindow->Init(aInitParameters.windowSize, "Hello Wengine"))
		{
			return false;
		}

		myFramework = std::make_unique<COpenGLFramework>();
		
		if (!myFramework->Init(*myWindow))
		{
			return false;
		}

		myRenderer = std::make_unique<COpenGLRenderer>();

		testSprite = new TestSprite2(*myRenderer);

		myUpdateCallback = aInitParameters.updateCallback;
		myRenderCallback = aInitParameters.renderCallback;

		myThreadedRender = aInitParameters.threadedRendering;

		return true;
	}

	bool CEngine::Run()
	{
		WorkPool::Init(!myThreadedRender);

		myIsRunning = true;
		bool runSuccess = true;
		
		try
		{
			if (myThreadedRender)
			{
				AddRenderWork();
			}

			bool shouldContinue = true;
			while (shouldContinue)
			{
				shouldContinue = Update();
			}
		}
		catch (const std::exception& e)
		{
			DL_MESSAGE_BOX(e.what());
			myIsRunning = false;
			runSuccess = false;
		}

		myIsRunning = false;

		WorkPool::Shutdown();

		return runSuccess;
	}

	bool CEngine::Update()
	{
		myWindow->PollEvents();
		
		myRenderer->SwapCommandBuffer();
		if (!myUpdateCallback())
		{
			return false;
		}

		myRenderCallback();
		testSprite->Render(*myRenderer);

		if (!myThreadedRender)
		{
			Render();
		}

		return myWindow->IsOpen();
	}

	void CEngine::Render()
	{
		myFramework->BeginFrame();
		myRenderer->DoRenderQueue();
		myFramework->EndFrame();
	}

	std::unique_ptr<CScene> CEngine::CreateScene()
	{
		return std::make_unique<CScene>(*myRenderer);
	}

	bool CEngine::DebugParameters(const SEngineParameters& aInitParameters)
	{
		if (aInitParameters.windowSize.Length2() == 0)
		{
			return false;
		}

		if (!aInitParameters.updateCallback)
		{
			return false;
		}

		if (!aInitParameters.renderCallback)
		{
			return false;
		}

		return true;
	}

	void CEngine::AddRenderWork()
	{
		myWindow->MakeContextCurrent(nullptr);
		auto renderFunction = [this]()
		{
			myRenderer->Start(*myWindow);

			while (myIsRunning)
			{
				Render();
			}
		};

		Work renderWork(renderFunction);
		renderWork.SetName("Render thread");
		WorkPool::AddWork(std::move(renderWork));
	}
}
