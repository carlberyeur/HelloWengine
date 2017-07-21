#include "stdafx.h"
#include "InitState.h"

#include "../Engine/Engine.h"
#include "../Engine/Scene.h"
#include "../Engine/Model.h"

CInitState::CInitState(CStateStack& aStateStack)
	: CBaseState(aStateStack)
	//, myTorus(SIZE_MAX)
	, myTumbleWeed(SIZE_MAX)
	, myAngle(0.f)
{
}

CInitState::~CInitState()
{
}

bool CInitState::Init()
{
	myScene = wendy::CEngine::GetInstance()->CreateScene();
	myScene->Init();
	
	//myTorus = myScene->AddModel("Meshes/sphere.fbx");

	//myTorus = myScene->AddModel("Meshes/torus.obj");
	//wendy::CModel* model = myScene->GetModel(myTorus);
	//cu::Matrix44f transform;
	//transform.SetScale({ 0.5f, 0.5f, 0.5f });
	//transform = transform * cu::Matrix44f::CreateRotateAroundX(3.14f * 0.5f);
	//model->SetTransformation(transform);

	myTumbleWeed = myScene->AddModel("Meshes/M_thumbleweed_01.fbx", wendy::eRenderPipeline_Model);
	wendy::CModel* model2 = myScene->GetModel(myTumbleWeed, wendy::eRenderPipeline_Model);
	cu::Matrix44f transform2;
	transform2.SetScale({ 0.5f, 0.5f, 0.5f });
	model2->SetTransformation(transform2);
	model2->SetPosition(0.f, 0.f, -10.f);

	myStopWatch.Init();

	return true;
}

bool CInitState::Update()
{
	myStopWatch.Update();

	wendy::CModel* model = myScene->GetModel(myTumbleWeed, wendy::eRenderPipeline_Model);
	//cu::Matrix44f transform = model->GetTransformation();
	cu::Matrix44f transform;
	transform.SetScale({ 0.5f, 0.5f, 0.5f });
	transform = transform * cu::Matrix44f::CreateRotateAroundX(3.14f * 0.5f);
	transform = transform * cu::Matrix44f::CreateRotateAroundZ(myAngle);
	myAngle += myStopWatch.GetDeltaTime().GetSeconds() * 0.9f;
	model->SetTransformation(transform);

	return myShouldContinue;
}

void CInitState::Render()
{
	myScene->Render();
}

void CInitState::OnEnter()
{
}

void CInitState::OnExit()
{
}

bool CInitState::LetThroughUpdate()
{
	return false;
}

bool CInitState::LetThroughRender()
{
	return false;
}
