#include "PrecompileHeader.h"
#include "BaseContentActor.h"

static UINT NextCode = 1;

BaseContentActor::BaseContentActor() :
	Code(++NextCode)
{
}

BaseContentActor::~BaseContentActor()
{
}
