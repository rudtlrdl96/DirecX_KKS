#pragma once
#include "BaseContentActor.h"

class InventorySlot : public BaseContentActor
{
public:
	InventorySlot();
	~InventorySlot();

	InventorySlot(const InventorySlot& _Other) = delete;
	InventorySlot(InventorySlot&& _Other) noexcept = delete;
	InventorySlot& operator=(const InventorySlot& _Other) = delete;
	InventorySlot& operator=(InventorySlot&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	std::shared_ptr<class ContentUIRender> SlotFrameRender = nullptr;
	std::shared_ptr<class ContentUIRender> SlotImageRender = nullptr;

	ColorBuffer SlotFrameBuffer = ColorBuffer();
	ColorBuffer SlotImageBuffer = ColorBuffer();
};

