#include "PrecompileHeader.h"
#include "Tilemap.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/imgui.h>
#include "TileActor.h"

Tilemap::Tilemap() :
	TileScale(ContentConst::TileSize)
{
}

Tilemap::~Tilemap()
{
}


void Tilemap::SetDepth(UINT _DepthCount)
{
	if (0 == _DepthCount)
	{		
		return;
	}

	TilemapDatas.reserve(_DepthCount);

	for (UINT i = _DepthCount; i < TilemapDatas.size(); i++)
	{
		std::vector<std::vector<std::shared_ptr<TileActor>>>& TilemapRef = TilemapDatas[i];

		for (UINT y	 = 0; y < TilemapRef.size(); y++)
		{
			for (UINT x = 0; x < TilemapRef[y].size(); x++)
			{
				if (nullptr != TilemapRef[y][x])
				{
					TilemapRef[y][x]->Death();
					TilemapRef[y][x] = nullptr;
				}
			}

			TilemapRef[y].clear();
		}

		TilemapRef.clear();
	}

	TilemapDatas.resize(_DepthCount);

	ResizeTilemap(static_cast<UINT>(TilemapSize.x), static_cast<UINT>(TilemapSize.y));
}

void Tilemap::ResizeTilemap(UINT _SizeX, UINT _SizeY)
{
	int2 PrevTileSize = TilemapSize;
	TilemapSize = int2(_SizeX, _SizeY); 
	Gui_TilemapSize = TilemapSize;

	for (UINT i = 0; i < TilemapDatas.size(); i++)
	{
		std::vector<std::vector<std::shared_ptr<TileActor>>>& TilemapRef = TilemapDatas[i];

		for (UINT y = 0; y < TilemapRef.size(); y++)
		{
			for (UINT x = 0; x < TilemapRef[y].size(); x++)
			{
				if (nullptr != TilemapRef[y][x])
				{
					TilemapRef[y][x]->TileOff();
				}
			}
		}
	}

	for (UINT i = 0; i < TilemapDatas.size(); i++)
	{
		std::vector<std::vector<std::shared_ptr<TileActor>>>& TilemapRef = TilemapDatas[i];

		if (TilemapRef.size() < TilemapSize.y)
		{
			TilemapRef.resize(TilemapSize.y);
		}

		for (UINT y = 0; y < static_cast<UINT>(TilemapSize.y); y++)
		{
			if (TilemapRef[y].size() < TilemapSize.x)
			{
				TilemapRef[y].resize(TilemapSize.x);
			}

			for (UINT x = 0; x < static_cast<UINT>(TilemapSize.x); x++)
			{
				if (nullptr != TilemapRef[y][x])
				{
					TilemapRef[y][x]->TileOn();
				}
			}
		}
	}
}

void Tilemap::ChangeData(int _Depth, const float4& _WorldPos, UINT Index)
{
	int2 InputIndex = GetTileIndex(_WorldPos);

	if (InputIndex.x < 0)
	{
		return;
	}

	if (InputIndex.y < 0)
	{
		return;
	}

	ChangeData(_Depth, InputIndex.x, InputIndex.y, Index);
}

void Tilemap::ChangeData(int _Depth, UINT _X, UINT _Y, UINT Index)
{
	std::vector<std::vector<std::shared_ptr<TileActor>>>& TilemapRef = TilemapDatas[_Depth];
	
	if (true == IsOver(_X, _Y))
	{
		return;
	}

	if (0 == Index)
	{
		ReleseTile(_Depth, _X, _Y);
		return;
	}

	if (nullptr == TilemapRef[_Y][_X])
	{
		CreateTile(_Depth, _X, _Y);
	}

	TilemapRef[_Y][_X]->SetTileData(Index);
}

void Tilemap::ChangeData(int _Depth, UINT _StartX, UINT _EndX, UINT _StartY, UINT _EndY, size_t Index)
{
	if (true == IsOver(_StartX, _StartY))
	{
		return;
	}

	if (true == IsOver(_EndX, _EndY))
	{
		return;
	}

	std::vector<std::vector<std::shared_ptr<TileActor>>>& TilemapRef = TilemapDatas[_Depth];

	for (UINT y = _StartY; y <= _EndY; y++)
	{
		for (UINT x = _StartX; x <= _EndX; x++)
		{
			if (0 == Index)
			{
				ReleseTile(_Depth, x, y);
				continue;
			}

			if (nullptr == TilemapRef[y][x])
			{
				CreateTile(_Depth, x, y);
			}

			TilemapRef[y][x]->SetTileData(Index);
		}
	}
}

