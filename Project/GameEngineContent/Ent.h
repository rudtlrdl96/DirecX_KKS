#pragma once
#include "BaseMonster.h"

class Ent : public BaseMonster
{
public:
	Ent();
	~Ent();

	Ent(const Ent& _Other) = delete;
	Ent(Ent&& _Other) noexcept = delete;
	Ent& operator=(const Ent& _Other) = delete;
	Ent& operator=(Ent&& _Other) noexcept = delete;

protected:
	void DataLoad() override;
	void TextureLoad() override;
	void LoadAnimation() override;
	void AnimationAttackMetaDataLoad() override;
	void SetColData() override;
	void DeathPartLoad() override;

	void Attack_Enter() override;
	void Attack_Update(float _DeltaTime) override;

private:
	bool IsAttackMove = false;
};

