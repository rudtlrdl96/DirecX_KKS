#pragma once

enum class TileArea
{
	None,			// µð¹ö±ë¿ë None
	Castle,			// Ä³½½
	ForestOfHamory,	// Á¶È­ÀÇ ½£
	GrandHall,		// ±×·£µå È¦
	SacredGrounds,	// ¼º¿ª
};

class TilemapData
{
public:
	std::string Name = "";
	size_t Index = 0;
	TileArea Grade = TileArea::None;
};