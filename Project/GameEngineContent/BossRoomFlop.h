#pragma once
#include "BaseContentActor.h"

class BossRoomFlop : public BaseContentActor
{
public:
	BossRoomFlop();
	~BossRoomFlop();

	BossRoomFlop(const BossRoomFlop& _Other) = delete;
	BossRoomFlop(BossRoomFlop&& _Other) noexcept = delete;
	BossRoomFlop& operator=(const BossRoomFlop& _Other) = delete;
	BossRoomFlop& operator=(BossRoomFlop&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	std::shared_ptr<ContentSpriteRenderer> Render = nullptr;
	ColorBuffer Buffer;

};

