#include "PrecompileHeader.h"
#include "Collision2D.h"

Collision2D::Collision2D()
{
	ColTypes.reserve(8);
}

Collision2D::~Collision2D()
{
}

void Collision2D::AddColType(int _ColType, bool _IsCol/* = true*/)
{
	for (size_t i = 0; i < ColTypes.size(); i++)
	{
		if (ColTypes[i].first == _ColType)
		{
			MsgAssert_Rtti<Collision2D>(" - �ߺ��� �浹 Ÿ���� �߰��Ϸ� �߽��ϴ�.");
			return;
		}
	}

	ColTypes.push_back(std::make_pair(_ColType, _IsCol));
}

void Collision2D::Update(float _DeltaTime)
{

}
