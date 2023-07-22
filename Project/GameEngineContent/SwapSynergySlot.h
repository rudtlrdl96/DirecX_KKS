#pragma once
#include "BaseContentActor.h"
#include "ItemData.h"

class SwapSynergySlot : public BaseContentActor
{
public:
	SwapSynergySlot();
	~SwapSynergySlot();

	SwapSynergySlot(const SwapSynergySlot& _Other) = delete;
	SwapSynergySlot(SwapSynergySlot&& _Other) noexcept = delete;
	SwapSynergySlot& operator=(const SwapSynergySlot& _Other) = delete;
	SwapSynergySlot& operator=(SwapSynergySlot&& _Other) noexcept = delete;

	void SetSynergy(Synergy _Synergy, int _NewSynergyGradeCount);

	inline int GetNewSynergyCount() const
	{
		return NewSynergyCount;
	}

protected:
	void Start();	
private:
	std::shared_ptr<GameEngineUIRenderer> FrameRender = nullptr;
	std::shared_ptr<GameEngineUIRenderer> SynergyTexRender = nullptr;
	std::shared_ptr<ContentUIFontRenderer> GradeFontRender = nullptr;

	float4 NormalColor = float4(0.843f, 0.753f, 0.667f);
	float4 AddColor = float4(0.408f, 0.9177f, 0.4f);
	float4 MinusColor = float4(0.99f, 0.306f, 0.302f);

	int NewSynergyCount = 0;

};

