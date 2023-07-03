#pragma once
#include "BaseContentActor.h"

class CaptureRenderer : public BaseContentActor
{
public:
	CaptureRenderer();
	~CaptureRenderer();

	CaptureRenderer(const CaptureRenderer& _Other) = delete;
	CaptureRenderer(CaptureRenderer&& _Other) noexcept = delete;
	CaptureRenderer& operator=(const CaptureRenderer& _Other) = delete;
	CaptureRenderer& operator=(CaptureRenderer&& _Other) noexcept = delete;

	void SetTexture(const std::string_view& _TextureName, const float4& _AtlasData, float _ScaleRatio = 1.0f);
	void Play(const float4& _StartColor, const float4& _EndColor, float _Time);
	
	inline void SetLoop(bool _IsLoop)
	{
		IsLoop = _IsLoop;
	}

	inline void SetWaitTime(float _Time)
	{
		WaitTime = _Time;
	}

	inline bool IsPlaying() const
	{
		return IsPlayingValue;
	}


protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> CaptureRender = nullptr;

	ColorBuffer Buffer;

	float4 AtlasData = float4(0.0f, 0.0f, 1.0f, 1.0f);

	float4 StartColor = float4::Zero;
	float4 EndColor = float4::Zero;

	bool IsPlayingValue = false;
	bool IsLoop = false;
	
	float ProgressTime = 0.0f;
	float WaitTime = 0.0f;
	float PlaySpeed = 1.0f;
};