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
	case 0: // ���̷�-��
	{
		NewNPC = GetLevel()->CreateActor<SkeleTong>();
	}
		break; // ��-�̷���
	case 1:
	{
		NewNPC = GetLevel()->CreateActor<SueKeleton>();
	}
		break;
	case 2: // ���̷���A
	{
		NewNPC = GetLevel()->CreateActor<SkeletonA>();
	}
		break;
	case 3: // ���̷���B
	{
		NewNPC = GetLevel()->CreateActor<SkeletonB>();
	}
		break;
	case 4: // ����(������)
	{
		NewNPC = GetLevel()->CreateActor<WitchOpening>();
	}
		break;
	case 5: // ������
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