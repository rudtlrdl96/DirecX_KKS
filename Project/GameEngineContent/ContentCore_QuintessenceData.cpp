#include "PrecompileHeader.h"
#include "ContentCore.h"
#include "QuintessenceData.h"

static void LoadQuintessence(const QuintessenceData& _Data)
{
	ContentDatabase<QuintessenceData, QuintessenceGrade>::InsertData(_Data);
}

void ContentCore::QuintessenceDataLoad()
{
	LoadQuintessence({ .Name = "��Ƽ", .Index = 0, .Grade = QuintessenceGrade::Normal});
	LoadQuintessence({ .Name = "��ũ", .Index = 100, .Grade = QuintessenceGrade::Rare });
	LoadQuintessence({ .Name = "ȭ��", .Index = 200, .Grade = QuintessenceGrade::Unique });
	LoadQuintessence({ .Name = "��ũ����", .Index = 300, .Grade = QuintessenceGrade::Legendary });
}