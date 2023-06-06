#pragma once
#include "BaseNPC.h"


class SkeletonA : public BaseNPC
{
public:
	SkeletonA();
	~SkeletonA();

	SkeletonA(const SkeletonA& _Other) = delete;
	SkeletonA(SkeletonA&& _Other) noexcept = delete;
	SkeletonA& operator=(const SkeletonA& _Other) = delete;
	SkeletonA& operator=(SkeletonA&& _Other) noexcept = delete;

protected:
	void Start() override;
	
private:
	void SpriteLoad() override;


};

