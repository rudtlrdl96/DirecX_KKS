#include "PrecompileHeader.h"
#include "NPCManager.h"

#include "ChiefGuardNPC.h"
#include "SkeletonA.h"
#include "SkeletonB.h"
#include "SkeleTong.h"
#include "SueKeleton.h"
#include "WitchOpening.h"

std::shared_ptr<BaseNPC> NPCManager::CreateNPC(const NPCMetaData& _NewNPCData)
{
	std::shared_ptr<BaseNPC> NewNPC = nullptr;

	switch (_NewNPCData.Index)
	{
	case 0: // ½ºÄÌ·¹-Åë
	{
		NewNPC = GetLevel()->CreateActor<SkeleTong>();
	}
		break; // ¼ö-ÄÌ·¹Åæ
	case 1:
	{
		NewNPC = GetLevel()->CreateActor<SueKeleton>();
	}
		break;
	case 2: // ½ºÄÌ·¹ÅæA
	{
		NewNPC = GetLevel()->CreateActor<SkeletonA>();
	}
		break;
	case 3: // ½ºÄÌ·¹ÅæB
	{
		NewNPC = GetLevel()->CreateActor<SkeletonB>();
	}
		break;
	case 4: // ¸¶³à(¿ÀÇÁ´×)
	{
		NewNPC = GetLevel()->CreateActor<WitchOpening>();
	}
		break;
	case 5: // °æºñ´ëÀå
	{
		NewNPC = GetLevel()->CreateActor<ChiefGuardNPC>();
	}
		break;
	default:
		break;
	}

	NewNPC->Data = _NewNPCData;
	NewNPC->GetTransform()->SetParent(GetTransform());
	NewNPC->GetTransform()->SetLocalPosition(_NewNPCData.CenterPos);

	NpcActors.push_back(NewNPC);
	GUI_SelectNPC = static_cast<int>(NpcActors.size() - 1);

	return NewNPC;
}