#pragma once
#include "BaseContentActor.h"

class CaptureTrail : public BaseContentActor
{
public:
	CaptureTrail();
	~CaptureTrail();

	CaptureTrail(const CaptureTrail& _Other) = delete;
	CaptureTrail(CaptureTrail&& _Other) noexcept = delete;
	CaptureTrail& operator=(const CaptureTrail& _Other) = delete;
	CaptureTrail& operator=(CaptureTrail&& _Other) noexcept = delete;
	
	void SetTime(float _Time);
	void SetColor(const float4& _StartColor, const float4& _EndColor);
	std::shared_ptr<class CaptureRenderer> PlayTrail(const std::string_view& _TextureName, const float4& _AtlasData, bool _IsFlipX, float _ScaleRatio = 1.0f);

protected:
	void Update(float _DeltaTime) override;

private:
	std::vector<std::shared_ptr<class CaptureRenderer>> WaitRenders;
	std::list<std::shared_ptr<class CaptureRenderer>> PlayRenders;

	float4 StartColor = float4::Zero;
	float4 EndColor = float4::Null;

	float Time = 1.0f;
};

