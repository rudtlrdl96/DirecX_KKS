#include "PrecompileHeader.h"
#include "StoryTextureView.h"

StoryTextureView::StoryTextureView()
{
}

StoryTextureView::~StoryTextureView()
{
}

void StoryTextureView::SetMainTexture(const std::string_view& _TextureName, const float4& _Pos/* = float4{ 0, 35 }*/)
{
	MainTextureName = _TextureName;

	std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find(MainTextureName);

	if (nullptr == FindTex)
	{
		MsgAssert(std::string("해당 이름을 가진 이미지를 찾을 수 없습니다 ") + MainTextureName.data());
	}

	float4 ImageScale = {
		static_cast<float>(FindTex->GetWidth()),
		static_cast<float>(FindTex->GetHeight()), 1.0f };

	ImageScale *= 2.0f;

	float4 RenderPos = MainTextureRender->GetTransform()->GetWorldPosition();

	RenderPos.x = _Pos.x;
	RenderPos.y = _Pos.y;

	MainTextureRender->SetTexture(MainTextureName);
	MainTextureRender->GetTransform()->SetWorldScale(ImageScale);
	MainTextureRender->GetTransform()->SetWorldPosition(RenderPos);
}

void StoryTextureView::SetSubTexture(const std::string_view& _TextureName, const float4& _Pos/*= float4{ 0, 35 }*/)
{
	SubTextureName = _TextureName;

	std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find(SubTextureName);

	if (nullptr == FindTex)
	{
		MsgAssert(std::string("해당 이름을 가진 이미지를 찾을 수 없습니다 ") + SubTextureName.data());
	}

	float4 ImageScale = {
		static_cast<float>(FindTex->GetWidth()),
		static_cast<float>(FindTex->GetHeight()), 1.0f };

	ImageScale *= 2.0f;

	float4 RenderPos = SubTextureRender->GetTransform()->GetWorldPosition();

	RenderPos.x = _Pos.x;
	RenderPos.y = _Pos.y;

	SubTextureRender->SetTexture(SubTextureName);
	SubTextureRender->GetTransform()->SetWorldScale(ImageScale);
	SubTextureRender->GetTransform()->SetWorldPosition(RenderPos);
}

void StoryTextureView::SetBackgroundTexture(const std::string_view& _TextureName, const float4& _Pos /*= float4{ 0, 35 }*/)
{
	BackTextureName = _TextureName;

	std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find(BackTextureName);

	if (nullptr == FindTex)
	{
		MsgAssert(std::string("해당 이름을 가진 이미지를 찾을 수 없습니다 ") + BackTextureName.data());
	}

	float4 ImageScale = {
		static_cast<float>(FindTex->GetWidth()),
		static_cast<float>(FindTex->GetHeight()), 1.0f };

	ImageScale *= 2.0f;

	float4 RenderPos = BackgroundTextureRender->GetTransform()->GetWorldPosition();

	RenderPos.x = _Pos.x;
	RenderPos.y = _Pos.y;

	BackgroundTextureRender->SetTexture(BackTextureName);
	BackgroundTextureRender->GetTransform()->SetWorldScale(ImageScale);
	BackgroundTextureRender->GetTransform()->SetWorldPosition(RenderPos);
}

void StoryTextureView::SwapMainSubTexture()
{
	ContentFunc::Swap<std::string>(&MainTextureName, &SubTextureName);
	ContentFunc::Swap<float4>(&MainColor, &SubColor);

	TransformData MainTrans = MainTextureRender->GetTransform()->GetTransDataRef();
	TransformData SubTrans = SubTextureRender->GetTransform()->GetTransDataRef();
	
	MainTextureRender->SetTexture(MainTextureName);
	SubTextureRender->SetTexture(SubTextureName);

	MainTextureRender->GetTransform()->SetTransformData(SubTrans);
	SubTextureRender->GetTransform()->SetTransformData(MainTrans);
	
	float4 MainPos = MainTextureRender->GetTransform()->GetWorldPosition();
	MainPos.z = -100;
	
	float4 SubPos = SubTextureRender->GetTransform()->GetWorldPosition();
	SubPos.z = 0;

	MainTextureRender->GetTransform()->SetWorldPosition(MainPos);
	SubTextureRender->GetTransform()->SetWorldPosition(SubPos);
}

