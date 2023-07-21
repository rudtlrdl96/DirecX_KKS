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
	std::shared_ptr<GameEngineUIRenderer> PopupFrameRender = nullptr;
	std::shared_ptr<GameEngineUIRenderer> PopupBackRender = nullptr;
};

