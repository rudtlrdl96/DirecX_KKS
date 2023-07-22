#pragma once
#include "BaseGear.h"
#include "SkullData.h"

class SkullGear : public BaseGear
{
public:
	SkullGear();
	~SkullGear();

	SkullGear(const SkullGear& _Other) = delete;
	SkullGear(SkullGear&& _Other) noexcept = delete;
	SkullGear& operator=(const SkullGear& _Other) = delete;
	SkullGear& operator=(SkullGear&& _Other) noexcept = delete;

	void Init(size_t _SkullIndex);
	void Init(const SkullData& _Data);

	int GetPrice() override;
protected:
	void Start() override;
	void UseGear() override;

	void Destroy() override;
	void PlayDestroyEffect() override;


private:
	SkullData Data = SkullData();


};