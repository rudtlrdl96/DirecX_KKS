#pragma once
#include <vector>
#include <string>
#include <string_view>

class GameEngineSerializer
{
public:
	GameEngineSerializer();
	~GameEngineSerializer();

	GameEngineSerializer(const GameEngineSerializer& _Other) = delete;
	GameEngineSerializer(GameEngineSerializer&& _Other) noexcept = delete;
	GameEngineSerializer& operator=(const GameEngineSerializer& _Other) = delete;
	GameEngineSerializer& operator=(GameEngineSerializer&& _Other) noexcept = delete;

	void BufferResize(size_t _Size);

	void Write(const int& _Value);
	void Write(const std::string_view& _Value);
	void Write(const void* _Ptr, size_t _Size);

	void Read(int& _Value);
	void Read(std::string& _Value);
	void Read(void* _Ptr, size_t _Size);


	inline void* GetData()
	{
		return &Datas[0];
	}

	inline const void* GetConstData() const
	{
		return &Datas[0];
	}

	inline size_t GetOffset() const
	{
		return Offset;
	}

	inline size_t GetBufferSize() const
	{
		return Datas.size();
	}

	std::string GetString();

protected:

private:
	std::vector<char> Datas = std::vector<char>(1024);
	size_t Offset = 0;
};

