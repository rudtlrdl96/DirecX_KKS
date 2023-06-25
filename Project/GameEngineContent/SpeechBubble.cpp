#include "PrecompileHeader.h"
#include "SpeechBubble.h"
#include "ContentUIRender.h"

SpeechBubble::SpeechBubble()
{
}

SpeechBubble::~SpeechBubble()
{
}

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
		BubbleRender->SetTextureAndSlice("SpeechBubble_Large.png", 0.03f, 0.03f, 0.06f, 0.2f);
		FontRender->GetTransform()->SetLocalPosition(float4(0, 5, -0.1f));
	}
	else
	{
		BubbleRender->SetTextureAndSlice("SpeechBubble.png", 0.034f, 0.034f, 0.49f, 0.49f);
		FontRender->GetTransform()->SetLocalPosition(float4(0, 5, -0.1f));
	}

	KeyImages.resize(_BubbleParameter.KeyImages.size());

	for (size_t i = 0; i < KeyImages.size(); i++)
	{
		std::shared_ptr<GameEngineSpriteRenderer> NewKeyImage = CreateComponent<GameEngineSpriteRenderer>();
		NewKeyImage->SetScaleToTexture(_BubbleParameter.KeyImages[i].KeyImageName);

		float4 Scale = NewKeyImage->GetTransform()->GetLocalScale();
		NewKeyImage->GetTransform()->SetLocalScale(Scale * 1.5f);

		NewKeyImage->GetTransform()->SetLocalPosition(FontRender->GetTransform()->GetLocalPosition() + _BubbleParameter.KeyImages[i].LocalPos);
		KeyImages[i] = NewKeyImage;
	}

	LiveTime = _BubbleParameter.LiveTime;
	LoopInter = _BubbleParameter.LoopInter;

	BubbleRender->ResetScale();

	if (true == _BubbleParameter.IsAutoScale)
	{
		std::wstring BubbleText = GameEngineString::AnsiToUniCode(TalkText);

		float TextureBoardX = 0.0f;
		float TextureBoardY = 0.0f;
		
		if (true == _BubbleParameter.IsLarge)
		{
			TextureBoardX = 195.0f;
			TextureBoardY = 55.0f;
		}
		else
		{
			TextureBoardX = 120.0f;
			TextureBoardY = 30.0f;
		}

		float CurX = 0.0f;
		float CurY = _BubbleParameter.FontSize;

		float MaxX = 0.0f;
		float MaxY = 0.0f;

		for (size_t i = 0; i < BubbleText.size(); i++)
		{
			if (BubbleText[i] == L'\n')
			{
				CurX = 0;
				CurY += _BubbleParameter.FontSize;
			}
			else
			{
				CurX += _BubbleParameter.FontSize * 0.7f;
			}

			if (CurX > MaxX)
			{
				MaxX = CurX;
			}

			if (CurY > MaxY)
			{
				MaxY = CurY;
			}
		}

		if (TextureBoardX < MaxX)
		{
			BubbleRender->GetTransform()->AddWorldScale(float4(MaxX - TextureBoardX + 10, 0));

		}

		if (TextureBoardX < MaxY)
		{
			BubbleRender->GetTransform()->AddWorldScale(float4(0, MaxY - TextureBoardY + 10));
		}
	}

	BubbleRender->On();
}

void SpeechBubble::SetBubbleScale(const float4& _Scale)
{
	BubbleRender->GetTransform()->SetLocalScale(_Scale);
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

	BubbleRender = CreateComponent<ContentSlice9Renderer>();
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

		for (size_t i = 0; i < KeyImages.size(); i++)
		{
			KeyImages[i]->Off();
		}

		return;
	}
	else
	{
		BubbleRender->On();
		FontRender->On();

		for (size_t i = 0; i < KeyImages.size(); i++)
		{
			KeyImages[i]->On();
		}
	}

	OffTime += _DeltaTime;

	if (0.0f > OffTime)
	{
		BubbleRender->Off();
		FontRender->Off();

		for (size_t i = 0; i < KeyImages.size(); i++)
		{
			KeyImages[i]->Off();
		}

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