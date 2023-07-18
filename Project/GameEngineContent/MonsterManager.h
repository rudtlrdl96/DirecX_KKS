#pragma once
#include "BaseContentActor.h"
#include "BaseMonster.h"

class MonsterSpawnMetaData
{
public:
	size_t Index = 0;
	float4 SpawnPos = float4::Zero;

	std::shared_ptr<BaseMonster> MonsterSpawn(GameEngineLevel* _SpawnLevel, GameEngineTransform* _Parent);

	void SaveBin(GameEngineSerializer& _SaveSerializer) const;
	void LoadBin(GameEngineSerializer& _LoadSerializer);

	// GUI
	void ShowGUI();
};

class MonsterGroupMetaData
{
public:
	UINT WaveNumber = 0;

	bool IsSpawnEnd = false;
	bool IsCollision = false;
	
	float4 ColCenter = float4::Zero;
	float4 ColScale = float4::Zero;

	std::vector<MonsterSpawnMetaData> SpawnMonsters;
	
	void WaveSpawn(GameEngineLevel* _SpawnLevel, GameEngineTransform* _Parent, std::vector<std::shared_ptr<BaseMonster>>& _WaveGroup);

	void AddMonster(size_t _Index, const float4& _Pos);

	void SaveBin(GameEngineSerializer& _SaveSerializer) const;
	void LoadBin(GameEngineSerializer& _LoadSerializer);

	// GUI
	UINT GUI_SelectMonster = 0;

	void ShowGUI();
};


class MonsterManager : public BaseContentActor
{
	friend class MapToolLevel;
public:
	MonsterManager();
	~MonsterManager();

	MonsterManager(const MonsterManager& _Other) = delete;
	MonsterManager(MonsterManager&& _Other) noexcept = delete;
	MonsterManager& operator=(const MonsterManager& _Other) = delete;
	MonsterManager& operator=(MonsterManager&& _Other) noexcept = delete;

	void SaveBin(GameEngineSerializer& _SaveSerializer) const;
	void LoadBin(GameEngineSerializer& _LoadSerializer);

	// GUI
	void ShowGUI();

	inline void SetMapToolManager()
	{
		IsMapTool = true;
	}

	inline bool IsSpawnEnd() const
	{
		bool SpawnCheck = true;

		for (size_t i = 0; i < MonsterActors.size(); i++)
		{
			if (0 != MonsterActors[i].size())
			{
				SpawnCheck = true;
			}
		}

		return CurWave >= WaveDatas.size() && SpawnCheck;
	}

	void ResetMonster();

	size_t GetMonsterCount() const;

protected:
	void Start() override;
	void Update(float _DeltaTime);

private:
	std::vector<std::vector<std::shared_ptr<BaseMonster>>> MonsterActors;
	std::vector<std::vector<MonsterGroupMetaData>> WaveDatas;

	std::shared_ptr<GameEngineCollision> WaveCollision = nullptr;

	UINT CurWave = 0;

	void InsertWave(int _Index);
	void RemoveWave(int _Index);

	void InsertGroup(int _Index);
	void RemoveGroup(int _Index);

	void AddMonster(size_t _Index, const float4& _Pos);

	// GUI
	int GUI_SelectWave = 0;
	int GUI_SelectGroup = 0;

	bool IsMapTool = false;	
	bool IsMonsterAllDeathCheck = false;

	std::shared_ptr<class MonsterGroupRender> GUI_GroupRenders;
	std::shared_ptr<class ScaleDebugRender> GUI_GroupColRender;

};