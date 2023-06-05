#include "PrecompileHeader.h"
#include "ContentCore.h"
#include "BaseNPC.h"

void ContentCore::NPCDataLoad()
{
	ContentDatabase<NPCMetaData, LevelArea>::InsertData({
		.Index = 0, .Grade = LevelArea::Opening, 
		.Name = "½ºÄÌ·¹-Åë", .TalkboxNameTag = "½ºÄÌ·¹-Åë",
		.PreviewName = "SkeleTong_Preview.png"});

	ContentDatabase<NPCMetaData, LevelArea>::InsertData({
		.Index = 1, .Grade = LevelArea::Opening,
		.Name = "¼ö-ÄÌ·¹Åæ", .TalkboxNameTag = "¼ö-ÄÌ·¹Åæ",
		.PreviewName = "SueKeleton_Preview.png"});

	ContentDatabase<NPCMetaData, LevelArea>::InsertData({
		.Index = 2, .Grade = LevelArea::Opening,
		.Name = "½ºÄÌ·¹ÅæA", .TalkboxNameTag = "½ºÄÌ·¹ÅæA",
		.PreviewName = "SkeletonA_Preview.png"});

	ContentDatabase<NPCMetaData, LevelArea>::InsertData({
		.Index = 3, .Grade = LevelArea::Opening,
		.Name = "½ºÄÌ·¹ÅæB", .TalkboxNameTag = "½ºÄÌ·¹ÅæB",
		.PreviewName = "SkeletonB_Preview.png"});

	ContentDatabase<NPCMetaData, LevelArea>::InsertData({
		.Index = 4, .Grade = LevelArea::Opening,
		.Name = "¸¶³à(¿ÀÇÁ´×)", .TalkboxNameTag = "¸¶³à",
		.PreviewName = "WitchOpening_Preview.png"});

	ContentDatabase<NPCMetaData, LevelArea>::InsertData({
		.Index = 5, .Grade = LevelArea::Opening,
		.Name = "°æºñ´ëÀå", .TalkboxNameTag = "°æºñ´ëÀå",
		.PreviewName = "ChiefGuardNPC_Preview.png" });
}