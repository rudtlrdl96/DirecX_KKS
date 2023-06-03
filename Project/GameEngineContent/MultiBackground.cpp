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

void MultiBackground::CreateBackground(BackgroundMetaData& _MetaData)
{
	std::shared_ptr<Background> NewBackground = GetLevel()->CreateActor<Background>();
	NewBackground->GetTransform()->SetParent(GetTransform());
	NewBackground->SetName(_MetaData.Name + " - " + std::to_string(NewBackground->GetActorCode()));
	NewBackground->Init(_MetaData);

	CurrentBackgroundIndex = static_cast<int>(BackgroundBuffer.size());
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
	ClearBackground();

	int BackCount = 0;
	_SaveSerializer.Read(BackCount);

	for (int i = 0; i < BackCount; i++)
	{
		BackgroundMetaData LoadMetaData = Background::LoadBin(_SaveSerializer);
		CreateBackground(LoadMetaData);
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

	if (0 <= CurrentBackgroundIndex && BackgroundBuffer.size() > CurrentBackgroundIndex)
	{
		ImGui::Spacing();
		ImGui::Spacing();

		if (true == ImGui::Button("Remove", ImVec2(70, 25)))
		{
			std::vector<std::shared_ptr<Background>>::iterator EraseIter = BackgroundBuffer.begin();

			EraseIter += CurrentBackgroundIndex;

			(*EraseIter)->Death();
			(*EraseIter) = nullptr;
			EraseIter = BackgroundBuffer.erase(EraseIter);

			if (CurrentBackgroundIndex >= BackgroundBuffer.size())
			{
				CurrentBackgroundIndex = static_cast<int>(BackgroundBuffer.size() - 1);
			}

			if (BackgroundBuffer.size() <= 0)
			{
				CurrentBackgroundIndex = -1;
				return;
			}
		}

		std::shared_ptr<Background> BackPtr = BackgroundBuffer[CurrentBackgroundIndex];

		BackgroundMetaData& MetaDataRef = BackPtr->GetMetaDataRef();
		TextureMoveBuffer& BufferRef = BackPtr->GetShaderBuffer();

		float4 CenterPosition = MetaDataRef.Center;
		float CenterArrPosition[4] = { CenterPosition.x, CenterPosition.y, CenterPosition.z, CenterPosition.w };
		ImGui::DragFloat4("Center", CenterArrPosition);
		float4 ResultCenter = ContentFunc::ConvertFloat4(CenterArrPosition);

		if (CenterPosition != ResultCenter)
		{
			MetaDataRef.Center = ResultCenter;
		}

		ImGui::Checkbox("IsActive LeftRender", &MetaDataRef.IsLeftRender);

		if (true == MetaDataRef.IsLeftRender)
		{
			BackPtr->CreateLeftRender();
		}
		else
		{
			BackPtr->ReleaseLeftRender();
		}

		ImGui::Checkbox("IsActive RightRender", &MetaDataRef.IsRightRender);

		if (true == MetaDataRef.IsRightRender)
		{
			BackPtr->CreateRightRedner();
		}
		else
		{
			BackPtr->ReleaseRightRender();
		}

		{
			float4 ShaderColor = BufferRef.OutColor;
			float ShaderArrColor[4] = { ShaderColor.x, ShaderColor.y, ShaderColor.z, ShaderColor.w };
			ImGui::ColorEdit4("Color", ShaderArrColor, ImGuiColorEditFlags_HDR | ImGuiColorEditFlags_AlphaBar);
			float4 ResultColor = ContentFunc::ConvertFloat4(ShaderArrColor);

			BufferRef.OutColor = ResultColor;
		}
		
		{
			float4 ShaderColor = BufferRef.LightColor;
			float ShaderArrColor[4] = { ShaderColor.x, ShaderColor.y, ShaderColor.z, ShaderColor.w };
			ImGui::ColorEdit4("LightColor", ShaderArrColor, ImGuiColorEditFlags_HDR | ImGuiColorEditFlags_AlphaBar);
			float4 ResultColor = ContentFunc::ConvertFloat4(ShaderArrColor);

			BufferRef.LightColor = ResultColor;
		}

		float BackScale = MetaDataRef.TextureScale;
		ImGui::DragFloat("Scale", &BackScale, 0.01f);

		if (BackScale != MetaDataRef.TextureScale)
		{
			BackPtr->ResizeTextureScale(BackScale);
		}

		ImGui::DragFloat("Ratio", &MetaDataRef.MoveRatio, 0.01f);

		ImGui::Checkbox("Is Animation", &MetaDataRef.Animation);

		if (true == MetaDataRef.Animation)
		{
			ImGui::DragFloat("Animation Speed", &MetaDataRef.AnimationSpeed, 0.01f);
		}
	}

	
}

void MultiBackground::ClearBackground()
{
	for (size_t i = 0; i < BackgroundBuffer.size(); i++)
	{
		BackgroundBuffer[i]->Death();
		BackgroundBuffer[i] = nullptr;
	}

	BackgroundBuffer.clear();
}
