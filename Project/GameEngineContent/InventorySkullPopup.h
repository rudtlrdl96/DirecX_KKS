#pragma once
#include "BaseContentActor.h"

class InventorySkullPopup : public BaseContentActor
{
public:
	InventorySkullPopup();
	~InventorySkullPopup();

	InventorySkullPopup(const InventorySkullPopup& _Other) = delete;
	InventorySkullPopup(InventorySkullPopup&& _Other) noexcept = delete;
	InventorySkullPopup& operator=(const InventorySkullPopup& _Other) = delete;
	InventorySkullPopup& operator=(InventorySkullPopup&& _Other) noexcept = delete;

	void UpdateSkullData(size_t _DataIndex);

protected:
	void Start() override;

private:
	std::shared_ptr<GameEngineUIRenderer> PopupFrameRender = nullptr;

	std::shared_ptr<GameEngineUIRenderer> SkullIcon = nullptr;
	std::shared_ptr<GameEngineUIRenderer> SkillIconA = nullptr;
	std::shared_ptr<GameEngineUIRenderer> SkillIconB = nullptr;

	std::shared_ptr<ContentUIFontRenderer> SkullStoryFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> SkullNoteFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> SkullSwitchFont = nullptr;

	std::shared_ptr<ContentUIFontRenderer> SkullNameFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> SkullGradeFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> SkullTypeFont = nullptr;

	std::shared_ptr<ContentUIFontRenderer> SkullAFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> SkullBFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> SwitchFont = nullptr;

	std::shared_ptr<ContentUIFontRenderer> CreateNewFont(const float4& _Pos, float FontSize, const float4& _Color, FW1_TEXT_FLAG _Sort);
};

