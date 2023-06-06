#pragma once
#include "BaseNPC.h"

class ChiefGuardNPC : public BaseNPC
{
public:
	ChiefGuardNPC();
	~ChiefGuardNPC();

	ChiefGuardNPC(const ChiefGuardNPC& _Other) = delete;
	ChiefGuardNPC(ChiefGuardNPC&& _Other) noexcept = delete;
	ChiefGuardNPC& operator=(const ChiefGuardNPC& _Other) = delete;
	ChiefGuardNPC& operator=(ChiefGuardNPC&& _Other) noexcept = delete;

protected:
	void Start() override;
	
private:
	std::shared_ptr<ContentSpriteRenderer> HeadRender = nullptr;
	ColorBuffer Buffer;


	void SpriteLoad() override;

};