void Tilemap::ChangeData(int _Depth, UINT _StartX, UINT _StartY, const std::vector<std::vector<size_t>>& _Indexs)
{ 
	if (_Indexs.size() == 0)
	{
		return;
	}

	if (_Indexs[0].size() == 0)
	{
		return;
	}

	if (true == IsOver(_StartX, _StartY))
	{
		return;
	}

	std::vector<std::vector<std::shared_ptr<TileActor>>>& TilemapRef = TilemapDatas[_Depth];

	for (UINT y = 0; y < _Indexs.size(); y++)
	{
		for (UINT x = 0; x < _Indexs[y].size(); x++)
		{
			if (true == IsOver(_StartX + x, _StartY + y))
			{
				continue;
			}

			TilemapRef[_StartY + y][_StartX + x]->SetTileData(_Indexs[y][x]);
		}
	}
}

void Tilemap::ClearTileMap()
{
	for (UINT i = 0; i < TilemapDatas.size(); i++)
	{
		std::vector<std::vector<std::shared_ptr<TileActor>>>& TilemapRef = TilemapDatas[i];

		for (UINT y = 0; y < TilemapRef.size(); y++)
		{
			for (UINT x = 0; x < TilemapRef[y].size(); x++)
			{
				if (nullptr != TilemapRef[y][x])
				{
					TilemapRef[y][x]->Death();
					TilemapRef[y][x] = nullptr;
				}
			}

			TilemapRef[y].clear();
		}

		TilemapRef.clear();
	}

	TilemapDatas.clear();
	TilemapSize = int2::Zero;
}

bool Tilemap::IsOver(UINT _X, UINT _Y)
{
	if (TilemapSize.x <= static_cast<int>(_X) || TilemapSize.y <= static_cast<int>(_Y))
	{
		return true;
	}

	return false;
}

int2 Tilemap::GetTileIndex(const float4& _WorldPos)
{
	float4 LocalPos = _WorldPos - GetTransform()->GetWorldPosition();

	LocalPos.x += TileScale.hx();
	LocalPos.y += TileScale.y;

	int2 ResultIndex = int2::Zero;

	float IndexFloatX = LocalPos.x / TileScale.x;
	float IndexFloatY = LocalPos.y / TileScale.y;

	if (IndexFloatX < 0)
	{
		ResultIndex.x = static_cast<int>(floorf(IndexFloatX));
	}
	else
	{
		ResultIndex.x = static_cast<int>(IndexFloatX);
	}

	if (IndexFloatY < 0)
	{
		ResultIndex.y = static_cast<int>(floorf(IndexFloatY));
	}
	else
	{
		ResultIndex.y = static_cast<int>(IndexFloatY);
	}

	return ResultIndex;
}

float4 Tilemap::GetTilePos(UINT _X, UINT _Y) const
{
	return float4(static_cast<float>(_X), static_cast<float>(_Y), 0, 0) * TileScale;
}

TilemapMetaData Tilemap::GetTilemapMetaData()
{
	TilemapMetaData Result = TilemapMetaData();

	float4 TilemapPos = GetTransform()->GetWorldPosition();

	TilemapPos.x -= ContentConst::TileSize.hx();
	TilemapPos.y -= ContentConst::TileSize.y;

	Result.Bottom = TilemapPos.y + 128;
	Result.Top	  = TilemapPos.y + (TilemapSize.y * TileScale.y) - 128;
	Result.Left   = TilemapPos.x + 128;
	Result.Right  = TilemapPos.x + (TilemapSize.x * TileScale.x) - 128;

	return Result;
}

void Tilemap::SaveBin(GameEngineSerializer& _SaveSerializer)
{
	if (0 >= TilemapSize.x)
	{
		MsgAssert_Rtti<Tilemap>(" - X 사이즈가 0인 타일맵은 저장할 수 없습니다");
		return;
	}

	if (0 >= TilemapSize.y)
	{
		MsgAssert_Rtti<Tilemap>(" - Y 사이즈가 0인 타일맵은 저장할 수 없습니다");
		return;
	}

	_SaveSerializer.Write(static_cast<UINT>(TilemapDatas.size()));
	_SaveSerializer.Write(static_cast<int>(TilemapSize.x));
	_SaveSerializer.Write(static_cast<int>(TilemapSize.y));

	using namespace std;

	for (UINT i = 0; i < TilemapDatas.size(); i++)
	{
		const vector<vector<shared_ptr<TileActor>>>& TileRef = TilemapDatas[i];

		for (UINT y = 0; y < static_cast<UINT>(TilemapSize.y); y++)
		{
			for (UINT x = 0; x < static_cast<UINT>(TilemapSize.x); x++)
			{
				if (nullptr == TileRef[y][x])
				{
					TileActor::SaveEmptyBin(_SaveSerializer);
				}
				else
				{
					TileRef[y][x]->SaveBin(_SaveSerializer);
				}
			}
		}
	}
}

void Tilemap::SaveBin_TileMetaData(TileMetaData _Meta, GameEngineSerializer& _SaveSerializer)
{
	_SaveSerializer.Write(_Meta.Index);
}

