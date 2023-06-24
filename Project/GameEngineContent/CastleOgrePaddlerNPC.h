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

	bool IsGiveItem = true;

	std::vector<std::function<void()>> TalkScripts;

	int ScriptNumber = -1;

	void CreateTalkScript();
	void PlayNextScript();
	void TalkEndCallback();
};

