#pragma once
#include "BaseContentActor.h"
#include "ItemData.h"

class InventorySynergyGrade : public BaseContentActor
{
public:
	InventorySynergyGrade();
	~InventorySynergyGrade();

	InventorySynergyGrade(const InventorySynergyGrade& _Other) = delete;
	InventorySynergyGrade(InventorySynergyGrade&& _Other) noexcept = delete;
	InventorySynergyGrade& operator=(const InventorySynergyGrade& _Other) = delete;
	InventorySynergyGrade& operator=(InventorySynergyGrade&& _Other) noexcept = delete;

	void UpdateSynergyData(Synergy _Synergy, int _Grade);

	inline void FullGradeColorOn()
	{
		IsFullGradeColorOn = true;
	}

protected:
	
private:
	std::vector<std::shared_ptr<GameEngineUIRenderer>> GradeArrows;
	std::vector<std::shared_ptr<ContentUIFontRenderer>> GradeFonts;

	float4 ActiveFontColor = float4(0.898f, 0.8235f, 0.745f, 1.0f);
	float4 DisableFontColor = float4(0.6118f, 0.5059f, 0.3804f, 1.0f);
	float4 FullGradeFontColor = float4(0.984f, 0.835f, 0.24f, 1.0f);

	bool IsFullGradeColorOn = false;

	void CreateGradeArrow();
	void CreateGradeFont();
	void SortActor(std::vector<int>& _Grades);
};

