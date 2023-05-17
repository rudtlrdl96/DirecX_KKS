#include "PrecompileHeader.h"
#include "AnimationAttackMetaData.h"
#include <GameEngineCore/imgui.h>

////////////////////
/// ColMetaData  ///
////////////////////

void ColMetaData::SaveBin(GameEngineSerializer& _SaveSerializer) const
{
	_SaveSerializer.Write(&LocalCenter, sizeof(float4));
	_SaveSerializer.Write(&LocalSize, sizeof(float4));
}

void ColMetaData::LoadBin(GameEngineSerializer& _LoadSerializer)
{
	_LoadSerializer.Read(&LocalCenter, sizeof(float4));
	_LoadSerializer.Read(&LocalSize, sizeof(float4));
}

void ColMetaData::ShowGUI()
{
	float Center[4] = { LocalCenter.x, LocalCenter.y, LocalCenter.z, LocalCenter.w };
	ImGui::DragFloat4("Center", Center);

	LocalCenter.x = Center[0];
	LocalCenter.y = Center[1];
	LocalCenter.z = Center[2];
	LocalCenter.w = Center[3];

	float Size[4] = { LocalSize.x, LocalSize.y, LocalSize.z, LocalSize.w };
	ImGui::DragFloat4("Size", Size);

	LocalSize.x = Size[0];
	LocalSize.y = Size[1];
	LocalSize.z = Size[2];
	LocalSize.w = Size[3];
}

/////////////////////////
/// AttackColMetaData ///
/////////////////////////

void AttackColMetaData::SaveBin(GameEngineSerializer& _SaveSerializer) const
{
	_SaveSerializer.Write(static_cast<int>(ColMetaDatas.size()));

	for (size_t i = 0; i < ColMetaDatas.size(); i++)
	{
		ColMetaDatas[i].SaveBin(_SaveSerializer);
	}
}

void AttackColMetaData::LoadBin(GameEngineSerializer& _LoadSerializer)
{
	int Size = 0;

	_LoadSerializer.Read(Size);
	ColMetaDatas.resize(Size);

	for (int i = 0; i < ColMetaDatas.size(); i++)
	{
		ColMetaDatas[i].LoadBin(_LoadSerializer);
	}
}

void AttackColMetaData::ShowGUI()
{
	int Count = static_cast<int>(ColMetaDatas.size());

	ImGui::InputInt("ColCount", &Count);

	if (0 > Count)
	{
		Count = 0;
	}

	if (Count != ColMetaDatas.size())
	{
		ColMetaDatas.resize(Count);
	}

	if (0 == ColMetaDatas.size())
	{
		return;
	}

	if (ImGui::BeginListBox("Col ListBox"))
	{
		static int SelectCol = 0;

		if (SelectCol < 0)
		{
			SelectCol = 0;
		}

		if (SelectCol >= ColMetaDatas.size())
		{
			SelectCol = static_cast<int>(ColMetaDatas.size() - 1);
		}

		for (int n = 0; n < ColMetaDatas.size(); n++)
		{
			const bool is_selected = (SelectCol == n);

			if (ImGui::Selectable(std::string("Col, " + std::to_string(n)).c_str(), is_selected))
			{
				SelectCol = n;
			}

			// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}

		ImGui::EndListBox();

		if(true == ImGui::Button("Copy"))
		{
			ColMetaData& NewData = ColMetaDatas.emplace_back();

			NewData.LocalCenter = ColMetaDatas[SelectCol].LocalCenter;
			NewData.LocalSize = ColMetaDatas[SelectCol].LocalSize;

		}
		ImGui::SameLine();
		if (true == ImGui::Button("Remove"))
		{
			std::vector<ColMetaData>::iterator Iter = ColMetaDatas.begin();
			Iter += SelectCol;

			ColMetaDatas.erase(Iter);
			return;
		}

		ColMetaDatas[SelectCol].ShowGUI();
	}
}

////////////////////////////////
/// AnimationAttackMetaData  ///
////////////////////////////////

void AnimationAttackMetaData::Create(const std::string_view& _SpriteName, UINT _Start, UINT _End)
{
	if (0 != AttackMetaData.size())
	{
		Clear();
	}

	int AnimCount = _End - _Start + 1;

	if (0 >= AnimCount)
	{
		return;
	}

	SpriteName = _SpriteName;
	AttackMetaData.resize(AnimCount);
}

void AnimationAttackMetaData::Clear()
{
	SpriteName = "";
	AnimationName = "";
	AttackMetaData.clear();
}

const AttackColMetaData& AnimationAttackMetaData::GetAttackMetaData(UINT _Frame)
{
	return AttackMetaData[_Frame];
}

void AnimationAttackMetaData::SaveBin(GameEngineSerializer& _SaveSerializer) const
{
	_SaveSerializer.Write(SpriteName);
	_SaveSerializer.Write(AnimationName);

	_SaveSerializer.Write(static_cast<int>(AttackMetaData.size()));


	for (size_t i = 0; i < AttackMetaData.size(); i++)
	{
		AttackMetaData[i].SaveBin(_SaveSerializer);
	}
}

void AnimationAttackMetaData::LoadBin(GameEngineSerializer& _LoadSerializer)
{
	Clear();

	_LoadSerializer.Read(SpriteName);
	_LoadSerializer.Read(AnimationName);

	int Size = 0;
	_LoadSerializer.Read(Size);
	AttackMetaData.resize(Size);

	for (int i = 0; i < AttackMetaData.size(); i++)
	{
		AttackMetaData[i].LoadBin(_LoadSerializer);
	}
}

void AnimationAttackMetaData::ShowGUI(UINT _Frame)
{
	if (_Frame >= AttackMetaData.size())
	{
		return;
	}

	char Input[255] = { };
	strcpy_s(Input, 255, AnimationName.c_str());

	ImGui::InputText("Animation Name", Input, IM_ARRAYSIZE(Input));
	AnimationName = Input;

	AttackMetaData[_Frame].ShowGUI();
}