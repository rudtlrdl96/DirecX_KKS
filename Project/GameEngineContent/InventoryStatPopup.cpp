#include "PrecompileHeader.h"
#include "InventoryStatPopup.h"
#include "ContentUIRender.h"
#include "PlayerState.h"
#include "Inventory.h"

InventoryStatPopup::InventoryStatPopup()
{
}

InventoryStatPopup::~InventoryStatPopup()
{
}

void InventoryStatPopup::Start()
{
	{
		std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find("Inventory_Stat_Frame.png");

		if (nullptr == FindTex)
		{
			MsgAssert_Rtti<InventoryStatPopup>(" - �����Ϸ��� �ؽ��ĸ� ã�� ���߽��ϴ�.");
			return;
		}

		float4 TexSize = { static_cast<float>(FindTex->GetWidth()), static_cast<float>(FindTex->GetHeight()), 1.0f};
		TexSize.x *= 2.0f;
		TexSize.y *= 2.0f;

		PopupFrameRender = CreateComponent<GameEngineUIRenderer>();
		PopupFrameRender->SetTexture("Inventory_Stat_Frame.png");
		PopupFrameRender->GetTransform()->SetLocalScale(TexSize);
	}

	{
		std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find("Inventory_Stat_Back.png");

		if (nullptr == FindTex)
		{
			MsgAssert_Rtti<InventoryStatPopup>(" - �����Ϸ��� �ؽ��ĸ� ã�� ���߽��ϴ�.");
			return;
		}

		float4 TexSize = { static_cast<float>(FindTex->GetWidth()), static_cast<float>(FindTex->GetHeight()), 1.0f};
		TexSize.x *= 2.0f;
		TexSize.y *= 2.0f;

		PopupBackRender = CreateComponent<GameEngineUIRenderer>();
		PopupBackRender->SetTexture("Inventory_Stat_Back.png");
		PopupBackRender->GetTransform()->SetLocalPosition(float4(-465, 1, 0));
		PopupBackRender->GetTransform()->SetLocalScale(TexSize);

	}

	FW1_TEXT_FLAG LeftSort = static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_VCENTER | FW1_TEXT_FLAG::FW1_LEFT);
	FW1_TEXT_FLAG CenterSort = static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_VCENTER | FW1_TEXT_FLAG::FW1_CENTER);
	FW1_TEXT_FLAG RightSort = static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_VCENTER | FW1_TEXT_FLAG::FW1_RIGHT);

	TitleFont = CreateNewFont(float4(0, 270, -1), 23, float4(0.294f, 0.208f, 0.196f, 1.0f), CenterSort);
	TitleFont->SetText("ĳ���� ����");

	//0.459f, 0.337f, 0.337f, 1.0f

	HPNameFont = CreateNewFont(float4(-5, 185, -1), 19, float4(0.459f, 0.337f, 0.337f, 1.0f), RightSort);
	HPNameFont->SetText("ü��");
	HPValueFont = CreateNewFont(float4(140, 185, -1), 19, float4(0.294f, 0.208f, 0.196f, 1.0f), RightSort);
	HPValueFont->SetText("100 %");

	DamageReductionNameFont = CreateNewFont(float4(-5, 155, -1), 19, float4(0.459f, 0.337f, 0.337f, 1.0f), RightSort);
	DamageReductionNameFont->SetText("�޴� ������");	
	DamageReductionValueFont = CreateNewFont(float4(140, 155, -1), 19, float4(0.294f, 0.208f, 0.196f, 1.0f), RightSort);
	DamageReductionValueFont->SetText("100 %");

	MeleeAttackNameFont = CreateNewFont(float4(-5, 102, -1), 19, float4(0.459f, 0.337f, 0.337f, 1.0f), RightSort);
	MeleeAttackNameFont->SetText("�������ݷ�");
	MeleeAttackValueFont = CreateNewFont(float4(140, 102, -1), 19, float4(0.294f, 0.208f, 0.196f, 1.0f), RightSort);
	MeleeAttackValueFont->SetText("100 %");

	MagicAttackNameFont = CreateNewFont(float4(-5, 72, -1), 19, float4(0.459f, 0.337f, 0.337f, 1.0f), RightSort);
	MagicAttackNameFont->SetText("�������ݷ�");
	MagicAttackValueFont = CreateNewFont(float4(140, 72, -1), 19, float4(0.294f, 0.208f, 0.196f, 1.0f), RightSort);
	MagicAttackValueFont->SetText("100 %");


	AttackSpeedNameFont = CreateNewFont(float4(-5, 17, -1), 19, float4(0.459f, 0.337f, 0.337f, 1.0f), RightSort);
	AttackSpeedNameFont->SetText("���ݼӵ�");
	AttackSpeedValueFont = CreateNewFont(float4(140, 17, -1), 19, float4(0.294f, 0.208f, 0.196f, 1.0f), RightSort);
	AttackSpeedValueFont->SetText("100 %");
	MoveSpeedNameFont = CreateNewFont(float4(-5, -13, -1), 19, float4(0.459f, 0.337f, 0.337f, 1.0f), RightSort);
	MoveSpeedNameFont->SetText("�̵��ӵ�");
	MoveSpeedValueFont = CreateNewFont(float4(140, -13, -1), 19, float4(0.294f, 0.208f, 0.196f, 1.0f), RightSort);
	MoveSpeedValueFont->SetText("100 %");
	CastingNameFont = CreateNewFont(float4(-5, -43, -1), 19, float4(0.459f, 0.337f, 0.337f, 1.0f), RightSort);
	CastingNameFont->SetText("�������� �ӵ�");
	CastingValueFont = CreateNewFont(float4(140, -43, -1), 19, float4(0.294f, 0.208f, 0.196f, 1.0f), RightSort);
	CastingValueFont->SetText("100 %");

	SkillCooldownNameFont = CreateNewFont(float4(-5, -90, -1), 19, float4(0.459f, 0.337f, 0.337f, 1.0f), RightSort);
	SkillCooldownNameFont->SetText("��ų ��ٿ� �ӵ�");
	SkillCooldownValueFont = CreateNewFont(float4(140, -90, -1), 19, float4(0.294f, 0.208f, 0.196f, 1.0f), RightSort);
	SkillCooldownValueFont->SetText("100 %");
	SwitchCooldownNameFont = CreateNewFont(float4(-5, -120, -1), 19, float4(0.459f, 0.337f, 0.337f, 1.0f), RightSort);
	SwitchCooldownNameFont->SetText("���� ��ٿ� �ӵ�");
	SwitchCooldownValueFont = CreateNewFont(float4(140, -120, -1), 19, float4(0.294f, 0.208f, 0.196f, 1.0f), RightSort);
	SwitchCooldownValueFont->SetText("100 %");
	QuintessenceCooldownNameFont = CreateNewFont(float4(-5, -150, -1), 19, float4(0.459f, 0.337f, 0.337f, 1.0f), RightSort);
	QuintessenceCooldownNameFont->SetText("���� ��ٿ� �ӵ�");
	QuintessenceCooldownValueFont = CreateNewFont(float4(140, -150, -1), 19, float4(0.294f, 0.208f, 0.196f, 1.0f), RightSort);
	QuintessenceCooldownValueFont->SetText("100 %");

	CriticalPerNameFont = CreateNewFont(float4(-5, -200, -1), 19, float4(0.459f, 0.337f, 0.337f, 1.0f), RightSort);
	CriticalPerNameFont->SetText("ġ��Ÿ Ȯ��");
	CriticalPerValueFont = CreateNewFont(float4(140, -200, -1), 19, float4(0.294f, 0.208f, 0.196f, 1.0f), RightSort);
	CriticalPerValueFont->SetText("0 %");
	CriticalDamageNameFont = CreateNewFont(float4(-5, -230, -1), 19, float4(0.459f, 0.337f, 0.337f, 1.0f), RightSort);
	CriticalDamageNameFont->SetText("ġ��Ÿ ������");
	CriticalDamageValueFont = CreateNewFont(float4(140, -230, -1), 19, float4(0.294f, 0.208f, 0.196f, 1.0f), RightSort);
	CriticalDamageValueFont->SetText("100 %");
}

