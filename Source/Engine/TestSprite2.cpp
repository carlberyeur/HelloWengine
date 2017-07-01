#include "stdafx.h"
#include "TestSprite2.h"

#include "BaseRenderer.h"
#include "VertexStructs.h"
#include "RenderModelCommand.h"
#include "SetCullModeCommand.h"

#include "../CommonUtilities/ObjLoader.h"

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

	cu::CVector<std::uint32_t> indices = { 1, 2, 3 };


	vertices.clear();
	cu::CObjLoader loader;
	cu::CObjLoader::SIndexedMeshData objData;
	loader.LoadObjFile("Meshes/torus.obj", objData);
	for (const auto& vertex : objData.vertices)
	{
		wendy::SBaseVertex temp;
		temp.x = vertex.position.x * 0.5f;
		temp.y = vertex.position.y * 0.5f;
		temp.z = vertex.position.z * 0.5f;

		temp.u = vertex.uv.x;
		temp.v = vertex.uv.y;

		vertices.push_back(temp);
	}
	indices = objData.indices;

	wendy::SMeshDesc mesh;
	mesh.vertices.AddChunk(vertices.data(), vertices.ByteSize<>());
	mesh.vertexCount = vertices.Size<int>();
	mesh.vertexSize = sizeof(wendy::SBaseVertex);
	mesh.indices = indices;
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

	cu::Matrix33f rotation;
	rotation = cu::Matrix33f::CreateRotateAroundX(3.14f * 0.5f);
	rotation *= cu::Matrix33f::CreateRotateAroundZ(myAngle);

	myAngle += myStopWatch.GetDeltaTime().GetSeconds() * 0.5f;

	//wendy::CSetCullModeCommand* cullCmd = new wendy::CSetCullModeCommand(wendy::eCullMode::eCullMode_Back | wendy::eCullMode::eCullMode_Fill);
	//aRenderer.AddRenderCommand(cullCmd);

	//wendy::CRenderModelCommand* renderCmd = new wendy::CRenderModelCommand(myMesh, myEffect, myConstantBuffer, rotation, nullptr);
	//aRenderer.AddRenderCommand(renderCmd);
}
