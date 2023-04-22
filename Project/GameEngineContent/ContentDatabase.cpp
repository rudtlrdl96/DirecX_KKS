#include "PrecompileHeader.h"
#include "ContentDatabase.h"
#include "SkullData.h"
#include "ItemData.h"

// SkullData Static
std::vector<SkullData> ContentDatabase::AllSkullDatas;
std::map<SkullGrade, std::vector<SkullData>> ContentDatabase::GradeSkullDatas;
std::map<std::string, size_t> ContentDatabase::AllSkullDatasIndex;

void ContentDatabase::InsertSkullData(const SkullData& _Data)
{
}

SkullData ContentDatabase::GetSkullData(size_t _Index)
{
	if (_Index >= AllSkullDatas.size())
	{
		MsgAssert("Skull Datas의 인덱스를 초과해 접근하려 했습니다");
	}

	return AllSkullDatas[_Index];
}

SkullData ContentDatabase::GetSkullData(const std::string_view& _Name)
{
	return GetSkullData(GetAllSkullIndex(_Name));
}

size_t ContentDatabase::GetAllSkullIndex(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);
	std::map<std::string, size_t>::iterator FindIter = AllSkullDatasIndex.find(UpperName);

	if (FindIter == AllSkullDatasIndex.end())
	{
		MsgAssert("존재하지 않는 스컬의 인덱스를 참조하려 했습니다");
	}

	return FindIter->second;
}

SkullData ContentDatabase::GetSkullData(SkullGrade _Grade, size_t _Index)
{
	std::vector<SkullData>& RefDatas = GradeSkullDatas[_Grade];

	if (RefDatas.size() >= _Index)
	{
		MsgAssert("Skull Datas의 인덱스를 초과해 접근하려 했습니다");
	}

	return GradeSkullDatas[_Grade][_Index];
}

size_t ContentDatabase::GetGradeSkullIndex(SkullGrade _Grade, const std::string_view& _Name)
{
	std::vector<SkullData>& RefDatas = GradeSkullDatas[_Grade];

	std::string UpperName = GameEngineString::ToUpper(_Name);

	for (size_t i = 0; i < RefDatas.size(); i++)
	{
		if (RefDatas[i].Name == UpperName)
		{
			return RefDatas[i].Index;
		}
	}

	MsgAssert("존재하지 않는 스컬의 인덱스를 참조하려 했습니다");
	return 0;
}

size_t ContentDatabase::GetAllSkullCount()
{
	return AllSkullDatas.size();
}

size_t ContentDatabase::GetGradeSkullCount(SkullGrade _SkullGrade)
{
	return GradeSkullDatas[_SkullGrade].size();
}

// ItemData Static
std::vector<ItemData> ContentDatabase::AllItemDatas;
std::map<ItemGrade, std::vector<ItemData>> ContentDatabase::GradeItemDatas;
std::map<std::string, size_t> ContentDatabase::AllItemDatasIndex;

void ContentDatabase::InsertItemData(const ItemData& _Data)
{
}

ItemData ContentDatabase::GetItemData(size_t _Index)
{
	if (_Index >= AllItemDatas.size())
	{
		MsgAssert("Item Datas의 인덱스를 초과해 접근하려 했습니다");
	}

	return AllItemDatas[_Index];
}

ItemData ContentDatabase::GetItemData(const std::string_view& _Name)
{
	return AllItemDatas[GetAllItemIndex(_Name)];
}

size_t ContentDatabase::GetAllItemIndex(const std::string_view& _Name)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	std::map<std::string, size_t>::iterator FindIter = AllItemDatasIndex.find(UpperName);

	if (FindIter == AllItemDatasIndex.end())
	{
		MsgAssert("존재하지 않는 스컬의 인덱스를 참조하려 했습니다");
	}

	return FindIter->second;
}

ItemData ContentDatabase::GetItemData(ItemGrade _Grade, size_t _Index)
{
	std::vector<ItemData>& ItemDatasRef = GradeItemDatas[_Grade];

	if (_Index >= ItemDatasRef.size())
	{
		MsgAssert("Grade Item Datas의 인덱스를 초과해 접근하려 했습니다");
	}

	return ItemDatasRef[_Index];
}

size_t ContentDatabase::GetGradeItemIndex(ItemGrade _Grade, const std::string_view& _Name)
{
	std::vector<ItemData>& RefDatas = GradeItemDatas[_Grade];

	std::string UpperName = GameEngineString::ToUpper(_Name);

	for (size_t i = 0; i < RefDatas.size(); i++)
	{
		if (RefDatas[i].Name == UpperName)
		{
			return RefDatas[i].Index;
		}
	}

	MsgAssert("존재하지 않는 스컬의 인덱스를 참조하려 했습니다");
	return 0;
}

size_t ContentDatabase::GetAllItemCount()
{
	return AllItemDatas.size();
}

size_t ContentDatabase::GetGradeItemCount(ItemGrade _ItemGrade)
{
	return GradeItemDatas[_ItemGrade].size();
}
