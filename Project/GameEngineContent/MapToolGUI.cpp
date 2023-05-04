#include "PrecompileHeader.h"
#include "MapToolGUI.h"

#include <GameEngineCore/GameEngineTexture.h>

#include "TilemapData.h"

MapToolGUI::MapToolGUI()
{
}

MapToolGUI::~MapToolGUI()
{
}

void MapToolGUI::Start()
{
	ImGui::SetWindowSize(GetName().data(), ImVec2(200, 500));

	//TileTexDatas[TileArea::SacredGrounds] = 0;
	//TileTexDatas[TileArea::SacredGrounds] = 0;
	//TileTexDatas[TileArea::SacredGrounds] = 0;
	//TileTexDatas[TileArea::SacredGrounds] = 0;
}

void MapToolGUI::OnGUI(std::shared_ptr<class GameEngineLevel>, float _DeltaTime)
{
	std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find("DebugBoxTexture.png");

	if (nullptr == FindTex)
	{
		MsgAssert_Rtti<MapToolGUI>(" - �ؽ��ĸ� ã�� �� �����ϴ�.");
		return;
	}
	
	float4 TextureSize = FindTex->GetTextureSize();
	ImGui::ImageButton("TestButton", (void*)FindTex->GetSRV(), ImVec2(TextureSize.x, TextureSize.y));

}
