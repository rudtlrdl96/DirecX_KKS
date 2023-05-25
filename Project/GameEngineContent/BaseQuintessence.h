#pragma once
#include "BaseContentActor.h"

 
class BaseQuintessence : public BaseContentActor
{
public:
	BaseQuintessence();
	~BaseQuintessence();

	BaseQuintessence(const BaseQuintessence& _Other) = delete;
	BaseQuintessence(BaseQuintessence&& _Other) noexcept = delete;
	BaseQuintessence& operator=(const BaseQuintessence& _Other) = delete;
	BaseQuintessence& operator=(BaseQuintessence&& _Other) noexcept = delete;

protected:
	
private:


};

