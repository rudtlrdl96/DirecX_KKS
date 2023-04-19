#include "PrecompileHeader.h"
#include "ContentCore.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineVertexShader.h>
#include <GameEngineCore/GameEnginePixelShader.h>
#include <GameEngineCore/GameEngineRenderingPipeLine.h>
#include "LogoLevel.h"

ContentCore::ContentCore()
{
}

ContentCore::~ContentCore()
{
}

void ContentCore::CoreLoading()
{
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("Resources");
		NewDir.Move("Resources");
		NewDir.Move("Shader");

		std::vector<GameEngineFile> Files = NewDir.GetAllFile({ ".hlsl", ".fx" });

		GameEngineVertexShader::Load(Files[0].GetFullPath(), "Texture_VS");
		GameEnginePixelShader::Load(Files[0].GetFullPath(), "Texture_PS");
	}

	{
		std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Find("2DTexture");

		Pipe->SetVertexShader("ContentShader.hlsl");
		Pipe->SetPixelShader("ContentShader.hlsl");
	}

	GameEngineCore::CreateLevel<LogoLevel>("Logo");
	GameEngineCore::ChangeLevel("Logo");
}

void ContentCore::CoreEnd()
{

}