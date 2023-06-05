#pragma once
#include "ContentLevel.h"
#include "BattleArea.h"

class BattleLevel : public ContentLevel
{
	friend class BaseDoor;
private:
	class LoadStageInfo
	{
	public:
		std::string LoadMapName = "";
		std::string LoadBackgroundName = "";
		float4 BackgroundPivot = float4::Zero;
	};
public:
	BattleLevel();
	~BattleLevel();

	BattleLevel(const BattleLevel& _Other) = delete;
	BattleLevel(BattleLevel&& _Other) noexcept = delete;
	BattleLevel& operator=(const BattleLevel& _Other) = delete;
	BattleLevel& operator=(BattleLevel&& _Other) noexcept = delete;

protected:
	std::vector<LoadStageInfo> StageNameInfos;
	UINT CurStageIndex = 0;

	std::string MainStageName = "";
	std::string MainBackgroundName = "";
	float4 BackgroundPivot = float4::Zero;

	std::shared_ptr<class FadeActor> FadeActorPtr = nullptr;
	std::shared_ptr<class FadeActor> FadeActorPtr_White = nullptr;
	std::shared_ptr<class StoryFade> StoryFadePtr = nullptr;
	std::shared_ptr<class TalkBox> TalkBoxPtr = nullptr;

	std::shared_ptr<class Player> MainPlayer = nullptr;
	std::shared_ptr<class BattleArea> BattleAreaPtr = nullptr;

	std::shared_ptr<class GameEngineActorGUI> ActorGUIPtr = nullptr;

	bool IsLevelMove = false;

	void Start() override;
	void Update(float _DeltaTime) override;

	void SetPlayerPos(const float4& _Pos);

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

	virtual void ChangeStage();
	void MovePrevStage(bool _ForceMove = false);
	void MoveNextStage(bool _ForceMove = false);

	void MoveLevel(const std::string_view& _Level);
	virtual void AreaClear() {}

private:

};

