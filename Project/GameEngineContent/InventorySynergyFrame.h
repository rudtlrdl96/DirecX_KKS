#pragma once
#include "BaseContentActor.h"
#include "ItemData.h"

class InventorySynergyFrame : public BaseContentActor
{
public:
	InventorySynergyFrame();
	~InventorySynergyFrame();

	InventorySynergyFrame(const InventorySynergyFrame& _Other) = delete;
	InventorySynergyFrame(InventorySynergyFrame&& _Other) noexcept = delete;
	InventorySynergyFrame& operator=(const InventorySynergyFrame& _Other) = delete;
	InventorySynergyFrame& operator=(InventorySynergyFrame&& _Other) noexcept = delete;

	void UpdateSynergy(Synergy _Synergy);

	inline Synergy GetSynergy() const
	{
		return CurSynergy;
	}	

protected:
	void Start() override;
	
private:
	Synergy CurSynergy = Synergy::Count;

	std::shared_ptr<GameEngineUIRenderer> Frame = nullptr;
	std::shared_ptr<GameEngineUIRenderer> SynergyImage = nullptr;

	std::shared_ptr<ContentUIFontRenderer> GradeFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> SynergyNameFont = nullptr;

	std::shared_ptr<class InventorySynergyGrade> SynergyGrade = nullptr;

	float4 ActiveFontColor = float4(0.898f, 0.8235f, 0.745f, 1.0f);
	float4 DisableFontColor = float4(0.6118f, 0.5059f, 0.3804f, 1.0f);
	float4 FullGradeFontColor = float4(0.984f, 0.835f, 0.24f, 1.0f);

	std::shared_ptr<ContentUIFontRenderer> CreateNewFont(const float4& _Pos, float FontSize, const float4& _Color, FW1_TEXT_FLAG _Sort);
};

