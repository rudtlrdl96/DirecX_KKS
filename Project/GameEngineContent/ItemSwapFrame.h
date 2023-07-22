#pragma once
#include "BaseContentActor.h"
#include "ItemData.h"
#include "ContentSlice9UIRenderer.h"
#include "ContentUIFontRenderer.h"

class ItemSwapFrame : public BaseContentActor
{
public:
	ItemSwapFrame();
	~ItemSwapFrame();

	ItemSwapFrame(const ItemSwapFrame& _Other) = delete;
	ItemSwapFrame(ItemSwapFrame&& _Other) noexcept = delete;
	ItemSwapFrame& operator=(const ItemSwapFrame& _Other) = delete;
	ItemSwapFrame& operator=(ItemSwapFrame&& _Other) noexcept = delete;

	void PopupOn(ItemData& _Data);
	void PopupOff();

protected:
	void Start() override;

private:
	ItemData Data;

	std::shared_ptr<ContentSlice9UIRenderer> ItemFrameRender = nullptr;

	std::shared_ptr<ContentUIFontRenderer> ItemNoteFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> ItemNameFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> ItemGradeFont = nullptr;

	std::shared_ptr<GameEngineUIRenderer> SynergyIconA = nullptr;
	std::shared_ptr<GameEngineUIRenderer> SynergyIconB = nullptr;

	std::shared_ptr<ContentUIFontRenderer> SynergyAFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> SynergyBFont = nullptr;
};