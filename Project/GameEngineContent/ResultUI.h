#pragma once
#include "BaseContentActor.h"
#include "QuintessenceData.h"

class ResultUI : public BaseContentActor
{
public:
	ResultUI();
	~ResultUI();

	ResultUI(const ResultUI& _Other) = delete;
	ResultUI(ResultUI&& _Other) noexcept = delete;
	ResultUI& operator=(const ResultUI& _Other) = delete;
	ResultUI& operator=(ResultUI&& _Other) noexcept = delete;

	void ResultUIOn();
	void ResultUIOff();

	inline void SetBattleLevel(BattleLevel* _Ptr)
	{
		Level = _Ptr;
	}

	inline float GetMoveProgress()
	{
		return MoveProgress;
	}

	void Reset();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	
private:
	class BattleLevel* Level = nullptr;
	std::shared_ptr<GameEngineUIRenderer> UIRender = nullptr;

	std::vector<std::shared_ptr<GameEngineUIRenderer>> GearRenders;

	std::shared_ptr<ContentUIFontRenderer> PlayTimeNameFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> PlayTimeValueFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> DeathCountNameFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> DeathCountValueFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> KillCountNameFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> KillCountValueFont = nullptr;

	std::shared_ptr<ContentUIFontRenderer> GetManaStoneNameFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> GetManaStoneValueFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> GetGoldNameFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> GetGoldValueFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> GetBoneNameFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> GetBoneValueFont = nullptr;

	std::shared_ptr<ContentUIFontRenderer> TotalDamageNameFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> TotalDamageValueFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> MaxDamageNameFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> MaxDamageValueFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> HitDamageNameFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> HitDamageValueFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> HealNameFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> HealValueFont = nullptr;

	std::shared_ptr<ContentUIFontRenderer> GetSkullCountNameFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> GetSkullCountValueFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> GetItemCountNameFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> GetItemCountValueFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> GetQuintessenceNameFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> GetQuintessenceValueFont = nullptr;

	std::shared_ptr<ContentUIFontRenderer> StageNameFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> DeathInfoFont = nullptr;
	std::shared_ptr<ContentUIFontRenderer> KeyInfoFont = nullptr;

	std::shared_ptr<ContentUIFontRenderer> ResultTitle0 = nullptr;
	std::shared_ptr<ContentUIFontRenderer> ResultTitle1 = nullptr;

	float MoveProgress = 0.0f;

	float4 StartPos = float4::Zero;
	float4 EndPos = float4::Zero;

	void CreateLeftFont(std::shared_ptr<ContentUIFontRenderer>& _Font, const float4& _WorldPos, const std::string_view& _Name = "999999999");
};

