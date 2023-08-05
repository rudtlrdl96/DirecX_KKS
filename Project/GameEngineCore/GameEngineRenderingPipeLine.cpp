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
		MsgAssert("���ؽ� ���̴��� �������� �ʾƼ� ���ؽ� ���̴� ������ ������ �� �����ϴ�.");
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
		MsgAssert("�����Ͷ������� �������� �ʾƼ� ������ �Ұ����մϴ�.");
		return;
	}

	RasterizerPtr->SetFILL_MODE(FILL_MODE);
	RasterizerPtr->Setting();
}


void GameEngineRenderingPipeLine::PixelShader() 
{
	if (nullptr == PixelShaderPtr)
	{
		MsgAssert("�ȼ� ���̴��� �������� �ʾƼ� �ȼ� ���̴� ������ ������ �� �����ϴ�.");
		return;
	}

	PixelShaderPtr->Setting();
}
void GameEngineRenderingPipeLine::OutputMerger() 
{
	if (nullptr == BlendStatePtr)
	{
		MsgAssert("���尡 �������� �ʾ� �ƿ�ǲ ���� ������ �Ϸ��Ҽ��� �����ϴ�.");
		return;
	}


	BlendStatePtr->Setting();

	if (nullptr == DepthStatePtr)
	{
		MsgAssert("���尡 �������� �ʾ� �ƿ�ǲ ���� ������ �Ϸ��Ҽ��� �����ϴ�.");
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
		MsgAssert("�������� �ʴ� ���ؽ� ���̴��� ����Ϸ��� �߽��ϴ�.");
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
		MsgAssert("�������� �ʴ� �ȼ� ���̴��� ����Ϸ��� �߽��ϴ�.");
	}
}

void GameEngineRenderingPipeLine::SetBlendState(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	BlendStatePtr = GameEngineBlend::Find(UpperName);

	if (nullptr == BlendStatePtr)
	{
		MsgAssert("�������� �ʴ� ���带 �����Ϸ��� �߽��ϴ�.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetDepthState(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	DepthStatePtr = GameEngineDepthState::Find(UpperName);

	if (nullptr == DepthStatePtr)
	{
		MsgAssert("�������� �ʴ� ���̹��� ������Ʈ�� �����Ϸ��� �߽��ϴ�.");
		return;
	}
}

void GameEngineRenderingPipeLine::SetRasterizer(const std::string_view& _Value)
{
	std::string UpperName = GameEngineString::ToUpper(_Value);
	RasterizerPtr = GameEngineRasterizer::Find(UpperName);

	if (nullptr == RasterizerPtr)
	{
		MsgAssert("�������� �ʴ� �����Ͷ������� ����Ϸ��� �߽��ϴ�.");
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