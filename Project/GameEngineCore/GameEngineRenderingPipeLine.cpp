#include "PrecompileHeader.h"
#include "GameEngineRenderingPipeLine.h"
#include <GameEngineCore/GameEngineDevice.h>
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineRasterizer.h"
#include "GameEnginePixelShader.h"
#include "GameEngineBlend.h"
#include "GameEngineInputLayOut.h"
#include "GameEngineDepthState.h"

GameEngineRenderingPipeLine::GameEngineRenderingPipeLine() 
{
}

GameEngineRenderingPipeLine::~GameEngineRenderingPipeLine() 
{
}

void GameEngineRenderingPipeLine::VertexShader()
{
	if (nullptr == VertexShaderPtr)
	{
		MsgAssert("버텍스 쉐이더가 존재하지 않아서 버텍스 쉐이더 과정을 실행할 수 없습니다.");
		return;
	}

	VertexShaderPtr->Setting();
}

void GameEngineRenderingPipeLine::HullShader() 
{

}
void GameEngineRenderingPipeLine::Tessellator() 
{

}
void GameEngineRenderingPipeLine::DomainShader() 
{

}
void GameEngineRenderingPipeLine::GeometryShaeder() 
{

}

void GameEngineRenderingPipeLine::Rasterizer() 
{
	if (nullptr == RasterizerPtr)
	{
		MsgAssert("레스터라이저가 존재하지 않아서 세팅이 불가능합니다.");
		return;
	}

	RasterizerPtr->SetFILL_MODE(FILL_MODE);
	RasterizerPtr->Setting();
}


void GameEngineRenderingPipeLine::PixelShader() 
{
	if (nullptr == PixelShaderPtr)
	{
		MsgAssert("픽셀 쉐이더가 존재하지 않아서 픽셀 쉐이더 과정을 실행할 수 없습니다.");
		return;
	}

	PixelShaderPtr->Setting();
}
void GameEngineRenderingPipeLine::OutputMerger() 
{
	if (nullptr == BlendStatePtr)
	{
		MsgAssert("블랜드가 존재하지 않아 아웃풋 머저 과정을 완료할수가 없습니다.");
		return;
	}


	BlendStatePtr->Setting();

	if (nullptr == DepthStatePtr)
	{
		MsgAssert("블랜드가 존재하지 않아 아웃풋 머저 과정을 완료할수가 없습니다.");
		return;
	}
	DepthStatePtr->Setting();
}

void GameEngineRenderingPipeLine::SetVertexShader(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	VertexShaderPtr = GameEngineVertexShader::Find(UpperName);

	if (nullptr == VertexShaderPtr)
	{
		MsgAssert("존재하지 않는 버텍스 쉐이더를 사용하려고 했습니다.");
	}

	if (nullptr == VertexBufferPtr)
	{
		return;
	}
}


void GameEngineRenderingPipeLine::SetPixelShader(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	PixelShaderPtr = GameEnginePixelShader::Find(UpperName);

	if (nullptr == PixelShaderPtr)
	{
		MsgAssert("존재하지 않는 픽셀 쉐이더를 사용하려고 했습니다.");
	}
}

void GameEngineRenderingPipeLine::SetBlendState(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	BlendStatePtr = GameEngineBlend::Find(UpperName);

	if (nullptr == BlendStatePtr)
	{
		MsgAssert("존재하지 않는 블랜드를 세팅하려고 했습니다.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetDepthState(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	DepthStatePtr = GameEngineDepthState::Find(UpperName);

	if (nullptr == DepthStatePtr)
	{
		MsgAssert("존재하지 않는 깊이버퍼 스테이트를 세팅하려고 했습니다.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetRasterizer(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	RasterizerPtr = GameEngineRasterizer::Find(UpperName);

	if (nullptr == RasterizerPtr)
	{
		MsgAssert("존재하지 않는 레스터라이저를 사용하려고 했습니다.");
	}
}

void GameEngineRenderingPipeLine::RenderingPipeLineSetting()
{
	// InputAssembler1();
	VertexShader();
	// InputAssembler2();
	HullShader();
	Tessellator();
	DomainShader();
	GeometryShaeder();
	Rasterizer();
	PixelShader();
	OutputMerger();
}

void GameEngineRenderingPipeLine::Render()
{
}

std::shared_ptr<GameEngineRenderingPipeLine> GameEngineRenderingPipeLine::Clone() 
{
	std::shared_ptr<GameEngineRenderingPipeLine> ClonePipe = std::make_shared<GameEngineRenderingPipeLine>();

	ClonePipe->VertexBufferPtr = VertexBufferPtr;
	ClonePipe->VertexShaderPtr = VertexShaderPtr;
	ClonePipe->RasterizerPtr = RasterizerPtr;
	ClonePipe->PixelShaderPtr = PixelShaderPtr;
	ClonePipe->BlendStatePtr = BlendStatePtr;
	ClonePipe->DepthStatePtr = DepthStatePtr;
	ClonePipe->IsCloneValue = true;

	return ClonePipe;
}