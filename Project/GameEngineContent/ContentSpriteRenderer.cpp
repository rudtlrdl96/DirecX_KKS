#include "PrecompileHeader.h"
#include "ContentSpriteRenderer.h"

const SpriteInfo& ContentAnimationInfo::CurSpriteInfo()
{
	const SpriteInfo& Info = Sprite->GetSpriteInfo(FrameIndex[CurFrame]);
	return Info;
}

bool ContentAnimationInfo::IsEnd()
{
	return IsEndValue;
}

void ContentAnimationInfo::Reset()
{
	CurFrame = 0;
	CurTime = FrameTime[0];
	IsEndValue = false;
	IsPauseValue = false;
}

void ContentAnimationInfo::Update(float _DeltaTime)
{
	IsEndValue = false;

	// 1;
	// 

	if (true == IsPauseValue)
	{
		return;
	}

	size_t CurFrameIndex = FrameIndex[CurFrame];


	if (UpdateEventFunction.end() != UpdateEventFunction.find(CurFrameIndex))
	{
		UpdateEventFunction[CurFrameIndex]();
	}

	CurTime -= _DeltaTime;

	if (0.0f >= CurTime)
	{
		++CurFrame;


		if (StartEventFunction.end() != StartEventFunction.find(CurFrameIndex))
		{
			StartEventFunction[CurFrameIndex]();
		}

		if (FrameIndex.size() <= CurFrame)
		{
			IsEndValue = true;

			if (true == Loop)
			{
				CurFrame = 0;
			}
			else
			{
				--CurFrame;
			}
		}
		CurTime += FrameTime[CurFrame];

		// 0 ~ 9

		// 9
	}
}

// SpriteRenderer

ContentSpriteRenderer::ContentSpriteRenderer()
{
}

ContentSpriteRenderer::~ContentSpriteRenderer()
{
}


void ContentSpriteRenderer::Start()
{
	GameEngineRenderer::Start();

	SetPipeLine("2DTexture");

	AtlasData.x = 0.0f;
	AtlasData.y = 0.0f;
	AtlasData.z = 1.0f;
	AtlasData.w = 1.0f;

	ColorOptionValue.MulColor = float4::One;
	ColorOptionValue.PlusColor = float4::Null;

	GetShaderResHelper().SetConstantBufferLink("AtlasData", AtlasData);
	GetShaderResHelper().SetConstantBufferLink("ColorOption", ColorOptionValue);

	// AtlasData
}

void ContentSpriteRenderer::SetTexture(const std::string_view& _Name)
{
	GetShaderResHelper().SetTexture("DiffuseTex", _Name);
}

void ContentSpriteRenderer::SetFlipX()
{
	float4 LocalScale = GetTransform()->GetLocalScale();
	LocalScale.x = -LocalScale.x;
	GetTransform()->SetLocalScale(LocalScale);
}

void ContentSpriteRenderer::SetFlipY()
{
	float4 LocalScale = GetTransform()->GetLocalScale();
	LocalScale.y = -LocalScale.y;
	GetTransform()->SetLocalScale(LocalScale);
}

void ContentSpriteRenderer::SetScaleToTexture(const std::string_view& _Name)
{
	GetShaderResHelper().SetTexture("DiffuseTex", _Name);
	std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find(_Name);

	if (nullptr == FindTex)
	{
		MsgAssert("�������� �ʴ� �̹��� �Դϴ�.");
		return;
	}

	float4 Scale = float4(static_cast<float>(FindTex->GetWidth()), static_cast<float>(FindTex->GetHeight()), 1);
	GetTransform()->SetLocalScale(Scale);
}

void ContentSpriteRenderer::SetSprite(const std::string_view& _SpriteName, size_t _Frame/* = 0*/)
{
	Sprite = GameEngineSprite::Find(_SpriteName);
	Frame = _Frame;

	const SpriteInfo& Info = Sprite->GetSpriteInfo(Frame);
	GetShaderResHelper().SetTexture("DiffuseTex", Info.Texture);
	AtlasData = Info.CutData;
}

void ContentSpriteRenderer::SetFrame(size_t _Frame)
{
	Frame = _Frame;

	const SpriteInfo& Info = Sprite->GetSpriteInfo(Frame);
	GetShaderResHelper().SetTexture("DiffuseTex", Info.Texture);
	AtlasData = Info.CutData;
}

