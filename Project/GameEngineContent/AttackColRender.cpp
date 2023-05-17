#include "PrecompileHeader.h"
#include "AttackColRender.h"

AttackColRender::AttackColRender()
{
	Renders.reserve(8);
}

AttackColRender::~AttackColRender()
{
}

void AttackColRender::DrawColData(const AttackColMetaData& _Data)
{
	size_t ColCount = _Data.ColMetaDatas.size();

	for (size_t i = 0; i < Renders.size(); i++)
	{
		Renders[i]->Off();
	}

	if (Renders.size() < ColCount)
	{
		Renders.resize(ColCount);
	}

	for (size_t i = 0; i < ColCount; i++)
	{
		if (nullptr == Renders[i])
		{
			Renders[i] = CreateComponent<GameEngineSpriteRenderer>();
			Renders[i]->GetTransform()->SetParent(GetTransform());
			Renders[i]->SetTexture("BoxCol.png");
		}

		Renders[i]->On();

		GameEngineTransform* RenderTrans = Renders[i]->GetTransform();

		RenderTrans->SetLocalPosition(_Data.ColMetaDatas[i].LocalCenter);
		RenderTrans->SetLocalScale(_Data.ColMetaDatas[i].LocalSize);
	}
}