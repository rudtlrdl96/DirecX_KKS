#pragma once
#include "BaseContentActor.h"

class MonsterDebugRender : public BaseContentActor
{
public:
	MonsterDebugRender();
	~MonsterDebugRender();

	MonsterDebugRender(const MonsterDebugRender& _Other) = delete;
	MonsterDebugRender(MonsterDebugRender&& _Other) noexcept = delete;
	MonsterDebugRender& operator=(const MonsterDebugRender& _Other) = delete;
	MonsterDebugRender& operator=(MonsterDebugRender&& _Other) noexcept = delete;

	void SetScaleToTexture(const std::string_view& _TextureName);
	
	inline void SetOutlineColor(const float4& _Color)
	{
		Buffer.OutlineColor = _Color;
	}

protected:
	void Start() override;

private:
	std::shared_ptr<ContentSpriteRenderer> Redner = nullptr;
	
	OutlineColorBuffer Buffer;

};

