#pragma once

class MapCollision
{
public:
	MapCollision();
	~MapCollision();

	MapCollision(const MapCollision& _Other) = delete;
	MapCollision(MapCollision&& _Other) noexcept = delete;
	MapCollision& operator=(const MapCollision& _Other) = delete;
	MapCollision& operator=(MapCollision&& _Other) noexcept = delete;

	void SetSize(const float4& _Size);

protected:
	
private:
	float4 ColSize = float4::Zero;
};

