#pragma once

#include "../CommonUtilities/StopWatch.h"

namespace wendy
{
	class CBaseRenderer;
	typedef struct MeshID_t* MeshID;
	typedef struct EffectID_t* EffectID;
	typedef struct TextureID_t* TextureID;
}

class TestSprite2
{
public:
	TestSprite2(wendy::CBaseRenderer& aRenderer);
	~TestSprite2();

	void Render(wendy::CBaseRenderer& aRenderer);

	cu::CStopWatch myStopWatch;

	wendy::MeshID myMesh;
	wendy::EffectID myEffect;
	size_t myConstantBuffer;
	float myAngle;
};
