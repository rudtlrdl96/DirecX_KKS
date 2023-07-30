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
#include "GameConsoleGUI.h"
#include "AnimationCollisionToolGUI.h"
#include "TalkboxDebugGUI.h"
#include "ContentLevelLightGUI.h"
#include "FPSCheckGUI.h"

// Player Level
#include "TitleLevel.h"
#include "OpeningLevel.h"
#include "CastleLevel.h"
#include "ForestOfHarmonyLevel.h"
#include "StoryLevel.h"
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
	FontFind();
	VertextBufferCreate();
	BlendCreate();
	ShaderCreate();
	ContentPipeLineCreate();

	SwitchShowCursor();

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
	SoundLoad();
	FontLoad();


	// GameLevel Create
	GameEngineCore::CreateLevel<TitleLevel>("Title");
	GameEngineCore::CreateLevel<OpeningLevel>("Opening");
	GameEngineCore::CreateLevel<CastleLevel>("Castle");
	GameEngineCore::CreateLevel<ForestOfHarmonyLevel>("ForestOfHarmony");
	GameEngineCore::CreateLevel<StoryLevel>("Story");
	GameEngineCore::CreateLevel<EndingLogoLevel>("EndingLogo");
	
	// DebugLevel Create
	GameEngineCore::CreateLevel<MapToolLevel>("MapTool");
	GameEngineCore::CreateLevel<BackgroundToolLevel>("BackgroundTool");
	GameEngineCore::CreateLevel<AnimationColToolLevel>("AnimationColTool");
	GameEngineCore::CreateLevel<BrokenObjectTool>("BrokenObjectTool");

	Inventory::ResetSkull();
	Inventory::ItemReset();

	GameEngineCore::ChangeLevel("Title");
}

void ContentCore::CoreEnd()
{
	FontRemove();
}

