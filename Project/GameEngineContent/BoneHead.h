#pragma once
#include "BaseContentActor.h"
#include "PlayerBaseSkull.h"
#include "BounceRigidbody2D.h"

class BoneHead : public BaseContentActor
{
	friend class BoneSkull;
public:
	BoneHead();
	~BoneHead();

	BoneHead(const BoneHead& _Other) = delete;
	BoneHead(BoneHead&& _Other) noexcept = delete;
	BoneHead& operator=(const BoneHead& _Other) = delete;
	BoneHead& operator=(BoneHead&& _Other) noexcept = delete;

	inline void SetParentSkull(PlayerBaseSkull* _Parent)
	{
		ParentSkull = _Parent;
	}

	void ShotHead(ActorViewDir _Dir);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	PlayerBaseSkull* ParentSkull = nullptr;

	std::shared_ptr<GameEngineSpriteRenderer> Render = nullptr;
	std::shared_ptr<class GameEngineCollision> Collision = nullptr;
	std::shared_ptr<class GameEngineCollision> BounceCollision = nullptr;

	BounceRigidbody2D HeadRigid;

	float ShotProgress = 0.0f;
	float ShotTime = 1.25f;
	float ShotSpeed = 800.0f;
	float RotSpeed = 720.0f;

	float ShotLiveTime = 0.0f;

	bool IsMoveEnd = false;
	ActorViewDir Dir = ActorViewDir::Left;

	void PlayEndEffect();
};

