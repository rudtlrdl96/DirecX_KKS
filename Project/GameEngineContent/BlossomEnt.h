#pragma once
#include "BaseMonster.h"

class BlossomEnt : public BaseMonster
{
public:
	BlossomEnt();
	~BlossomEnt();

	BlossomEnt(const BlossomEnt& _Other) = delete;
	BlossomEnt(BlossomEnt&& _Other) noexcept = delete;
	BlossomEnt& operator=(const BlossomEnt& _Other) = delete;
	BlossomEnt& operator=(BlossomEnt&& _Other) noexcept = delete;

protected:
	void DataLoad() override;
	void TextureLoad() override;
	void LoadAnimation() override;
	void AnimationAttackMetaDataLoad() override;
	void SetColData() override;
	void DeathPartLoad() override;

	void Attack_Enter() override;
	void Attack_Update(float _DeltaTime) override;
	void Attack_End() override;

private:
	bool IsAttackStart = false;

};

