#pragma once
#include "BaseGear.h"
#include "ItemData.h"

class ItemGear : public BaseGear
{
public:
	ItemGear();
	~ItemGear();

	ItemGear(const ItemGear& _Other) = delete;
	ItemGear(ItemGear&& _Other) noexcept = delete;
	ItemGear& operator=(const ItemGear& _Other) = delete;
	ItemGear& operator=(ItemGear&& _Other) noexcept = delete;

	void Init(size_t _ItemIndex);
	void Init(const ItemData& _Data);

protected:
	void Start() override;
	void UseGear() override;

	void Destroy() override;
	void PlayDestroyEffect() override;


private:
	ItemData Data = ItemData();

};

