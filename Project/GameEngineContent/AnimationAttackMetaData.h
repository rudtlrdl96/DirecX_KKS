#pragma once

class ColMetaData
{
	friend class AttackColMetaData;
public:
	float4 LocalCenter = float4::Zero;
	float4 LocalSize = float4::Zero;

	void SaveBin(GameEngineSerializer& _SaveSerializer) const;
	void LoadBin(GameEngineSerializer& _LoadSerializer);

private:
	void ShowGUI();
};

class AttackColMetaData
{
	friend class AnimationAttackMetaData;
public:
	std::vector<ColMetaData> ColMetaDatas;

	void SaveBin(GameEngineSerializer& _SaveSerializer) const;
	void LoadBin(GameEngineSerializer& _LoadSerializer);

private:
	void ShowGUI();
};

class AnimationAttackMetaData
{
	friend class AnimationCollisionToolGUI;
public:
	inline std::string GetSpriteName() const
	{
		return SpriteName;
	}

	inline std::string GetAnimationName() const
	{
		return AnimationName;
	}

	inline UINT GetStartFrame() const
	{
		return AnimStart;
	}

	inline UINT GetEndFrame() const
	{
		return AnimEnd;
	}

	const AttackColMetaData& GetAttackMetaData(UINT _Frame);

	void SaveBin(GameEngineSerializer& _SaveSerializer) const;
	void LoadBin(GameEngineSerializer& _LoadSerializer);
private:
	std::string SpriteName = "";
	std::string AnimationName = "";

	UINT AnimStart = 0;
	UINT AnimEnd = 0;

	std::vector<AttackColMetaData> AttackMetaData;

	void Create(const std::string_view& _SpriteName, UINT _Start, UINT _End);
	void Clear();

	void ShowGUI(UINT _Frame);
};