#pragma once
#include "BaseMonster.h"

class CarleonRecruit : public BaseMonster
{
public:
	CarleonRecruit();
	~CarleonRecruit();

	CarleonRecruit(const CarleonRecruit& _Other) = delete;
	CarleonRecruit(CarleonRecruit&& _Other) noexcept = delete;
	CarleonRecruit& operator=(const CarleonRecruit& _Other) = delete;
	CarleonRecruit& operator=(CarleonRecruit&& _Other) noexcept = delete;

protected:
	void DataLoad() override;
	void TextureLoad() override;
	void LoadAnimation() override;
	void AnimationAttackMetaDataLoad() override;
	void SetColData() override;

	void Attack_Enter() override;
	void Attack_Update(float _DeltaTime) override;

private:
	bool IsAttackMove = false;

};

