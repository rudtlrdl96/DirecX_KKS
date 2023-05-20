#include "PrecompileHeader.h"
#include "Background.h"

Background::Background()
{
}

Background::~Background()
{
}

void Background::Init(const BackgroundMetaData& _MetaData)
{
	MetaData = _MetaData;

	if (nullptr == BackRender)
	{
		MsgAssert("백그라운드 이미지를 초기화 하지 않고 사용하려 했습니다");
		return;
	}

	float4 RenderSize = MetaData.TextureSize * MetaData.TextureScale;
	RenderSize.z = 1;

	BackRender->SetTexture(MetaData.Name);
	BackRender->GetTransform()->SetLocalScale(RenderSize);
	BackRender->On();

	if (true == MetaData.IsLeftRender)
	{
		CreateLeftRender();
		LeftRender->SetTexture(MetaData.Name);
		LeftRender->GetTransform()->SetLocalScale(RenderSize);
		LeftRender->On();	
	}

	if (true == MetaData.IsRightRender)
	{
		CreateRightRedner();
		RightRender->SetTexture(MetaData.Name);
		RightRender->GetTransform()->SetLocalScale(RenderSize);
		RightRender->On();
	}

	Buffer.OutColor = MetaData.Color;
	Buffer.Uv = float4::Zero;

	GetTransform()->SetLocalPosition(MetaData.Center);
}

void Background::UpdateTargetPos(float _DeltaTime, const float4& _TargetPos)
{
	if (nullptr == BackRender)
	{
		MsgAssert("백그라운드 이미지를 초기화 하지 않고 사용하려 했습니다");
		return;
	}

	float4 RenderPos = MetaData.Center;
	float4 TargetDir = _TargetPos - MetaData.Center;

	TargetDir.z = MetaData.Center.z;

	RenderPos += TargetDir * (1.0f - MetaData.MoveRatio);
	RenderPos.z = MetaData.Center.z;

	if (true == MetaData.Animation)
	{
		if (0 < MetaData.AnimationSpeed)
		{
			Buffer.Uv.x += _DeltaTime * MetaData.AnimationSpeed;

			if (1.0f <= Buffer.Uv.x)
			{
				Buffer.Uv.x -= 1.0f;
			}
		}
		else
		{
			Buffer.Uv.x += _DeltaTime * MetaData.AnimationSpeed;

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

	MetaData.TextureScale = _Scale;

	float4 RenderSize = MetaData.TextureSize * MetaData.TextureScale;
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

	float4 RenderSize = MetaData.TextureSize * MetaData.TextureScale;
	RenderSize.z = 1;

	LeftRender = CreateComponent<ContentSpriteRenderer>();
	LeftRender->PipeSetting("2DTexture_Background", false);
	LeftRender->GetShaderResHelper().SetConstantBufferLink("TextureMoveBuffer", Buffer);
	LeftRender->SetTexture(MetaData.Name);
	LeftRender->GetTransform()->SetLocalPosition(float4(-RenderSize.x, 0));
	LeftRender->GetTransform()->SetLocalScale(RenderSize);
}

void Background::CreateRightRedner()
{
	if (nullptr != RightRender)
	{
		return;
	}

	float4 RenderSize = MetaData.TextureSize * MetaData.TextureScale;
	RenderSize.z = 1;

	RightRender = CreateComponent<ContentSpriteRenderer>();
	RightRender->PipeSetting("2DTexture_Background", false);
	RightRender->GetShaderResHelper().SetConstantBufferLink("TextureMoveBuffer", Buffer);
	RightRender->SetTexture(MetaData.Name);
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
	MetaData.Color = Buffer.OutColor;

	_SaveSerializer.Write(MetaData.Name);
	_SaveSerializer.Write(&MetaData.Index, sizeof(UINT));
	_SaveSerializer.Write(&MetaData.Center, sizeof(float4));
	_SaveSerializer.Write(&MetaData.IsLeftRender, sizeof(bool));
	_SaveSerializer.Write(&MetaData.IsRightRender, sizeof(bool));
	_SaveSerializer.Write(&MetaData.Animation, sizeof(bool));
	_SaveSerializer.Write(&MetaData.AnimationSpeed, sizeof(float));
	_SaveSerializer.Write(&MetaData.MoveRatio, sizeof(float));
	_SaveSerializer.Write(&MetaData.TextureSize, sizeof(float4));
	_SaveSerializer.Write(&MetaData.TextureScale, sizeof(float));
	_SaveSerializer.Write(&MetaData.Color, sizeof(float4));
}

BackgroundMetaData Background::LoadBin(GameEngineSerializer& _LoadSerializer)
{
	BackgroundMetaData LoadMetaData = BackgroundMetaData();

	_LoadSerializer.Read(LoadMetaData.Name);
	_LoadSerializer.Read((void*)&LoadMetaData.Index, sizeof(UINT));
	_LoadSerializer.Read((void*)&LoadMetaData.Center, sizeof(float4));
	_LoadSerializer.Read((void*)&LoadMetaData.IsLeftRender, sizeof(bool));
	_LoadSerializer.Read((void*)&LoadMetaData.IsRightRender, sizeof(bool));
	_LoadSerializer.Read((void*)&LoadMetaData.Animation, sizeof(bool));
	_LoadSerializer.Read((void*)&LoadMetaData.AnimationSpeed, sizeof(float));
	_LoadSerializer.Read((void*)&LoadMetaData.MoveRatio, sizeof(float));
	_LoadSerializer.Read((void*)&LoadMetaData.TextureSize, sizeof(float4));
	_LoadSerializer.Read((void*)&LoadMetaData.TextureScale, sizeof(float));
	_LoadSerializer.Read((void*)&LoadMetaData.Color, sizeof(float4));

	return LoadMetaData;
}

void Background::Start()
{
	BackRender = CreateComponent<ContentSpriteRenderer>();
	BackRender->PipeSetting("2DTexture_Background", false);
	BackRender->GetShaderResHelper().SetConstantBufferLink("TextureMoveBuffer", Buffer);
	BackRender->Off();
	BackRender->GetTransform()->SetLocalPosition(float4::Zero);
}