void ContentCore::SwitchShowCursor()
{
	static bool MouseCursorShow = true;
	MouseCursorShow = !MouseCursorShow;

	if (true == MouseCursorShow)
	{
		ShowCursor(TRUE);
	}
	else
	{
		ShowCursor(FALSE);
	}
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
		D3D11_SAMPLER_DESC SamperData = {};

		// 
		SamperData.Filter = D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;
		SamperData.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		SamperData.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		SamperData.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		// 텍스처가 멀리있을때 뭉갤꺼냐
		// 안뭉갠다.
		SamperData.MipLODBias = 0.0f;
		SamperData.MaxAnisotropy = 1;
		SamperData.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		SamperData.MinLOD = -FLT_MAX;
		SamperData.MaxLOD = FLT_MAX;

		GameEngineSampler::Create("TEXMOVESAMPLEER", SamperData);
	}

	{
		D3D11_SAMPLER_DESC SamperData = {};
		SamperData.Filter = D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;
		SamperData.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		SamperData.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		SamperData.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		// 텍스처가 멀리있을때 뭉갤꺼냐
		// 안뭉갠다.
		SamperData.MipLODBias = 0.0f;
		SamperData.MaxAnisotropy = 1;
		SamperData.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		SamperData.MinLOD = -FLT_MAX;
		SamperData.MaxLOD = FLT_MAX;

		GameEngineSampler::ReSetting("ENGINEBASE", SamperData);
	}

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
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTexture_ColorLinear");

		Pipe->SetVertexShader("ColorShader_Linear.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("ColorShader_Linear.hlsl");
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


	{
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTexture_BlackAndWhite");

		Pipe->SetVertexShader("BlackAndWhiteShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("BlackAndWhiteShader.hlsl");
		Pipe->SetBlendState("ContentAlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTexture_FixedColor");

		Pipe->SetVertexShader("FixedColorShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("FixedColorShader.hlsl");
		Pipe->SetBlendState("ContentAlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTexture_Minimap");

		Pipe->SetVertexShader("MinimapShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("MinimapShader.hlsl");
		Pipe->SetBlendState("MergeBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("WorldLight");

		Pipe->SetVertexShader("WorldLightShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("WorldLightShader.hlsl");
		Pipe->SetBlendState("MergeBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("PointLight");

		Pipe->SetVertexShader("PointLightShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("PointLightShader.hlsl");
		Pipe->SetBlendState("MergeBlend");
		Pipe->SetDepthState("EngineDepth");
	}		
	
	{
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("AnglePointLight");

		Pipe->SetVertexShader("AnglePointLightShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("AnglePointLightShader.hlsl");
		Pipe->SetBlendState("MergeBlend");
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

	std::shared_ptr<GameEngineGUIWindow> AnimationColToolGUIPtr = GameEngineGUI::GUIWindowCreate<AnimationCollisionToolGUI>("AnimationCollisionToolGUI");
	AnimationColToolGUIPtr->Off();

	std::shared_ptr<GameEngineGUIWindow> TalkboxGUIPtr = GameEngineGUI::GUIWindowCreate<TalkboxDebugGUI>("TalkboxDebugGUI");
	TalkboxGUIPtr->Off();

	std::shared_ptr<GameEngineGUIWindow> LightGUIPtr = GameEngineGUI::GUIWindowCreate<ContentLevelLightGUI>("ContentLevelLightGUI");
	LightGUIPtr->Off();

	std::shared_ptr<GameEngineGUIWindow> FPSGUIPtr = GameEngineGUI::GUIWindowCreate<FPSCheckGUI>("FPSCheckGUI");
	FPSGUIPtr->Off();

	std::shared_ptr<GameEngineGUIWindow> GameConsoleGUIPtr = GameEngineGUI::GUIWindowCreate<GameConsoleGUI>("GameConsoleGUI");
	GameConsoleGUIPtr->On();
}

void ContentCore::FontFind()
{
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("Resources");
		NewDir.Move("Resources");
		NewDir.Move("Font");

		if (0 == AddFontResourceA(NewDir.GetPlusFileName("NEXON Lv2 Gothic Bold.ttf").GetFullPath().data()))
		{
			MsgAssert_Rtti<ContentCore>(" - 폰트 로드에 실패했습니다.");
			return;
		}

		SendMessage(GameEngineWindow::GetHWnd(), WM_FONTCHANGE, NULL, NULL);

		if (0 == AddFontResourceA(NewDir.GetPlusFileName("Perfect DOS VGA 437.ttf").GetFullPath().data()))
		{
			MsgAssert_Rtti<ContentCore>(" - 폰트 로드에 실패했습니다.");
			return;
		}

		SendMessage(GameEngineWindow::GetHWnd(), WM_FONTCHANGE, NULL, NULL);
	}
}

void ContentCore::FontLoad()
{
	GameEngineFont::Load("궁서");
	GameEngineFont::Load("휴먼둥근헤드라인");
	GameEngineFont::Load("HY견고딕");
	GameEngineFont::Load("넥슨Lv2고딕");
	GameEngineFont::Load("Perfect DOS VGA 437");
}

void ContentCore::FontRemove()
{
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("Resources");
		NewDir.Move("Resources");
		NewDir.Move("Font");

		if (0 == RemoveFontResourceA(NewDir.GetPlusFileName("NEXON Lv2 Gothic Bold.ttf").GetFullPath().data()))
		{
			MsgAssert_Rtti<ContentCore>(" - 폰트 로드에 실패했습니다.");
			return;
		}

		SendMessage(GameEngineWindow::GetHWnd(), WM_FONTCHANGE, NULL, NULL);

		if (0 == RemoveFontResourceA(NewDir.GetPlusFileName("Perfect DOS VGA 437.ttf").GetFullPath().data()))
		{
			MsgAssert_Rtti<ContentCore>(" - 폰트 로드에 실패했습니다.");
			return;
		}

		SendMessage(GameEngineWindow::GetHWnd(), WM_FONTCHANGE, NULL, NULL);
	}
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

		Path.MoveParent();
		Path.Move("Effect");

		{
			std::vector<GameEngineFile> Files = Path.GetAllFile({ ".wav" });

			for (size_t i = 0; i < Files.size(); i++)
			{
				GameEngineSound::Load(Files[i].GetFullPath());
			}
		}

	}
}
