#include "PrecompileHeader.h"
#include "NPCManager.h"

std::shared_ptr<BaseNPC> NPCManager::CreateNPC(const NPCMetaData& _NewNPCData)
{
	std::shared_ptr<BaseNPC> NewNPC = nullptr;

	switch (_NewNPCData.Index)
	{
	case 0: // ���̷�-��
	{
	
	}
		break; // ��-�̷���
	case 1:
	{
	
	}
		break;
	case 2: // ���̷���A
	{
	
	}
		break;
	case 3: // ���̷���B
	{

	}
		break;
	case 4: // ����(������)
	{
	
	}
		break;
	case 5: // ������
	{
	
	}
		break;
	default:
		break;
	}

	return NewNPC;
}