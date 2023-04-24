#include "PrecompileHeader.h"
#include "BaseContentActor.h"

static UINT NextCode = 0;

BaseContentActor::BaseContentActor() :
	Code(++NextCode)
{
}

BaseContentActor::~BaseContentActor()
{
}
