#pragma once
#include "BaseNPC.h"

class SkeleTong : public BaseNPC
{
public:
	SkeleTong();
	~SkeleTong();

	SkeleTong(const SkeleTong& _Other) = delete;
	SkeleTong(SkeleTong&& _Other) noexcept = delete;
	SkeleTong& operator=(const SkeleTong& _Other) = delete;
	SkeleTong& operator=(SkeleTong&& _Other) noexcept = delete;

protected:
	void Start() override;
	
private:
	void SpriteLoad() override;

};

