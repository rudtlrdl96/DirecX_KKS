#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>

enum class LightType
{
	None,
	Circle,
	Box,
};

class PointBuffer
{
public:
	/// <summary>
	/// 스크린 좌표를 나타냅니다, 매 프레임 스크린기준 좌표를 설정해야 합니다
	/// </summary>
	float4 LightPos = float4::Zero;
	float4 LightColor = float4::One;

	/// <summary>
	/// 포인트 라이트 옵션을 나타냅니다
	/// </summary>
	/// <param name="x"> Distance 픽셀 거리를 설정합니다</param>
	/// <param name="y"> Brightness 라이트의 밝기를 설정합니다</param>
	/// 
	float4 LightOption = float4::Null;
};


class PointLightEffect : public GameEnginePostProcess
{
public:
	PointLightEffect();
	~PointLightEffect();

	PointLightEffect(const PointLightEffect& _Other) = delete;
	PointLightEffect(PointLightEffect&& _Other) noexcept = delete;
	PointLightEffect& operator=(const PointLightEffect& _Other) = delete;
	PointLightEffect& operator=(PointLightEffect&& _Other) noexcept = delete;

	void SetState(LightType _State);
	PointBuffer LightBuffer;

protected:
	LightType State = LightType::None;

	void Start(GameEngineRenderTarget* _Target) override;
	void Effect(GameEngineRenderTarget* _Target, float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineRenderUnit> LightUnit;

	RenderBaseValue BaseValue;

};

