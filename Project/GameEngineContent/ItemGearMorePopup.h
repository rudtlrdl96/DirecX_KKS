#pragma once
#include "BaseContentActor.h"
#include "ContentSlice9UIRenderer.h"
#include "ItemData.h"

class ItemGearMorePopup : public BaseContentActor
{
public:
	ItemGearMorePopup();
	~ItemGearMorePopup();

	ItemGearMorePopup(const ItemGearMorePopup& _Other) = delete;
	ItemGearMorePopup(ItemGearMorePopup&& _Other) noexcept = delete;
	ItemGearMorePopup& operator=(const ItemGearMorePopup& _Other) = delete;
	ItemGearMorePopup& operator=(ItemGearMorePopup&& _Other) noexcept = delete;

	void SynergyUpdate(Synergy _Synergy);

protected:
	void Start() override;
	
private:
	std::shared_ptr<ContentSlice9UIRenderer> FrameRender = nullptr;

	std::shared_ptr<GameEngineUIRenderer> SynergyImage = nullptr;	

	std::shared_ptr<ContentUIFontRenderer> SynergyNameText = nullptr;
	std::shared_ptr<ContentUIFontRenderer> GradeText = nullptr;

	std::vector<std::shared_ptr<class ItemGearMorePopupFont>> NoteActors;

	std::shared_ptr<class ItemGearMorePopupFont> CreatePopupFont();
};

