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

	void AddEvent(const std::string_view& _Event, UINT _ActorCode, std::function<void()> _Callback);
	void RemoveEvent(const std::string_view& _Event, UINT _ActorCode);
	void CallEvent(const std::string_view& _Event);

	void PlayBaseBGM();
	void StopBaseBGM();

	void PlayCustomBgm(const std::string_view& _BgmName, float _FadeTime = 1.0f);
	void StopCustomBgm(float _FadeTime = 1.0f);

protected:
	CameraController MainCamCtrl;
	std::string BgmName = "";

	const UINT LevelCode = 0;

	float BGM_FadeIn_Time = 1.0f;
	float BGM_FadeOut_Time = 1.0f;

	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	std::shared_ptr<GameEngineCamera> MainCam = nullptr;
	std::map<std::string, std::map<UINT, std::function<void(void)>>> EventCallback;

	GameEngineSoundPlayer BaseBgmPlayer;
	GameEngineSoundPlayer CustomBgmPlayer;
};