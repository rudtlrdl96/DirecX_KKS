#pragma once


class ContentDebug
{
public:
	template<typename Class>
	static void RttiAssert(std::string _AddErrorText)
	{
		const type_info& RttiInfo = typeid(Class);
		std::string ErrorText = std::string(RttiInfo.name()) + _AddErrorText.data();
		MessageBoxA(nullptr, ErrorText.c_str(), "Error", MB_OK);
		assert(false);
	}
private:
	ContentDebug() {}
	~ContentDebug() {}

	ContentDebug(const ContentDebug& _Other) = delete;
	ContentDebug(ContentDebug&& _Other) noexcept = delete;
	ContentDebug& operator=(const ContentDebug& _Other) = delete;
	ContentDebug& operator=(ContentDebug&& _Other) noexcept = delete;
};