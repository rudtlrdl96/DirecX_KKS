#pragma once
#include "ContentLevel.h"

class MapToolLevel : public ContentLevel
{
public:
	MapToolLevel();
	~MapToolLevel();

	MapToolLevel(const MapToolLevel& _Other) = delete;
	MapToolLevel(MapToolLevel&& _Other) noexcept = delete;
	MapToolLevel& operator=(const MapToolLevel& _Other) = delete;
	MapToolLevel& operator=(MapToolLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:


};

