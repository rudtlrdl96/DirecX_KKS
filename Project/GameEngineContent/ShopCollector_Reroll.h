#pragma once
#include "BaseContentActor.h"

class ShopCollector_Reroll : public BaseContentActor
{
public:
	ShopCollector_Reroll();
	~ShopCollector_Reroll();

	ShopCollector_Reroll(const ShopCollector_Reroll& _Other) = delete;
	ShopCollector_Reroll(ShopCollector_Reroll&& _Other) noexcept = delete;
	ShopCollector_Reroll& operator=(const ShopCollector_Reroll& _Other) = delete;
	ShopCollector_Reroll& operator=(ShopCollector_Reroll&& _Other) noexcept = delete;

	inline void SetPrice(int _Price)
	{
		RerollPrice = _Price;
	}

	inline void SetCallback(std::function<void()> _RerollCallback)
	{
		RerollCallback = _RerollCallback;
	}

	void CallUseEvent() override;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> RerollBox = nullptr;
	std::shared_ptr<GameEngineCollision> RerollCol = nullptr;
	std::shared_ptr<class FieldNoteActor> RerollNote = nullptr;

	std::function<void()> RerollCallback = nullptr;

	int RerollPrice = 0;
};

