#include "stdafx.h"

#include "../Engine/Engine.h"
#include "../Game/Game.h"

//#define USE_WIDE_CHAR

template <typename CharType>
bool Init(int argc, CharType** argv);

#ifdef USE_WIDE_CHAR
int wmain(int argc, wchar_t** argv)
#else
int main(int argc, char** argv)
#endif // USE_WIDE_CHAR
{
	if (!Init(argc, argv))
	{
		return 1336;
	}

	return 0;
}


template <typename CharType>
bool Init(int /*argc*/, CharType** /*argv*/)
{
	pulp::CEngine engine;
	CGame game;

	pulp::SEngineParameters params = {};
	params.updateCallback = [&game]() -> bool { return game.Update(); };
	params.renderCallback = [&game]() { game.Render(); };
	params.threadedRendering = true;
	params.windowSize.Set(800u, 600u);

	if (!engine.Init(params))
	{
		return false;
	}

	if (!game.Init())
	{
		return false;
	}

	bool startSuccess = engine.Run();

	return startSuccess;
}
