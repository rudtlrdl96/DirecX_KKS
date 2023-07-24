#pragma once
#include "BaseContentActor.h"
#include "ItemData.h"

class InventoryItemMorePopup : public BaseContentActor
{
public:
	InventoryItemMorePopup();
	~InventoryItemMorePopup();

	InventoryItemMorePopup(const InventoryItemMorePopup& _Other) = delete;
	InventoryItemMorePopup(InventoryItemMorePopup&& _Other) noexcept = delete;
	InventoryItemMorePopup& operator=(const InventoryItemMorePopup& _Other) = delete;
	InventoryItemMorePopup& operator=(InventoryItemMorePopup&& _Other) noexcept = delete;

	void SynergyUpdate(Synergy _SynergyA, Synergy _SynergyB);

protected:
	void Start() override;
	
private:
	std::shared_ptr<GameEngineUIRenderer> FrameRender = nullptr;
	std::shared_ptr<GameEngineUIRenderer> SynergyAImage = nullptr;
	std::shared_ptr<GameEngineUIRenderer> SynergyBImage = nullptr;

	std::shared_ptr<ContentUIFontRenderer> SynergyANameFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> SynergyBNameFont = nullptr;

	std::shared_ptr<ContentUIFontRenderer> SynergyAGradeFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> SynergyBGradeFont = nullptr;

	std::vector<std::shared_ptr<class InventoryItemMorePopupFont>> SynergyAFonts;
	std::vector<std::shared_ptr<class InventoryItemMorePopupFont>> SynergyBFonts;

	void SynergyFontSort(std::vector<std::shared_ptr<class InventoryItemMorePopupFont>>& _Font, const float4& _Pos, Synergy _Synergy);
};

