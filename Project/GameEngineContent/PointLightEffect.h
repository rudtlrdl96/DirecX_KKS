#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>

enum class PointLightType
{
	None,
	Circle,
	CircleAngle,
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
    /// <param name="x"> Brightness 라이트의 밝기를 설정합니다</param>
    /// <param name="y"> Light의 길이를 나타냅니다</param>
    /// <param name="z"> Light의 시작 각도를 설정합니다 [Angle Type]</param>
    /// <param name="w"> Light의 끝 각도를 설정합니다 [Angle Type]</param>
	float4 LightOption = float4(0, 0, 0.0f, 360.0f);
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

	PointBuffer LightBuffer;

	void SetState(PointLightType _State);

	void ShowGUI();

protected:

	void Start(GameEngineRenderTarget* _Target) override;
	void Effect(GameEngineRenderTarget* _Target, float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineRenderUnit> LightUnit;

	RenderBaseValue BaseValue;

	PointLightType State = PointLightType::None;

};

