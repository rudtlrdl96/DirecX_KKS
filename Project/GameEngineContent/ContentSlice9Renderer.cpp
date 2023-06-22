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

	TextureSize = FindTex->GetScale();
	TextureSize.z = 1.0f;

	GetTransform()->SetLocalScale(TextureSize);
	GetShaderResHelper().SetTexture("DiffuseTex", _TextureName);

	Buffer.BorderSize.x = _Left;
	Buffer.BorderSize.y = _Right;
	Buffer.BorderSize.z = _Top;
	Buffer.BorderSize.w = _Bottom;

	Buffer.TexturePer.x = 2.0f;
	Buffer.TexturePer.y = 2.0f;
}

void ContentSlice9Renderer::Start()
{
	SetMesh("Rect");
	PushCameraRender(0);
	Init();
}

void ContentSlice9Renderer::Update(float _DeltaTime)
{
	Buffer.RenderScale = GetTransform()->GetWorldScale();
}

void ContentSlice9Renderer::Init()
{
	SetPipeLine("2DTexture_Slice");
	GetShaderResHelper().SetConstantBufferLink("SliceBuffer", Buffer);
}