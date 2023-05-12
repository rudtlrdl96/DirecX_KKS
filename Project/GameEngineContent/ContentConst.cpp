#include "PrecompileHeader.h"
#include "ContentConst.h"
#include <GameEngineCore/imgui.h>

//Physics
const float4 ContentConst::Gravity = float4(0.0f, -200.0f, 0.0f, 0.0f);
const float ContentConst::Gravity_f = -1000.0f;
const float4 ContentConst::TileSize = float4(64.0f, 64.0f, 1.0f, 0.0f);

ContentConst::ContentConst()
{
}

ContentConst::~ContentConst()
{
}
