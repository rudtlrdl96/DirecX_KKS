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
		ResultTextureName = "���";
		break;
	case Synergy::Antique:
		ResultTextureName = "��ǰ";
		break;
	case Synergy::Heritage:
		ResultTextureName = "����� ��";
		break;
	case Synergy::Misfortune:
		ResultTextureName = "�ҿ�";
		break;
	case Synergy::Rapidity:
		ResultTextureName = "�ż�";
		break;
	case Synergy::Soar:
		ResultTextureName = "���";
		break;
	case Synergy::Strike:
		ResultTextureName = "��Ÿ";
		break;
	case Synergy::Wisdom:
		ResultTextureName = "����";
		break;
	case Synergy::Chase:
		ResultTextureName = "����";
		break;
	case Synergy::ManaCycle:
		ResultTextureName = "���� ��ȯ";
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
			ResultText = "���� ���ݷ��� 20% �����˴ϴ�.";
		}
		else if (4 >= SynergyCount)
		{
			ResultText = "���� ���ݷ��� 30% �����˴ϴ�.";
		}
		break;
	case Synergy::Antique:
		if (2 >= SynergyCount)
		{
			ResultText = "�ִ�ü���� 35 �����մϴ�.";
		}
		else if (4 >= SynergyCount)
		{
			ResultText = "���� ü���� 70% �̻��� �� �޴� �������� 45% �����մϴ�.";
		}
		break;
	case Synergy::Heritage:
		if (2 >= SynergyCount)
		{
			ResultText = "���� ��ٿ� �ӵ��� 45% �����մϴ�.";
		}
		else if (4 >= SynergyCount)
		{
			ResultText = "���� ���� 3�ʰ� ������ ������ �������� 25% �����˴ϴ�.\n(��Ÿ�� : 20��)";
		}
		break;
	case Synergy::Misfortune:
		if (2 >= SynergyCount)
		{
			ResultText = "ġ��Ÿ Ȯ���� 15% �����մϴ�.";
		}
		else if (4 >= SynergyCount)
		{
			ResultText = "ġ��Ÿ Ȯ���� 15% �����մϴ�.";
		}
		break;
	case Synergy::Rapidity:
		if (2 >= SynergyCount)
		{
			ResultText = "���ݼӵ��� 15% �����մϴ�";
		}
		else if (4 >= SynergyCount)
		{
			ResultText = "���ݼӵ��� 15% �����մϴ�";
		}
		break;
	case Synergy::Soar:
		if (2 >= SynergyCount)
		{
			ResultText = "���߿� ���� �� ġ��Ÿ Ȯ���� 20% �����մϴ�.";
		}
		else if (4 >= SynergyCount)
		{
			ResultText = "���߿� ���� �� ������ ������ �������� 40% �����˴ϴ�.";
		}
		break;
	case Synergy::Strike:
		if (2 >= SynergyCount)
		{
			ResultText = "ġ��Ÿ �������� 20% �����մϴ�.";
		}
		else if (4 >= SynergyCount)
		{
			ResultText = "ġ��Ÿ �������� 30% �����մϴ�.";
		}
		break;
	case Synergy::Wisdom:
		if (2 >= SynergyCount)
		{
			ResultText = "���� ���ݷ��� 20% �����˴ϴ�.";
		}
		else if (4 >= SynergyCount)
		{
			ResultText = "���� ���ݷ��� 30% �����˴ϴ�.";
		}
		break;
	case Synergy::Chase:
		if (2 >= SynergyCount)
		{
			ResultText = "�뽬 ��ٿ� �ӵ��� 40% �����մϴ�.";
		}
		else if (4 >= SynergyCount)
		{
			ResultText = "�뽬 ���ݷ��� 50% �����մϴ�";
		}
		break;
	case Synergy::ManaCycle:
		if (2 >= SynergyCount)
		{
			ResultText = "��ų ��ٿ� �ӵ��� 50% �����մϴ�.";
		}
		else if (4 >= SynergyCount)
		{
			ResultText = "��ų�� ������ ������ �������� 30% �����˴ϴ�.";
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
