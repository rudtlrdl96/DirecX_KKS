#include "PrecompileHeader.h"
#include "Rigidbody2D.h"

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