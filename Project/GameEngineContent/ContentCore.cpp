#include "PrecompileHeader.h"
#include "ContentCore.h"
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
		ArrVertex.resize(8);

		// 앞면
		// 0   1
		// 3   2

		// 뒷면
		// 4   5
		// 7   6

		ArrVertex[0] = ContentVertex(float4{-0.5f, 0.5f, -0.5f  }, {0.0f, 1.0f}, float4{-0.5f, 0.5f, -0.5f  }.NormalizeReturn());
		ArrVertex[1] = ContentVertex(float4{ 0.5f, 0.5f, -0.5f  }, {0.0f, 1.0f}, float4{ 0.5f, 0.5f, -0.5f  }.NormalizeReturn());
		ArrVertex[2] = ContentVertex(float4{ 0.5f, -0.5f, -0.5f }, {0.0f, 1.0f}, float4{ 0.5f, -0.5f, -0.5f }.NormalizeReturn());
		ArrVertex[3] = ContentVertex(float4{ -0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}, float4{ -0.5f, -0.5f, -0.5f}.NormalizeReturn());
		ArrVertex[4] = ContentVertex(float4{ -0.5f, 0.5f , 0.5f }, {0.0f, 1.0f}, float4{ -0.5f, 0.5f , 0.5f }.NormalizeReturn());
		ArrVertex[5] = ContentVertex(float4{ 0.5f , 0.5f , 0.5f }, {0.0f, 1.0f}, float4{ 0.5f , 0.5f , 0.5f }.NormalizeReturn());
		ArrVertex[6] = ContentVertex(float4{ 0.5f , -0.5f, 0.5f }, {0.0f, 1.0f}, float4{ 0.5f , -0.5f, 0.5f }.NormalizeReturn());
		ArrVertex[7] = ContentVertex(float4{ -0.5f, -0.5f, 0.5f }, {0.0f, 1.0f}, float4{ -0.5f, -0.5f, 0.5f }.NormalizeReturn());

		std::vector<UINT> ArrIndex = {
			 0, 1, 2, 0, 2, 3, // 앞면
			 5, 4, 7, 5, 7, 6, // 뒷면
			 4, 0, 3, 4, 3, 7, // 왼쪽
			 1, 5, 6, 1, 6, 2, // 오른쪽
			 4, 5, 1, 4, 1, 0, // 위
			 3, 2, 6, 3, 6, 7 // 아래
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

	GameEngineCore::CreateLevel<LogoLevel>("Logo");
	GameEngineCore::CreateLevel<ShaderDebugLevel>("ShaderDebug");
	GameEngineCore::ChangeLevel("ShaderDebug");
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
		Pipe->SetRasterizer("EngineBase");
		Pipe->SetPixelShader("ContentShader.hlsl");
	}
}