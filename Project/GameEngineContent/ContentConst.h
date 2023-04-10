#pragma once
#include <GameEngineBase/GameEngineMath.h>

class ContentConst
{
public:
	//Physics
	static const float4 Gravity;

	// Player Const
	// ¤¤ Arm
	static const float ArmChainInterval;
	static const float ArmShotSpeed;
	static const int ArmChainCount;

private:
	ContentConst();
	~ContentConst();

	ContentConst(const ContentConst& _Other) = delete;
	ContentConst(ContentConst&& _Other) noexcept = delete;
	ContentConst& operator=(const ContentConst& _Other) = delete;
	ContentConst& operator=(ContentConst&& _Other) noexcept = delete;
};