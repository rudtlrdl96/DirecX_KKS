#pragma once
#include "BaseContentActor.h"

class InventoryItemPopup : public BaseContentActor
{
public:
	InventoryItemPopup();
	~InventoryItemPopup();

	InventoryItemPopup(const InventoryItemPopup& _Other) = delete;
	InventoryItemPopup(InventoryItemPopup&& _Other) noexcept = delete;
	InventoryItemPopup& operator=(const InventoryItemPopup& _Other) = delete;
	InventoryItemPopup& operator=(InventoryItemPopup&& _Other) noexcept = delete;

	void UpdateItemData(size_t _DataIndex);

protected:
	void Start() override;

private:
	std::shared_ptr<GameEngineUIRenderer> PopupFrameRender = nullptr;

	std::shared_ptr<GameEngineUIRenderer> ItemIcon = nullptr;
	std::shared_ptr<GameEngineUIRenderer> SynergyIconA = nullptr;
	std::shared_ptr<GameEngineUIRenderer> SynergyIconB = nullptr;

	std::shared_ptr<ContentUIFontRenderer> ItemStoryFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> ItemNoteFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> ItemSwitchFont = nullptr;

	std::shared_ptr<ContentUIFontRenderer> ItemNameFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> ItemGradeFont = nullptr;

	std::shared_ptr<ContentUIFontRenderer> SynergyAFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> SynergyBFont = nullptr;

	std::shared_ptr<class InventorySynergyGrade> SynergyAGrade = nullptr;
	std::shared_ptr<class InventorySynergyGrade> SynergyBGrade = nullptr;

	std::shared_ptr<ContentUIFontRenderer> CreateNewFont(const float4& _Pos, float FontSize, const float4& _Color, FW1_TEXT_FLAG _Sort);
};

