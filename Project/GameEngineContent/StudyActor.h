#pragma once
#include "BaseContentActor.h"

class StudyActor : public BaseContentActor
{
public:
	StudyActor();
	~StudyActor();

	StudyActor(const StudyActor& _Other) = delete;
	StudyActor(StudyActor&& _Other) noexcept = delete;
	StudyActor& operator=(const StudyActor& _Other) = delete;
	StudyActor& operator=(StudyActor&& _Other) noexcept = delete;

protected:
	void Start() override;

private:


};

