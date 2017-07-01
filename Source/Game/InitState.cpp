#include "stdafx.h"
#include "InitState.h"

#include "../Engine/Engine.h"
#include "../Engine/Scene.h"
#include "../Engine/Model.h"

CInitState::CInitState(CStateStack& aStateStack)
	: CBaseState(aStateStack)
{
}

CInitState::~CInitState()
{
}

bool CInitState::Init()
{
	myScene = wendy::CEngine::GetInstance()->CreateScene();
	myScene->Init();
	myTorus = myScene->AddModel("Meshes/torus.obj");


	wendy::CModel* model = myScene->GetModel(myTorus);
	cu::Matrix44f transform;
	transform.SetScale({ 0.5f, 0.5f, 0.5f });
	transform = transform * cu::Matrix44f::CreateRotateAroundX(3.14f * 0.5f);
	model->SetTransformation(transform);

	return true;
}

bool CInitState::Update()
{
	//wendy::CModel* model = myScene->GetModel(myTorus);
	//cu::Matrix44f transform = model->GetTransformation();
	//transform = transform * cu::Matrix44f::CreateRotateAroundZ(myAngle);
	//model->SetTransformation(transform);
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
