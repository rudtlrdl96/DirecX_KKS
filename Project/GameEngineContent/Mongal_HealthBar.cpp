#include "PrecompileHeader.h"
#include "Mongal_HealthBar.h"

Mongal_HealthBar::Mongal_HealthBar()
{
}

Mongal_HealthBar::~Mongal_HealthBar()
{
}

void Mongal_HealthBar::Start()
{
	VeteranHero_HealthBar::Start();

	NameFontRender->SetText("몬갈");
	SubFontRender->SetText("오우거");
}
