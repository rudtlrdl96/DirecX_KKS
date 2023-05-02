#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "CameraController.h"

class ContentLevel : public GameEngineLevel
{
public:
	ContentLevel();
	~ContentLevel();

	ContentLevel(const ContentLevel& _Other) = delete;
	ContentLevel(ContentLevel&& _Other) noexcept = delete;
	ContentLevel& operator=(const ContentLevel& _Other) = delete;
	ContentLevel& operator=(ContentLevel&& _Other) noexcept = delete;

	float4 GetMousePos() const;

protected:
	CameraController MainCamCtrl;

	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static std::string CurLevelName;
	static std::string PrevLevelName;

	std::shared_ptr<GameEngineCamera> MainCam = nullptr;

	void Debug_LevelMove(const std::string_view& _LevelName);
};