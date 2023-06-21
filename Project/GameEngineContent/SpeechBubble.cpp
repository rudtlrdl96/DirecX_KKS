#include "PrecompileHeader.h"
#include "SpeechBubble.h"
#include "ContentUIRender.h"

SpeechBubble::SpeechBubble()
{
}

SpeechBubble::~SpeechBubble()
{
}

#include "GameEngineActorGUI.h"

void SpeechBubble::PlayBubble(const SpeechBubbleParameter& _BubbleParameter)
{
	Target = _BubbleParameter.Target;

	if (nullptr == Target.lock())
	{
		BubbleRender->Off();
		return;
	}

	if (0.0f != _BubbleParameter.FontSize)
	{
		FontRender->SetScale(_BubbleParameter.FontSize);
	}

	FontRender->SetText(_BubbleParameter.Text);
	FontRender->On();

	TalkText = _BubbleParameter.Text;
	Pivot = _BubbleParameter.Pivot;

	IsLoop = _BubbleParameter.IsLoop;

	if (true == _BubbleParameter.IsLarge)
	{
		BubbleRender->SetScaleToTexture("SpeechBubble_Large.png");
		FontRender->GetTransform()->SetLocalPosition(float4(0, 5, -0.1f));
	}
	else
	{
		BubbleRender->SetScaleToTexture("SpeechBubble.png");
		FontRender->GetTransform()->SetLocalPosition(float4(0, 5, -0.1f));
	}

	//std::shared_ptr<GameEngineActorGUI> Ptr = GameEngineGUI::FindGUIWindowConvert<GameEngineActorGUI>("GameEngineActorGUI");
	//Ptr->SetTarget(FontRender->GetTransform());
	//Ptr->On();

	BubbleRender->On();

	LiveTime = _BubbleParameter.LiveTime;
	LoopInter = _BubbleParameter.LoopInter;
}


void SpeechBubble::On()
{
	BaseContentActor::On();
}

void SpeechBubble::Start()
{
	if (nullptr == GameEngineTexture::Find("SpeechBubble.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("UI");

		GameEngineTexture::Load(Path.GetPlusFileName("SpeechBubble.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("SpeechBubble_Large.png").GetFullPath());
	}

	BubbleRender = CreateComponent<ContentSpriteRenderer>();
	BubbleRender->PipeSetting("2DTexture_Color");
	BubbleRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	BubbleRender->Off();

	FontRender = CreateComponent<GameEngineFontRenderer>();
	FontRender->SetFont("³Ø½¼Lv2°íµñ");
	FontRender->SetScale(15);
	FontRender->SetColor(float4(1, 1, 1, 1));
	FontRender->SetFontFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_VCENTER | FW1_TEXT_FLAG::FW1_CENTER));

	FontRender->Off();
}

void SpeechBubble::Update(float _DeltaTime)
{
	if (nullptr != Target.lock() && true == Target.lock()->IsDeath())
	{
		Target.lock() = nullptr;
	}

	if (nullptr == Target.lock())
	{
		BubbleRender->Off();
		FontRender->Off();
		return;
	}
	else
	{
		BubbleRender->On();
		FontRender->On();
	}

	OffTime += _DeltaTime;

	if (0.0f > OffTime)
	{
		BubbleRender->Off();
		FontRender->Off();
		ResetLiveTime();
	}

	float4 TargetPos = Target.lock()->GetTransform()->GetWorldPosition();
	TargetPos.z = 0.0f;

	GetTransform()->SetWorldPosition(TargetPos + Pivot);
	
	if (GetLiveTime() >= LiveTime)
	{
		if (false == IsLoop)
		{
			Death();
		}
		else
		{
			ResetLiveTime();
			OffTime = -LoopInter;
		}
	}

}