#include "GameEngineActorGUI.h"

void InventoryStatPopup::Update(float _DeltaTime)
{
	std::shared_ptr<GameEngineActorGUI> Ptr = GameEngineGUI::FindGUIWindowConvert<GameEngineActorGUI>("GameEngineActorGUI");
	Ptr->SetTarget(CriticalPerValueFont->GetTransform());
	Ptr->On();

	HPValueFont->SetText(std::to_string((int)(PlayerState::GetMaxHP() + Inventory::GetMaxHP())) + " ��");
	DamageReductionValueFont->SetText(std::to_string((int)((1.0f - Inventory::GetDamageReduction()) * 100.0f)) + " %");
	MeleeAttackValueFont->SetText(std::to_string((int)(Inventory::GetMeleeAttack() * 100.0f)) + " %");
	MagicAttackValueFont->SetText(std::to_string((int)(Inventory::GetMagicAttack() * 100.0f)) + " %");
	AttackSpeedValueFont->SetText(std::to_string((int)(Inventory::GetAttackSpeed() * 100.0f)) + " %");
	MoveSpeedValueFont->SetText(std::to_string((int)(Inventory::GetMoveSpeed() * 100.0f)) + " %");
	CastingValueFont->SetText(std::to_string((int)(Inventory::GetCastingSpeed() * 100.0f)) + " %");
	SkillCooldownValueFont->SetText(std::to_string((int)(Inventory::GetSkillCoolDown() * 100.0f)) + " %");
	SwitchCooldownValueFont->SetText(std::to_string((int)(Inventory::GetSwitchCoolDown() * 100.0f)) + " %");
	QuintessenceCooldownValueFont->SetText(std::to_string((int)(Inventory::GetQuintessenceCoolDown() * 100.0f)) + " %");;
	CriticalPerValueFont->SetText(std::to_string((int)Inventory::GetCriPer()) + " %");;
	CriticalDamageValueFont->SetText(std::to_string((int)((1.0f + Inventory::GetCriDamage()) * 100.0f)) + " %");;
}

std::shared_ptr<ContentUIFontRenderer> InventoryStatPopup::CreateNewFont(const float4& _Pos, float FontSize, const float4& _Color, FW1_TEXT_FLAG _Sort)
{
	std::shared_ptr<ContentUIFontRenderer> NewFont = CreateComponent<ContentUIFontRenderer>();
	NewFont->GetTransform()->SetLocalPosition(_Pos);

	NewFont->SetFont("�ؽ�Lv2���");
	NewFont->SetScale(FontSize);
	NewFont->SetColor(_Color);
	NewFont->SetFontFlag(_Sort);

	return NewFont;
}