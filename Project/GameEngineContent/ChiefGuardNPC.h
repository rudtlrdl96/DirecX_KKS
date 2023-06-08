#pragma once
#include "BaseNPC.h"

class ChiefGuardNPC : public BaseNPC
{
public:
	ChiefGuardNPC();
	~ChiefGuardNPC();

	ChiefGuardNPC(const ChiefGuardNPC& _Other) = delete;
	ChiefGuardNPC(ChiefGuardNPC&& _Other) noexcept = delete;
	ChiefGuardNPC& operator=(const ChiefGuardNPC& _Other) = delete;
	ChiefGuardNPC& operator=(ChiefGuardNPC&& _Other) noexcept = delete;

	void Death() override;
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	
	void ResetBehavior() override;
	void PlayBehavior() override;

private:
	std::shared_ptr<ContentSpriteRenderer> HeadRender = nullptr;
	ColorBuffer Buffer;

	std::shared_ptr<GameEngineCollision> ScriptCol = nullptr;

	void SpriteLoad() override;

};

