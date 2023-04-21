#pragma once


class ContentCore
{
public:
	ContentCore();
	~ContentCore();

	ContentCore(const ContentCore& _Other) = delete;
	ContentCore(ContentCore&& _Other) noexcept = delete;
	ContentCore& operator=(const ContentCore& _Other) = delete;
	ContentCore& operator=(ContentCore&& _Other) noexcept = delete;

	static void CoreLoading();
	static void CoreEnd();

protected:

private:
	static void ContentPipeLineCreate();

};