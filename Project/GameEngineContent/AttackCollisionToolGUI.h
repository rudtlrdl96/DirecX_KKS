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

	void Start() override;
	void OnGUI(std::shared_ptr<class GameEngineLevel> _Level, float _DeltaTime) override;
protected:
	
private:
	std::shared_ptr<class GameEngineSpriteRenderer> SpriteRender = nullptr;

	std::string SpriteAnimationName = "";

	UINT LoadWitdhCount = 1;
	UINT LoadHeightCount = 1;

	UINT ShowIndex = 0;
	UINT StartIndex = 0;
	UINT EndIndex = 0;

	float4 ColCenterPos = float4::Zero;
	float4 ColSize = float4::Zero;
};