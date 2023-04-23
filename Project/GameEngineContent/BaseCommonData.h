#pragma once
class BaseCommonData sealed
{
public:
	std::string Name = "";
	size_t Index = 0;

private:
	BaseCommonData() {}
	~BaseCommonData() {}
};