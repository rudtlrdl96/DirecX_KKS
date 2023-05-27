#include "PrecompileHeader.h"
#include "ContentCore.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineVertexShader.h>
#include <GameEngineCore/GameEnginePixelShader.h>
#include <GameEngineCore/GameEngineRenderingPipeLine.h>
#include <GameEngineCore/GameEngineVertexBuffer.h>
#include <GameEngineCore/GameEngineIndexBuffer.h>
#include <GameEngineCore/GameEngineGUI.h>
#include <GameEngineCore/GameEngineBlend.h>

// Vertext
#include "ContentVertex.h"

// ImGui
#include "GameEngineActorGUI.h"
#include "MapToolGUI.h"
#include "BackgroundToolGUI.h"
#include "LevelMoveGUI.h"
#include "AnimationCollisionToolGUI.h"

// Player Level
#include "TitleLevel.h"
#include "OpeningLevel.h"
#include "CastleLevel.h"
#include "ForestOfHarmonyLevel.h"
#include "GrandHallLevel.h"
#include "HolyCourtyardLevel.h"
#include "StoryLevel.h"
#include "ShopLevel.h"
#include "EndingLogoLevel.h"

// Game Class
#include "Inventory.h"

// Debug Level
#include "ShaderDebugLevel.h"
#include "InventoryDebugLevel.h"
#include "PhysicsDebugLevel.h"
#include "MapToolLevel.h"
#include "BackgroundToolLevel.h"
#include "AnimationColToolLevel.h"
#include "TilemapDebugLevel.h"

ContentCore::ContentCore()
{
}

ContentCore::~ContentCore()
{
}

void ContentCore::CoreLoading()
{
	VertextBufferCreate();
	BlendCreate();
	ShaderCreate();
	ContentPipeLineCreate();

	// DB Load
	ItemDataLoad();
	SkullDataLoad();
	QuintessenceDataLoad();
	MonsterDataLoad();
	TileDataLoad();
	StaticObjectLoad();
	BackgroundDataLoad();

	// Common Load
	CommonTextureLoad();
	ImGuiCreate();

	if (false == GameEngineInput::IsKey("LevelMove_ShaderDebug"))
	{
		GameEngineInput::CreateKey("CheckDebugCtrl", VK_LCONTROL);
		GameEngineInput::CreateKey("CheckUIAlt", VK_MENU);

		GameEngineInput::CreateKey("NumPad0", VK_NUMPAD0);
		GameEngineInput::CreateKey("NumPad1", VK_NUMPAD1);
		GameEngineInput::CreateKey("NumPad2", VK_NUMPAD2);
		GameEngineInput::CreateKey("NumPad3", VK_NUMPAD3);
		GameEngineInput::CreateKey("NumPad4", VK_NUMPAD4);
		GameEngineInput::CreateKey("NumPad5", VK_NUMPAD5);
		GameEngineInput::CreateKey("NumPad6", VK_NUMPAD6);
		GameEngineInput::CreateKey("NumPad7", VK_NUMPAD7);
		GameEngineInput::CreateKey("NumPad8", VK_NUMPAD8);
		GameEngineInput::CreateKey("NumPad9", VK_NUMPAD9);
	}

	// GameLevel Create
	GameEngineCore::CreateLevel<TitleLevel>("Title");
	GameEngineCore::CreateLevel<OpeningLevel>("Opening");
	GameEngineCore::CreateLevel<CastleLevel>("Castle");
	GameEngineCore::CreateLevel<ForestOfHarmonyLevel>("ForestOfHarmony");
	GameEngineCore::CreateLevel<GrandHallLevel>("GrandHall");
	GameEngineCore::CreateLevel<HolyCourtyardLevel>("HolyCourtyard");
	GameEngineCore::CreateLevel<StoryLevel>("Story");
	GameEngineCore::CreateLevel<ShopLevel>("Shop");
	GameEngineCore::CreateLevel<EndingLogoLevel>("EndingLogo");
	
	// DebugLevel Create
	GameEngineCore::CreateLevel<ShaderDebugLevel>("ShaderDebug");
	GameEngineCore::CreateLevel<InventoryDebugLevel>("InventoryDebug");
	GameEngineCore::CreateLevel<PhysicsDebugLevel>("PhysicsDebug");
	GameEngineCore::CreateLevel<MapToolLevel>("MapTool");
	GameEngineCore::CreateLevel<BackgroundToolLevel>("BackgroundTool");
	GameEngineCore::CreateLevel<AnimationColToolLevel>("AnimationColTool");
	GameEngineCore::CreateLevel<TilemapDebugLevel>("TilemapDebugLevel");

	Inventory::SetMainSkull(ContentDatabase<SkullData, SkullGrade>::GetData(0)); // 기본 리틀본
	//Inventory::SetSubSkull(ContentDatabase<SkullData, SkullGrade>::GetData(203)); // 디버그용 경비대장

	GameEngineCore::ChangeLevel("Title");

}

