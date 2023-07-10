#pragma once
#include "BaseContentActor.h"
#include "ContentUIFontRenderer.h"
#include "Rigidbody2D.h"

enum class StageFrameState
{
	None, 
	Down,
	Wait,
	Up
};

class StageInfoFrame : public BaseContentActor
{
public:
	StageInfoFrame();
	~StageInfoFrame();

	StageInfoFrame(const StageInfoFrame& _Other) = delete;
	StageInfoFrame(StageInfoFrame&& _Other) noexcept = delete;
	StageInfoFrame& operator=(const StageInfoFrame& _Other) = delete;
	StageInfoFrame& operator=(StageInfoFrame&& _Other) noexcept = delete;

	void FrameOn(const std::string_view& _LevelName, const std::string_view& _StageNumber, const std::string_view& _StageName);
	void FrameOff(); 


protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	
private:
	std::shared_ptr<GameEngineUIRenderer> FrameRender = nullptr;

	std::shared_ptr<ContentUIFontRenderer> LevelFontRender = nullptr;
	std::shared_ptr<ContentUIFontRenderer> StageNumberFontRender = nullptr;
	std::shared_ptr<ContentUIFontRenderer> StageNameFontRender = nullptr;

	Rigidbody2D Rigid;

	float4 StartPos = float4::Zero;
	float4 EndPos = float4::Zero;

	float WaitTime = 0.0f;

	int GroundColCount = 0;


	StageFrameState State = StageFrameState::None;
};

