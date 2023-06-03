#pragma once
#include "BaseContentActor.h"

class BehaviorObjectMetaData
{
public:
	UINT Index = 0;
	LevelArea Grade = LevelArea::None;

	std::string Name = "";

	float4 Postion = float4::Zero;
	float4 Rotation = float4::Zero;
};

class BehaviorObject : public BaseContentActor
{
	friend class ObjectManager;
public:
	BehaviorObject();
	~BehaviorObject();

	BehaviorObject(const BehaviorObject& _Other) = delete;
	BehaviorObject(BehaviorObject&& _Other) noexcept = delete;
	BehaviorObject& operator=(const BehaviorObject& _Other) = delete;
	BehaviorObject& operator=(BehaviorObject&& _Other) noexcept = delete;

	virtual void ResetBehavior() = 0;
	virtual void PlayBehavior() = 0;

	void SaveBin(GameEngineSerializer& _SaveSerializer);
	virtual void SaveBin_Child(GameEngineSerializer& _SaveSerializer) {}
	static BehaviorObjectMetaData LoadBin(GameEngineSerializer& _LoadSerializer);
	virtual void LoadBin_Child(GameEngineSerializer& _LoadSerializer) {}

	void ShowGUI() override;

	inline void SetMetaData(const BehaviorObjectMetaData& _Data)
	{
		Data = _Data;
	}

	inline BehaviorObjectMetaData& GetMetaData()
	{
		return Data;
	}

	GameEngineTransform* GetRenderTrans()
	{
		return Render->GetTransform();
	}

protected:
	std::shared_ptr<ContentSpriteRenderer> Render = nullptr;
	ColorBuffer Buffer;

	BehaviorObjectMetaData Data;

	void Start() override;
};

