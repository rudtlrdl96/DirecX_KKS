#pragma once
#include "BaseContentActor.h"
#include "ItemData.h"

class InventoryItemMorePopupFont : public BaseContentActor
{
public:
	InventoryItemMorePopupFont();
	~InventoryItemMorePopupFont();

	InventoryItemMorePopupFont(const InventoryItemMorePopupFont& _Other) = delete;
	InventoryItemMorePopupFont(InventoryItemMorePopupFont&& _Other) noexcept = delete;
	InventoryItemMorePopupFont& operator=(const InventoryItemMorePopupFont& _Other) = delete;
	InventoryItemMorePopupFont& operator=(InventoryItemMorePopupFont&& _Other) noexcept = delete;

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

