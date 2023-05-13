#include "PrecompileHeader.h"
#include "AttackColToolLevel.h"
#include "AttackCollisionToolGUI.h"
#include "AttackColToolAnimActor.h"
#include "DebugCollisionRender.h"

AttackColToolLevel::AttackColToolLevel()
{
}

AttackColToolLevel::~AttackColToolLevel()
{
}

void AttackColToolLevel::Start()
{
	ContentLevel::Start();

	AttackCollisionToolGUIPtr = GameEngineGUI::FindGUIWindowConvert<AttackCollisionToolGUI>("AttackCollisionToolGUI");

	if (nullptr == AttackCollisionToolGUIPtr)
	{
		MsgAssert_Rtti<AttackColToolLevel>(" - AttackColGui�� �������� �ʾҽ��ϴ�");
		return;
	}

	AnimRenderActor = CreateActor<AttackColToolAnimActor>();
	ColRenderActor = CreateActor<DebugCollisionRender>();
}

void AttackColToolLevel::Update(float _DeltaTime)
{
	ContentLevel::Update(_DeltaTime);
}

void AttackColToolLevel::LevelChangeStart()
{
	if (nullptr == AttackCollisionToolGUIPtr)
	{
		MsgAssert_Rtti<AttackColToolLevel>(" - AttackColGui�� �������� �ʾҽ��ϴ�");
		return;
	}

	AttackCollisionToolGUIPtr->SetRenderer(AnimRenderActor->GetSpriteRender());
	AttackCollisionToolGUIPtr->SetCol(ColRenderActor);
	AttackCollisionToolGUIPtr->On();
}

void AttackColToolLevel::LevelChangeEnd()
{
	if (nullptr == AttackCollisionToolGUIPtr)
	{
		MsgAssert_Rtti<AttackColToolLevel>(" - AttackColGui�� �������� �ʾҽ��ϴ�");
		return;
	}

	AttackCollisionToolGUIPtr->Off();
}