#pragma once
#include "BehaviorObject.h"

class ShopObjectA : public BehaviorObject
{
public:
	ShopObjectA();
	~ShopObjectA();

	ShopObjectA(const ShopObjectA& _Other) = delete;
	ShopObjectA(ShopObjectA&& _Other) noexcept = delete;
	ShopObjectA& operator=(const ShopObjectA& _Other) = delete;
	ShopObjectA& operator=(ShopObjectA&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void ResetBehavior() override;
	void PlayBehavior() override;

private:


};