void Tilemap::LoadBin(GameEngineSerializer& _LoadSerializer)
{
	ClearTileMap();

	int DepthCount = 0;
	_LoadSerializer.Read(DepthCount);
	SetDepth(static_cast<UINT>(DepthCount));

	_LoadSerializer.Read(TilemapSize.x);
	_LoadSerializer.Read(TilemapSize.y);

	ResizeTilemap(static_cast<UINT>(TilemapSize.x), static_cast<UINT>(TilemapSize.y));

	for (UINT i = 0; i < static_cast<UINT>(DepthCount); i++)
	{
		for (UINT y = 0; y < static_cast<UINT>(TilemapSize.y); y++)
		{
			for (UINT x = 0; x < static_cast<UINT>(TilemapSize.x); x++)
			{
				UINT LoadIndex = TileActor::LoadBin(_LoadSerializer);
				ChangeData(i, x, y, LoadIndex);
			}
		}
	}
}

TileMetaData Tilemap::LoadBin_TileMetaData(GameEngineSerializer& _SaveSerializer)
{
	TileMetaData LoadMetaData;
	_SaveSerializer.Write(LoadMetaData.Index);
	return LoadMetaData;
}

void Tilemap::ShowGUI()
{
	int InputCurDepth = static_cast<int>(Gui_TilemapCurDepth);
	ImGui::InputInt("Cur Depth", &InputCurDepth);

	if (InputCurDepth < 0)
	{
		InputCurDepth = 0;
	}

	if (InputCurDepth >= TilemapDatas.size())
	{
		InputCurDepth = static_cast<int>(TilemapDatas.size() - 1);
	}

	Gui_TilemapCurDepth = static_cast<UINT>(InputCurDepth);

	int InputDepthCount = static_cast<int>(Gui_TilemapDepthCount);
	ImGui::InputInt("DepthCount", &InputDepthCount);

	if (InputDepthCount < 1)
	{
		InputDepthCount = 1;
	}

	Gui_TilemapDepthCount = static_cast<UINT>(InputDepthCount);

	if (true == ImGui::Button("Depth Resize"))
	{
		SetDepth(InputDepthCount);
	}

	int TileData[2] = { Gui_TilemapSize.x, Gui_TilemapSize.y };
	ImGui::DragInt2("TilemapSize", TileData, 1.0f, 0, 100);

	Gui_TilemapSize.x = TileData[0];
	Gui_TilemapSize.y = TileData[1];

	if (Gui_TilemapSize.x < 1)
	{
		Gui_TilemapSize.x = 1;
	}

	if (Gui_TilemapSize.y < 1)
	{
		Gui_TilemapSize.y = 1;
	}

	if (true == ImGui::Button("Tilemap Resize"))
	{
		ResizeTilemap(static_cast<UINT>(Gui_TilemapSize.x), static_cast<UINT>(Gui_TilemapSize.y));
	}
	else if (true == ImGui::Button("Tilemap Clear"))
	{
		ClearTileMap();
	}

	float ArrowButtonSize = ImGui::GetFrameHeight();

	ImGui::Dummy(ImVec2(ArrowButtonSize, ArrowButtonSize));
	ImGui::SameLine();
	if (true == ImGui::ArrowButton("Tilemap Push Up ArrowButton", ImGuiDir_Up))
	{
		Push_Tilemap_Up(Gui_TilemapCurDepth); 
	}

	if (true == ImGui::ArrowButton("Tilemap Push Left ArrowButton", ImGuiDir_Left))
	{
		Push_Tilemap_Left(Gui_TilemapCurDepth);
	}

	ImGui::SameLine();
	ImGui::Dummy(ImVec2(ArrowButtonSize, ArrowButtonSize));
	ImGui::SameLine();
	if (true == ImGui::ArrowButton("Tilemap Push Right ArrowButton", ImGuiDir_Right))
	{
		Push_Tilemap_Right(Gui_TilemapCurDepth);
	}

	ImGui::Dummy(ImVec2(ArrowButtonSize, ArrowButtonSize));
	ImGui::SameLine();
	if (true == ImGui::ArrowButton("Tilemap Push Down ArrowButton", ImGuiDir_Down))
	{
		Push_Tilemap_Down(Gui_TilemapCurDepth);
	}

}

void Tilemap::CreateTile(UINT _Depth, UINT _X, UINT _Y)
{
	std::shared_ptr<TileActor> NewTile = GetLevel()->CreateActor<TileActor>();
	NewTile->GetTransform()->SetParent(GetTransform());

	float4 TilePos = GetTilePos(_X, _Y);
	TilePos.z = _Depth * 10.0f;

	NewTile->GetTransform()->SetLocalPosition(TilePos);
	NewTile->SetTileData(0);

	TilemapDatas[_Depth][_Y][_X] = NewTile;
}

