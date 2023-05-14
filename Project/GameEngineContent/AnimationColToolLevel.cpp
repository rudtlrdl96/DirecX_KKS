#include "PrecompileHeader.h"
#include "AnimationColToolLevel.h"
#include "AnimationCollisionToolGUI.h"
#include "AttackColToolAnimActor.h"
#include "DebugCollisionRender.h"

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
	ColRenderActor = CreateActor<DebugCollisionRender>();
}

void AnimationColToolLevel::Update(float _DeltaTime)
{
	ContentLevel::Update(_DeltaTime);
}

void AnimationColToolLevel::LevelChangeStart()
{
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
	if (nullptr == AnimationCollisionGUIPtr)
	{
		MsgAssert_Rtti<AnimationColToolLevel>(" - AttackColGui�� �������� �ʾҽ��ϴ�");
		return;
	}

	AnimationCollisionGUIPtr->Off();
}