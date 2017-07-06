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

namespace wendy
{
	CEngine::CEngine()
		: myWindow(nullptr)
		, myFramework(nullptr)
		, myRenderer(nullptr)
	{
	}

	CEngine::~CEngine()
	{
	}

	TestSprite2* testSprite = nullptr;

	bool CEngine::Init(const SEngineParameters& aInitParameters)
	{
		
		myWindow = std::make_unique<CGLFWWindow>();
		if (!myWindow->Init(800, 600, "Hello Wengine"))
		{
			return false;
		}

		myFramework = std::make_unique<COpenGLFramework>();
		
		if (!myFramework->Init(800, 600, *myWindow))
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
			DL_MESSAGE_BOX(e.what(), false);
			myIsRunning = false;
			return false;
		}

		myIsRunning = false;

		WorkPool::Shutdown();

		return true;
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
