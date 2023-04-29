#pragma once
#include "BaseContentActor.h"

class InventoryQuintessencePopup : public BaseContentActor
{
public:
	InventoryQuintessencePopup();
	~InventoryQuintessencePopup();

	InventoryQuintessencePopup(const InventoryQuintessencePopup& _Other) = delete;
	InventoryQuintessencePopup(InventoryQuintessencePopup&& _Other) noexcept = delete;
	InventoryQuintessencePopup& operator=(const InventoryQuintessencePopup& _Other) = delete;
	InventoryQuintessencePopup& operator=(InventoryQuintessencePopup&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> PopupFrameRender = nullptr;
	float4 PopupFrameColor = float4::Zero;
};

