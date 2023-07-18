#pragma once
#include "VeteranHero_HealthBar.h"

class Mongal_HealthBar : public VeteranHero_HealthBar
{
public:
	Mongal_HealthBar();
	~Mongal_HealthBar();

	Mongal_HealthBar(const Mongal_HealthBar& _Other) = delete;
	Mongal_HealthBar(Mongal_HealthBar&& _Other) noexcept = delete;
	Mongal_HealthBar& operator=(const Mongal_HealthBar& _Other) = delete;
	Mongal_HealthBar& operator=(Mongal_HealthBar&& _Other) noexcept = delete;

protected:
	void Start() override;
	
private:


};

