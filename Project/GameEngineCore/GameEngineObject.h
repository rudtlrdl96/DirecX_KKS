#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObjectBase.h"
#include "GameEngineTransform.h"
#include <GameEngineCore/GameEngineNameObject.h>

class GameEngineObject : 
	public GameEngineObjectBase, 
	public GameEngineNameObject,
	public std::enable_shared_from_this<GameEngineObject>
{
	friend class GameEngineComponent;
	friend class GameEngineActor;
	friend class GameEngineCore;
	friend class GameEngineTransform;
	friend class GameEngineLevel;

public:
	GameEngineObject();
	virtual ~GameEngineObject() = 0;

	GameEngineObject(const GameEngineObject& _Other) = delete;
	GameEngineObject(GameEngineObject&& _Other) noexcept = delete;
	GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
	GameEngineObject& operator=(GameEngineObject&& _Other) noexcept = delete;

	GameEngineTransform* GetTransform()
	{
		return &Transform;
	}

	template<typename PtrType>
	std::shared_ptr<PtrType> DynamicThis()
	{
		return std::dynamic_pointer_cast<PtrType>(std::enable_shared_from_this<GameEngineObject>::shared_from_this());
	}


	virtual void AccLiveTime(float _LiveTime)
	{
		LiveTime += _LiveTime;
	}

	void ResetLiveTime()
	{
		LiveTime = 0.0f;
	}

	float GetLiveTime()
	{
		return LiveTime;
	}


	inline class GameEngineLevel* GetLevel() const
	{
		return Level;
	}

	bool IsDeath() override;
	bool IsUpdate() override;

protected:
	virtual void Start() {}
	virtual void Update(float _DeltaTime) {}
	virtual void Render(float _DeltaTime) {}
	virtual void Destroy() {}
	virtual void Release();
	virtual void LevelChangeStart() {}
	virtual void LevelChangeEnd() {}

	void PushChild(std::shared_ptr<GameEngineObject> _Child)
	{
		Childs.push_back(_Child);
	}

private:
	float LiveTime = 0.0f;
	GameEngineTransform Transform;

	class GameEngineLevel* Level;

	std::list<std::shared_ptr<GameEngineObject>> Childs;

	void AllAccTime(float _DeltaTime);
	void AllUpdate(float _DeltaTime);
	void AllRender(float _DeltaTime);
	void AllDestroy();
	void AllRelease();
	void AllLevelChangeStart();
	void AllLevelChangeEnd();
};
