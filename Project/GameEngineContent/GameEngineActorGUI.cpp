#include "PrecompileHeader.h"
#include "GameEngineActorGUI.h"
#include <GameEngineCore/GameEngineLevel.h>

GameEngineActorGUI::GameEngineActorGUI()
{
}

GameEngineActorGUI::~GameEngineActorGUI()
{
}

void GameEngineActorGUI::SetTarget(GameEngineTransform* _Target, const std::vector<std::function<void()>>& _CustomActorGuiFunctions)
{
	if (TargetTransform == _Target)
	{
		return;
	}

	CustomActorGuiFunctions.clear();
	TargetTransform = _Target;

	if (nullptr != TargetTransform)
	{
		IsWorldPosition = false;
		IsWorldRotation = false;
		IsWorldScale = false;

		float4 LocalPos = TargetTransform->GetLocalPosition();
		float4 LocalRotation = TargetTransform->GetLocalRotation();
		float4 LocalScale = TargetTransform->GetLocalScale();

		Position[0] = LocalPos.x;
		Position[1] = LocalPos.y;
		Position[2] = LocalPos.z;
		Position[3] = LocalPos.w;

		Rotation[0] = LocalRotation.x;
		Rotation[1] = LocalRotation.y;
		Rotation[2] = LocalRotation.z;
		Rotation[3] = LocalRotation.w;

		Scale[0] = LocalScale.x;
		Scale[1] = LocalScale.y;
		Scale[2] = LocalScale.z;
		Scale[3] = LocalScale.w;

	}

	for (size_t i = 0; i < _CustomActorGuiFunctions.size(); i++)
	{
		CustomActorGuiFunctions.push_back(_CustomActorGuiFunctions[i]);
	}
}

void GameEngineActorGUI::Start()
{
	ImGui::SetWindowSize(GetName().data(), ImVec2(300, 150));
}

void GameEngineActorGUI::OnGUI(std::shared_ptr<GameEngineLevel>, float _DeltaTime)
{
	if (nullptr == TargetTransform)
	{
		return;
	}

	if (true == TargetTransform->IsDeath())
	{
		TargetTransform = nullptr;
		return;
	}
	
	ImGui::Checkbox("W", &IsWorldPosition);
	ImGui::SameLine();
	ContentFunc::ImGuiHelpMarker("Setting World Position");
	ImGui::SameLine();

	float4 GetPosition = float4::Zero; 

	if (true == IsWorldPosition)
	{
		TargetTransform->SetWorldPosition(TargetTransform->GetWorldPosition());
		GetPosition = TargetTransform->GetWorldPosition();
	}
	else
	{
		TargetTransform->SetLocalPosition(TargetTransform->GetLocalPosition());
		GetPosition = TargetTransform->GetLocalPosition();
	}

	Position[0] = GetPosition.x;
	Position[1] = GetPosition.y;
	Position[2] = GetPosition.z;
	Position[3] = GetPosition.w;

	ImGui::DragFloat4(" - Position", Position);

	if (true == IsWorldPosition)
	{
		TargetTransform->SetWorldPosition(ContentFunc::ConvertFloat4(Position));
	}
	else
	{
		TargetTransform->SetLocalPosition(ContentFunc::ConvertFloat4(Position));
	}

	ImGui::Checkbox("W", &IsWorldRotation);
	ImGui::SameLine();
	ContentFunc::ImGuiHelpMarker("Setting World Rotation");
	ImGui::SameLine();

	float4 GetRoation = float4::Zero;

	if (true == IsWorldRotation)
	{
		TargetTransform->SetWorldRotation(TargetTransform->GetWorldRotation());
		GetRoation = TargetTransform->GetWorldRotation();
	}
	else
	{
		TargetTransform->SetLocalRotation(TargetTransform->GetLocalRotation());
		GetRoation = TargetTransform->GetLocalRotation();
	}

	Rotation[0] = GetRoation.x;
	Rotation[1] = GetRoation.y;
	Rotation[2] = GetRoation.z;
	Rotation[3] = GetRoation.w;

	ImGui::DragFloat4(" - Rotation", Rotation);

	if (true == IsWorldRotation)
	{
		TargetTransform->SetWorldRotation(ContentFunc::ConvertFloat4(Rotation));
	}
	else
	{
		TargetTransform->SetLocalRotation(ContentFunc::ConvertFloat4(Rotation));
	}

	ImGui::Checkbox("W", &IsWorldScale);
	ImGui::SameLine();
	ContentFunc::ImGuiHelpMarker("Setting World Scale");
	ImGui::SameLine();

	float4 GetScale = float4::Zero;

	if (true == IsWorldScale)
	{
		TargetTransform->SetWorldScale(TargetTransform->GetWorldScale());
		GetScale = TargetTransform->GetWorldScale();
	}
	else
	{
		TargetTransform->SetLocalScale(TargetTransform->GetLocalScale());
		GetScale = TargetTransform->GetLocalScale();
	}

	Scale[0] = GetScale.x;
	Scale[1] = GetScale.y;
	Scale[2] = GetScale.z;
	Scale[3] = GetScale.w;

	ImGui::DragFloat4(" - Scale", Scale);

	if (true == IsWorldScale)
	{
		TargetTransform->SetWorldScale(ContentFunc::ConvertFloat4(Scale));
	}
	else
	{
		TargetTransform->SetLocalScale(ContentFunc::ConvertFloat4(Scale));
	}

	for (std::function<void()>& _CallbackRef: CustomActorGuiFunctions)
	{	

		if (nullptr == _CallbackRef)
		{
			continue;
		}

		ImGui::Spacing();
		ImGui::Spacing();

		_CallbackRef();
	}
}
