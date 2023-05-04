#include "PrecompileHeader.h"
#include "ContentConst.h"
#include <GameEngineCore/imgui.h>

//Physics
const float4 ContentConst::Gravity = float4(0.0f, -9.807f, 0.0f, 0.0f);
const float4 ContentConst::TileSize = float4(64.0f, 64.0f, 0.0f, 0.0f);

ContentConst::ContentConst()
{
}

ContentConst::~ContentConst()
{
}
