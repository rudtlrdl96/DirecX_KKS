#pragma once
#include "BaseMonster.h"

class GiantEnt : public BaseMonster
{
public:
	GiantEnt();
	~GiantEnt();

	GiantEnt(const GiantEnt& _Other) = delete;
	GiantEnt(GiantEnt&& _Other) noexcept = delete;
	GiantEnt& operator=(const GiantEnt& _Other) = delete;
	GiantEnt& operator=(GiantEnt&& _Other) noexcept = delete;

protected:
	void DataLoad() override;
	void TextureLoad() override;
	void LoadAnimation() override;
	void AnimationAttackMetaDataLoad() override;
	void SetColData() override;

	void Attack_Enter() override;
	void Attack_Update(float _DeltaTime) override;

private:
	AnimationAttackMetaData AnimColMeta_Tackle;
	std::map<size_t, float> TacklePauseTimes;

	bool IsAttackStempEffect = false;

	bool IsShotAttack = false;
	bool IsShotProjectile = false;
	

};

