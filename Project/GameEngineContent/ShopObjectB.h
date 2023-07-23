#pragma once
#include "BehaviorObject.h"

class ShopObjectB : public BehaviorObject
{
public:
	ShopObjectB();
	~ShopObjectB();

	ShopObjectB(const ShopObjectB& _Other) = delete;
	ShopObjectB(ShopObjectB&& _Other) noexcept = delete;
	ShopObjectB& operator=(const ShopObjectB& _Other) = delete;
	ShopObjectB& operator=(ShopObjectB&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void ResetBehavior() override;
	void PlayBehavior() override;

private:


};

