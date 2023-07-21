#pragma once
#include "BaseContentActor.h"

class InventorySynergyGrade : public BaseContentActor
{
public:
	InventorySynergyGrade();
	~InventorySynergyGrade();

	InventorySynergyGrade(const InventorySynergyGrade& _Other) = delete;
	InventorySynergyGrade(InventorySynergyGrade&& _Other) noexcept = delete;
	InventorySynergyGrade& operator=(const InventorySynergyGrade& _Other) = delete;
	InventorySynergyGrade& operator=(InventorySynergyGrade&& _Other) noexcept = delete;

protected:
	
private:
	std::vector<GameEngineUIRenderer> GradeArrows;
	std::vector<ContentUIFontRenderer> GradeFonts;

};

