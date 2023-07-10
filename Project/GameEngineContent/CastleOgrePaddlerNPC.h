#pragma once
#include "BaseNPC.h"

class CastleOgrePaddlerNPC : public BaseNPC
{
public:
	CastleOgrePaddlerNPC();
	~CastleOgrePaddlerNPC();

	CastleOgrePaddlerNPC(const CastleOgrePaddlerNPC& _Other) = delete;
	CastleOgrePaddlerNPC(CastleOgrePaddlerNPC&& _Other) noexcept = delete;
	CastleOgrePaddlerNPC& operator=(const CastleOgrePaddlerNPC& _Other) = delete;
	CastleOgrePaddlerNPC& operator=(CastleOgrePaddlerNPC&& _Other) noexcept = delete;

	void CallUseEvent() override;

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
	std::vector<std::function<void()>> GiveItemScritps;
	std::vector<std::string> BubbleScripts;

	int TalkScriptNumber = -1;
	int GiveItemScriptNumber = -1;
	int BubbleScriptNumber = -1;

	float BubbleTalkTime = -20.0f;

	void CreateBubbleScript();
	void PlayBubble();

	void CreateTalkScript();
	void PlayNextTalkScript();
	void TalkEndCallback();

	void CreateGiveItemScript();
	void PlayNextGiveItemScript();
	void GiveItemEndCallback();
};

