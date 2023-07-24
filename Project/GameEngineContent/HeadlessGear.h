#pragma once
#include "BaseGear.h"
#include "SkullData.h"

class HeadlessGear : public BaseGear
{
public:
	HeadlessGear();
	~HeadlessGear();

	HeadlessGear(const HeadlessGear& _Other) = delete;
	HeadlessGear(HeadlessGear&& _Other) noexcept = delete;
	HeadlessGear& operator=(const HeadlessGear& _Other) = delete;
	HeadlessGear& operator=(HeadlessGear&& _Other) noexcept = delete;

	void Init(size_t _SkullIndex);
	void Init(const SkullData& _Data);

	int GetPrice() override;

	inline void SetUseCallback(std::function<void()> _UseCallback)
	{
		UseCallback = _UseCallback;
	}

protected:
	void Start() override;
	void UseGear() override;

	void Destroy() override;
	void PlayDestroyEffect() override;

private:
	SkullData Data = SkullData();

	std::function<void()> UseCallback = nullptr;

};

