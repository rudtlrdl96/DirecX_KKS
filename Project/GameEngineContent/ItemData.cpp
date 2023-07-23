#include "PrecompileHeader.h"
#include "ItemData.h"

std::string ItemData::GetSynergyIconTextureName(Synergy _Type, size_t SynergyCount /*= -1*/)
{
    std::string ResultTextureName = "Empty.png";

	switch (_Type)
	{
	case Synergy::Courage:
		if (-1 == SynergyCount)
		{
			ResultTextureName = "Brave.png";
		}
		else if (2 > SynergyCount)
		{
			ResultTextureName = "Brave_Deactivation.png";
		}
		else if (4 > SynergyCount)
		{
			ResultTextureName = "Brave.png";
		}
		else
		{
			ResultTextureName = "Brave_FullActivation.png";
		}
		break;
	case Synergy::Antique:
		if (-1 == SynergyCount)
		{
			ResultTextureName = "Antique.png";
		}
		else if (2 > SynergyCount)
		{
			ResultTextureName = "Antique_Deactivation.png";
		}
		else if (4 > SynergyCount)
		{
			ResultTextureName = "Antique.png";
		}
		else
		{
			ResultTextureName = "Antique_FullActivation.png";
		}
		break;
	case Synergy::Heritage:
		if (-1 == SynergyCount)
		{
			ResultTextureName = "ExcessiveBleeding.png";
		}
		else if (2 > SynergyCount)
		{
			ResultTextureName = "ExcessiveBleeding_Deactivation.png";
		}
		else if (4 > SynergyCount)
		{
			ResultTextureName = "ExcessiveBleeding.png";
		}
		else
		{
			ResultTextureName = "ExcessiveBleeding_FullActivation.png";
		}
		break;
	case Synergy::Misfortune:
		if (-1 == SynergyCount)
		{
			ResultTextureName = "Misfortune.png";
		}
		else if (2 > SynergyCount)
		{
			ResultTextureName = "Misfortune_Deactivation.png";
		}
		else if (4 > SynergyCount)
		{
			ResultTextureName = "Misfortune.png";
		}
		else
		{
			ResultTextureName = "Misfortune_FullActivation.png";
		}
		break;
	case Synergy::Rapidity:
		if (-1 == SynergyCount)
		{
			ResultTextureName = "Rapidity.png";
		}
		else if (2 > SynergyCount)
		{
			ResultTextureName = "Rapidity_Deactivation.png";
		}
		else if (4 > SynergyCount)
		{
			ResultTextureName = "Rapidity.png";
		}
		else
		{
			ResultTextureName = "Rapidity_FullActivation.png";
		}
		break;
	case Synergy::Soar:
		if (-1 == SynergyCount)
		{
			ResultTextureName = "Soar.png";
		}
		else if (2 > SynergyCount)
		{
			ResultTextureName = "Soar_Deactivation.png";
		}
		else if (4 > SynergyCount)
		{
			ResultTextureName = "Soar.png";
		}
		else
		{
			ResultTextureName = "Soar_FullActivation.png";
		}
		break;
	case Synergy::Strike:
		if (-1 == SynergyCount)
		{
			ResultTextureName = "Strike.png";
		}
		else if (2 > SynergyCount)
		{
			ResultTextureName = "Strike_Deactivation.png";
		}
		else if (4 > SynergyCount)
		{
			ResultTextureName = "Strike.png";
		}
		else
		{
			ResultTextureName = "Strike_FullActivation.png";
		}
		break;
	case Synergy::Wisdom:
		if (-1 == SynergyCount)
		{
			ResultTextureName = "Wisdom.png";
		}
		else if (2 > SynergyCount)
		{
			ResultTextureName = "Wisdom_Deactivation.png";
		}
		else if (4 > SynergyCount)
		{
			ResultTextureName = "Wisdom.png";
		}
		else
		{
			ResultTextureName = "Wisdom_FullActivation.png";
		}
		break;
	case Synergy::Chase:
		if (-1 == SynergyCount)
		{
			ResultTextureName = "Chase.png";
		}
		else if (2 > SynergyCount)
		{
			ResultTextureName = "Chase_Deactivation.png";
		}
		else if (4 > SynergyCount)
		{
			ResultTextureName = "Chase.png";
		}
		else
		{
			ResultTextureName = "Chase_FullActivation.png";
		}
		break;
	case Synergy::ManaCycle:
		if (-1 == SynergyCount)
		{
			ResultTextureName = "ManaCycle.png";
		}
		else if (2 > SynergyCount)
		{
			ResultTextureName = "ManaCycle_Deactivation.png";
		}
		else if (4 > SynergyCount)
		{
			ResultTextureName = "ManaCycle.png";
		}
		else
		{
			ResultTextureName = "ManaCycle_FullActivation.png";
		}
		break;
	}

    return ResultTextureName;
}

std::string ItemData::GetSynergyName(Synergy _Type)
{
	std::string ResultTextureName = "";
	
	switch (_Type)
	{
	case Synergy::Courage:
		ResultTextureName = "용기";
		break;
	case Synergy::Antique:
		ResultTextureName = "골동품";
		break;
	case Synergy::Heritage:
		ResultTextureName = "고대의 힘";
		break;
	case Synergy::Misfortune:
		ResultTextureName = "불운";
		break;
	case Synergy::Rapidity:
		ResultTextureName = "신속";
		break;
	case Synergy::Soar:
		ResultTextureName = "비상";
		break;
	case Synergy::Strike:
		ResultTextureName = "강타";
		break;
	case Synergy::Wisdom:
		ResultTextureName = "지혜";
		break;
	case Synergy::Chase:
		ResultTextureName = "추적";
		break;
	case Synergy::ManaCycle:
		ResultTextureName = "마나 순환";
		break;
	}

	return ResultTextureName;
}

