#pragma once
#include "BaseContentActor.h"
#include "ItemData.h"
#include "ContentSlice9UIRenderer.h"
#include "ContentUIFontRenderer.h"

class ItemGearPopup : public BaseContentActor
{
public:
	ItemGearPopup();
	~ItemGearPopup();

	ItemGearPopup(const ItemGearPopup& _Other) = delete;
	ItemGearPopup(ItemGearPopup&& _Other) noexcept = delete;
	ItemGearPopup& operator=(const ItemGearPopup& _Other) = delete;
	ItemGearPopup& operator=(ItemGearPopup&& _Other) noexcept = delete;

	static void SetItemData(size_t _Index)
	{
		SetItemData(ContentDatabase<ItemData, ItemGrade>::GetData(_Index));
	}

	static void SetItemData(const ItemData& _Data)
	{
		GlobalData = _Data;
	}

	void PopupOn();
	void PopupOn(ItemData& _Data);
	void PopupOff();

protected:
	void Start() override;

private:
	static ItemData GlobalData;
	ItemData LocalData;

	std::shared_ptr<ContentSlice9UIRenderer> ItemFrameRender = nullptr;
	std::shared_ptr<ContentSlice9UIRenderer> NoteRender = nullptr;


	std::shared_ptr<ContentUIFontRenderer> ItemNoteFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> ItemNameFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> ItemGradeFont = nullptr;

	std::shared_ptr<GameEngineUIRenderer> SynergyFrame = nullptr;
	std::shared_ptr<GameEngineUIRenderer> SynergyIconA = nullptr;
	std::shared_ptr<GameEngineUIRenderer> SynergyIconB = nullptr;
	std::shared_ptr<ContentUIFontRenderer> SynergyAFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> SynergyBFont = nullptr;

	std::shared_ptr<class UINoteActor> GetItemFontActor = nullptr;
	std::shared_ptr<class UINoteActor> BrokenFontActor = nullptr;

	GameEngineUIRenderer* BrokenKeyRender = nullptr;
	GameEngineUIRenderer* BrokenGoldRender = nullptr;

};

