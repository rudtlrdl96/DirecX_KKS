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

	if (nullptr == GameEngineSprite::Find("FirstHero_Story_Landing.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("1_Opening");
		Path.Move("Npc");
		Path.Move("FirstHero");
		Path.Move("Sheet");


		GameEngineSprite::LoadSheet(Path.GetPlusFileName("FirstHero_Story_Landing.png").GetFullPath(), 10, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("FirstHero_Story_FlyIdle.png").GetFullPath(), 9, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("FirstHero_Story_CastingIntro.png").GetFullPath(), 6, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("FirstHero_Story_CastingLoop.png").GetFullPath(), 6, 1);

		Path.MoveParent();
		Path.Move("Effect");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("FirstHero_BigbangReady_Effect.png").GetFullPath(), 5, 5);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("FirstHero_Landing_Effect.png").GetFullPath(), 7, 7);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("FirstHero_OrbLoop_Effect.png").GetFullPath(), 7, 6);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("FirstHero_OrbStart_Effect.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("FirstHero_OrbTrail_Effect.png").GetFullPath(), 5, 5);

		EffectManager::CreateMetaData("FirstHero_BigbangReady", {
			.SpriteName = "FirstHero_BigbangReady_Effect.png",
			.AnimStart = 0,
			.AnimEnd = 22,
			.AnimInter = 0.05f,
			.ScaleRatio = 2.0f });

		EffectManager::CreateMetaData("FirstHero_Landing", {
			.SpriteName = "FirstHero_Landing_Effect.png",
			.AnimStart = 0,
			.AnimEnd = 42,
			.AnimInter = 0.04f,
			.ScaleRatio = 2.0f });

		EffectManager::CreateMetaData("FirstHero_OrbLoop", {
			.SpriteName = "FirstHero_OrbLoop_Effect.png",
			.AnimStart = 0,
			.AnimEnd = 37,
			.AnimInter = 0.05f,
			.ScaleRatio = 2.0f });

		EffectManager::CreateMetaData("FirstHero_OrbStart", {
			.SpriteName = "FirstHero_OrbStart_Effect.png",
			.AnimStart = 0,
			.AnimEnd = 4,
			.AnimInter = 0.05f,
			.ScaleRatio = 3.0f });

		EffectManager::CreateMetaData("FirstHero_OrbTrail", {
			.SpriteName = "FirstHero_OrbTrail_Effect.png",
			.AnimStart = 0,
			.AnimEnd = 21,
			.AnimInter = 0.05f,
			.ScaleRatio = 2.0f });

	}

	// Opening
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

	ContentDatabase<NPCMetaData, LevelArea>::InsertData({
		.Index = 6, .Grade = LevelArea::Opening,
		.Name = "¸¶³à °í¾çÀÌ(¿ÀÇÁ´×)", .TalkboxNameTag = "¸¶³à",
		.PreviewName = "WitchOpeningCat_Preview.png" });

	// Castle
	ContentDatabase<NPCMetaData, LevelArea>::InsertData({
		.Index = 100, .Grade = LevelArea::Castle,
		.Name = "¸¶³à (Ä³½½)", .TalkboxNameTag = "¸¶³à",
		.PreviewName = "Witch_Castle_Preview.png" });

	ContentDatabase<NPCMetaData, LevelArea>::InsertData({
		.Index = 101, .Grade = LevelArea::Castle,
		.Name = "ÀÎÈ£Á· »ç³É²Û", .TalkboxNameTag = "ÀÎÈ£Á· »ç³É²Û",
		.PreviewName = "FoxHunter_Castle_Preview.png" });

	ContentDatabase<NPCMetaData, LevelArea>::InsertData({
		.Index = 102, .Grade = LevelArea::Castle,
		.Name = "¿À¿ì°Å º¸ºÎ»ó", .TalkboxNameTag = "¿À¿ì°Å º¸ºÎ»ó",
		.PreviewName = "OgrePeddler_Castle_Preview.png" });


	// ForestOfHarmony
	ContentDatabase<NPCMetaData, LevelArea>::InsertData({
	.Index = 200, .Grade = LevelArea::ForestOfHarmory,
	.Name = "¾Æ¶óÅ©³×", .TalkboxNameTag = "¾Æ¶óÅ©³×",
	.PreviewName = "Arachne_Preview.png" });

	// Shop
	ContentDatabase<NPCMetaData, LevelArea>::InsertData({
		.Index = 600, .Grade = LevelArea::Shop,
		.Name = "½¦ÇÁ", .TalkboxNameTag = "½¦ÇÁ",
		.PreviewName = "Chef_Preview.png" });

	ContentDatabase<NPCMetaData, LevelArea>::InsertData({
		.Index = 601, .Grade = LevelArea::Shop,
		.Name = "¼öÁý°¡", .TalkboxNameTag = "¼öÁý°¡",
		.PreviewName = "Collector_Preview.png" });	

	ContentDatabase<NPCMetaData, LevelArea>::InsertData({
		.Index = 602, .Grade = LevelArea::Shop,
		.Name = "Çìµå¸®½º", .TalkboxNameTag = "Çìµå¸®½º",
		.PreviewName = "Headless_Preview.png" });	
	
	ContentDatabase<NPCMetaData, LevelArea>::InsertData({
		.Index = 603, .Grade = LevelArea::Shop,
		.Name = "Á¤¼öÀåÀÎ", .TalkboxNameTag = "Á¤¼öÀåÀÎ",
		.PreviewName = "QuintessenceArtisan_Preview.png" });

	ContentDatabase<NPCMetaData, LevelArea>::InsertData({
		.Index = 604, .Grade = LevelArea::Shop,
		.Name = "µµ±¼²Û", .TalkboxNameTag = "µµ±¼²Û",
		.PreviewName = "ShopThief_Preview.png" });

}