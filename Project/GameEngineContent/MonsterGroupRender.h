#pragma once
#include "BaseContentActor.h"

class MonsterGroupRender : public BaseContentActor
{
public:
	MonsterGroupRender();
	~MonsterGroupRender();

	MonsterGroupRender(const MonsterGroupRender& _Other) = delete;
	MonsterGroupRender(MonsterGroupRender&& _Other) noexcept = delete;
	MonsterGroupRender& operator=(const MonsterGroupRender& _Other) = delete;
	MonsterGroupRender& operator=(MonsterGroupRender&& _Other) noexcept = delete;

	void ShowGroup(const class MonsterGroupMetaData& _GroupMetaData);
	void OffRender();

protected:
	void Start() override;

private:
	std::vector<std::shared_ptr<class MonsterDebugRender>> MonsterRenders;

	size_t OutlienActiveIndex = static_cast<size_t>(-1);
};

