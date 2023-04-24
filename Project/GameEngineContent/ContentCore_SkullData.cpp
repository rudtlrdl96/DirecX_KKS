#include "PrecompileHeader.h"
#include "ContentCore.h"
#include "SkullData.h"

static void LoadSkull(const SkullData& _Data)
{
	ContentDatabase<SkullData, SkullGrade>::InsertData(_Data);
}

void ContentCore::SkullDataLoad()
{
	LoadSkull({ .Name = "��Ʋ��", .Index = 0, .Grade = SkullGrade::Normal });

	LoadSkull({.Name = "�������", .Index = 1, .Grade = SkullGrade::Normal});
	LoadSkull({.Name = "���� �� �������", .Index = 100, .Grade = SkullGrade::Rare});
	LoadSkull({.Name = "��θӸ� �������", .Index = 200, .Grade = SkullGrade::Unique});
	LoadSkull({.Name = "������ �������", .Index = 300, .Grade = SkullGrade::Legendary});

	LoadSkull({ .Name = "�̳�Ÿ��ν�", .Index = 101, .Grade = SkullGrade::Rare });
	LoadSkull({ .Name = "�̳�Ÿ��ν� 2��", .Index = 201, .Grade = SkullGrade::Unique });
	LoadSkull({ .Name = "�̳�Ÿ��ν� 3��", .Index = 301, .Grade = SkullGrade::Legendary });

	LoadSkull({ .Name = "���ݼ���", .Index = 102, .Grade = SkullGrade::Rare });
	LoadSkull({ .Name = "���� ���ݼ���", .Index = 202, .Grade = SkullGrade::Unique });
	LoadSkull({ .Name = "���� ���ݼ���", .Index = 302, .Grade = SkullGrade::Legendary });

	LoadSkull({ .Name = "������", .Index = 203, .Grade = SkullGrade::Unique });


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