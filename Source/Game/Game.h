#pragma once

class CStateStack;

class CGame
{
public:
	CGame();
	~CGame();

	bool Init();
	bool Update();
	void Render();

private:
	std::unique_ptr<CStateStack> myStateStack;
};
