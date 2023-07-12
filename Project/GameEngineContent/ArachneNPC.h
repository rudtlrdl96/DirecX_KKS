#pragma once
#include "BaseNPC.h"

class ArachneNPC : public BaseNPC
{
public:
	ArachneNPC();
	~ArachneNPC();

	ArachneNPC(const ArachneNPC& _Other) = delete;
	ArachneNPC(ArachneNPC&& _Other) noexcept = delete;
	ArachneNPC& operator=(const ArachneNPC& _Other) = delete;
	ArachneNPC& operator=(ArachneNPC&& _Other) noexcept = delete;

	void CallUseEvent() override;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void SpriteLoad() override;

private:
	std::shared_ptr<class FieldNoteActor> NoteActor = nullptr;
	std::shared_ptr<class NPC_TalkBox> NpcTalkBox = nullptr;
	std::shared_ptr<GameEngineCollision> TalkEventCol = nullptr;

	std::vector<std::function<void()>> TalkScripts;
	std::vector<std::string> BubbleScripts;

	std::shared_ptr<GameEngineComponent> BubblePivot = nullptr;

	int TalkScriptNumber = -1;
	int BubbleScriptNumber = -1;

	bool IsFirstTalk = true;

	float BubbleTalkTime = -10.0f;

	void CreateBubbleScript();
	void PlayBubble();

	void CreateTalkScript();
	void PlayNextScript();
	void TalkEndCallback();

	void PlayFirstTalkScript();
};

