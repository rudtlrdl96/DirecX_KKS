#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "CameraController.h"

#include "WorldLightEffect.h"
#include "PointLightEffect.h"

class ContentLevel : public GameEngineLevel
{
	friend class ContentLevelLightGUI;
public:
	ContentLevel();
	~ContentLevel();

	ContentLevel(const ContentLevel& _Other) = delete;
	ContentLevel(ContentLevel&& _Other) noexcept = delete;
	ContentLevel& operator=(const ContentLevel& _Other) = delete;
	ContentLevel& operator=(ContentLevel&& _Other) noexcept = delete;

	float4 GetMousePos(int _CamOrder = 0);

	inline CameraController& GetCamCtrl()
	{
		return MainCamCtrl;
	}

	void AddEvent(const std::string_view& _Event, UINT _ActorCode, std::function<void()> _Callback);
	void RemoveEvent(const std::string_view& _Event, UINT _ActorCode);
	void CallEvent(const std::string_view& _Event);

	void PlayBaseBGM(bool _IsFade = true);
	void StopBaseBGM(bool _IsFade = true);

	void PlayCustomBgm(const std::string_view& _BgmName, bool _IsFade = true, float _FadeTime = 1.0f);
	void StopCustomBgm(float _FadeTime = 1.0f, bool _IsFade = true);

	inline std::shared_ptr<class WorldLightEffect> GetWorldLight()
	{
		return WorldLight;
	}

	std::shared_ptr<PointLightEffect> CreatePointLight(PointLightType _Type);

	void ReleasePointLight(std::shared_ptr<PointLightEffect> _Effect);

	void FadeWorldLightEffect(const float4& _Start, const float4& _End, float _Speed);

protected:
	CameraController MainCamCtrl;
	std::string BgmName = "";

	float BGM_FadeIn_Time = 1.0f;
	float BGM_FadeOut_Time = 1.0f;

	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	GameEngineCamera* MainCam = nullptr;

	std::map<std::string, std::map<UINT, std::function<void(void)>>> EventCallback;

	std::shared_ptr<WorldLightEffect> WorldLight = nullptr;
	std::vector<std::shared_ptr<PointLightEffect>> PointLightEffects;

	GameEngineSoundPlayer BaseBgmPlayer;
	GameEngineSoundPlayer CustomBgmPlayer;

	float4 WorldLightStart = float4::One;
	float4 WorldLightEnd = float4::One;

	float WorldLightProgress = 1.0f;
	float WorldLightSpeed = 1.0f;

};