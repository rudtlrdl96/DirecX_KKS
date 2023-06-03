#pragma once
#include "NormalMonster.h"

class Mongal : public NormalMonster
{
public:
	Mongal();
	~Mongal();

	Mongal(const Mongal& _Other) = delete;
	Mongal(Mongal&& _Other) noexcept = delete;
	Mongal& operator=(const Mongal& _Other) = delete;
	Mongal& operator=(Mongal&& _Other) noexcept = delete;

protected:
	void DataLoad() override;
	void TextureLoad() override;
	void LoadAnimation() override;
	void AnimationAttackMetaDataLoad() override;
	void SetColData() override;
	void DeathPartLoad() override;
private:

	void MonsterDeath() override;

};

