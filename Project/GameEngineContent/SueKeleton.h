#pragma once
#include "BaseNPC.h"

class SueKeleton : public BaseNPC
{
public:
	SueKeleton();
	~SueKeleton();

	SueKeleton(const SueKeleton& _Other) = delete;
	SueKeleton(SueKeleton&& _Other) noexcept = delete;
	SueKeleton& operator=(const SueKeleton& _Other) = delete;
	SueKeleton& operator=(SueKeleton&& _Other) noexcept = delete;

	void Death() override;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void ResetBehavior() override;
	void PlayBehavior() override;

private:
	void SpriteLoad() override;

	std::shared_ptr<GameEngineCollision> FirstScriptCol = nullptr;
	std::shared_ptr<GameEngineCollision> SecondScriptCol = nullptr;

	bool IsFirstScriptPlay = false;
	bool IsSecondScriptPlay = false;
	bool IsGiveWeapon = false;

};

