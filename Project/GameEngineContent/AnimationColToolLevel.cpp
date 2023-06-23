#include "PrecompileHeader.h"
#include "AnimationColToolLevel.h"
#include "AnimationCollisionToolGUI.h"
#include "AttackColToolAnimActor.h"
#include "AttackColRender.h"

AnimationColToolLevel::AnimationColToolLevel()
{
}

AnimationColToolLevel::~AnimationColToolLevel()
{
}

void AnimationColToolLevel::Start()
{
	ContentLevel::Start();

	AnimationCollisionGUIPtr = GameEngineGUI::FindGUIWindowConvert<AnimationCollisionToolGUI>("AnimationCollisionToolGUI");

	if (nullptr == AnimationCollisionGUIPtr)
	{
		MsgAssert_Rtti<AnimationColToolLevel>(" - AttackColGui�� �������� �ʾҽ��ϴ�");
		return;
	}

	AnimRenderActor = CreateActor<AttackColToolAnimActor>();
	ColRenderActor = CreateActor<AttackColRender>();
}

void AnimationColToolLevel::Update(float _DeltaTime)
{
	ContentLevel::Update(_DeltaTime);
}

void AnimationColToolLevel::LevelChangeStart()
{
	ContentLevel::LevelChangeStart();

	if (nullptr == AnimationCollisionGUIPtr)
	{
		MsgAssert_Rtti<AnimationColToolLevel>(" - AttackColGui�� �������� �ʾҽ��ϴ�");
		return;
	}

	AnimationCollisionGUIPtr->SetRenderer(AnimRenderActor->GetSpriteRender());
	AnimationCollisionGUIPtr->SetCol(ColRenderActor);
	AnimationCollisionGUIPtr->On();
}

void AnimationColToolLevel::LevelChangeEnd()
{
	ContentLevel::LevelChangeEnd();

	if (nullptr == AnimationCollisionGUIPtr)
	{
		MsgAssert_Rtti<AnimationColToolLevel>(" - AttackColGui�� �������� �ʾҽ��ϴ�");
		return;
	}

	AnimationCollisionGUIPtr->Off();
}