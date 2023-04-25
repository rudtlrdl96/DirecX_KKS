#include "PrecompileHeader.h"
#include "UILevel.h"

UILevel::UILevel()
{
}

UILevel::~UILevel()
{
}

void UILevel::Start()
{
	ContentLevel::Start();
}

void UILevel::Update(float _DeltaTime)
{
	ContentLevel::Update(_DeltaTime);
}
