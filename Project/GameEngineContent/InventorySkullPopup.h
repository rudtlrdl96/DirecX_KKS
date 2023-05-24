#pragma once
#include "BaseContentActor.h"

class InventorySkullPopup : public BaseContentActor
{
public:
	InventorySkullPopup();
	~InventorySkullPopup();

	InventorySkullPopup(const InventorySkullPopup& _Other) = delete;
	InventorySkullPopup(InventorySkullPopup&& _Other) noexcept = delete;
	InventorySkullPopup& operator=(const InventorySkullPopup& _Other) = delete;
	InventorySkullPopup& operator=(InventorySkullPopup&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	std::shared_ptr<class ContentUIRender> PopupFrameRender = nullptr;
	ColorBuffer Buffer = ColorBuffer();
};

