#pragma once

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/EngineContentRenderingStruct.h>

class ContentAnimationInfo : public std::enable_shared_from_this<ContentAnimationInfo>
{
	friend class ContentSpriteRenderer;

private:
	ContentSpriteRenderer* Parent = nullptr;

	std::shared_ptr<GameEngineSprite> Sprite;

	bool IsEndValue = false;

	void Reset();

	void Update(float _DeltaTime);

	const SpriteInfo& CurSpriteInfo();

	inline void PauseOn()
	{
		IsPauseValue = true;
	}

	inline void PauseOff()
	{
		IsPauseValue = false;
	}

public:
	size_t CurFrame = 0;
	size_t StartFrame = -1;
	size_t EndFrame = -1;
	float CurTime = 0.0f;
	float Inter = 0.1f;
	bool Loop = true;
	bool ScaleToTexture = false;
	bool IsPauseValue = false;
	std::vector<size_t> FrameIndex = std::vector<size_t>();
	std::vector<float> FrameTime = std::vector<float>();

	std::map<size_t, std::function<void()>> UpdateEventFunction;
	std::map<size_t, std::function<void()>> StartEventFunction;

	bool IsEnd();
};


class ContentAnimationParameter
{
public:
	std::string_view AnimationName = "";
	std::string_view SpriteName = "";
	size_t Start = static_cast<size_t>(-1);
	size_t End = static_cast<size_t>(-1);
	float FrameInter = 0.1f;
	bool Loop = true;
	bool ScaleToTexture = false;
	std::vector<size_t> FrameIndex = std::vector<size_t>();
	std::vector<float> FrameTime = std::vector<float>();
};


// Ό³Έν :
class ContentSpriteRenderer : public GameEngineRenderer
{
public:
	// constrcuter destructer
	ContentSpriteRenderer();
	~ContentSpriteRenderer();

	// delete Function
	ContentSpriteRenderer(const ContentSpriteRenderer& _Other) = delete;
	ContentSpriteRenderer(ContentSpriteRenderer&& _Other) noexcept = delete;
	ContentSpriteRenderer& operator=(const ContentSpriteRenderer& _Other) = delete;
	ContentSpriteRenderer& operator=(ContentSpriteRenderer&& _Other) noexcept = delete;

	void SetScaleToTexture(const std::string_view& _Name);

	void SetTexture(const std::string_view& _Name);

	void SetScaleRatio(float _Ratio)
	{
		ScaleRatio = _Ratio;
	}

	void SetFlipX();
	void SetFlipY();

	std::shared_ptr<ContentAnimationInfo> FindAnimation(const std::string_view& _Name);

	std::shared_ptr<ContentAnimationInfo> CreateAnimation(const ContentAnimationParameter& _Paramter);

	void ChangeAnimation(const std::string_view& _Name, bool _Force, size_t _Frame = -1)
	{
		ChangeAnimation(_Name, _Frame, _Force);
	}

	void ChangeAnimation(const std::string_view& _Name, size_t _Frame = -1, bool _Force = true);

	bool IsAnimationEnd()
	{
		return CurAnimation->IsEnd();
	}

	size_t GetCurrentFrame()
	{
		return CurAnimation->CurFrame;
	}

	void SetAtlasData(const float4& _AtlasData)
	{
		AtlasData = _AtlasData;
	}

	float4 GetAtlasData()
	{
		return AtlasData;
	}

	inline float GetScaleRatio() const
	{
		return ScaleRatio;
	}

	void SetSprite(const std::string_view& _SpriteName, size_t _Frame = 0);

	void SetFrame(size_t _Frame);

	void SetAnimPauseOn()
	{
		CurAnimation->PauseOn();
	}

	void SetAnimPauseOff()
	{
		CurAnimation->PauseOff();
	}

	void SetAnimationUpdateEvent(const std::string_view& _AnimationName, size_t _Frame, std::function<void()> _Event);

	void SetAnimationStartEvent(const std::string_view& _AnimationName, size_t _Frame, std::function<void()> _Event);

	std::string GetTexName();

	void PipeSetting(const std::string_view _PipeName, bool _IsAtlasData = true);

protected:
	void Render(float _Delta) override;

private:
	void Update(float _Delta) override;


	std::map<std::string, std::shared_ptr<ContentAnimationInfo>> Animations;

	std::shared_ptr<ContentAnimationInfo> CurAnimation;

	float4 AtlasData;


	std::shared_ptr<GameEngineSprite> Sprite = nullptr;
	size_t Frame = -1;


	float ScaleRatio = 1.0f;

	void Start() override;
};
