#include "stdafx.h"
#include "TestSprite2.h"

#include "BaseRenderer.h"
#include "VertexStructs.h"
#include "RenderModelCommand.h"


TestSprite2::TestSprite2(wendy::CBaseRenderer& aRenderer)
{
	myAngle = 0.f;

	wendy::SEffectDesc eff;
	eff.vertexPath = "Shaders/shader.vert";
	eff.pixelPath = "Shaders/shader.frag";
	eff.inputAttributes = { "Pos" };
	eff.constantBuffers = { "hej" };

	myConstantBuffer = std::hash<std::string>()("hej");
	myEffect = aRenderer.CreateEffect(eff);

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

	wendy::SMeshDesc mesh;
	mesh.vertices.AddChunk(vertices.data(), vertices.ByteSize<>());
	mesh.vertexCount = vertices.Size<int>();
	mesh.vertexSize = sizeof(wendy::SBaseVertex);
	mesh.indices = { 0, 1, 2 };
	mesh.attributeInfos = wendy::SBaseVertex::AttributeInfos;

	myMesh = aRenderer.CreateMesh(mesh);

	myStopWatch.Init();
}

TestSprite2::~TestSprite2()
{
}

void TestSprite2::Render(wendy::CBaseRenderer& aRenderer)
{
	myStopWatch.Update();

	cu::Matrix33f rotation = cu::Matrix33f::CreateRotateAroundZ(myAngle);
	myAngle += myStopWatch.GetDeltaTime().GetSeconds();

	wendy::CRenderModelCommand* renderCmd = new wendy::CRenderModelCommand(myMesh, myEffect, myConstantBuffer, rotation, 0);
	aRenderer.AddRenderCommand(renderCmd);
}
