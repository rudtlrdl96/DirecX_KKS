#pragma once
#include <GameEngineCore/GameEngineRenderer.h>


class ContentSlice9Renderer : public GameEngineRenderer
{
public:
	ContentSlice9Renderer();
	~ContentSlice9Renderer();

	ContentSlice9Renderer(const ContentSlice9Renderer& _Other) = delete;
	ContentSlice9Renderer(ContentSlice9Renderer&& _Other) noexcept = delete;
	ContentSlice9Renderer& operator=(const ContentSlice9Renderer& _Other) = delete;
	ContentSlice9Renderer& operator=(ContentSlice9Renderer&& _Other) noexcept = delete;

	void SetTextureAndSlice(const std::string_view& _TextureName, float _Left, float _Right, float _Top, float _Bottom);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Init();

private:
	SliceBuffer Buffer;
	float4 TextureSize = float4::Zero;
	
};