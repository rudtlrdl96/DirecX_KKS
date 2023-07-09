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
	/// ��ũ�� ��ǥ�� ��Ÿ���ϴ�, �� ������ ��ũ������ ��ǥ�� �����ؾ� �մϴ�
	/// </summary>
	float4 LightPos = float4::Zero;
	float4 LightColor = float4::One;

	/// <summary>
	/// ����Ʈ ����Ʈ �ɼ��� ��Ÿ���ϴ�
	/// </summary>
    /// <param name="x"> Brightness ����Ʈ�� ��⸦ �����մϴ�</param>
    /// <param name="y"> Light�� ���̸� ��Ÿ���ϴ�</param>
    /// <param name="z"> Light�� ���� ������ �����մϴ� [Angle Type]</param>
    /// <param name="w"> Light�� �� ������ �����մϴ� [Angle Type]</param>
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

