#include "PrecompileHeader.h"
#include "InventoryDebugLevel.h"
#include "InventoryUI.h"

InventoryDebugLevel::InventoryDebugLevel()
{
}

InventoryDebugLevel::~InventoryDebugLevel()
{
}

void InventoryDebugLevel::Start()
{
	ContentLevel::Start();

	Inventory = CreateActor<InventoryUI>();
	Inventory->GetTransform()->SetLocalPosition({ 0, 0, 0, 1 });
}

void InventoryDebugLevel::Update(float _DeltaTime)
{
	ContentLevel::Update(_DeltaTime);
}