std::string ItemData::GetSynergyNote(Synergy _Type, size_t SynergyCount)
{
	std::string ResultText = "";

	switch (_Type)
	{
	case Synergy::Courage:
		if (2 >= SynergyCount)
		{
			ResultText = "물리 공격력이 20% 증폭됩니다.";
		}
		else if (4 >= SynergyCount)
		{
			ResultText = "물리 공격력이 30% 증폭됩니다.";
		}
		break;
	case Synergy::Antique:
		if (2 >= SynergyCount)
		{
			ResultText = "최대체력이 35 증가합니다.";
		}
		else if (4 >= SynergyCount)
		{
			ResultText = "현재 체력이 70% 이상일 시 받는 데미지가 45% 감소합니다.";
		}
		break;
	case Synergy::Heritage:
		if (2 >= SynergyCount)
		{
			ResultText = "정수 쿨다운 속도가 45% 증가합니다.";
		}
		else if (4 >= SynergyCount)
		{
			ResultText = "정수 사용시 3초간 적에게 입히는 데미지가 25% 증폭됩니다.\n(쿨타임 : 20초)";
		}
		break;
	case Synergy::Misfortune:
		if (2 >= SynergyCount)
		{
			ResultText = "치명타 확률이 15% 증가합니다.";
		}
		else if (4 >= SynergyCount)
		{
			ResultText = "치명타 확률이 15% 증가합니다.";
		}
		break;
	case Synergy::Rapidity:
		if (2 >= SynergyCount)
		{
			ResultText = "공격속도가 15% 증가합니다";
		}
		else if (4 >= SynergyCount)
		{
			ResultText = "공격속도가 15% 증가합니다";
		}
		break;
	case Synergy::Soar:
		if (2 >= SynergyCount)
		{
			ResultText = "공중에 있을 시 치명타 확률이 20% 증가합니다.";
		}
		else if (4 >= SynergyCount)
		{
			ResultText = "공중에 있을 시 적에게 입히는 데미지가 40% 증폭됩니다.";
		}
		break;
	case Synergy::Strike:
		if (2 >= SynergyCount)
		{
			ResultText = "치명타 데미지가 20% 증가합니다.";
		}
		else if (4 >= SynergyCount)
		{
			ResultText = "치명타 데미지가 30% 증가합니다.";
		}
		break;
	case Synergy::Wisdom:
		if (2 >= SynergyCount)
		{
			ResultText = "마법 공격력이 20% 증폭됩니다.";
		}
		else if (4 >= SynergyCount)
		{
			ResultText = "마법 공격력이 30% 증폭됩니다.";
		}
		break;
	case Synergy::Chase:
		if (2 >= SynergyCount)
		{
			ResultText = "대쉬 쿨다운 속도가 40% 증가합니다.";
		}
		else if (4 >= SynergyCount)
		{
			ResultText = "대쉬 공격력이 50% 증가합니다";
		}
		break;
	case Synergy::ManaCycle:
		if (2 >= SynergyCount)
		{
			ResultText = "스킬 쿨다운 속도가 50% 증가합니다.";
		}
		else if (4 >= SynergyCount)
		{
			ResultText = "스킬로 적에게 입히는 데미지가 30% 증폭됩니다.";
		}
		break;
	}

	return ResultText;
}

std::vector<int> ItemData::GetSynergyGrade(Synergy _Type)
{
	std::vector<int> SynergyGrades;
	SynergyGrades.resize(2);
	
	SynergyGrades[0] = 2;
	SynergyGrades[1] = 4;

	//switch (_Type)
	//{
	//case Synergy::Courage:
	//	SynergyGrades[0] = 2;
	//	SynergyGrades[1] = 4;
	//	break;
	//case Synergy::Antique:
	//	SynergyGrades[0] = 2;
	//	SynergyGrades[1] = 4;
	//	break;
	//case Synergy::Heritage:
	//	SynergyGrades[0] = 2;
	//	SynergyGrades[1] = 4;
	//	break;
	//case Synergy::Misfortune:
	//	SynergyGrades[0] = 2;
	//	SynergyGrades[1] = 4;
	//	break;
	//case Synergy::Rapidity:
	//	SynergyGrades[0] = 2;
	//	SynergyGrades[1] = 4;
	//	break;
	//case Synergy::Soar:
	//	SynergyGrades[0] = 2;
	//	SynergyGrades[1] = 4;
	//	break;
	//case Synergy::Strike:
	//	SynergyGrades[0] = 2;
	//	SynergyGrades[1] = 4;
	//	break;
	//case Synergy::Wisdom:
	//	SynergyGrades[0] = 2;
	//	SynergyGrades[1] = 4;
	//	break;
	//case Synergy::Chase:
	//	SynergyGrades[0] = 2;
	//	SynergyGrades[1] = 4;
	//	break;
	//case Synergy::ManaCycle:
	//	SynergyGrades[0] = 2;
	//	SynergyGrades[1] = 4;
	//	break;
	//}

	return SynergyGrades;
}
