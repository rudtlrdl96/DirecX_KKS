#pragma once
#include "BaseNPC.h"


class SkeletonB : public BaseNPC
{
public:
	SkeletonB();
	~SkeletonB();

	SkeletonB(const SkeletonB& _Other) = delete;
	SkeletonB(SkeletonB&& _Other) noexcept = delete;
	SkeletonB& operator=(const SkeletonB& _Other) = delete;
	SkeletonB& operator=(SkeletonB&& _Other) noexcept = delete;

	void Death() override;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void PlayBehavior() override;
	void ResetBehavior() override;


private:
	void SpriteLoad() override;


};

