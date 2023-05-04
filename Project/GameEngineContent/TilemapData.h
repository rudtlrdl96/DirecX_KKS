#pragma once

enum class TileArea
{
	None,			// µð¹ö±ë¿ë None
	Opening,		// ¿ÀÇÁ´×
	Castle,			// Ä³½½
	ForestOfHamory,	// Á¶È­ÀÇ ½£
	GrandHall,		// ±×·£µå È¦
	SacredGrounds,	// ¼º¿ª
};

class TilemapData
{
public:
	std::string Name = "";
	UINT Index = 0;
	TileArea Grade = TileArea::None;
};