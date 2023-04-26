#include "PrecompileHeader.h"
#include "ContentCore.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineVertexShader.h>
#include <GameEngineCore/GameEnginePixelShader.h>
#include <GameEngineCore/GameEngineRenderingPipeLine.h>
#include <GameEngineCore/GameEngineVertexBuffer.h>
#include <GameEngineCore/GameEngineIndexBuffer.h>

// Vertext
#include "ContentVertex.h"

// Player Level
#include "LogoLevel.h"
#include "OpeningLevel.h"
#include "CastleLevel.h"
#include "ForestOfHarmonyLevel.h"
#include "GrandHallLevel.h"
#include "HolyCourtyardLevel.h"
#include "StoryLevel.h"
#include "ShopLevel.h"

// Debug Level
#include "ShaderDebugLevel.h"
#include "BattleDebugLevel.h"

ContentCore::ContentCore()
{
}

ContentCore::~ContentCore()
{
}

void ContentCore::CoreLoading()
{
	VertextBufferCreate();
	ShaderCreate();
	ContentPipeLineCreate();

	// DB Load
	ItemDataLoad();
	SkullDataLoad();
	QuintessenceDataLoad();
	MonsterDataLoad();
	TimeDataLoad();

	// GameLevel Create
	GameEngineCore::CreateLevel<LogoLevel>("Logo");
	GameEngineCore::CreateLevel<OpeningLevel>("Opening");
	GameEngineCore::CreateLevel<CastleLevel>("Castle");
	GameEngineCore::CreateLevel<ForestOfHarmonyLevel>("ForestOfHarmony");
	GameEngineCore::CreateLevel<HolyCourtyardLevel>("HolyCourtyard");
	GameEngineCore::CreateLevel<StoryLevel>("Story");
	GameEngineCore::CreateLevel<ShopLevel>("Shop");
	
	// DebugLevel Create
	GameEngineCore::CreateLevel<ShaderDebugLevel>("ShaderDebug");
	GameEngineCore::CreateLevel<BattleDebugLevel>("BattleDebug");
	GameEngineCore::ChangeLevel("BattleDebug");

	if (false == GameEngineInput::IsKey("LevelMove_ShaderDebug"))
	{
		GameEngineInput::CreateKey("LevelMove_ShaderDebug", VK_NUMPAD7);
		GameEngineInput::CreateKey("LevelMove_BattleDebug", VK_NUMPAD8);
		GameEngineInput::CreateKey("LevelMove_BackPrevLevel", VK_NUMPAD0);
	}
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
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}

	{
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTexture_ColorLight");

		Pipe->SetVertexBuffer("Rect");
		Pipe->SetIndexBuffer("Rect");
		Pipe->SetVertexShader("ColorShader.hlsl");
		Pipe->SetRasterizer("Engine2DBase");
		Pipe->SetPixelShader("ColorShader.hlsl");
		Pipe->SetBlendState("AlphaBlend");
		Pipe->SetDepthState("EngineDepth");
	}
}