std::shared_ptr<ContentAnimationInfo> ContentSpriteRenderer::FindAnimation(const std::string_view& _Name)
{
	std::map<std::string, std::shared_ptr<ContentAnimationInfo>>::iterator FindIter = Animations.find(_Name.data());

	if (FindIter == Animations.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

std::shared_ptr<ContentAnimationInfo> ContentSpriteRenderer::CreateAnimation(const AnimationParameter& _Paramter)
{
	if (nullptr != FindAnimation(_Paramter.AnimationName))
	{
		MsgAssert("�̹� �����ϴ� �̸��� �ִϸ��̼��� �� ������� �߽��ϴ�." + std::string(_Paramter.AnimationName));
		return nullptr;
	}

	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find(_Paramter.SpriteName);

	if (nullptr == Sprite)
	{
		MsgAssert("�������� �ʴ� ��������Ʈ�� �ִϸ��̼��� ������� �߽��ϴ�." + std::string(_Paramter.AnimationName));
		return nullptr;
	}

	std::shared_ptr<ContentAnimationInfo> NewAnimation = std::make_shared<ContentAnimationInfo>();
	Animations[_Paramter.AnimationName.data()] = NewAnimation;

	if (0 != _Paramter.FrameIndex.size())
	{
		// ������ �ε��� �Է½�
		NewAnimation->FrameIndex = _Paramter.FrameIndex;

	}
	else
	{
		// ������ �ε��� �� �Է½�

		// ���� ������ ����
		if (-1 != _Paramter.Start)
		{
			if (_Paramter.Start < 0)
			{
				MsgAssert("��������Ʈ ������ �ʰ��ϴ� �ε����� �ִϸ��̼��� ������� �߽��ϴ�." + std::string(_Paramter.AnimationName));
				return nullptr;
			}

			NewAnimation->StartFrame = _Paramter.Start;
		}
		else
		{
			// -1 �Է½� ���������� 0
			NewAnimation->StartFrame = 0;
		}
		// �� ������ ����
		if (-1 != _Paramter.End)
		{
			if (_Paramter.End >= Sprite->GetSpriteCount())
			{
				MsgAssert("��������Ʈ ������ �ʰ��ϴ� �ε����� �ִϸ��̼��� ������� �߽��ϴ�." + std::string(_Paramter.AnimationName));
				return nullptr;
			}

			NewAnimation->EndFrame = _Paramter.End;
		}
		else
		{
			// -1 �Է½� ���������� ������
			NewAnimation->EndFrame = Sprite->GetSpriteCount() - 1;
		}

		if (NewAnimation->EndFrame < NewAnimation->StartFrame)
		{
			MsgAssert("�ִϸ��̼��� �����Ҷ� End�� Start���� Ŭ �� �����ϴ�");
			return nullptr;
		}
		NewAnimation->FrameIndex.reserve(NewAnimation->EndFrame - NewAnimation->StartFrame + 1);

		// StartFrame ���� EndFrame���� ������� FrameIndex�� Ǫ��
		for (size_t i = NewAnimation->StartFrame; i <= NewAnimation->EndFrame; ++i)
		{
			NewAnimation->FrameIndex.push_back(i);
		}
	}

	// Ÿ�� �����Ͱ� �ִٸ�
	if (0 != _Paramter.FrameTime.size())
	{
		NewAnimation->FrameTime = _Paramter.FrameTime;

	}
	else
	{
		for (size_t i = 0; i < NewAnimation->FrameIndex.size(); ++i)
		{
			NewAnimation->FrameTime.push_back(_Paramter.FrameInter);
		}
	}



	NewAnimation->Sprite = Sprite;
	NewAnimation->Parent = this;
	NewAnimation->Loop = _Paramter.Loop;
	NewAnimation->ScaleToTexture = _Paramter.ScaleToTexture;

	return NewAnimation;
}


void ContentSpriteRenderer::ChangeAnimation(const std::string_view& _Name, size_t _Frame, bool _Force)
{
	std::shared_ptr<ContentAnimationInfo> Find = FindAnimation(_Name);

	if (nullptr == Find)
	{
		MsgAssert("�̷��� �̸��� �ִϸ��̼��� �������� �ʽ��ϴ�" + std::string(_Name));
		return;
	}

	if (CurAnimation == Find && false == _Force)
	{
		return;
	}

	CurAnimation = FindAnimation(_Name);
	CurAnimation->Reset();

	if (_Frame != -1)
	{
		CurAnimation->CurFrame = _Frame;
	}

}

void ContentSpriteRenderer::Update(float _Delta)
{
	if (nullptr != CurAnimation)
	{
		CurAnimation->Update(_Delta);
	}
}

void ContentSpriteRenderer::Render(float _Delta)
{
	if (nullptr != CurAnimation)
	{
		const SpriteInfo& Info = CurAnimation->CurSpriteInfo();

		GetShaderResHelper().SetTexture("DiffuseTex", Info.Texture);
		AtlasData = Info.CutData;

		if (true == CurAnimation->ScaleToTexture)
		{
			std::shared_ptr<GameEngineTexture> Texture = Info.Texture;

			float4 Scale = Texture->GetScale();

			Scale.x *= Info.CutData.SizeX;
			Scale.y *= Info.CutData.SizeY;
			Scale.z = 1.0f;

			Scale *= ScaleRatio;

			GetTransform()->SetLocalScale(Scale);
		}

	}
	GameEngineRenderer::Render(_Delta);
}

void ContentSpriteRenderer::SetAnimationUpdateEvent(const std::string_view& _AnimationName, size_t _Frame, std::function<void()> _Event)
{
	std::shared_ptr<ContentAnimationInfo>  Info = FindAnimation(_AnimationName);

	if (nullptr == Info)
	{
		MsgAssert("�������� �ʴ� �ִϸ��̼ǿ� �̺�Ʈ ������ �Ϸ��� �߽��ϴ�.");
	}

	Info->UpdateEventFunction[_Frame] = _Event;
}

void ContentSpriteRenderer::SetAnimationStartEvent(const std::string_view& _AnimationName, size_t _Frame, std::function<void()> _Event)
{
	std::shared_ptr<ContentAnimationInfo>  Info = FindAnimation(_AnimationName);

	if (nullptr == Info)
	{
		MsgAssert("�������� �ʴ� �ִϸ��̼ǿ� �̺�Ʈ ������ �Ϸ��� �߽��ϴ�.");
	}

	Info->StartEventFunction[_Frame] = _Event;
}

void ContentSpriteRenderer::SetAtlasConstantBuffer()
{
	GetShaderResHelper().SetConstantBufferLink("AtlasData", AtlasData);
}

std::string ContentSpriteRenderer::GetTexName()
{
	GameEngineTextureSetter* Tex = GetShaderResHelper().GetTextureSetter("DiffuseTex");
	std::string Name = Tex->Res->GetNameToString();
	return Name;
}