#include "PrecompileHeader.h"
#include "Rigidbody2D.h"
#include <GameEngineCore/imgui.h>

Rigidbody2D::Rigidbody2D()
{
}

Rigidbody2D::~Rigidbody2D()
{
}

void Rigidbody2D::UpdateForce(float _DeltaTime)
{
	if (ForceVector.Size() > 0)
	{
		Accel = ForceVector / Mass;
		Velocity += Accel * _DeltaTime;
	}

	if (true == IsGravity)
	{
		Velocity += float4(0, Gravity) * Mass * _DeltaTime;
	}

	float4 VelDir = Velocity.NormalizeReturn();
	float VelSize = Velocity.Size();
		
	VelSize -= FricCoeff * _DeltaTime;

	if (VelSize > MaxSpeed)
	{
		VelSize = MaxSpeed;
	}
	
	if (VelSize > 0)
	{
		Velocity = VelDir * VelSize;
	}
	else
	{
		Velocity = float4::Zero;
	}


	ForceVector = float4::Zero;
}

void Rigidbody2D::ShowGUI()
{
	float ForceArr[4] = { ForceVector.x, ForceVector.y, ForceVector.z, ForceVector.w };
	ImGui::InputFloat4("Force", ForceArr);

	float AccelArr[4] = { Accel.x, Accel.y, Accel.z, Accel.w };
	ImGui::InputFloat4("Accel", AccelArr);

	float VelocityArr[4] = { Velocity.x, Velocity.y, Velocity.z, Velocity.w };
	ImGui::InputFloat4("Velocity", VelocityArr);

	ImGui::Spacing();

	ImGui::Checkbox("IsGravity", &IsGravity);
	ImGui::DragFloat("Gravity", &Gravity);

	ImGui::Spacing();

	ImGui::DragFloat("MaxSpeed", &MaxSpeed);
	ImGui::DragFloat("Mass", &Mass);
	ImGui::DragFloat("FricCoeff", &FricCoeff);
}