#pragma once
#include "BaseContentActor.h"

class InventoryUI : public BaseContentActor
{
public:
	InventoryUI();
	~InventoryUI();

	InventoryUI(const InventoryUI& _Other) = delete;
	InventoryUI(InventoryUI&& _Other) noexcept = delete;
	InventoryUI& operator=(const InventoryUI& _Other) = delete;
	InventoryUI& operator=(InventoryUI&& _Other) noexcept = delete;

	void InventoryOn();
	void InventoryOff();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineUIRenderer> MainFrameRender = nullptr;
	std::shared_ptr<GameEngineUIRenderer> InventoryBackRender = nullptr;

	std::shared_ptr<class InventorySlot> CurSelectSlot = nullptr;

	std::vector<std::shared_ptr<class InventorySlot>> InventorySlotDatas;
	std::vector<std::shared_ptr<class InventorySynergyFrame>> SynergyFrames;

	size_t SlotIndex = 0;

	std::shared_ptr<class InventoryItemPopup> ItemPopup = nullptr;
	std::shared_ptr<class InventoryQuintessencePopup> QuintessencePopup = nullptr;
	std::shared_ptr<class InventorySkullPopup> SkullPopup = nullptr;
	std::shared_ptr<class InventoryStatPopup> StatPopup = nullptr;

	std::shared_ptr<ContentUIFontRenderer> SkullTitleFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> ItemTitleFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> QuintessenceTitleFont = nullptr;

	std::shared_ptr<ContentUIFontRenderer> CreateNewFont(const float4& _Pos, float FontSize, const float4& _Color, FW1_TEXT_FLAG _Sort);
	std::shared_ptr<class InventorySynergyFrame> CreateSynergyFrame();

	void UpdateInventoryFrame();
	void SortSynergyFrame();

	void MoveSlot_Up();
	void MoveSlot_Down();
	void MoveSlot_Left();
	void MoveSlot_Right();
};

