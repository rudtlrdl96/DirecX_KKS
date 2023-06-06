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

protected:
	void Start() override;
	
private:
	void SpriteLoad() override;


};

