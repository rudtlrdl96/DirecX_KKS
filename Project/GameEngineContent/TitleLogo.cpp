#include "PrecompileHeader.h"
#include "TitleLogo.h"

TitleLogo::TitleLogo()
{
}

TitleLogo::~TitleLogo()
{
}

void TitleLogo::SetLogo(const std::string_view& _TexName, float _IntroTime, float _OutroTime, float _WaitTime, float _Scale)
{
	std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find(_TexName);

	if (nullptr == FindTex)
	{
		MsgAssert_Rtti<TitleLogo>(" - 해당 이름의 텍스쳐를 찾을 수 없습니다 : " + std::string(_TexName));
	}

	float4 TextureSize = { static_cast<float>(FindTex->GetWidth()),static_cast<float>(FindTex->GetHeight()) };

	LogoRender->SetTexture(_TexName);
	LogoRender->GetTransform()->SetWorldScale(TextureSize * _Scale);
	LogoRender->On();

	Buffer.Color = float4::Zero;
	ProgressTime = 0.0f;

	LogoEndValue = false;
	IntroStartTime = 0.0f;
	IntroEndTime = _IntroTime;
	WaitStartTime = IntroEndTime;
	WaitEndTime = WaitStartTime + _WaitTime;
	OutroStartTime = WaitEndTime;
	OutroEndTime = OutroStartTime + _OutroTime;
}

void TitleLogo::Start()
{
	LogoRender = CreateComponent<ContentSpriteRenderer>();
	LogoRender->SetPipeLine("2DTexture_ColorLight");
	LogoRender->SetAtlasConstantBuffer();
	LogoRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	LogoRender->SetTexture("Empty.png");

	LogoRender->Off();
	LogoEndValue = false;
}

void TitleLogo::Update(float _DeltaTime)
{
	ProgressTime += _DeltaTime;

	if (ProgressTime > OutroEndTime)
	{
		LogoEndValue = true;
		return;
	}

	if (ProgressTime >= OutroStartTime)
	{
		Buffer.Color.w = 1.0f - ProgressCheck(OutroStartTime, OutroEndTime, ProgressTime);
	}
	else if (ProgressTime >= WaitStartTime)
	{

	}
	else if (ProgressTime >= IntroStartTime)
	{
		Buffer.Color.w = ProgressCheck(IntroStartTime, IntroEndTime, ProgressTime);
	}	 
}

float TitleLogo::ProgressCheck(float _StartTime, float _EndTime, float _TotalProgressTime)
{
	float TimeDis = _EndTime - _StartTime;
	float CurStateProgress = _TotalProgressTime - _StartTime;
	return CurStateProgress / TimeDis;
}
