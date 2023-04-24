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
	ContentVertex::LayOut.AddInputLayOut("POSITION", DXGI_FORMAT_R32G32B32A32_FLOAT);
	ContentVertex::LayOut.AddInputLayOut("TEXCOORD", DXGI_FORMAT_R32G32B32A32_FLOAT);
	ContentVertex::LayOut.AddInputLayOut("NORMAL", DXGI_FORMAT_R32G32B32A32_FLOAT);

	{
		std::vector<ContentVertex> ArrVertex;
		ArrVertex.resize(24);

		float UV1Div3 = 1.0f / 3.0f;
		float UV2Div3 = 2.0f / 3.0f;

		// ¾Õ¸é
		ArrVertex[0] = ContentVertex(float4{-0.5f, 0.5f, -0.5f  }, { UV1Div3, UV1Div3 }, float4{-0.5f, 0.5f, -0.5f  }.NormalizeReturn());
		ArrVertex[1] = ContentVertex(float4{ 0.5f, 0.5f, -0.5f  }, { UV2Div3, UV1Div3 }, float4{ 0.5f, 0.5f, -0.5f  }.NormalizeReturn());
		ArrVertex[2] = ContentVertex(float4{ 0.5f, -0.5f, -0.5f }, { UV2Div3, UV2Div3 }, float4{ 0.5f, -0.5f, -0.5f }.NormalizeReturn());
		ArrVertex[3] = ContentVertex(float4{ -0.5f, -0.5f, -0.5f}, { UV1Div3, UV2Div3 }, float4{ -0.5f, -0.5f, -0.5f}.NormalizeReturn());
		
		// µÞ¸é
		ArrVertex[4] = ContentVertex(float4{ -0.5f, -0.5f, 0.5f }, { UV2Div3, UV2Div3 }, float4{ -0.5f, -0.5f, 0.5f }.NormalizeReturn());
		ArrVertex[5] = ContentVertex(float4{ 0.5f, -0.5f , 0.5f }, { 1.0f, UV2Div3 }, float4{ 0.5f, -0.5f , 0.5f }.NormalizeReturn());
		ArrVertex[6] = ContentVertex(float4{ 0.5f, 0.5f  , 0.5f }, { 1.0f, 1.0f}, float4{ 0.5f, 0.5f  , 0.5f }.NormalizeReturn());
		ArrVertex[7] = ContentVertex(float4{ -0.5f, 0.5f, 0.5f  }, { UV2Div3, 1.0f}, float4{ -0.5f, 0.5f, 0.5f  }.NormalizeReturn());

		// À­¸é
		ArrVertex[8] = ContentVertex(float4{ -0.5f , 0.5f , 0.5f }, { UV1Div3, 0.0f }, float4{ -0.5f , 0.5f , 0.5f }.NormalizeReturn());
		ArrVertex[9] = ContentVertex(float4{ 0.5f, 0.5f , 0.5f },   { UV2Div3, 0.0f }, float4{ 0.5f, 0.5f , 0.5f }.NormalizeReturn());
		ArrVertex[10] = ContentVertex(float4{ 0.5f, 0.5f, -0.5f },  { UV2Div3, UV1Div3 }, float4{ 0.5f, 0.5f, -0.5f }.NormalizeReturn());
		ArrVertex[11] = ContentVertex(float4{ -0.5f, 0.5f, -0.5f }, { UV1Div3, UV1Div3 }, float4{ -0.5f, 0.5f, -0.5f }.NormalizeReturn());
		
		// ¾Æ·§¸é
		ArrVertex[12] = ContentVertex(float4{ -0.5f, -0.5f, -0.5f },{ UV1Div3, UV2Div3 }, float4{ -0.5f, -0.5f, -0.5f }.NormalizeReturn());
		ArrVertex[13] = ContentVertex(float4{ 0.5f, -0.5f, -0.5f }, { UV2Div3, UV2Div3 }, float4{ 0.5f, -0.5f, -0.5f }.NormalizeReturn());
		ArrVertex[14] = ContentVertex(float4{ 0.5f, -0.5f, 0.5f },  { UV2Div3, 1.0f }, float4{ 0.5f, -0.5f, 0.5f }.NormalizeReturn());
		ArrVertex[15] = ContentVertex(float4{ -0.5f , -0.5f, 0.5f },{ UV1Div3, 1.0f }, float4{ -0.5f , -0.5f, 0.5f }.NormalizeReturn());
		
		// ¿ÞÂÊ¸é
		ArrVertex[16] = ContentVertex(float4{ -0.5f, 0.5f, 0.5f },  { 0.0f, UV1Div3 }, float4{ -0.5f, 0.5f, 0.5f }.NormalizeReturn());
		ArrVertex[17] = ContentVertex(float4{ -0.5f, 0.5f, -0.5f }, { UV1Div3, UV1Div3 }, float4{ -0.5f, 0.5f, -0.5f }.NormalizeReturn());
		ArrVertex[18] = ContentVertex(float4{ -0.5f, -0.5f, -0.5f },{ UV1Div3, UV2Div3 }, float4{ -0.5f, -0.5f, -0.5f }.NormalizeReturn());
		ArrVertex[19] = ContentVertex(float4{ -0.5f, -0.5f , 0.5f },{ 0.0f, UV2Div3 }, float4{ -0.5f, -0.5f , 0.5f }.NormalizeReturn());
		
		// ¿À¸¥ÂÊ¸é
		ArrVertex[20] = ContentVertex(float4{ 0.5f, 0.5f, -0.5f },  { UV2Div3, UV1Div3 }, float4{ 0.5f, 0.5f, -0.5f }.NormalizeReturn());
		ArrVertex[21] = ContentVertex(float4{ 0.5f , 0.5f, 0.5f },  { 1.0f, UV1Div3 }, float4{ 0.5f , 0.5f, 0.5f }.NormalizeReturn());
		ArrVertex[22] = ContentVertex(float4{ 0.5f , -0.5f , 0.5f },{ 1.0f, UV2Div3}, float4{ 0.5f , -0.5f , 0.5f }.NormalizeReturn());
		ArrVertex[23] = ContentVertex(float4{ 0.5f, -0.5f, -0.5f }, { UV2Div3, UV2Div3}, float4{ 0.5f, -0.5f, -0.5f }.NormalizeReturn());


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

	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("Resources");
		NewDir.Move("Resources");
		NewDir.Move("Shader");

		std::vector<GameEngineFile> Files = NewDir.GetAllFile({ ".hlsl", ".fx" });

		GameEngineVertexShader::Load(Files[0].GetFullPath(), "Texture_VS");
		GameEnginePixelShader::Load(Files[0].GetFullPath(), "Texture_PS");
	}

	ContentPipeLineCreate();

	// DB Load
	ItemDataLoad();
	SkullDataLoad();
	QuintessenceDataLoad();
	MonsterDataLoad();
	TimeDataLoad();

	GameEngineCore::CreateLevel<LogoLevel>("Logo");
	GameEngineCore::CreateLevel<ShaderDebugLevel>("ShaderDebug");
	GameEngineCore::CreateLevel<BattleDebugLevel>("BattleDebug");
	GameEngineCore::ChangeLevel("BattleDebug");

	if (false == GameEngineInput::IsKey("LevelMove_ShaderDebug"))
	{
		GameEngineInput::CreateKey("LevelMove_ShaderDebug", VK_NUMPAD7);
		GameEngineInput::CreateKey("LevelMove_BattleDebug", VK_NUMPAD8);
	}
}

void ContentCore::CoreEnd()
{

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
		Pipe->SetBlend("AlphaBlend");
	}
}