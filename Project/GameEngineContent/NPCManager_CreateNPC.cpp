#include "PrecompileHeader.h"
#include "NPCManager.h"

std::shared_ptr<BaseNPC> NPCManager::CreateNPC(const NPCMetaData& _NewNPCData)
{
	std::shared_ptr<BaseNPC> NewNPC = nullptr;

	switch (_NewNPCData.Index)
	{
	case 0: // ½ºÄÌ·¹-Åë
	{
	
	}
		break; // ¼ö-ÄÌ·¹Åæ
	case 1:
	{
	
	}
		break;
	case 2: // ½ºÄÌ·¹ÅæA
	{
	
	}
		break;
	case 3: // ½ºÄÌ·¹ÅæB
	{

	}
		break;
	case 4: // ¸¶³à(¿ÀÇÁ´×)
	{
	
	}
		break;
	case 5: // °æºñ´ëÀå
	{
	
	}
		break;
	default:
		break;
	}

	return NewNPC;
}