#include "PrecompileHeader.h"
#include "ColEnterCheck.h"

ColEnterCheck::ColEnterCheck()
{
}

ColEnterCheck::~ColEnterCheck()
{
}

void ColEnterCheck::AddCollision(std::vector<std::shared_ptr<GameEngineCollision>>& _Cols, const AttackColMetaData& _Data)
{
	for (size_t i = 0; i < _Cols.size(); i++)
	{
		std::shared_ptr<BaseContentActor> CastPtr = _Cols[i]->GetActor()->DynamicThis<BaseContentActor>();

		if (nullptr == CastPtr)
		{
			MsgAssert_Rtti<ColEnterCheck>(" - BaseContentActor를 상속받은 클래스만 프레임 체크를 할 수 있습니다.");
			continue;
		}

		UINT ColsCode = CastPtr->GetActorCode();

		std::shared_ptr<BaseContentActor> FindActor = AllCols[ColsCode];

		if (nullptr == FindActor)
		{
			if (nullptr != EnterEvent)
			{
				EnterEvent(CastPtr, _Data);
			}

			AllCols[ColsCode] = CastPtr;
		}
		else
		{
			if (true == FindActor->IsDeath())
			{
				AllCols[ColsCode] = nullptr;
			}
		}
	}
}
