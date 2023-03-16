#pragma once
#include <vector>
#include <string>
#include <string_view>

// �����͸� ����Ʈ ���� char �迭�� ������ִ� �༮
// ����ȭ�� Ŭ������ ����� c++�� ���� ��� �����Լ������ͳ� 
// �����Ͱ��� �����غ��� ������� �����͵��� �� �����ϰ� �ʿ��� �����͸�
// ����Ʈ ������ �����ϴ°��� �ǹ��մϴ�.

// ���� :
class GameEngineSerializer
{
public:
	// constrcuter destructer
	GameEngineSerializer();
	~GameEngineSerializer();

	// delete Function
	GameEngineSerializer(const GameEngineSerializer& _Other) = delete;
	GameEngineSerializer(GameEngineSerializer&& _Other) noexcept = delete;
	GameEngineSerializer& operator=(const GameEngineSerializer& _Other) = delete;
	GameEngineSerializer& operator=(GameEngineSerializer&& _Other) noexcept = delete;

	// �Ǽ��� ������ �־ �������� ���ø��� ���߿� ������� �մϴ�.
	void Write(const int& _Value);

	void Write(const std::string_view& _Value);

	//template<typename T>
	//void Write(const T& _Value) 
	//{
	//	Write(&_Value, sizeof(_Value));
	//}

	void Write(const void* _Ptr, size_t _Size);

	inline void* GetData() 
	{
		return &Datas[0];
	}

	inline size_t GetDataSize()
	{
		return Offset;
	}

protected:

private:
	std::vector<char> Datas = std::vector<char>(1024);
	size_t Offset = 0;
};

