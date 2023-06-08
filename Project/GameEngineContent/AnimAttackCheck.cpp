#include "PrecompileHeader.h"
#include "AnimAttackCheck.h"

AnimAttackCheck::AnimAttackCheck()
{
	Orders.reserve(4);
}

AnimAttackCheck::~AnimAttackCheck()
{
}

bool AnimAttackCheck::Update()
{
	if (nullptr == Render)
	{
		return false;
	}
	else if(true == Render->IsDeath())
	{
		Render = nullptr;
		return false;
	}

	if (true == Render->IsAnimationEnd())
	{
		return false;
	}

	UINT CurAnimFrame = static_cast<UINT>(Render->GetCurrentFrame());

	if (CurAnimFrame != Frame)
	{
		ColCheck.FrameReset();
		Frame = CurAnimFrame;
	}

	const AttackColMetaData& Data = ColData.GetAttackMetaData(Frame);


	if (0 < Data.ColMetaDatas.size())
	{
		if (nullptr == Col)
		{
			MsgAssert_Rtti<AnimAttackCheck>(" - 콜리전이 세팅되지 않았습니다");
			return false;
		}

		GameEngineTransform* ColTrans = Col->GetTransform();

		for (size_t i = 0; i < Data.ColMetaDatas.size(); i++)
		{
			ColTrans->SetLocalPosition(Data.ColMetaDatas[i].LocalCenter);
			ColTrans->SetWorldScale(Data.ColMetaDatas[i].LocalSize);

			std::vector<std::shared_ptr<GameEngineCollision>> Cols;

			for (size_t n = 0; n < Orders.size(); n++)
			{
				Cols.clear();

				Col->CollisionAll(
					Orders[n],
					Cols,
					ColType::AABBBOX2D,
					ColType::AABBBOX2D
				);

				ColCheck.AddCollision(Cols, Data);
			}	
		}	
	}


	return true;
}