void Tilemap::ReleseTile(UINT _Depth, UINT _X, UINT _Y)
{
	if (true == IsOver(_X, _Y))
	{
		return;
	}

	if (nullptr != TilemapDatas[_Depth][_Y][_X])
	{
		TilemapDatas[_Depth][_Y][_X]->Death();
		TilemapDatas[_Depth][_Y][_X] = nullptr;
	}
}

void Tilemap::Push_Tilemap_Up(UINT _Depth)
{
	if (_Depth >= TilemapDatas.size())
	{
		return;
	}

	if (TilemapSize.x <= 0 || TilemapSize.y <= 0)
	{
		return;
	}

	std::vector<std::vector<std::shared_ptr<TileActor>>>& TilemapRef = TilemapDatas[_Depth];

	for (int y = TilemapSize.y - 2; y >= 0; y--)
	{
		for (int x = 0; x < TilemapSize.x; x++)
		{
			if (nullptr == TilemapRef[y][x])
			{
				ChangeData(_Depth, static_cast<UINT>(x), static_cast<UINT>(y + 1), 0);
			}
			else
			{
				ChangeData(_Depth, static_cast<UINT>(x), static_cast<UINT>(y + 1), TilemapRef[y][x]->GetTileIndex());
			}

		}
	}

	for (UINT x = 0; x < static_cast<UINT>(TilemapSize.x); x++)
	{
		ChangeData(_Depth, x, 0, 0);
	}
}

void Tilemap::Push_Tilemap_Down(UINT _Depth)
{
	if (_Depth >= TilemapDatas.size())
	{
		return;
	}

	if (TilemapSize.x <= 0 || TilemapSize.y <= 0)
	{
		return;
	}

	std::vector<std::vector<std::shared_ptr<TileActor>>>& TilemapRef = TilemapDatas[_Depth];

	for (int y = 1; y < TilemapSize.y; y++)
	{
		for (int x = 0; x < TilemapSize.x; x++)
		{
			if (nullptr == TilemapRef[y][x])
			{
				ChangeData(_Depth, static_cast<UINT>(x), static_cast<UINT>(y - 1), 0);
			}
			else
			{
				ChangeData(_Depth, static_cast<UINT>(x), static_cast<UINT>(y - 1), TilemapRef[y][x]->GetTileIndex());
			}

		}
	}

	UINT EmptyIndexY = static_cast<UINT>(TilemapSize.y - 1);

	for (UINT x = 0; x < static_cast<UINT>(TilemapSize.x); x++)
	{
		ChangeData(_Depth, x, EmptyIndexY, 0);
	}
}

void Tilemap::Push_Tilemap_Left(UINT _Depth)
{
	if (_Depth >= TilemapDatas.size())
	{
		return;
	}

	if (TilemapSize.x <= 0 || TilemapSize.y <= 0)
	{
		return;
	}

	std::vector<std::vector<std::shared_ptr<TileActor>>>& TilemapRef = TilemapDatas[_Depth];

	for (int y = 0; y < TilemapSize.y; y++)
	{
		for (int x = 1; x < TilemapSize.x; x++)
		{
			if (nullptr == TilemapRef[y][x])
			{
				ChangeData(_Depth, static_cast<UINT>(x - 1), static_cast<UINT>(y), 0);
			}
			else
			{
				ChangeData(_Depth, static_cast<UINT>(x - 1), static_cast<UINT>(y), TilemapRef[y][x]->GetTileIndex());
			}

		}
	}

	UINT EmptyIndexX = static_cast<UINT>(TilemapSize.x - 1);

	for (UINT y = 0; y < static_cast<UINT>(TilemapSize.y); y++)
	{
		ChangeData(_Depth, EmptyIndexX, y, 0);
	}
}

void Tilemap::Push_Tilemap_Right(UINT _Depth)
{
	if (_Depth >= TilemapDatas.size())
	{
		return;
	}

	if (TilemapSize.x <= 0 || TilemapSize.y <= 0)
	{
		return;
	}

	std::vector<std::vector<std::shared_ptr<TileActor>>>& TilemapRef = TilemapDatas[_Depth];

	for (int y = 0; y < TilemapSize.y; y++)
	{
		for (int x = TilemapSize.x - 2; x >= 0; x--)
		{
			if (nullptr == TilemapRef[y][x])
			{
				ChangeData(_Depth, static_cast<UINT>(x + 1), static_cast<UINT>(y), 0);
			}
			else
			{
				ChangeData(_Depth, static_cast<UINT>(x + 1), static_cast<UINT>(y), TilemapRef[y][x]->GetTileIndex());
			}

		}
	}

	for (UINT y = 0; y < static_cast<UINT>(TilemapSize.y); y++)
	{
		ChangeData(_Depth, 0, y, 0);
	}
}
