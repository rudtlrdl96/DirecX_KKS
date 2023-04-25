#pragma once


template<typename Class>
static void MsgAssert_Rtti(std::string _AddErrorText)
{
	const type_info& RttiInfo = typeid(Class);
	std::string ErrorText = std::string(RttiInfo.name()) + _AddErrorText.data();
	MessageBoxA(nullptr, ErrorText.c_str(), "Error", MB_OK);
	assert(false);
}

class ContentDebug
{
public:
	
private:
	ContentDebug() {}
	~ContentDebug() {}

	ContentDebug(const ContentDebug& _Other) = delete;
	ContentDebug(ContentDebug&& _Other) noexcept = delete;
	ContentDebug& operator=(const ContentDebug& _Other) = delete;
	ContentDebug& operator=(ContentDebug&& _Other) noexcept = delete;
};