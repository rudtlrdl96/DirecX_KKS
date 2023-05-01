#include "PrecompileHeader.h"
#include "CaptureRenderer.h"

CaptureRenderer::CaptureRenderer()
{
}

CaptureRenderer::~CaptureRenderer()
{
}

void CaptureRenderer::SetTexture(const std::string_view& _TextureName, const float4& _TextureSize /*= float4::Zero*/)
{
	if (nullptr == CaptureRender)
	{
		MsgAssert_Rtti<CaptureRenderer>(" - 랜더러를 생성하지 않고 사용하려 했습니다.");
		return;
	}

	CaptureRender->SetTexture(_TextureName);

	if (float4::Zero == _TextureSize)
	{
		std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find(_TextureName);

		if (nullptr == FindTex)
		{
			MsgAssert_Rtti<CaptureRenderer>(" - 존재 하지 않는 텍스쳐를 세팅하려 했습니다.");
			return;
		}

		float4 TexSize = { static_cast<float>(FindTex->GetWidth()), static_cast<float>(FindTex->GetHeight()), 1.0f };
		CaptureRender->GetTransform()->SetLocalScale(TexSize);
	}
	else
	{
		CaptureRender->GetTransform()->SetLocalScale(_TextureSize);
	}
}

void CaptureRenderer::Play(const float4& _StartColor, const float4& _EndColor, float _Time)
{
	if (_Time == 0.0f)
	{
		MsgAssert_Rtti<CaptureRenderer>(" - 시간을 0으로 설정할 수 없습니다");
		return;
	}

	CaptureRender->On();
	IsPlayingValue = true;
	ProgressTime = 0.0f;

	StartColor = _StartColor;
	EndColor = _EndColor;

	PlaySpeed = 1.0f / _Time;
}

void CaptureRenderer::Start()
{
	CaptureRender = CreateComponent<GameEngineSpriteRenderer>();
	CaptureRender->SetPipeLine("2DTexture_Capture");
	CaptureRender->GetShaderResHelper().SetConstantBufferLink("OutPixelColor", Color);
	CaptureRender->SetTexture("Empty.png");
	CaptureRender->Off();
}

void CaptureRenderer::Update(float _DeltaTime)
{
	if (false == IsPlayingValue)
	{
		return;
	}

	ProgressTime += _DeltaTime * PlaySpeed;
	Color = float4::LerpClamp(StartColor, EndColor, ProgressTime);

	if (1.0f + (WaitTime * PlaySpeed) <= ProgressTime)
	{
		if (true == IsLoop)
		{
			ProgressTime -= 1.0f + (WaitTime * PlaySpeed);
		}
		else
		{
			IsPlayingValue = false;
			CaptureRender->Off();
		}
	}
}