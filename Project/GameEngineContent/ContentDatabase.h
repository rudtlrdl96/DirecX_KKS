#pragma once

template<typename DataClass, typename GradeEnum>
class ContentDatabase
{
public:
	static void InsertData(const DataClass& _Data)
	{
		{
			typename std::map<size_t, DataClass>::iterator FindIter = AllDatas.find(_Data.Index);
			typename std::map<size_t, DataClass>::iterator EndIter = AllDatas.end();

			if (FindIter != EndIter)
			{
				ContentDebug::RttiAssert<ContentDatabase<DataClass, GradeEnum>>(" - 중복된 인덱스의 데이터를 입력하려 했습니다 : " + std::to_string(_Data.Index));
				return;
			}		
		}

		{
			std::map<std::string, size_t>::iterator FindIter = AllDatasIndex.find(_Data.Name);
			std::map<std::string, size_t>::iterator EndIter = AllDatasIndex.end();

			if (FindIter != EndIter)
			{
				ContentDebug::RttiAssert<ContentDatabase<DataClass, GradeEnum>>(" - 중복된 이름의 데이터를 입력하려 했습니다 : " + _Data.Name);
				return;
			}		
		}

		AllDatas.insert(std::make_pair(_Data.Index, _Data));
		AllDatasIndex.insert(std::make_pair(_Data.Name, _Data.Index));
		GradeDatas[_Data.Grade].push_back(_Data);
	}

	static const DataClass& GetData(size_t _Index)
	{
		typename std::map<size_t, DataClass>::iterator FindIter = AllDatas.find(_Index);
		typename std::map<size_t, DataClass>::iterator EndIter = AllDatas.end();

		if (FindIter == EndIter)
		{
			ContentDebug::RttiAssert<ContentDatabase<DataClass, GradeEnum>>(" - 존재하지 않는 데이터를 참조하려 했습니다 : " + std::to_string(_Index));
			//return DataClass();
		}

		return FindIter->second;
	}

	static const DataClass& GetData(const std::string_view& _Name)
	{
		return GetData(GetAllIndex(_Name));
	}

	static size_t GetAllIndex(const std::string_view& _Name)
	{
		std::map<std::string, size_t>::iterator FindIter = AllDatasIndex.find(_Name.data());

		if (FindIter == AllDatasIndex.end())
		{
			ContentDebug::RttiAssert<ContentDatabase<DataClass, GradeEnum>>(" - 존재하지 않는 데이터를 참조하려 했습니다 : " + std::string(_Name.data()));
			return 0;
		}

		return FindIter->second;
	}

	static const DataClass& GetData(GradeEnum _Grade, size_t _Index)
	{
		std::vector<DataClass>& RefDatas = GradeDatas[_Grade];

		if (RefDatas.size() >= _Index)
		{
			const type_info& EnumGradeRtti = typeid(GradeEnum);

			ContentDebug::RttiAssert<ContentDatabase<DataClass, GradeEnum>>(" - 존재하지 않는 등급의 데이터를 참조하려 했습니다 : " + std::string(EnumGradeRtti.name()) + std::string(", ") + std::to_string(_Index));
			return DataClass();
		}

		return GradeDatas[_Grade][_Index];
	}
	
	static size_t GetAllCount()
	{
		return AllDatas.size();
	}

	static size_t GetGradeCount(GradeEnum _Grade)
	{
		return GradeDatas[_Grade].size();
	}

	static void CopyGradeDatas(GradeEnum _Grade, std::vector<DataClass>& _CopyBuffer)
	{
		const std::vector<DataClass>& CopyRef = GradeDatas[_Grade];

		_CopyBuffer.clear();
		_CopyBuffer.resize(CopyRef.size());

		for (size_t i = 0; i < CopyRef.size(); i++)
		{
			_CopyBuffer[i] = CopyRef[i];
		}
	}
private:
	static std::map<size_t, DataClass> AllDatas;
	static std::map<GradeEnum, std::vector<DataClass>> GradeDatas;

	static std::map<std::string, size_t> AllDatasIndex;
private:
	ContentDatabase() {}
	~ContentDatabase() {}
	
	ContentDatabase(const ContentDatabase& _Other) = delete;
	ContentDatabase(ContentDatabase&& _Other) noexcept = delete;
	ContentDatabase& operator=(const ContentDatabase& _Other) = delete;
	ContentDatabase& operator=(ContentDatabase&& _Other) noexcept = delete;
};

template<typename DataClass, typename GradeEnum>
std::map<size_t, DataClass> ContentDatabase<DataClass, GradeEnum>::AllDatas;

template<typename DataClass, typename GradeEnum>
std::map<GradeEnum, std::vector<DataClass>> ContentDatabase<DataClass, GradeEnum>::GradeDatas;

template<typename DataClass, typename GradeEnum>
std::map<std::string, size_t> ContentDatabase<DataClass, GradeEnum>::AllDatasIndex;