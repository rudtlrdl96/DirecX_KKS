#include "PrecompileHeader.h"
#include "TransformGUI.h"
#include <GameEngineCore/GameEngineLevel.h>

TransformGUI::TransformGUI()
{
}

TransformGUI::~TransformGUI()
{
}

void TransformGUI::OnGUI(std::shared_ptr<GameEngineLevel>, float _DeltaTime)
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
	
	ImGui::Checkbox("W", &IsWorldPostion);
	ImGui::SameLine();
	HelpMarker("Setting World Postion");
	ImGui::SameLine();

	ImGui::DragFloat4(" - Postion", Postion);

	if (true == IsWorldPostion)
	{
		TargetTransform->SetWorldPosition(ConvertFloat4(Postion));
	}
	else
	{
		TargetTransform->SetLocalPosition(ConvertFloat4(Postion));
	}

	ImGui::Checkbox("W", &IsWorldRotation);
	ImGui::SameLine();
	HelpMarker("Setting World Rotation");
	ImGui::SameLine();

	ImGui::DragFloat4(" - Rotation", Rotation);

	if (true == IsWorldRotation)
	{
		TargetTransform->SetWorldRotation(ConvertFloat4(Rotation));
	}
	else
	{
		TargetTransform->SetLocalRotation(ConvertFloat4(Rotation));
	}

	ImGui::Checkbox("W", &IsWorldScale);
	ImGui::SameLine();
	HelpMarker("Setting World Scale");
	ImGui::SameLine();

	ImGui::DragFloat4(" - Scale", Scale);

	if (true == IsWorldScale)
	{
		TargetTransform->SetWorldScale(ConvertFloat4(Scale));
	}
	else
	{
		TargetTransform->SetLocalScale(ConvertFloat4(Scale));
	}
}

void TransformGUI::SetTarget(GameEngineTransform* _Target)
{
	TargetTransform = _Target;

	if (nullptr != TargetTransform)
	{
		IsWorldPostion = false;
		IsWorldRotation = false;
		IsWorldScale = false;

		float4 LocalPos = TargetTransform->GetLocalPosition();
		float4 LocalRotation = TargetTransform->GetLocalRotation();
		float4 LocalScale = TargetTransform->GetLocalScale();

		Postion[0] = LocalPos.x;
		Postion[1] = LocalPos.y;
		Postion[2] = LocalPos.z;
		Postion[3] = LocalPos.w;

		Rotation[0] = LocalRotation.x;
		Rotation[1] = LocalRotation.y;
		Rotation[2] = LocalRotation.z;
		Rotation[3] = LocalRotation.w;

		Scale[0] = LocalScale.x;
		Scale[1] = LocalScale.y;
		Scale[2] = LocalScale.z;
		Scale[3] = LocalScale.w;
	}
}

void TransformGUI::HelpMarker(const std::string_view& _Text)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort) && ImGui::BeginTooltip())
	{
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(_Text.data());
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

float4 TransformGUI::ConvertFloat4(float _FloatArr[4])
{
	return float4(_FloatArr[0], _FloatArr[1], _FloatArr[2], _FloatArr[3]);
}
