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
		MsgAssert("백그라운드 이미지를 초기화 하지 않고 사용하려 했습니다");
		return;
	}

	Desc.Center;
	Desc.Ratio;
	BackImage->SetTexture(Desc.TextureName);
	BackImage->GetTransform()->SetLocalScale(Desc.Size);
	BackImage->On();

	Buffer.Color = Desc.Color;
	Buffer.Uv = float4::Zero;

	GetTransform()->SetLocalPosition(Desc.Center);

	if (true == Desc.Animation)
	{
		Desc.AnimationSpeed = Desc.AnimationSpeed / Desc.Size.x;

		if (0 < Desc.AnimationSpeed)
		{
			AnimationMoveDir = float4(Desc.Size.x, 0, 0, 0);
		}
		else
		{
			AnimationMoveDir = float4(-Desc.Size.x, 0, 0, 0);
		}
	}
}

void Background::UpdateTargetPos(float _DeltaTime, const float4& _TargetPos)
{
	if (nullptr == BackImage)
	{
		MsgAssert("백그라운드 이미지를 초기화 하지 않고 사용하려 했습니다");
		return;
	}

	float4 RenderPos = Desc.Center;
	float4 TargetDir = _TargetPos - Desc.Center;

	RenderPos += TargetDir * (1.0f - Desc.Ratio);
	RenderPos.z = Desc.Center.z;

	if (true == Desc.Animation)
	{
		Buffer.Uv.x += _DeltaTime * Desc.AnimationSpeed;

		if (1.0f <= Buffer.Uv.x)
		{
			Buffer.Uv.x -= 1.0f;
		}
	}

	BackImage->GetTransform()->SetLocalPosition(RenderPos);
}

void Background::SaveBin(GameEngineSerializer& _SaveSerializer) const
{
	// std::string TextureName = "";
	// float4 Center = float4::Zero;
	// float Ratio = 0.0f;
	// float4 Size = float4::Zero;
	// float4 Color = float4::Null;
	// bool Animation = false;
	// float AnimationSpeed = 0.0f;

	_SaveSerializer.Write(Desc.TextureName);
	_SaveSerializer.Write(&Desc.Center, sizeof(float4));
	_SaveSerializer.Write(&Desc.Ratio, sizeof(float));
	_SaveSerializer.Write(&Desc.Size, sizeof(float4));
	_SaveSerializer.Write(&Desc.Color, sizeof(float4));
	_SaveSerializer.Write(&Desc.Animation, sizeof(bool));
	_SaveSerializer.Write(&Desc.AnimationSpeed, sizeof(float));
}

Background::BG_DESC Background::LoadBin(GameEngineSerializer& _SaveSerializer)
{
	BG_DESC LoadDesc = BG_DESC();

	_SaveSerializer.Read(LoadDesc.TextureName);
	_SaveSerializer.Read((void*)&LoadDesc.Center, sizeof(float4));
	_SaveSerializer.Read((void*)&LoadDesc.Ratio, sizeof(float));
	_SaveSerializer.Read((void*)&LoadDesc.Size, sizeof(float4));
	_SaveSerializer.Read((void*)&LoadDesc.Color, sizeof(float4));
	_SaveSerializer.Read((void*)&LoadDesc.Animation, sizeof(bool));
	_SaveSerializer.Read((void*)&LoadDesc.AnimationSpeed, sizeof(float));

	return LoadDesc;
}

void Background::Start()
{
	BackImage = CreateComponent<GameEngineSpriteRenderer>();
	BackImage->SetPipeLine("2DTexture_Background");
	BackImage->GetShaderResHelper().SetConstantBufferLink("OutPixelColor", Buffer);
	BackImage->Off();
}
