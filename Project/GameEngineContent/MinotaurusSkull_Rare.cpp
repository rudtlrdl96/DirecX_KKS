#include "PrecompileHeader.h"
#include "MinotaurusSkull_Rare.h"

MinotaurusSkull_Rare::MinotaurusSkull_Rare()
{
}

MinotaurusSkull_Rare::~MinotaurusSkull_Rare()
{
}

void MinotaurusSkull_Rare::DataLoad()
{
	Data = ContentDatabase<SkullData, SkullGrade>::GetData(101); // 101 == 미노타우로스
}

void MinotaurusSkull_Rare::TextureLoad()
{
	DeadPartNames.reserve(6);
	DeadPartNames.push_back("Minotaurus_Head1.png");
	DeadPartNames.push_back("Skul_DeatParts01.png");
	DeadPartNames.push_back("Skul_DeatParts02.png");
	DeadPartNames.push_back("Skul_DeatParts03.png");
	DeadPartNames.push_back("Skul_DeatParts04.png");
	DeadPartNames.push_back("Skul_DeatParts05.png");

	TexName_MainSkullUI = "Rare_Minotaurus_UI_MainSkull.png";
	TexName_SubSkullUI = "Rare_Minotaurus_UI_SubSkull.png";
	TexName_InventoryUI = "Rare_Minotaurus_UI_Inventory.png";

	TexName_SkillA = "Empty.png";
	TexName_SkillB = "Empty.png";
}

void MinotaurusSkull_Rare::CreateAnimation()
{
}

void MinotaurusSkull_Rare::AnimationColLoad()
{
}
