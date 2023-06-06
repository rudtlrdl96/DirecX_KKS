#include "PrecompileHeader.h"
#include "ContentCore.h"
#include "BaseNPC.h"

void ContentCore::NPCDataLoad()
{
	{
		GameEngineDirectory Path;
		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("Npc");
		Path.Move("Preview");
		
		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (UINT i = 0; i < Files.size(); i++)
		{
			GameEngineTexture::Load(Files[i].GetFullPath());
		}
	}

	ContentDatabase<NPCMetaData, LevelArea>::InsertData({
		.Index = 0, .Grade = LevelArea::Opening, 
		.Name = "���̷�-��", .TalkboxNameTag = "���̷�-��",
		.PreviewName = "SkeleTong_Preview.png"});

	ContentDatabase<NPCMetaData, LevelArea>::InsertData({
		.Index = 1, .Grade = LevelArea::Opening,
		.Name = "��-�̷���", .TalkboxNameTag = "��-�̷���",
		.PreviewName = "SueKeleton_Preview.png"});

	ContentDatabase<NPCMetaData, LevelArea>::InsertData({
		.Index = 2, .Grade = LevelArea::Opening,
		.Name = "���̷���A", .TalkboxNameTag = "���̷���A",
		.PreviewName = "SkeletonA_Preview.png"});

	ContentDatabase<NPCMetaData, LevelArea>::InsertData({
		.Index = 3, .Grade = LevelArea::Opening,
		.Name = "���̷���B", .TalkboxNameTag = "���̷���B",
		.PreviewName = "SkeletonB_Preview.png"});

	ContentDatabase<NPCMetaData, LevelArea>::InsertData({
		.Index = 4, .Grade = LevelArea::Opening,
		.Name = "����(������)", .TalkboxNameTag = "����",
		.PreviewName = "WitchOpening_Preview.png"});

	ContentDatabase<NPCMetaData, LevelArea>::InsertData({
		.Index = 5, .Grade = LevelArea::Opening,
		.Name = "������", .TalkboxNameTag = "������",
		.PreviewName = "ChiefGuardNPC_Preview.png" });
}