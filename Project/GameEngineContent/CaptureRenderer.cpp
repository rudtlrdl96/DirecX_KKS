#include "PrecompileHeader.h"
#include "CaptureRenderer.h"

CaptureRenderer::CaptureRenderer()
{
}

CaptureRenderer::~CaptureRenderer()
{
}

void CaptureRenderer::SetTexture(const std::string_view& _TextureName, const float4& _AtlasData, float _ScaleRatio /*= 1.0f*/)
{
	if (nullptr == CaptureRender)
	{
		MsgAssert_Rtti<CaptureRenderer>(" - 랜더러를 생성하지 않고 사용하려 했습니다.");
		return;
	}

	CaptureRender->SetScaleToTexture(_TextureName);	
	float4 TetxureScale = CaptureRender->GetTransform()->GetLocalScale();

	TetxureScale.x *= _AtlasData.SizeX;
	TetxureScale.y *= _AtlasData.SizeY;

	CaptureRender->GetTransform()->SetLocalScale(TetxureScale * _ScaleRatio);

	AtlasData = _AtlasData;
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
	CaptureRender->SetPipeLine("2DTexture_Color");
	CaptureRender->GetShaderResHelper().SetConstantBufferLink("AtlasData", AtlasData);
	CaptureRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
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
	Buffer.Color = float4::LerpClamp(StartColor, EndColor, ProgressTime);

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