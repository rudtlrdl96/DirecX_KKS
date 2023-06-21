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
	std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find(_TextureName);

	GetShaderResHelper().SetTexture("DiffuseTex", _TextureName);

	Buffer.TextureScale = FindTex->GetScale();
	GetTransform()->SetLocalScale(Buffer.TextureScale);
	
	Buffer.Pivot.x = _Left;
	Buffer.Pivot.y = _Right;
	Buffer.Pivot.z = _Top;
	Buffer.Pivot.w = _Bottom;
}

void ContentSlice9Renderer::Start()
{
	SetMesh("Rect");
	PushCameraRender(0);
	Init();
}



void ContentSlice9Renderer::Init()
{
	SetPipeLine("2DTexture_Slice");
	GetShaderResHelper().SetConstantBufferLink("SliceBuffer", Buffer);
	GetShaderResHelper().SetConstantBufferLink("PixelScaleBuffer", GetTransform()->GetWorldPosition());
}