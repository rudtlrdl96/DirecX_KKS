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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> Render = nullptr;

};

