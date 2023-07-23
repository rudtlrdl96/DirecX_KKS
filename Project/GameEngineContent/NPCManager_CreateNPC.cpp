#include "PrecompileHeader.h"
#include "NPCManager.h"

#include "ChiefGuardNPC.h"
#include "SkeletonA.h"
#include "SkeletonB.h"
#include "SkeleTong.h"
#include "SueKeleton.h"
#include "WitchOpening.h"
#include "Witch_CatFollow.h"

#include "CastleWitchNPC.h"
#include "CastleFoxHunterNPC.h"
#include "CastleOgrePaddlerNPC.h"

#include "ArachneNPC.h"

#include "ShopChef.h"
#include "ShopCollector.h"
#include "ShopHeadless.h"
#include "ShopQuintessenceArtisan.h"
#include "ShopThief.h"

std::shared_ptr<BaseNPC> NPCManager::CreateNPC(const NPCMetaData& _NewNPCData)
{
	std::shared_ptr<BaseNPC> NewNPC = nullptr;

	switch (_NewNPCData.Index)
	{
	case 0: // ���̷�-��
		NewNPC = GetLevel()->CreateActor<SkeleTong>();
		break; // ��-�̷���
	case 1:
		NewNPC = GetLevel()->CreateActor<SueKeleton>();
		break;
	case 2: // ���̷���A
		NewNPC = GetLevel()->CreateActor<SkeletonA>();
		break;
	case 3: // ���̷���B
		NewNPC = GetLevel()->CreateActor<SkeletonB>();
		break;
	case 4: // ����(������)
		NewNPC = GetLevel()->CreateActor<WitchOpening>();
		break;
	case 5: // ������
		NewNPC = GetLevel()->CreateActor<ChiefGuardNPC>();
	break;
	case 6: // ���� �����(������)
		NewNPC = GetLevel()->CreateActor<Witch_CatFollow>();
		break;

	case 100: // ���� (ĳ��)
		NewNPC = GetLevel()->CreateActor<CastleWitchNPC>();
	break;
	case 101: // ��ȣ�� ��ɲ� (ĳ��)
		NewNPC = GetLevel()->CreateActor<CastleFoxHunterNPC>();
	break;
	case 102: // ���찡 ���λ� (ĳ��)
		NewNPC = GetLevel()->CreateActor<CastleOgrePaddlerNPC>();
	break;
	case 200: // �ƶ�ũ��
		NewNPC = GetLevel()->CreateActor<ArachneNPC>();
		break;
	case 600: // ���� ����
		NewNPC = GetLevel()->CreateActor<ShopChef>();
		break;
	case 601: // ���� �ݷ���
		NewNPC = GetLevel()->CreateActor<ShopCollector>();
		break;	
	case 602: // ���� �ݷ���
		NewNPC = GetLevel()->CreateActor<ShopHeadless>();
		break;	
	case 603: // ���� ��������
		NewNPC = GetLevel()->CreateActor<ShopQuintessenceArtisan>();
		break;	
	case 604: // ���� ������
		NewNPC = GetLevel()->CreateActor<ShopThief>();
		break;
	default:
		break;
	}

	NewNPC->Data = _NewNPCData;
	NewNPC->Data.CenterPos.z = GameEngineRandom::MainRandom.RandomFloat(-10.0f, -5.0f);
	NewNPC->GetTransform()->SetParent(GetTransform());
	NewNPC->GetTransform()->SetLocalPosition(NewNPC->Data.CenterPos);

	NpcActors.push_back(NewNPC);
	GUI_SelectNPC = static_cast<int>(NpcActors.size() - 1);

	return NewNPC;
}