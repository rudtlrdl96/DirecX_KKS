#pragma once
#include "BaseNPC.h"

class ShopChef : public BaseNPC
{
public:
	ShopChef();
	~ShopChef();

	ShopChef(const ShopChef& _Other) = delete;
	ShopChef(ShopChef&& _Other) noexcept = delete;
	ShopChef& operator=(const ShopChef& _Other) = delete;
	ShopChef& operator=(ShopChef&& _Other) noexcept = delete;

	void CallUseEvent() override;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void SpriteLoad() override;

private:
	std::shared_ptr<ContentMinimapRender> MinimapImageRender = nullptr;

	std::shared_ptr<class FieldNoteActor> NoteActor = nullptr;
	std::shared_ptr<class NPC_TalkBox> NpcTalkBox = nullptr;
	std::shared_ptr<GameEngineCollision> TalkEventCol = nullptr;

	std::vector<std::function<void()>> TalkScripts;

	int TalkScriptNumber = -1;
	int BubbleScriptNumber = -1;

	float BubbleTalkTime = -13.0f;

	void CreateTalkScript();
	void PlayNextScript();
	void TalkEndCallback();
};

