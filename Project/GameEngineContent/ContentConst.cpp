#include "PrecompileHeader.h"
#include "ContentConst.h"
#include <GameEngineCore/imgui.h>

//Physics
const float4 ContentConst::Gravity = float4(0.0f, -2000.0f, 0.0f, 0.0f);
const float ContentConst::Gravity_f = -2000.0f;

//Tile
const float4 ContentConst::TileSize = float4(64.0f, 64.0f, 1.0f, 0.0f);

//Goods
const int ContentConst::Goods_Bone_Normal = 5;
const int ContentConst::Goods_Bone_Rare = 11;
const int ContentConst::Goods_Bone_Unique = 23;
const int ContentConst::Goods_Bone_Legendary = 44;

ContentConst::ContentConst()
{
}

ContentConst::~ContentConst()
{
}