void StoryTextureView::FadeIntro(float _FadeSpeed/*= 1.0f*/)
{
	FadeSpeed = _FadeSpeed;
	FadeProgress = 0.0f;

	State = StoryViewState::Fade;
}

void StoryTextureView::MoveMainTexture(const float4& _MoveDir, float _MoveSpeed /*= 50.0f*/)
{
	MoveProgress = 0.0f;

	MaxMoveSpeed = _MoveSpeed / _MoveDir.Size();
	MinMoveSpeed = MaxMoveSpeed * 0.1f;
	CurMoveSpeed = MinMoveSpeed;
	DiffMoveSpeed = MaxMoveSpeed * 2.0f;

	MoveStart = MainTextureRender->GetTransform()->GetWorldPosition();
	MoveEnd = MoveStart + _MoveDir;

	State = StoryViewState::Move;
}

void StoryTextureView::Reset()
{
	State = StoryViewState::None;

	SetMainTexture("Empty.png");
	SetSubTexture("Empty.png");
	SetBackgroundTexture("Empty.png");

	MainColor = float4::Zero;
	SubColor = float4::Zero;
	BackColor = float4::Zero;

	MoveStart = float4::Zero;
	MoveEnd = float4::Zero;

	MoveProgress = 0.0f;

	CurMoveSpeed = 0.0f;
	MaxMoveSpeed = 1.0f;
	MinMoveSpeed = 1.0f;
	DiffMoveSpeed = 1.0f;

	FadeProgress = 0.0f;
	FadeSpeed = 1.0f;
}


void StoryTextureView::Start()
{
	BackgroundTextureRender = CreateComponent<GameEngineSpriteRenderer>();
	BackgroundTextureRender->SetPipeLine("2DTexture_ColorLight");
	BackgroundTextureRender->GetShaderResHelper().SetConstantBufferLink("OutPixelColor", BackColor);
	BackgroundTextureRender->SetTexture("Empty.png");
	BackgroundTextureRender->GetTransform()->SetWorldPosition({ 0, 0, 100 });

	SubTextureRender = CreateComponent<GameEngineSpriteRenderer>();
	SubTextureRender->SetPipeLine("2DTexture_ColorLight");
	SubTextureRender->GetShaderResHelper().SetConstantBufferLink("OutPixelColor", SubColor);
	SubTextureRender->SetTexture("Empty.png");
	SubTextureRender->GetTransform()->SetWorldPosition({ 0, 0, 0});

	MainTextureRender = CreateComponent<GameEngineSpriteRenderer>();
	MainTextureRender->SetPipeLine("2DTexture_ColorLight");
	MainTextureRender->GetShaderResHelper().SetConstantBufferLink("OutPixelColor", MainColor);
	MainTextureRender->SetTexture("Empty.png");	
	MainTextureRender->GetTransform()->SetWorldPosition({0, 0, -100});
}

void StoryTextureView::Update(float _DeltaTime)
{
	switch (State)
	{
	case StoryTextureView::StoryViewState::Fade:
	{
		FadeProgress += _DeltaTime * FadeSpeed;	
		MainColor.w = FadeProgress;

		if (FadeProgress >= 1.0f)
		{
			FadeProgress = 0.0f;
			State = StoryViewState::None;
		}

		break;
	}
	case StoryTextureView::StoryViewState::Move:
	{
		float CenterDistance = 0.5f - MoveProgress;

		if (0 < CenterDistance)
		{
			CurMoveSpeed += DiffMoveSpeed * _DeltaTime;

			if (CurMoveSpeed > MaxMoveSpeed)
			{
				CurMoveSpeed = MaxMoveSpeed;
			}
		}
		else
		{
			CurMoveSpeed -= DiffMoveSpeed * _DeltaTime;

			if (CurMoveSpeed < MinMoveSpeed)
			{
				CurMoveSpeed = MinMoveSpeed;
			}
		}

		MoveProgress += _DeltaTime * CurMoveSpeed;
		float4 MovePos = float4::LerpClamp(MoveStart, MoveEnd, MoveProgress);

		MainTextureRender->GetTransform()->SetWorldPosition(MovePos);

		if (MoveProgress >= 1.0f)
		{
			MoveProgress = 0.0f;
			State = StoryViewState::None;
		}

		break;
	}
	default:
		return;
	}

}
