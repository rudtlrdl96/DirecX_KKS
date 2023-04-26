#include "PrecompileHeader.h"
#include "BoneSkull.h"

BoneSkull::BoneSkull()
{
}

BoneSkull::~BoneSkull()
{
}

void BoneSkull::Start()
{
	FSMInit<BoneSkull>(SkullFsm, Shared_This_dynamic_pointer<BoneSkull>());
}

void BoneSkull::Update(float _DeltaTime)
{
	SkullFsm.Update(_DeltaTime);
}