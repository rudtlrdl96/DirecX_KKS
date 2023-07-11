#pragma once
#include "BaseContentActor.h"

class GoodsUI : public BaseContentActor
{
private:
	enum class GoodsState
	{
		None,
		On,
		Off
	};
public:
	GoodsUI();
	~GoodsUI();

	GoodsUI(const GoodsUI& _Other) = delete;
	GoodsUI(GoodsUI&& _Other) noexcept = delete;
	GoodsUI& operator=(const GoodsUI& _Other) = delete;
	GoodsUI& operator=(GoodsUI&& _Other) noexcept = delete;

	void GoodsUIOn(bool _IsMinimapOn);
	void GoodsUIOff(bool _IsMinimapOn);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	
private:
	std::shared_ptr<GameEngineUIRenderer> BoneGoodsRender = nullptr;
	std::shared_ptr<GameEngineUIRenderer> GoldGoodsRender = nullptr;
	std::shared_ptr<GameEngineUIRenderer> ManaStoneGoodsRender = nullptr;

	std::shared_ptr<ContentUIFontRenderer> BoneCountFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> GoldCountFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> ManaStoneCountFont = nullptr;

	std::shared_ptr<EffectActor> GoldEffect = nullptr;
	std::shared_ptr<EffectActor> BoneEffect = nullptr;
	std::shared_ptr<EffectActor> ManaStoneEffect = nullptr;

	std::shared_ptr<GameEngineComponent> GoldGoodsPivot = nullptr;
	std::shared_ptr<GameEngineComponent> BoneGoodsPivot = nullptr;
	std::shared_ptr<GameEngineComponent> ManaStoneGoodsPivot = nullptr;

	GoodsState State = GoodsState::None;

	float Progress = 0.0f;
	float GoldEffectProgress = 0.0f;
	float BoneEffectProgress = 0.0f;
	float ManaStoneEffectProgress = 0.0f;

	float4 StartPos = float4::Zero;
	float4 EndPos = float4::Zero;

	bool IsGetGoldEffectMove = false;
	bool IsGetBoneEffectMove = false;
	bool IsGetManaStoneEffectMove = false;

	int PrevFrame_GoldCount = 0;
	int PrevFrame_BoneCount = 0;
	int PrevFrame_ManaStoneCount = 0;

	void GoodsEffect(std::shared_ptr<GameEngineComponent>& _Pivot, std::shared_ptr<ContentUIFontRenderer>& _Font, const float4& _Color, float _Progress);
};

