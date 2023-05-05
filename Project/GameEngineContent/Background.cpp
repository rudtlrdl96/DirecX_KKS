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

	BackImage->SetTexture(Desc.Name);
	BackImage->GetTransform()->SetLocalScale(Desc.TextureSize * Desc.TextureScale);
	BackImage->On();

	Buffer.OutColor = Desc.Color;
	Buffer.Uv = float4::Zero;

	GetTransform()->SetLocalPosition(Desc.Center);
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

	TargetDir.z = Desc.Center.z;

	RenderPos += TargetDir * (1.0f - Desc.MoveRatio);
	RenderPos.z = Desc.Center.z;

	if (true == Desc.Animation)
	{
		if (0 < Desc.AnimationSpeed)
		{
			Buffer.Uv.x += _DeltaTime * Desc.AnimationSpeed;

			if (1.0f <= Buffer.Uv.x)
			{
				Buffer.Uv.x -= 1.0f;
			}
		}
		else
		{
			Buffer.Uv.x += _DeltaTime * Desc.AnimationSpeed;

			if (0.0f > Buffer.Uv.x)
			{
				Buffer.Uv.x += 1.0f;
			}
		}
	}

	BackImage->GetTransform()->SetLocalPosition(RenderPos);
}

void Background::SaveBin(GameEngineSerializer& _SaveSerializer) const
{
	_SaveSerializer.Write(Desc.Name);
	_SaveSerializer.Write(&Desc.Index, sizeof(UINT));
	_SaveSerializer.Write(&Desc.Center, sizeof(float4));
	_SaveSerializer.Write(&Desc.Animation, sizeof(bool));
	_SaveSerializer.Write(&Desc.AnimationSpeed, sizeof(float));
	_SaveSerializer.Write(&Desc.MoveRatio, sizeof(float));
	_SaveSerializer.Write(&Desc.TextureSize, sizeof(float4));
	_SaveSerializer.Write(&Desc.TextureScale, sizeof(float));
	_SaveSerializer.Write(&Desc.Color, sizeof(float4));
}

BG_DESC Background::LoadBin(GameEngineSerializer& _LoadSerializer)
{
	BG_DESC LoadDesc = BG_DESC();

	_LoadSerializer.Read(LoadDesc.Name);
	_LoadSerializer.Read((void*)&LoadDesc.Index, sizeof(UINT));
	_LoadSerializer.Read((void*)&LoadDesc.Center, sizeof(float4));
	_LoadSerializer.Read((void*)&LoadDesc.Animation, sizeof(bool));
	_LoadSerializer.Read((void*)&LoadDesc.AnimationSpeed, sizeof(float));
	_LoadSerializer.Read((void*)&LoadDesc.MoveRatio, sizeof(float));
	_LoadSerializer.Read((void*)&LoadDesc.TextureSize, sizeof(float4));
	_LoadSerializer.Read((void*)&LoadDesc.TextureScale, sizeof(float));
	_LoadSerializer.Read((void*)&LoadDesc.Color, sizeof(float4));

	return LoadDesc;
}

void Background::Start()
{
	BackImage = CreateComponent<GameEngineSpriteRenderer>();
	BackImage->SetPipeLine("2DTexture_Background");
	BackImage->GetShaderResHelper().SetConstantBufferLink("TextureMoveBuffer", Buffer);
	BackImage->Off();
}
