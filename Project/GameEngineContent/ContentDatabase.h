#pragma once


class ContentDatabase
{
public:
	// Skull Data
	// AllSkullDatas 기준 함수
	static class SkullData GetSkullData(size_t _Index);
	static class SkullData GetSkullData(const std::string_view& _Name);
	static size_t GetAllSkullIndex(const std::string_view& _Name);

	// GradeSkullDatas 기준 함수
	static class SkullData GetSkullData(SkullGrade _Grade, size_t _Index);
	static size_t GetGradeSkullIndex(SkullGrade _Grade, const std::string_view& _Name);

	static size_t GetAllSkullCount();
	static size_t GetGradeSkullCount(SkullGrade _SkullGrade);
	
	// Item Data
	// AllItemDatas 기준 함수
	static class ItemData GetItemData(size_t _Index);
	static class ItemData GetItemData(const std::string_view& _Name);
	static size_t GetAllItemIndex(const std::string_view& _Name);

	// GradeItemDatas 기준 함수
	static class ItemData GetItemData(ItemGrade _Grade, size_t _Index);
	static size_t GetGradeItemIndex(ItemGrade _Grade, const std::string_view& _Name);

	static size_t GetAllItemCount();
	static size_t GetGradeItemCount(ItemGrade _ItemGrade);

private:
	// Skull Data
	static std::vector<class SkullData> AllSkullDatas;
	static std::map<SkullGrade, std::vector<class SkullData>> GradeSkullDatas;

	static std::map<std::string, size_t> AllSkullDatasIndex;

	// Item Data
	static std::vector<class ItemData> AllItemDatas;
	static std::map<ItemGrade, std::vector<ItemData>> GradeItemDatas;

	static std::map<std::string, size_t> AllItemDatasIndex;

private:
	ContentDatabase() {}
	~ContentDatabase() {}

	ContentDatabase(const ContentDatabase& _Other) = delete;
	ContentDatabase(ContentDatabase&& _Other) noexcept = delete;
	ContentDatabase& operator=(const ContentDatabase& _Other) = delete;
	ContentDatabase& operator=(ContentDatabase&& _Other) noexcept = delete;
};

