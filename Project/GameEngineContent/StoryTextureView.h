#pragma once
#include "BaseContentActor.h"

class StoryTextureView : public BaseContentActor
{
private:
	enum class StoryViewState
	{
		None,
		Fade,
		Move
	};
public:
	StoryTextureView();
	~StoryTextureView();

	StoryTextureView(const StoryTextureView& _Other) = delete;
	StoryTextureView(StoryTextureView&& _Other) noexcept = delete;
	StoryTextureView& operator=(const StoryTextureView& _Other) = delete;
	StoryTextureView& operator=(StoryTextureView&& _Other) noexcept = delete;

	void SetMainTexture(const std::string_view& _TextureName, const float4& _Pos = float4{0, 35});
	void SetSubTexture(const std::string_view& _TextureName, const float4& _Pos = float4{ 0, 35 });
	void SetBackgroundTexture(const std::string_view& _TextureName, const float4& _Pos = float4{ 0, 35 });
	
	void SwapMainSubTexture();
	void FadeIntro(float _FadeSpeed = 1.0f);

	void MoveMainTexture(const float4& _MoveDir, float _MoveSpeed = 50.0f);

	void Reset();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
		
private:
	StoryViewState State = StoryViewState::None;

	std::shared_ptr<GameEngineSpriteRenderer> BackgroundTextureRender = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> MainTextureRender = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> SubTextureRender = nullptr;

	std::string MainTextureName = "Empty.png";
	std::string SubTextureName = "Empty.png";
	std::string BackTextureName = "Empty.png";

	ColorBuffer MainTexBuffer;
	ColorBuffer SubTexBuffer;
	ColorBuffer BackTexBuffer;

	float4 MoveStart = float4::Zero;
	float4 MoveEnd = float4::Zero;

	float MoveProgress = 0.0f;

	float CurMoveSpeed = 0.0f;
	float MaxMoveSpeed = 1.0f;
	float MinMoveSpeed = 1.0f;
	float DiffMoveSpeed = 1.0f;

	float FadeProgress = 0.0f;
	float FadeSpeed = 1.0f;

};