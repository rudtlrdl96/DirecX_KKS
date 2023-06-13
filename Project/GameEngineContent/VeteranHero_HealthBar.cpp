#include "PrecompileHeader.h"
#include "VeteranHero_HealthBar.h"
#include "ContentUIRender.h"

VeteranHero_HealthBar::VeteranHero_HealthBar()
{
}

VeteranHero_HealthBar::~VeteranHero_HealthBar()
{
}

void VeteranHero_HealthBar::UpdateBar(float _Progress, float _DeltaTime)
{
}

#include "GameEngineActorGUI.h"

void VeteranHero_HealthBar::Start()
{
	if (nullptr == GameEngineTexture::Find("EnemyHpBar.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("UI");

		GameEngineTexture::Load(Path.GetPlusFileName("EnemyHpBar.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("EnemySubBar.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("EnemyHpFrame.png").GetFullPath());
	}


	if (nullptr == GameEngineTexture::Find("VeteranHero_TopFrame.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("UI");

		GameEngineTexture::Load(Path.GetPlusFileName("VeteranHero_TopFrame.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("VeteranHero_BottomFrame.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("VeteranHero_BarFrame.png").GetFullPath());
	}

	BarRedner = CreateComponent<ContentUIRender>();
	BarRedner->PipeSetting("2DTexture_ProgressUI");
	BarRedner->GetShaderResHelper().SetConstantBufferLink("ProgressBuffer", BarBuffer);
	BarRedner->GetTransform()->SetLocalPosition(float4(-36, -21, 0.0f));
	BarRedner->GetTransform()->SetWorldRotation(float4(0, 0, 0));
	BarRedner->SetScaleToTexture("EnemyHpBar.png");
	BarRedner->GetTransform()->SetLocalScale(float4(148, 15, 1));

	SubBarRedner = CreateComponent<ContentUIRender>();
	SubBarRedner->PipeSetting("2DTexture_ProgressUI");
	SubBarRedner->GetShaderResHelper().SetConstantBufferLink("ProgressBuffer", SubBarBuffer);
	SubBarRedner->GetTransform()->SetLocalPosition(float4(-36, -21, 0.01f));
	SubBarRedner->GetTransform()->SetWorldRotation(float4(0, 0, 0));
	SubBarRedner->SetScaleToTexture("EnemySubBar.png");
	SubBarRedner->GetTransform()->SetLocalScale(float4(148, 15, 1));

	BarFrameRedner = CreateComponent<ContentUIRender>();
	BarFrameRedner->PipeSetting("2DTexture_Color");
	BarFrameRedner->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", FrameBuffer);
	BarFrameRedner->GetTransform()->SetLocalPosition(float4(0, 0, 0.02f));
	BarFrameRedner->GetTransform()->SetWorldRotation(float4(0, 0, 0));
	BarFrameRedner->SetScaleToTexture("VeteranHero_BarFrame.png");

	float4 BarFrameScale = BarFrameRedner->GetTransform()->GetLocalScale();
	BarFrameRedner->GetTransform()->SetLocalScale(BarFrameScale * 2.0f);

	TopFrameRedner = CreateComponent<ContentUIRender>();
	TopFrameRedner->PipeSetting("2DTexture_Color");
	TopFrameRedner->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", FrameBuffer);
	TopFrameRedner->GetTransform()->SetLocalPosition(float4(0, 0, 0.03f));
	TopFrameRedner->GetTransform()->SetWorldRotation(float4(0, 0, 0));
	TopFrameRedner->SetScaleToTexture("VeteranHero_TopFrame.png");

	float4 TopFrameScale = TopFrameRedner->GetTransform()->GetLocalScale();
	TopFrameRedner->GetTransform()->SetLocalScale(TopFrameScale * 2.0f);

	BottomFrameRedner = CreateComponent<ContentUIRender>();
	BottomFrameRedner->PipeSetting("2DTexture_Color");
	BottomFrameRedner->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", FrameBuffer);
	BottomFrameRedner->GetTransform()->SetLocalPosition(float4(0, 0, 0.04f));
	BottomFrameRedner->GetTransform()->SetWorldRotation(float4(0, 0, 0));
	BottomFrameRedner->SetScaleToTexture("VeteranHero_BottomFrame.png");

	float4 BottomFrameScale = BottomFrameRedner->GetTransform()->GetLocalScale();
	BottomFrameRedner->GetTransform()->SetLocalScale(BottomFrameScale * 2.0f);

	
	std::shared_ptr<GameEngineActorGUI> Ptr = GameEngineGUI::FindGUIWindowConvert<GameEngineActorGUI>("GameEngineActorGUI");
	Ptr->SetTarget(BarFrameRedner->GetTransform());
	Ptr->On();


	GetTransform()->SetWorldRotation(float4::Zero);
}
