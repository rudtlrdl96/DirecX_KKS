#pragma once

class ContentCore
{
public:
	ContentCore();
	~ContentCore();

	ContentCore(const ContentCore& _Other) = delete;
	ContentCore(ContentCore&& _Other) noexcept = delete;
	ContentCore& operator=(const ContentCore& _Other) = delete;
	ContentCore& operator=(ContentCore&& _Other) noexcept = delete;

	static void CoreLoading();
	static void CoreEnd();	
	static void SwitchShowCursor();


protected:

private:
	static void VertextBufferCreate();
	static void BlendCreate();
	static void ShaderCreate();
	static void ContentPipeLineCreate();

	// Data Base Load
	static void ItemDataLoad();
	static void SkullDataLoad();
	static void QuintessenceDataLoad();
	static void MonsterDataLoad();
	static void TileDataLoad();
	static void ObjectLoad();
	static void BackgroundDataLoad();
	static void NPCDataLoad();

	// Common Load
	static void CommonTextureLoad();
	static void ImGuiCreate();
	static void FontFind();
	static void FontLoad();
	static void SoundLoad();
};

