#pragma once
#include "BaseContentActor.h"

class InventoryStatPopup : public BaseContentActor
{
public:
	InventoryStatPopup();
	~InventoryStatPopup();

	InventoryStatPopup(const InventoryStatPopup& _Other) = delete;
	InventoryStatPopup(InventoryStatPopup&& _Other) noexcept = delete;
	InventoryStatPopup& operator=(const InventoryStatPopup& _Other) = delete;
	InventoryStatPopup& operator=(InventoryStatPopup&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	std::shared_ptr<ContentSpriteRenderer> PopupFrameRender = nullptr;
	std::shared_ptr<ContentSpriteRenderer> PopupBackRender = nullptr;
	float4 PopupFrameColor = float4::Zero;
	float4 PopupBackColor = float4::Zero;

};

