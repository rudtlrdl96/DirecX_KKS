#include "PrecompileHeader.h"
#include "ContentCore.h"
#include "SkullData.h"

static void LoadSkull(const SkullData& _Data)
{
	ContentDatabase<SkullData, SkullGrade>::InsertData(_Data);
}

void ContentCore::SkullDataLoad()
{
	LoadSkull({ .Name = "리틀본", .Index = 0, .Grade = SkullGrade::Normal });

	LoadSkull({.Name = "웨어울프", .Index = 1, .Grade = SkullGrade::Normal});
	LoadSkull({.Name = "나이 든 웨어울프", .Index = 100, .Grade = SkullGrade::Rare});
	LoadSkull({.Name = "우두머리 웨어울프", .Index = 200, .Grade = SkullGrade::Unique});
	LoadSkull({.Name = "영원의 웨어울프", .Index = 300, .Grade = SkullGrade::Legendary});

	LoadSkull({ .Name = "미노타우로스", .Index = 101, .Grade = SkullGrade::Rare });
	LoadSkull({ .Name = "미노타우로스 2세", .Index = 201, .Grade = SkullGrade::Unique });
	LoadSkull({ .Name = "미노타우로스 3세", .Index = 301, .Grade = SkullGrade::Legendary });

	LoadSkull({ .Name = "연금술사", .Index = 102, .Grade = SkullGrade::Rare });
	LoadSkull({ .Name = "고위 연금술사", .Index = 202, .Grade = SkullGrade::Unique });
	LoadSkull({ .Name = "검은 연금술사", .Index = 302, .Grade = SkullGrade::Legendary });

	LoadSkull({ .Name = "경비대장", .Index = 203, .Grade = SkullGrade::Unique });


	std::vector<SkullData> NormalDatas;
	ContentDatabase<SkullData, SkullGrade>::CopyGradeDatas(SkullGrade::Normal, NormalDatas);
	std::vector<SkullData> RareDatas;
	ContentDatabase<SkullData, SkullGrade>::CopyGradeDatas(SkullGrade::Rare, RareDatas);
	std::vector<SkullData> UniqueDatas;
	ContentDatabase<SkullData, SkullGrade>::CopyGradeDatas(SkullGrade::Unique, UniqueDatas);
	std::vector<SkullData> LegendaryDatas;
	ContentDatabase<SkullData, SkullGrade>::CopyGradeDatas(SkullGrade::Legendary, LegendaryDatas);

	int a = 0;
}