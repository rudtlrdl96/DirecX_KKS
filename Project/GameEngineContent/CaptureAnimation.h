#pragma once
#include "BaseContentActor.h"

class CaptureAnimParameter
{
public:
	std::shared_ptr<ContentSpriteRenderer> SpriteRender = nullptr;

	const float4& StartColor = float4::Zero;
	const float4& EndColor = float4::Zero;

	float Speed = 1.0f;
	float WaitTime = 1.0f;
};

class CaptureAnimation : public BaseContentActor
{
public:
	CaptureAnimation();
	~CaptureAnimation();

	CaptureAnimation(const CaptureAnimation& _Other) = delete;
	CaptureAnimation(CaptureAnimation&& _Other) noexcept = delete;
	CaptureAnimation& operator=(const CaptureAnimation& _Other) = delete;
	CaptureAnimation& operator=(CaptureAnimation&& _Other) noexcept = delete;

	void PlayCapture(const CaptureAnimParameter& _Parameter);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<ContentSpriteRenderer> CaptureRender = nullptr;
	std::weak_ptr<ContentSpriteRenderer> TargetRender;

	float4 StartColor = float4::Zero;
	float4 EndColor = float4::Zero;

	float Progress = 0.0f;
	float Speed = 0.0f;
	float WaitTime = 0.0f;

	float4 AtlasData = float4::Zero;
	CaptureBuffer Buffer = CaptureBuffer();

};

