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

	inline CameraController& GetCamCtrl()
	{
		return MainCamCtrl;
	}

protected:
	CameraController MainCamCtrl;

	const UINT LevelCode = 0;

	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineCamera> MainCam = nullptr;
};