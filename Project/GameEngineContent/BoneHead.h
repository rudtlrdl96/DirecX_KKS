#pragma once
#include "BaseContentActor.h"

class BoneHead : public BaseContentActor
{
public:
	BoneHead();
	~BoneHead();

	BoneHead(const BoneHead& _Other) = delete;
	BoneHead(BoneHead&& _Other) noexcept = delete;
	BoneHead& operator=(const BoneHead& _Other) = delete;
	BoneHead& operator=(BoneHead&& _Other) noexcept = delete;

	void ShotHead(ActorViewDir _Dir);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> Render = nullptr;
	std::shared_ptr<class GameEngineCollision> Collision = nullptr;

	float ShotProgress = 0.0f;
	float ShotTime = 1.25f;
	float ShotSpeed = 800.0f;
	float RotSpeed = 360.0f;

	bool IsMoveEnd = false;

	ActorViewDir Dir = ActorViewDir::Left;

	void PlayEndEffect();
};

