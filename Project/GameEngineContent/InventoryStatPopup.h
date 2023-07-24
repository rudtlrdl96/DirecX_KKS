#pragma once
#include "BaseContentActor.h"

class InventoryStatPopup : public BaseContentActor
{
public:
	InventoryStatPopup();
	~InventoryStatPopup();

	InventoryStatPopup(const InventoryStatPopup& _Other) = delete;
	InventoryStatPopup(InventoryStatPopup&& _Other) noexcept = delete;
	InventoryStatPopup& operator=(const InventoryStatPopup& _Other) = delete;
	InventoryStatPopup& operator=(InventoryStatPopup&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineUIRenderer> PopupFrameRender = nullptr;
	std::shared_ptr<GameEngineUIRenderer> PopupBackRender = nullptr;

	std::shared_ptr<ContentUIFontRenderer> TitleFont = nullptr;

	std::shared_ptr<ContentUIFontRenderer> HPNameFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> HPValueFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> DamageReductionNameFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> DamageReductionValueFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> MeleeAttackNameFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> MeleeAttackValueFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> MagicAttackNameFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> MagicAttackValueFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> AttackSpeedNameFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> AttackSpeedValueFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> MoveSpeedNameFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> MoveSpeedValueFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> CastingNameFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> CastingValueFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> SkillCooldownNameFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> SkillCooldownValueFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> SwitchCooldownNameFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> SwitchCooldownValueFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> QuintessenceCooldownNameFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> QuintessenceCooldownValueFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> CriticalPerNameFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> CriticalPerValueFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> CriticalDamageNameFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> CriticalDamageValueFont = nullptr;

	std::shared_ptr<ContentUIFontRenderer> CreateNewFont(const float4& _Pos, float FontSize, const float4& _Color, FW1_TEXT_FLAG _Sort);
};

