#include "PrecompileHeader.h"
#include "ResultUI.h"
#include <GameEngineCore/GameEngineCore.h>
#include "BattleLevel.h"
#include "ResultInfo.h"

ResultUI::ResultUI()
{
}

ResultUI::~ResultUI()
{
}

void ResultUI::ResultUIOn()
{
	MoveProgress = 0.0f;
	On();

	//ResultInfo::
	int TotalTime = static_cast<int>(ResultInfo::PlayTime);

	int Time_H = TotalTime / 3600;
	TotalTime = TotalTime % 3600;	

	int Time_M = TotalTime / 60;
	TotalTime = TotalTime % 60;

	int Time_S = TotalTime;

	std::string TimeText = "";

	if (10 > Time_H)
	{
		TimeText += "0" + std::to_string(Time_H);
	}
	else
	{
		TimeText += std::to_string(Time_H);
	}

	TimeText += ":";

	if (10 > Time_M)
	{
		TimeText += "0" + std::to_string(Time_M);
	}
	else
	{
		TimeText += std::to_string(Time_M);
	}

	TimeText += ":";

	if (10 > Time_S)
	{
		TimeText += "0" + std::to_string(Time_S);
	}
	else
	{
		TimeText += std::to_string(Time_S);
	}

	PlayTimeValueFont->SetText(TimeText);
	DeathCountValueFont->SetText(std::to_string(ResultInfo::DeathCount));
	KillCountValueFont->SetText(std::to_string(ResultInfo::KillCount));

	GetManaStoneValueFont->SetText(std::to_string(ResultInfo::GetManaStone));
	GetGoldValueFont->SetText(std::to_string(ResultInfo::GetGold));
	GetBoneValueFont->SetText(std::to_string(ResultInfo::GetBone));

	TotalDamageValueFont->SetText(std::to_string(static_cast<int>(ResultInfo::TotalDamage)));
	MaxDamageValueFont->SetText(std::to_string(static_cast<int>(ResultInfo::MaxDamage)));
	HitDamageValueFont->SetText(std::to_string(static_cast<int>(ResultInfo::HitDamage)));
	HealValueFont->SetText(std::to_string(static_cast<int>(ResultInfo::HealValue)));

	GetSkullCountValueFont->SetText(std::to_string(ResultInfo::GetSkullCount));
	GetItemCountValueFont->SetText(std::to_string(ResultInfo::GetItemCount));
	GetQuintessenceValueFont->SetText(std::to_string(ResultInfo::GetQuintessenceCount));

}

void ResultUI::ResultUIOff()
{
	Level->MoveCastle();
}

void ResultUI::Start()
{
	if (nullptr == GameEngineTexture::Find("Result.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("UI");

		GameEngineTexture::Load(Path.GetPlusFileName("Result.png").GetFullPath());
	}

	if (false == GameEngineInput::IsKey("ReturnCastle"))
	{
		GameEngineInput::CreateKey("ReturnCastle", 'X');
	}

	UIRender = CreateComponent<GameEngineUIRenderer>();
	UIRender->SetTexture("Result.png");
	UIRender->GetTransform()->SetWorldScale(GameEngineWindow::GetScreenSize() * 2.0f);


	CreateLeftFont(PlayTimeNameFont, float4(-340, 218, -1), "�÷��� Ÿ��");
	CreateLeftFont(PlayTimeValueFont, float4(-60, 218, -1));
	CreateLeftFont(DeathCountNameFont, float4(-340, 190, -1), "���� Ƚ��");
	CreateLeftFont(DeathCountValueFont, float4(-60, 190, -1));
	CreateLeftFont(KillCountNameFont, float4(-340, 162, -1), "����ģ ��");
	CreateLeftFont(KillCountValueFont, float4(-60, 162, -1));

	CreateLeftFont(GetManaStoneNameFont, float4(-340, 110, -1), "���� ����");
	CreateLeftFont(GetManaStoneValueFont, float4(-60, 110, -1));
	CreateLeftFont(GetGoldNameFont, float4(-340, 82, -1), "���� ��ȭ");
	CreateLeftFont(GetGoldValueFont, float4(-60, 82, -1));
	CreateLeftFont(GetBoneNameFont, float4(-340, 54, -1), "���� ������");
	CreateLeftFont(GetBoneValueFont, float4(-60, 54, -1));

	CreateLeftFont(TotalDamageNameFont, float4(-340, 2, -1), "�� ������");
	CreateLeftFont(TotalDamageValueFont, float4(-60, 2, -1));
	CreateLeftFont(MaxDamageNameFont, float4(-340, -26, -1), "�ְ� ������");
	CreateLeftFont(MaxDamageValueFont, float4(-60, -26, -1));
	CreateLeftFont(HitDamageNameFont, float4(-340, -54, -1), "���� ������");
	CreateLeftFont(HitDamageValueFont, float4(-60, -54, -1));
	CreateLeftFont(HealNameFont, float4(-340, -82, -1), "ȸ�� ��");
	CreateLeftFont(HealValueFont, float4(-60, -82, -1));

	CreateLeftFont(GetSkullCountNameFont, float4(-340, -134, -1), "���� ���� ����");
	CreateLeftFont(GetSkullCountValueFont, float4(-62, -134, -1));
	CreateLeftFont(GetItemCountNameFont, float4(-340, -162, -1), "���� ������ ����");
	CreateLeftFont(GetItemCountValueFont, float4(-60, -162, -1));
	CreateLeftFont(GetQuintessenceNameFont, float4(-340, -190, -1), "���� ���� ����");
	CreateLeftFont(GetQuintessenceValueFont, float4(-60, -190, -1));

	CreateLeftFont(StageNameFont, float4(320, 194, -1), "������ �� �� ����");
	StageNameFont->SetScale(24);
	StageNameFont->SetColor(float4(0.294f, 0.2078f, 0.196f, 1.0f));

	CreateLeftFont(DeathInfoFont, float4(320, -59, -1), "��� ����");
	DeathInfoFont->SetScale(20);
	DeathInfoFont->SetColor(float4(0.294f, 0.2078f, 0.196f, 1.0f));

	CreateLeftFont(KeyInfoFont, float4(320, -166, -1), "���ռ����� ���ư���");
	KeyInfoFont->SetColor(float4(0.45f, 0.294f, 0.2784f, 1.0f));
	KeyInfoFont->SetScale(20);

	StartPos = float4(0, 175, -4500);
	EndPos = float4(0, 0, -4500);
}

void ResultUI::Update(float _DeltaTime)
{
	if (1.0f > MoveProgress)
	{
		MoveProgress += GameEngineTime::GlobalTime.GetDeltaTime() * 10.0f;
		
		GetTransform()->SetWorldPosition(float4::LerpClamp(StartPos, EndPos, MoveProgress));
	}
	else
	{
		if (true == GameEngineInput::IsDown("ReturnCastle"))
		{
			ResultUIOff();
		}
	}
}

void ResultUI::CreateLeftFont(std::shared_ptr<ContentUIFontRenderer>& _Font, const float4& _WorldPos, const std::string_view& _Name /*= "999999999"*/)
{
	_Font = CreateComponent<ContentUIFontRenderer>();
	_Font->SetFont("�ؽ�Lv2���");
	_Font->SetFontFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_CENTER | FW1_TEXT_FLAG::FW1_VCENTER));
	_Font->SetScale(16);
	_Font->SetColor(float4(0.5255f, 0.3765f, 0.353f, 1));
	_Font->GetTransform()->SetLocalPosition(_WorldPos);
	_Font->SetText(_Name);
}