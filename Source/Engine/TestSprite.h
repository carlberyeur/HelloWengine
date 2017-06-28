#pragma once

namespace wendy
{
	class CGLMesh;
	class CGLEffect;
	class CGLUniformBuffer;
}

class TestSprite
{
public:
	TestSprite();
	~TestSprite();

	void Render();

	wendy::CGLMesh* myMesh;
	wendy::CGLEffect* myEffect;
	wendy::CGLUniformBuffer* myCBuffer;
};

