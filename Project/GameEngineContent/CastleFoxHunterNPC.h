#pragma once
#include "BaseNPC.h"
#include <GameEngineCore/GameEngineUIRenderer.h>

class CastleFoxHunterNPC : public BaseNPC
{
public:
	CastleFoxHunterNPC();
	~CastleFoxHunterNPC();

	CastleFoxHunterNPC(const CastleFoxHunterNPC& _Other) = delete;
	CastleFoxHunterNPC(CastleFoxHunterNPC&& _Other) noexcept = delete;
	CastleFoxHunterNPC& operator=(const CastleFoxHunterNPC& _Other) = delete;
	CastleFoxHunterNPC& operator=(CastleFoxHunterNPC&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void SpriteLoad() override;
	void Destroy() override;

private:
	std::shared_ptr<class FieldNoteActor> NoteActor = nullptr;
	std::shared_ptr<class NPC_TalkBox> NpcTalkBox = nullptr;
	std::shared_ptr<GameEngineCollision> TalkEventCol = nullptr;
	std::shared_ptr<GameEngineUIRenderer> NpcImageRender = nullptr;
	std::shared_ptr<GameEngineComponent> BubblePivot = nullptr;

	bool IsGiveItem = true;

	std::vector<std::function<void()>> TalkScripts;
	std::vector<std::function<void()>> GiveHeadScritps;
	std::vector<std::string> BubbleScripts;

	int TalkScriptNumber = -1;
	int GiveHeadScriptNumber = -1;
	int BubbleScriptNumber = -1;

	float BubbleTalkTime = -13.0f;

	void CreateBubbleScript();
	void PlayBubble();

	void CreateTalkScript();
	void PlayNextScript();
	void TalkEndCallback();

	void CreateGiveHeadScript();
	void PlayNextGiveHeadScript();
	void GiveHeadEndCallback();
};