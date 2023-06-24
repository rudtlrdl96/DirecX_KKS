#pragma once
#include "BaseNPC.h"

class CastleWitchNPC : public BaseNPC
{
public:
	CastleWitchNPC();
	~CastleWitchNPC();

	CastleWitchNPC(const CastleWitchNPC& _Other) = delete;
	CastleWitchNPC(CastleWitchNPC&& _Other) noexcept = delete;
	CastleWitchNPC& operator=(const CastleWitchNPC& _Other) = delete;
	CastleWitchNPC& operator=(CastleWitchNPC&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void SpriteLoad() override;

private:
	std::shared_ptr<class FieldNoteActor> NoteActor = nullptr;
	std::shared_ptr<class NPC_TalkBox> NpcTalkBox = nullptr;
	std::shared_ptr<GameEngineCollision> TalkEventCol = nullptr;
	std::shared_ptr<GameEngineUIRenderer> NpcImageRender = nullptr;

	std::vector<std::function<void()>> TalkScripts;

	int ScriptNumber = -1;

	void CreateTalkScript();
	void PlayNextScript();
	void TalkEndCallback();
};

