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
#include "TalkboxDebugGUI.h"

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
#include "MapToolLevel.h"
#include "BackgroundToolLevel.h"
#include "AnimationColToolLevel.h"
#include "BrokenObjectTool.h"

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
	ObjectLoad();
	BackgroundDataLoad();
	NPCDataLoad();

	// Common Load
	CommonTextureLoad();
	ImGuiCreate();
	FontLoad();
	SoundLoad();

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
	GameEngineCore::CreateLevel<MapToolLevel>("MapTool");
	GameEngineCore::CreateLevel<BackgroundToolLevel>("BackgroundTool");
	GameEngineCore::CreateLevel<AnimationColToolLevel>("AnimationColTool");
	GameEngineCore::CreateLevel<BrokenObjectTool>("BrokenObjectTool");

	Inventory::ResetSkull();

	GameEngineCore::ChangeLevel("ForestOfHarmony");

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

		// ¾Õ¸é
		ArrVertex[0] = ContentVertex(float4{ -0.5f, 0.5f, -0.5f }, { UV1Div3, UV1Div3 }, float4{ -0.5f, 0.5f, -0.5f }.NormalizeReturn());
		ArrVertex[1] = ContentVertex(float4{ 0.5f, 0.5f, -0.5f }, { UV2Div3, UV1Div3 }, float4{ 0.5f, 0.5f, -0.5f }.NormalizeReturn());
		ArrVertex[2] = ContentVertex(float4{ 0.5f, -0.5f, -0.5f }, { UV2Div3, UV2Div3 }, float4{ 0.5f, -0.5f, -0.5f }.NormalizeReturn());
		ArrVertex[3] = ContentVertex(float4{ -0.5f, -0.5f, -0.5f }, { UV1Div3, UV2Div3 }, float4{ -0.5f, -0.5f, -0.5f }.NormalizeReturn());

		// µÞ¸é
		ArrVertex[4] = ContentVertex(float4{ -0.5f, -0.5f, 0.5f }, { UV2Div3, UV2Div3 }, float4{ -0.5f, -0.5f, 0.5f }.NormalizeReturn());
		ArrVertex[5] = ContentVertex(float4{ 0.5f, -0.5f , 0.5f }, { 1.0f, UV2Div3 }, float4{ 0.5f, -0.5f , 0.5f }.NormalizeReturn());
		ArrVertex[6] = ContentVertex(float4{ 0.5f, 0.5f  , 0.5f }, { 1.0f, 1.0f }, float4{ 0.5f, 0.5f  , 0.5f }.NormalizeReturn());
		ArrVertex[7] = ContentVertex(float4{ -0.5f, 0.5f, 0.5f }, { UV2Div3, 1.0f }, float4{ -0.5f, 0.5f, 0.5f }.NormalizeReturn());

		// À­¸é
		ArrVertex[8] = ContentVertex(float4{ -0.5f , 0.5f , 0.5f }, { UV1Div3, 0.0f }, float4{ -0.5f , 0.5f , 0.5f }.NormalizeReturn());
		ArrVertex[9] = ContentVertex(float4{ 0.5f, 0.5f , 0.5f }, { UV2Div3, 0.0f }, float4{ 0.5f, 0.5f , 0.5f }.NormalizeReturn());
		ArrVertex[10] = ContentVertex(float4{ 0.5f, 0.5f, -0.5f }, { UV2Div3, UV1Div3 }, float4{ 0.5f, 0.5f, -0.5f }.NormalizeReturn());
		ArrVertex[11] = ContentVertex(float4{ -0.5f, 0.5f, -0.5f }, { UV1Div3, UV1Div3 }, float4{ -0.5f, 0.5f, -0.5f }.NormalizeReturn());

		// ¾Æ·§¸é
		ArrVertex[12] = ContentVertex(float4{ -0.5f, -0.5f, -0.5f }, { UV1Div3, UV2Div3 }, float4{ -0.5f, -0.5f, -0.5f }.NormalizeReturn());
		ArrVertex[13] = ContentVertex(float4{ 0.5f, -0.5f, -0.5f }, { UV2Div3, UV2Div3 }, float4{ 0.5f, -0.5f, -0.5f }.NormalizeReturn());
		ArrVertex[14] = ContentVertex(float4{ 0.5f, -0.5f, 0.5f }, { UV2Div3, 1.0f }, float4{ 0.5f, -0.5f, 0.5f }.NormalizeReturn());
		ArrVertex[15] = ContentVertex(float4{ -0.5f , -0.5f, 0.5f }, { UV1Div3, 1.0f }, float4{ -0.5f , -0.5f, 0.5f }.NormalizeReturn());

		// ¿ÞÂÊ¸é
		ArrVertex[16] = ContentVertex(float4{ -0.5f, 0.5f, 0.5f }, { 0.0f, UV1Div3 }, float4{ -0.5f, 0.5f, 0.5f }.NormalizeReturn());
		ArrVertex[17] = ContentVertex(float4{ -0.5f, 0.5f, -0.5f }, { UV1Div3, UV1Div3 }, float4{ -0.5f, 0.5f, -0.5f }.NormalizeReturn());
		ArrVertex[18] = ContentVertex(float4{ -0.5f, -0.5f, -0.5f }, { UV1Div3, UV2Div3 }, float4{ -0.5f, -0.5f, -0.5f }.NormalizeReturn());
		ArrVertex[19] = ContentVertex(float4{ -0.5f, -0.5f , 0.5f }, { 0.0f, UV2Div3 }, float4{ -0.5f, -0.5f , 0.5f }.NormalizeReturn());

		// ¿À¸¥ÂÊ¸é
		ArrVertex[20] = ContentVertex(float4{ 0.5f, 0.5f, -0.5f }, { UV2Div3, UV1Div3 }, float4{ 0.5f, 0.5f, -0.5f }.NormalizeReturn());
		ArrVertex[21] = ContentVertex(float4{ 0.5f , 0.5f, 0.5f }, { 1.0f, UV1Div3 }, float4{ 0.5f , 0.5f, 0.5f }.NormalizeReturn());
		ArrVertex[22] = ContentVertex(float4{ 0.5f , -0.5f , 0.5f }, { 1.0f, UV2Div3 }, float4{ 0.5f , -0.5f , 0.5f }.NormalizeReturn());
		ArrVertex[23] = ContentVertex(float4{ 0.5f, -0.5f, -0.5f }, { UV2Div3, UV2Div3 }, float4{ 0.5f, -0.5f, -0.5f }.NormalizeReturn());


		std::vector<UINT> ArrIndex = {
			 0, 1, 2, 0, 2, 3, // ¾Õ¸é
			 4, 5, 6, 4, 6, 7, // µÞ¸é
			 8, 9, 10, 8, 10, 11, // À§
			 12, 13, 14, 12, 14, 15, // ¾Æ·¡
			 16, 17, 18, 16, 18, 19, // ¿ÞÂÊ
			 20, 21, 22, 20, 22, 23 // ¿À¸¥ÂÊ
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

		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;

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

		Pipe->SetVertexShader("ContentShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("ContentShader.hlsl");
		Pipe->SetBlendState("ContentAlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTexture_Color");

		Pipe->SetVertexShader("ColorShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("ColorShader.hlsl");
		Pipe->SetBlendState("ContentAlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTexture_Capture");

		Pipe->SetVertexShader("CaptureShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("CaptureShader.hlsl");
		Pipe->SetBlendState("ContentAlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTexture_Background");

		Pipe->SetVertexShader("TextureMoveShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("TextureMoveShader.hlsl");
		Pipe->SetBlendState("ContentAlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTexture_Fade");

		Pipe->SetVertexShader("FadeShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("FadeShader.hlsl");
		Pipe->SetBlendState("ContentAlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTexture_Outline");

		Pipe->SetVertexShader("OutlineColorShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("OutlineColorShader.hlsl");
		Pipe->SetBlendState("ContentAlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTexture_ProgressUI");

		Pipe->SetVertexShader("ProgressUI.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("ProgressUI.hlsl");
		Pipe->SetBlendState("ContentAlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTexture_ProgressUI_Circle");

		Pipe->SetVertexShader("ProgressUI_Circle.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("ProgressUI_Circle.hlsl");
		Pipe->SetBlendState("ContentAlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTexture_Object");

		Pipe->SetVertexShader("ObjectColorShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("ObjectColorShader.hlsl");
		Pipe->SetBlendState("ContentAlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTexture_Slice");

		Pipe->SetVertexShader("SliceShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("SliceShader.hlsl");
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

	std::shared_ptr<GameEngineGUIWindow> TalkboxGUIPtr = GameEngineGUI::GUIWindowCreate<TalkboxDebugGUI>("TalkboxDebugGUI");
	TalkboxGUIPtr->Off();
}

void ContentCore::FontLoad()
{
	GameEngineFont::Load("±Ã¼­");
	GameEngineFont::Load("³Ø½¼Lv2°íµñ");
	GameEngineFont::Load("ÈÞ¸ÕµÕ±ÙÇìµå¶óÀÎ");
	GameEngineFont::Load("ÈÞ¸ÕµÕ±ÙÇìµå¶óÀÎSimBold");
	GameEngineFont::Load("HY°ß°íµñ");
	GameEngineFont::Load("Perfect DOS VGA 437");
}

void ContentCore::SoundLoad()
{
	{
		GameEngineDirectory Path;
		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Sound");
		Path.Move("BGM");

		{
			std::vector<GameEngineFile> Files = Path.GetAllFile({ ".wav" });

			for (size_t i = 0; i < Files.size(); i++)
			{
				GameEngineSound::Load(Files[i].GetFullPath());
			}
		}


		Path.MoveParent();
		Path.Move("UI");

		{
			std::vector<GameEngineFile> Files = Path.GetAllFile({ ".wav" });

			for (size_t i = 0; i < Files.size(); i++)
			{
				GameEngineSound::Load(Files[i].GetFullPath());
			}
		}
	}
}
