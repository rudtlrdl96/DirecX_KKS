#pragma once
#include "BaseContentActor.h"
#include "MapPlatform.h"

class MapPlatformDebugRender : public BaseContentActor
{
public:
	MapPlatformDebugRender();
	~MapPlatformDebugRender();

	MapPlatformDebugRender(const MapPlatformDebugRender& _Other) = delete;
	MapPlatformDebugRender(MapPlatformDebugRender&& _Other) noexcept = delete;
	MapPlatformDebugRender& operator=(const MapPlatformDebugRender& _Other) = delete;
	MapPlatformDebugRender& operator=(MapPlatformDebugRender&& _Other) noexcept = delete;

	void SetTargetPlatform(MapPlatform* _TargetPaltform);
protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> DebugRender = nullptr;
	ColorBuffer DebugBuffer;

	MapPlatform* ParentPlatform = nullptr;
};
