#pragma once
#include "BaseContentActor.h"
#include "BattleStage.h"
#include "MultiBackground.h"

class BattleArea : public BaseContentActor
{
public:
	BattleArea();
	~BattleArea();

	BattleArea(const BattleArea& _Other) = delete;
	BattleArea(BattleArea&& _Other) noexcept = delete;
	BattleArea& operator=(const BattleArea& _Other) = delete;
	BattleArea& operator=(BattleArea&& _Other) noexcept = delete;

	void LoadMap(GameEngineDirectory& _Directory, const std::string_view& _FileName);
	void ChangeMap(const std::string_view _Name, const float4& _Pivot = float4::Zero);

	void LoadBackground(GameEngineDirectory& _Directory, const std::string_view& _FileName);
	void ChangeBackground(const std::string_view _Name, const float4& _Pivot = float4::Zero);

	inline void UpdateBackground(float _DeltaTime, const float4& _CenterPos)
	{
		CurBackground->UpdateTargetPos(_DeltaTime, _CenterPos);
	}

	inline float4 GetSpawnPoint() const
	{
		return CurStage->GetSpawnPoint();
	}

	void SetCameraLock(class CameraController& _CameraCtrl);

	void SetParentToBackground(const std::string_view& _BackgroundName, size_t _Index, GameEngineTransform * _Actor);

protected:

private:
	std::map<std::string, std::shared_ptr<MultiBackground>> BattleBackgroundDatas;
	std::map<std::string, std::shared_ptr<BattleStage>> BattleStageDatas;

	std::shared_ptr<BattleStage> CurStage = nullptr;
	std::shared_ptr<MultiBackground> CurBackground = nullptr;
};