#include "PrecompileHeader.h"
#include "Background.h"

Background::Background()
{
}

Background::~Background()
{
}

void Background::Init(const BG_DESC& _Desc)
{
	Desc = _Desc;

	if (nullptr == BackImage)
	{
		MsgAssert("��׶��� �̹����� �ʱ�ȭ ���� �ʰ� ����Ϸ� �߽��ϴ�");
		return;
	}

	Desc.Center;
	Desc.Ratio;
	BackImage->SetTexture(Desc.TextureName);
	BackImage->GetTransform()->SetLocalScale(Desc.Size);
	BackImage->On();

	GetTransform()->SetLocalPosition(Desc.Center);

	if (true == Desc.Animation)
	{
		AnimationImage = CreateComponent<GameEngineSpriteRenderer>();
		AnimationImage->SetTexture(Desc.TextureName);
		AnimationImage->GetTransform()->SetLocalScale(Desc.Size);
		
		Desc.AnimationSpeed = Desc.AnimationSpeed / Desc.Size.x;

		if (0 < Desc.AnimationSpeed)
		{
			AnimationMoveDir = float4(Desc.Size.x, 0, 0, 0);
		}
		else
		{
			AnimationMoveDir = float4(-Desc.Size.x, 0, 0, 0);
		}

		AnimationImage->GetTransform()->SetLocalPosition(Desc.Center - AnimationMoveDir);
	}
}

void Background::UpdateTargetPos(float _DeltaTime, const float4& _TargetPos)
{
	if (nullptr == BackImage)
	{
		MsgAssert("��׶��� �̹����� �ʱ�ȭ ���� �ʰ� ����Ϸ� �߽��ϴ�");
		return;
	}

	float4 RenderPos = Desc.Center;
	float4 TargetDir = _TargetPos - Desc.Center;

	RenderPos += TargetDir * (1.0f - Desc.Ratio);
	RenderPos.z = Desc.Center.z;

	if (true == Desc.Animation)
	{
		AnimationProgress += _DeltaTime * Desc.AnimationSpeed;
		float4 AnimMove = float4::LerpClamp(float4::Zero, AnimationMoveDir, AnimationProgress);
		RenderPos += AnimMove;

		if (1.0f <= AnimationProgress)
		{
			AnimationProgress -= 1.0f;
		}

		AnimationImage->GetTransform()->SetLocalPosition(RenderPos - AnimationMoveDir);
	}

	BackImage->GetTransform()->SetLocalPosition(RenderPos);
}

void Background::Start()
{
	BackImage = CreateComponent<GameEngineSpriteRenderer>();
	BackImage->SetPipeLine("2DTexture_ColorLight");
	BackImage->GetShaderResHelper().SetConstantBufferLink("OutPixelColor", Desc.Color);
	BackImage->Off();
}
