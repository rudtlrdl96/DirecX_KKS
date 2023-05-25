#pragma once
#include "BaseMonster.h"

class CarleonManAtArms : public BaseMonster
{
public:
	CarleonManAtArms();
	~CarleonManAtArms();

	CarleonManAtArms(const CarleonManAtArms& _Other) = delete;
	CarleonManAtArms(CarleonManAtArms&& _Other) noexcept = delete;
	CarleonManAtArms& operator=(const CarleonManAtArms& _Other) = delete;
	CarleonManAtArms& operator=(CarleonManAtArms&& _Other) noexcept = delete;
		
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
	AnimationAttackMetaData AnimColMeta_Tackle;
	std::map<size_t, float> TacklePauseTimes;

	bool IsAttackStempEffect = false;
	bool IsTackleAttack = false;
	bool IsTackleEffect = false;
};