void ContentCore::CoreEnd()
{

}

void ContentCore::VertextBufferCreate()
{
	ContentVertex::LayOut.AddInputLayOut("POSITION", DXGI_FORMAT_R32G32B32A32_FLOAT);
	ContentVertex::LayOut.AddInputLayOut("TEXCOORD", DXGI_FORMAT_R32G32B32A32_FLOAT);
	ContentVertex::LayOut.AddInputLayOut("NORMAL", DXGI_FORMAT_R32G32B32A32_FLOAT);

	{
		std::vector<ContentVertex> ArrVertex;
		ArrVertex.resize(24);

		float UV1Div3 = 1.0f / 3.0f;
		float UV2Div3 = 2.0f / 3.0f;

		// 앞면
		ArrVertex[0] = ContentVertex(float4{ -0.5f, 0.5f, -0.5f }, { UV1Div3, UV1Div3 }, float4{ -0.5f, 0.5f, -0.5f }.NormalizeReturn());
		ArrVertex[1] = ContentVertex(float4{ 0.5f, 0.5f, -0.5f }, { UV2Div3, UV1Div3 }, float4{ 0.5f, 0.5f, -0.5f }.NormalizeReturn());
		ArrVertex[2] = ContentVertex(float4{ 0.5f, -0.5f, -0.5f }, { UV2Div3, UV2Div3 }, float4{ 0.5f, -0.5f, -0.5f }.NormalizeReturn());
		ArrVertex[3] = ContentVertex(float4{ -0.5f, -0.5f, -0.5f }, { UV1Div3, UV2Div3 }, float4{ -0.5f, -0.5f, -0.5f }.NormalizeReturn());

		// 뒷면
		ArrVertex[4] = ContentVertex(float4{ -0.5f, -0.5f, 0.5f }, { UV2Div3, UV2Div3 }, float4{ -0.5f, -0.5f, 0.5f }.NormalizeReturn());
		ArrVertex[5] = ContentVertex(float4{ 0.5f, -0.5f , 0.5f }, { 1.0f, UV2Div3 }, float4{ 0.5f, -0.5f , 0.5f }.NormalizeReturn());
		ArrVertex[6] = ContentVertex(float4{ 0.5f, 0.5f  , 0.5f }, { 1.0f, 1.0f }, float4{ 0.5f, 0.5f  , 0.5f }.NormalizeReturn());
		ArrVertex[7] = ContentVertex(float4{ -0.5f, 0.5f, 0.5f }, { UV2Div3, 1.0f }, float4{ -0.5f, 0.5f, 0.5f }.NormalizeReturn());

		// 윗면
		ArrVertex[8] = ContentVertex(float4{ -0.5f , 0.5f , 0.5f }, { UV1Div3, 0.0f }, float4{ -0.5f , 0.5f , 0.5f }.NormalizeReturn());
		ArrVertex[9] = ContentVertex(float4{ 0.5f, 0.5f , 0.5f }, { UV2Div3, 0.0f }, float4{ 0.5f, 0.5f , 0.5f }.NormalizeReturn());
		ArrVertex[10] = ContentVertex(float4{ 0.5f, 0.5f, -0.5f }, { UV2Div3, UV1Div3 }, float4{ 0.5f, 0.5f, -0.5f }.NormalizeReturn());
		ArrVertex[11] = ContentVertex(float4{ -0.5f, 0.5f, -0.5f }, { UV1Div3, UV1Div3 }, float4{ -0.5f, 0.5f, -0.5f }.NormalizeReturn());

		// 아랫면
		ArrVertex[12] = ContentVertex(float4{ -0.5f, -0.5f, -0.5f }, { UV1Div3, UV2Div3 }, float4{ -0.5f, -0.5f, -0.5f }.NormalizeReturn());
		ArrVertex[13] = ContentVertex(float4{ 0.5f, -0.5f, -0.5f }, { UV2Div3, UV2Div3 }, float4{ 0.5f, -0.5f, -0.5f }.NormalizeReturn());
		ArrVertex[14] = ContentVertex(float4{ 0.5f, -0.5f, 0.5f }, { UV2Div3, 1.0f }, float4{ 0.5f, -0.5f, 0.5f }.NormalizeReturn());
		ArrVertex[15] = ContentVertex(float4{ -0.5f , -0.5f, 0.5f }, { UV1Div3, 1.0f }, float4{ -0.5f , -0.5f, 0.5f }.NormalizeReturn());

		// 왼쪽면
		ArrVertex[16] = ContentVertex(float4{ -0.5f, 0.5f, 0.5f }, { 0.0f, UV1Div3 }, float4{ -0.5f, 0.5f, 0.5f }.NormalizeReturn());
		ArrVertex[17] = ContentVertex(float4{ -0.5f, 0.5f, -0.5f }, { UV1Div3, UV1Div3 }, float4{ -0.5f, 0.5f, -0.5f }.NormalizeReturn());
		ArrVertex[18] = ContentVertex(float4{ -0.5f, -0.5f, -0.5f }, { UV1Div3, UV2Div3 }, float4{ -0.5f, -0.5f, -0.5f }.NormalizeReturn());
		ArrVertex[19] = ContentVertex(float4{ -0.5f, -0.5f , 0.5f }, { 0.0f, UV2Div3 }, float4{ -0.5f, -0.5f , 0.5f }.NormalizeReturn());

		// 오른쪽면
		ArrVertex[20] = ContentVertex(float4{ 0.5f, 0.5f, -0.5f }, { UV2Div3, UV1Div3 }, float4{ 0.5f, 0.5f, -0.5f }.NormalizeReturn());
		ArrVertex[21] = ContentVertex(float4{ 0.5f , 0.5f, 0.5f }, { 1.0f, UV1Div3 }, float4{ 0.5f , 0.5f, 0.5f }.NormalizeReturn());
		ArrVertex[22] = ContentVertex(float4{ 0.5f , -0.5f , 0.5f }, { 1.0f, UV2Div3 }, float4{ 0.5f , -0.5f , 0.5f }.NormalizeReturn());
		ArrVertex[23] = ContentVertex(float4{ 0.5f, -0.5f, -0.5f }, { UV2Div3, UV2Div3 }, float4{ 0.5f, -0.5f, -0.5f }.NormalizeReturn());


		std::vector<UINT> ArrIndex = {
			 0, 1, 2, 0, 2, 3, // 앞면
			 4, 5, 6, 4, 6, 7, // 뒷면
			 8, 9, 10, 8, 10, 11, // 위
			 12, 13, 14, 12, 14, 15, // 아래
			 16, 17, 18, 16, 18, 19, // 왼쪽
			 20, 21, 22, 20, 22, 23 // 오른쪽
		};

		GameEngineVertexBuffer::Create("ContentBox", ArrVertex);
		GameEngineIndexBuffer::Create("ContentBox", ArrIndex);
	}

}

