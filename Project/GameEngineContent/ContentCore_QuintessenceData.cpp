#include "PrecompileHeader.h"
#include "ContentCore.h"
#include "QuintessenceData.h"

static void LoadQuintessence(const QuintessenceData& _Data)
{
	ContentDatabase<QuintessenceData, QuintessenceGrade>::InsertData(_Data);
}

void ContentCore::QuintessenceDataLoad()
{
	LoadQuintessence({ .Name = "예티", .Index = 0, .Grade = QuintessenceGrade::Normal});
	LoadQuintessence({ .Name = "오크", .Index = 100, .Grade = QuintessenceGrade::Rare });
	LoadQuintessence({ .Name = "화룡", .Index = 200, .Grade = QuintessenceGrade::Unique });
	LoadQuintessence({ .Name = "아크데몬", .Index = 300, .Grade = QuintessenceGrade::Legendary });
}