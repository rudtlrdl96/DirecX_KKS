#include "PrecompileHeader.h"
#include "ContentSlice9Renderer.h"

ContentSlice9Renderer::ContentSlice9Renderer()
{
}

ContentSlice9Renderer::~ContentSlice9Renderer()
{
}

void ContentSlice9Renderer::SetTextureAndSlice(const std::string_view& _TextureName, float _Left, float _Right, float _Top, float _Bottom)
{
}

void ContentSlice9Renderer::Start()
{
	GameEngineRenderer::Start();
	Init();
}

void ContentSlice9Renderer::Init()
{
	SetMesh("Rect");
	SetPipeLine("2DTexture_Slice9");
	GetShaderResHelper().SetConstantBufferLink("Slice9Buffer", Buffer);
}