#include "PrecompileHeader.h"
#include "BaseGear.h"

BaseGear::BaseGear()
{
}

BaseGear::~BaseGear()
{
}

void BaseGear::Start()
{
	Render = CreateComponent<ContentSpriteRenderer>();

	Render->PipeSetting("2DTexture_BlackAndWhite");
	Render->GetShaderResHelper().SetConstantBufferLink("BlackAndWihteBuffer", Buffer);

	GetContentLevel()->AddEvent("MoveStage", GetActorCode(), [this]()
		{
			Death();
		});
}

void BaseGear::Update(float _DeltaTime)
{
}

void BaseGear::Destroy()
{
	GetContentLevel()->RemoveEvent("MoveStage", GetActorCode());
	PlayDestroyEffect();
}

void BaseGear::PlayDestroyEffect()
{
}
