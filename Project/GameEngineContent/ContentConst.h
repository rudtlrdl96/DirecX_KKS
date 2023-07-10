#pragma once
#include <GameEngineBase/GameEngineMath.h>

class ContentConst sealed
{
public:
	//Physics
	static const float4 Gravity;
	static const float Gravity_f;

	// Tile
	static const float4 TileSize;

	// Goods
	static const int Goods_Bone_Normal;
	static const int Goods_Bone_Rare;
	static const int Goods_Bone_Unique;
	static const int Goods_Bone_Legendary;


private:
	ContentConst();
	~ContentConst();

	ContentConst(const ContentConst& _Other) = delete;
	ContentConst(ContentConst&& _Other) noexcept = delete;
	ContentConst& operator=(const ContentConst& _Other) = delete;
	ContentConst& operator=(ContentConst&& _Other) noexcept = delete;
};