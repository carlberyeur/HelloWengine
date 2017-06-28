#include "stdafx.h"

#include "../Engine/Engine.h"
#include "../Game/Game.h"

#include "../CommonUtilities/ObjLoader.h"

//#define USE_WIDE_CHAR

template <typename CharType>
bool Init(int argc, CharType** argv);

#ifdef USE_WIDE_CHAR

int wmain(int argc, wchar_t** argv)
{
	if (!Init(argc, argv))
	{
		return 1336;
	}

	return 0;
}

#else

int main(int argc, char** argv)
{
	if (!Init(argc, argv))
	{
		return 1336;
	}

	return 0;
}

#endif // USE_WIDE_CHAR

template <typename CharType>
bool Init(int /*argc*/, CharType** /*argv*/)
{
	wendy::CEngine engine;
	CGame game;

	wendy::SEngineParameters params = {};
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
