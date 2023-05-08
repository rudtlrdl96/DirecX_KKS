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

	if (nullptr == BackRender)
	{
		MsgAssert("백그라운드 이미지를 초기화 하지 않고 사용하려 했습니다");
		return;
	}

	float4 RenderSize = Desc.TextureSize * Desc.TextureScale;
	RenderSize.z = 1;

	BackRender->SetTexture(Desc.Name);
	BackRender->GetTransform()->SetLocalScale(RenderSize);
	BackRender->On();

	if (true == Desc.IsLeftRender)
	{
		CreateLeftRender();
		LeftRender->SetTexture(Desc.Name);
		LeftRender->GetTransform()->SetLocalScale(RenderSize);
		LeftRender->On();	
	}

	if (true == Desc.IsRightRender)
	{
		CreateRightRedner();
		RightRender->SetTexture(Desc.Name);
		RightRender->GetTransform()->SetLocalScale(RenderSize);
		RightRender->On();
	}

	Buffer.OutColor = Desc.Color;
	Buffer.Uv = float4::Zero;

	GetTransform()->SetLocalPosition(Desc.Center);
}

void Background::UpdateTargetPos(float _DeltaTime, const float4& _TargetPos)
{
	if (nullptr == BackRender)
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

	GetTransform()->SetLocalPosition(RenderPos);
}

void Background::ResizeTextureScale(float _Scale)
{
	if (nullptr == BackRender)
	{
		MsgAssert_Rtti<Background>(" - 랜더러를 생성하지 않고 크기를 변경하려 했습니다.");
	}

	Desc.TextureScale = _Scale;

	float4 RenderSize = Desc.TextureSize * Desc.TextureScale;
	RenderSize.z = 1;

	BackRender->GetTransform()->SetLocalScale(RenderSize);

	if (nullptr != LeftRender)
	{
		LeftRender->GetTransform()->SetLocalPosition(float4(-RenderSize.x, 0));
		LeftRender->GetTransform()->SetLocalScale(RenderSize);
	}

	if (nullptr != RightRender)
	{
		RightRender->GetTransform()->SetLocalPosition(float4(RenderSize.x, 0));
		RightRender->GetTransform()->SetLocalScale(RenderSize);
	}
}

void Background::CreateLeftRender()
{
	if (nullptr != LeftRender)
	{
		return;
	}

	float4 RenderSize = Desc.TextureSize * Desc.TextureScale;
	RenderSize.z = 1;

	LeftRender = CreateComponent<GameEngineSpriteRenderer>();
	LeftRender->SetPipeLine("2DTexture_Background");
	LeftRender->GetShaderResHelper().SetConstantBufferLink("TextureMoveBuffer", Buffer);
	LeftRender->SetTexture(Desc.Name);
	LeftRender->GetTransform()->SetLocalPosition(float4(-RenderSize.x, 0));
	LeftRender->GetTransform()->SetLocalScale(RenderSize);
}

void Background::CreateRightRedner()
{
	if (nullptr != RightRender)
	{
		return;
	}

	float4 RenderSize = Desc.TextureSize * Desc.TextureScale;
	RenderSize.z = 1;

	RightRender = CreateComponent<GameEngineSpriteRenderer>();
	RightRender->SetPipeLine("2DTexture_Background");
	RightRender->GetShaderResHelper().SetConstantBufferLink("TextureMoveBuffer", Buffer);
	RightRender->SetTexture(Desc.Name);
	RightRender->GetTransform()->SetLocalPosition(float4(RenderSize.x, 0));
	RightRender->GetTransform()->SetLocalScale(RenderSize);
}

void Background::ReleaseLeftRender()
{
	if (nullptr == LeftRender)
	{
		return;
	}

	//LeftRender->Death();
	//LeftRender = nullptr;
}

void Background::ReleaseRightRender()
{
	if (nullptr == RightRender)
	{
		return;
	}

	//RightRender->Death();
	//RightRender = nullptr;
}

void Background::SaveBin(GameEngineSerializer& _SaveSerializer)
{
	Desc.Color = Buffer.OutColor;

	_SaveSerializer.Write(Desc.Name);
	_SaveSerializer.Write(&Desc.Index, sizeof(UINT));
	_SaveSerializer.Write(&Desc.Center, sizeof(float4));
	_SaveSerializer.Write(&Desc.IsLeftRender, sizeof(bool));
	_SaveSerializer.Write(&Desc.IsRightRender, sizeof(bool));
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
	_LoadSerializer.Read((void*)&LoadDesc.IsLeftRender, sizeof(bool));
	_LoadSerializer.Read((void*)&LoadDesc.IsRightRender, sizeof(bool));
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
	BackRender = CreateComponent<GameEngineSpriteRenderer>();
	BackRender->SetPipeLine("2DTexture_Background");
	BackRender->GetShaderResHelper().SetConstantBufferLink("TextureMoveBuffer", Buffer);
	BackRender->Off();
	BackRender->GetTransform()->SetLocalPosition(float4::Zero);
}
