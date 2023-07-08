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
	/// ��ũ�� ��ǥ�� ��Ÿ���ϴ�, �� ������ ��ũ������ ��ǥ�� �����ؾ� �մϴ�
	/// </summary>
	float4 LightPos = float4::Zero;
	float4 LightColor = float4::One;

	/// <summary>
	/// ����Ʈ ����Ʈ �ɼ��� ��Ÿ���ϴ�
	/// </summary>
	/// <param name="x"> Distance �ȼ� �Ÿ��� �����մϴ�</param>
	/// <param name="y"> Brightness ����Ʈ�� ��⸦ �����մϴ�</param>
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

