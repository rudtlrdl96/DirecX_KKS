#pragma once
#include "BaseContentActor.h"
#include "ItemData.h"

class ItemGearMorePopupFont : public BaseContentActor
{
public:
	ItemGearMorePopupFont();
	~ItemGearMorePopupFont();

	ItemGearMorePopupFont(const ItemGearMorePopupFont& _Other) = delete;
	ItemGearMorePopupFont(ItemGearMorePopupFont&& _Other) noexcept = delete;
	ItemGearMorePopupFont& operator=(const ItemGearMorePopupFont& _Other) = delete;
	ItemGearMorePopupFont& operator=(ItemGearMorePopupFont&& _Other) noexcept = delete;

	void SetSynergyText(Synergy _Synergy, int _Grade);

	inline float GetSizeY() const
	{
		return SizeY;
	}

protected:
	void Start() override;

private:
	std::shared_ptr<GameEngineUIRenderer> LineImage = nullptr;
	std::shared_ptr<GameEngineUIRenderer> ArrowImage = nullptr;
	std::shared_ptr<ContentUIFontRenderer> NoteText = nullptr;
	std::shared_ptr<ContentUIFontRenderer> GradeText = nullptr;

	float SizeY = 0.0f;
};

