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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> MainFrameRender = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> InventoryBackRender = nullptr;

	std::shared_ptr<class InventorySlot> CurSelectSlot = nullptr;

	std::vector<std::shared_ptr<class InventorySlot>> SkullSlotDatas;
	std::vector<std::shared_ptr<class InventorySlot>> QuintessenceSlotDatas;
	std::vector<std::shared_ptr<class InventorySlot>> ItemSlotDatas;

	std::shared_ptr<class InventoryItemPopup> ItemPopup = nullptr;
	std::shared_ptr<class InventoryQuintessencePopup> QuintessencePopup = nullptr;
	std::shared_ptr<class InventorySkullPopup> SkullPopup = nullptr;
	std::shared_ptr<class InventoryStatPopup> StatPopup = nullptr;

	float4 MainFrameColor = float4::Zero;
	float4 BackFrameColor = float4::Zero;
};

