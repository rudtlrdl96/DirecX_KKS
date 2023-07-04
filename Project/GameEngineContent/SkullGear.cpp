#include "PrecompileHeader.h"
#include "SkullGear.h"

SkullGear::SkullGear()
{
}

SkullGear::~SkullGear()
{
}

void SkullGear::Start()
{
	BaseGear::Start();

	ColEnterCallback = [this]()
	{
		// SkullPopupOn
	};

	ColExitCallback = [this]()
	{
		// SkullPopupOff
	};
}
