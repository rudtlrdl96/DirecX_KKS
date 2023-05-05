#include "PrecompileHeader.h"
#include "MultiBackground.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/imgui.h>

MultiBackground::MultiBackground()
{
}

MultiBackground::~MultiBackground()
{
}

void MultiBackground::CreateBackground(BG_DESC& _Desc)
{
	std::shared_ptr<Background> NewBackground = GetLevel()->CreateActor<Background>();
	NewBackground->SetName(_Desc.Name + " - " + std::to_string(NewBackground->GetActorCode()));
	NewBackground->Init(_Desc);
	BackgroundBuffer.push_back(NewBackground);
}

void MultiBackground::UpdateTargetPos(float _DeltaTime, const float4& _TargetPos)
{
	std::vector<std::shared_ptr<Background>>::iterator LoopIter = BackgroundBuffer.begin();
	std::vector<std::shared_ptr<Background>>::iterator EndIter = BackgroundBuffer.end();

	while (LoopIter != EndIter)
	{
		if (true == (*LoopIter)->IsDeath())
		{
			LoopIter = BackgroundBuffer.erase(LoopIter);
			continue;
		}
		else
		{
			(*LoopIter)->UpdateTargetPos(_DeltaTime, _TargetPos);
			++LoopIter;
		}
	}
}

void MultiBackground::SaveBin(GameEngineSerializer& _SaveSerializer) const
{
	_SaveSerializer.Write(static_cast<int>(BackgroundBuffer.size()));

	for (size_t i = 0; i < BackgroundBuffer.size(); i++)
	{
		BackgroundBuffer[i]->SaveBin(_SaveSerializer);
	}
}

void MultiBackground::LoadBin(GameEngineSerializer& _SaveSerializer)
{
	int BackCount = 0;
	_SaveSerializer.Read(BackCount);

	for (int i = 0; i < BackCount; i++)
	{
		BG_DESC LoadDesc = Background::LoadBin(_SaveSerializer);
		CreateBackground(LoadDesc);
	}
}


void MultiBackground::ShowGUI()
{
	if (ImGui::BeginListBox("BackgroundBox"))
	{
		for (int i = 0; i < BackgroundBuffer.size(); i++)
		{
			const bool is_selected = (CurrentBackgroundIndex == i);

			if (ImGui::Selectable(BackgroundBuffer[i]->GetName().data(), is_selected))
			{
				CurrentBackgroundIndex = i;
			}

			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}

		ImGui::EndListBox();
	}

	//if (true == ImGui::Button("Remove", ImVec2(70, 25)))
	//{
	//	if (CurrentStaticObjectIndex < 0)
	//	{
	//		return;
	//	}
	//
	//	std::vector<std::shared_ptr<StaticObject>>::iterator EraseIter = StaticObjectActors.begin();
	//
	//	EraseIter += CurrentStaticObjectIndex;
	//
	//	(*EraseIter)->Death();
	//	(*EraseIter) = nullptr;
	//	EraseIter = StaticObjectActors.erase(EraseIter);
	//
	//	if (CurrentStaticObjectIndex >= StaticObjectActors.size())
	//	{
	//		CurrentStaticObjectIndex = static_cast<int>(StaticObjectActors.size() - 1);
	//	}
	//
	//	if (StaticObjectActors.size() <= 0)
	//	{
	//		CurrentStaticObjectIndex = -1;
	//	}
	//}
}
