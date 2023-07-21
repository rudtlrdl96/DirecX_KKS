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

protected:
	void Start() override;

private:
	std::shared_ptr<GameEngineUIRenderer> PopupFrameRender = nullptr;
};

