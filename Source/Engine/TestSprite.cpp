#include "stdafx.h"
#include "TestSprite.h"

#include "GLMesh.h"
#include "GLEffect.h"
#include "GLUniformBuffer.h"

#include "VertexStructs.h"

TestSprite::TestSprite()
{
	cu::CVector<wendy::SBaseVertex> vertices;
	vertices.resize(3);
	vertices[0].x = 0.f;
	vertices[0].y = 1.f;
	vertices[0].z = 1.f;

	vertices[1].x = 1.f;
	vertices[1].y = -1.f;
	vertices[1].z = 1.f;

	vertices[2].x = -1.f;
	vertices[2].y = -1.f;
	vertices[2].z = 1.f;

	myMesh = new wendy::CGLMesh();
	myMesh->Init(vertices, { 0, 1, 2 });

	myEffect = new wendy::CGLEffect();
	myEffect->Init("Shaders/shader.vert", "Shaders/shader.frag", { "Pos" }, {});
	myCBuffer = new wendy::CGLUniformBuffer(myEffect->GetUniformBuffer("hej"));
}

TestSprite::~TestSprite()
{
}

void TestSprite::Render()
{
	static float angle = 0.f;
	cu::Matrix33f rotation = cu::Matrix33f::CreateRotateAroundZ(angle);
	angle += 0.001f;

	myCBuffer->SetData(rotation);
	myEffect->Activate();
	myMesh->Draw();
}