void ContentCore::BlendCreate()
{
	{
		D3D11_BLEND_DESC Desc = { 0, };

		Desc.AlphaToCoverageEnable = false;
		Desc.IndependentBlendEnable = false;

		Desc.RenderTarget[0].BlendEnable = true;
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_MAX;
		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;

		GameEngineBlend::Create("ContentAlphaBlend", Desc);
	}
}

void ContentCore::ShaderCreate()
{
	GameEngineDirectory NewDir;
	NewDir.MoveParentToDirectory("Resources");
	NewDir.Move("Resources");
	NewDir.Move("Shader");

	std::vector<GameEngineFile> Files = NewDir.GetAllFile({ ".hlsl", ".fx" });

	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineVertexShader::Load(Files[i].GetFullPath(), "Texture_VS");
		GameEnginePixelShader::Load(Files[i].GetFullPath(), "Texture_PS");
	}
}

void ContentCore::ContentPipeLineCreate()
{
	{
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("BoxLight");

		Pipe->SetVertexBuffer("ContentBox");
		Pipe->SetIndexBuffer("ContentBox");
		Pipe->SetVertexShader("ContentShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("ContentShader.hlsl");
		Pipe->SetBlendState("ContentAlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTexture_ColorLight");

		Pipe->SetVertexBuffer("Rect");
		Pipe->SetIndexBuffer("Rect");
		Pipe->SetVertexShader("ColorShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("ColorShader.hlsl");
		Pipe->SetBlendState("ContentAlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTexture_Capture");

		Pipe->SetVertexBuffer("Rect");
		Pipe->SetIndexBuffer("Rect");
		Pipe->SetVertexShader("CaptureShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("CaptureShader.hlsl");
		Pipe->SetBlendState("ContentAlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTexture_Background");

		Pipe->SetVertexBuffer("Rect");
		Pipe->SetIndexBuffer("Rect");
		Pipe->SetVertexShader("TextureMoveShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("TextureMoveShader.hlsl");
		Pipe->SetBlendState("ContentAlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTexture_Fade");

		Pipe->SetVertexBuffer("Rect");
		Pipe->SetIndexBuffer("Rect");
		Pipe->SetVertexShader("FadeShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("FadeShader.hlsl");
		Pipe->SetBlendState("ContentAlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTexture_Outline");

		Pipe->SetVertexBuffer("Rect");
		Pipe->SetIndexBuffer("Rect");
		Pipe->SetVertexShader("OutlineColorShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("OutlineColorShader.hlsl");
		Pipe->SetBlendState("ContentAlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTexture_ProgressUI");

		Pipe->SetVertexBuffer("Rect");
		Pipe->SetIndexBuffer("Rect");
		Pipe->SetVertexShader("ProgressUI.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("ProgressUI.hlsl");
		Pipe->SetBlendState("ContentAlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTexture_ProgressUI_Circle");

		Pipe->SetVertexBuffer("Rect");
		Pipe->SetIndexBuffer("Rect");
		Pipe->SetVertexShader("ProgressUI_Circle.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("ProgressUI_Circle.hlsl");
		Pipe->SetBlendState("ContentAlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}
}


void ContentCore::ImGuiCreate()
{
	std::shared_ptr<GameEngineGUIWindow> ActorGUIPtr = GameEngineGUI::GUIWindowCreate<GameEngineActorGUI>("GameEngineActorGUI");	
	ActorGUIPtr->Off();

	std::shared_ptr<GameEngineGUIWindow> MapToolGUIPtr = GameEngineGUI::GUIWindowCreate<MapToolGUI>("MapToolGUI");
	MapToolGUIPtr->Off();

	std::shared_ptr<GameEngineGUIWindow> BackgroundGUIPtr = GameEngineGUI::GUIWindowCreate<BackgroundToolGUI>("BackgroundToolGUI");
	BackgroundGUIPtr->Off();

	std::shared_ptr<GameEngineGUIWindow> LevelMoveGUIPtr = GameEngineGUI::GUIWindowCreate<LevelMoveGUI>("LevelMoveGUI");
	LevelMoveGUIPtr->On();

	std::shared_ptr<GameEngineGUIWindow> AnimationColToolGUIPtr = GameEngineGUI::GUIWindowCreate<AnimationCollisionToolGUI>("AnimationCollisionToolGUI");
	AnimationColToolGUIPtr->Off();
}