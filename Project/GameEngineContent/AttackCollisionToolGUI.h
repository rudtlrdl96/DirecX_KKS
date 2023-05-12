#pragma once
#include <GameEngineCore/GameEngineCoreWindow.h>

class AttackCollisionToolGUI : public GameEngineCoreWindow
{
public:
	AttackCollisionToolGUI();
	~AttackCollisionToolGUI();

	AttackCollisionToolGUI(const AttackCollisionToolGUI& _Other) = delete;
	AttackCollisionToolGUI(AttackCollisionToolGUI&& _Other) noexcept = delete;
	AttackCollisionToolGUI& operator=(const AttackCollisionToolGUI& _Other) = delete;
	AttackCollisionToolGUI& operator=(AttackCollisionToolGUI&& _Other) noexcept = delete;

protected:
	
private:


};

