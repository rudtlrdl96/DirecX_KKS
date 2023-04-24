#pragma once

enum class TileArea
{
	None,			// ������ None
	Castle,			// ĳ��
	ForestOfHamory,	// ��ȭ�� ��
	GrandHall,		// �׷��� Ȧ
	SacredGrounds,	// ����
};

class TilemapData
{
public:
	std::string Name = "";
	size_t Index = 0;
	TileArea Grade = TileArea::None;
};