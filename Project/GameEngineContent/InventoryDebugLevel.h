#pragma once
#include "ContentLevel.h"

class InventoryDebugLevel : public ContentLevel
{
public:
	InventoryDebugLevel();
	~InventoryDebugLevel();

	InventoryDebugLevel(const InventoryDebugLevel& _Other) = delete;
	InventoryDebugLevel(InventoryDebugLevel&& _Other) noexcept = delete;
	InventoryDebugLevel& operator=(const InventoryDebugLevel& _Other) = delete;
	InventoryDebugLevel& operator=(InventoryDebugLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class InventoryUI> Inventory = nullptr;

};

