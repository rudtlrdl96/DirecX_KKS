#pragma once
#include "BaseNPC.h"
#include "ContentUIRender.h"

class SkeleTong : public BaseNPC
{
public:
	SkeleTong();
	~SkeleTong();

	SkeleTong(const SkeleTong& _Other) = delete;
	SkeleTong(SkeleTong&& _Other) noexcept = delete;
	SkeleTong& operator=(const SkeleTong& _Other) = delete;
	SkeleTong& operator=(SkeleTong&& _Other) noexcept = delete;

	void Destroy() override;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void PlayBehavior() override;

private:
	std::shared_ptr<ContentUIRender> FadeRender = nullptr;
	ColorBuffer Buffer = ColorBuffer(); 

	bool IsFadeEnd = false;
	float FadeProgress = 0.0f;

	bool IsMove = false;
	float MoveWaitTime = 0.0f;

	bool IsSurqrise = false;
	float SurqriseTime = 0.0f;

	bool IsScript3Active = false;
	float Script3WaitTime = 0.0f;

	UINT MoveCount = 0;

	void SpriteLoad() override;
};

