#pragma once
#include "BaseGear.h"
#include "ItemData.h"

class ShopItemGear : public BaseGear
{
public:
	ShopItemGear();
	~ShopItemGear();

	ShopItemGear(const ShopItemGear& _Other) = delete;
	ShopItemGear(ShopItemGear&& _Other) noexcept = delete;
	ShopItemGear& operator=(const ShopItemGear& _Other) = delete;
	ShopItemGear& operator=(ShopItemGear&& _Other) noexcept = delete;

	void Init(size_t _ItemIndex);
	void Init(const ItemData& _Data);

	void CallUseEvent() override;
	int GetPrice() override;

protected:
	void Start() override;
	void UseGear() override;

	void Destroy() override;
	void PlayDestroyEffect() override;


private:
	ItemData Data = ItemData();

	int Price = 0;

};

