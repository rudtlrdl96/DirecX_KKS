#pragma once
#include "BaseContentActor.h"

enum class GearState
{
	Fixed,
	Wave,
	Drop,
};

class BaseGear : public BaseContentActor
{
public:
	BaseGear();
	~BaseGear();

	BaseGear(const BaseGear& _Other) = delete;
	BaseGear(BaseGear&& _Other) noexcept = delete;
	BaseGear& operator=(const BaseGear& _Other) = delete;
	BaseGear& operator=(BaseGear&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void Destroy() override;

private:
	std::shared_ptr<ContentSpriteRenderer> Render = nullptr;
	BlackAndWihteBuffer Buffer;

	virtual void PlayDestroyEffect();

};

