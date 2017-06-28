#pragma once

class CBaseState;

class CStateStack
{
public:
	CStateStack();
	~CStateStack();

	bool Update();
	void Render();

	bool Push(std::unique_ptr<CBaseState> aState);

private:
	void Pop();
	bool UpdateAtIndex(const int aIndex);
	void RenderAtIndex(const int aIndex);

	cu::CVector<std::unique_ptr<CBaseState>> myStates;
};
