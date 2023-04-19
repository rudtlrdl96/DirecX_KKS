#pragma once


template<typename ClassType>
class ClassFSM
{
private:
	class FSMParameter
	{
	public:
		std::string StateName;

		std::function<void()> StartFunc = nullptr;
		std::function<void(float)> UpdateFunc = nullptr;
		std::function<void()> EndFunc = nullptr;
	};

public:
	ClassFSM()
	{
		FsmDatas.reserve(8);
	}

	~ClassFSM()
	{	
		FsmDatas.clear();
	}

	ClassFSM(const ClassFSM& _Other) = delete;
	ClassFSM(ClassFSM&& _Other) noexcept = delete;
	ClassFSM& operator=(const ClassFSM& _Other) = delete;
	ClassFSM& operator=(ClassFSM&& _Other) noexcept = delete;
	
	void Init(ClassType* _ClassPtr)
	{
		if (nullptr == _ClassPtr)
		{
			MsgAssert("FSM�� ClassPtr�� nullptr�� �����Ϸ� �߽��ϴ�");
		}

		ClassPtr = _ClassPtr;
	}

	void AddFSM(const std::string_view _Name,
		std::function<void(ClassType*)> _Start,
		std::function<void(ClassType*, float)> _Update,
		std::function<void(ClassType*)> _End)
	{
		if (nullptr == ClassPtr)
		{
			MsgAssert("FSM�� �ʱ�ȭ���� �ʰ� ����Ϸ� �߽��ϴ�");
			return;
		}

		std::string UpperName = GameEngineString::ToUpper(_Name);

		for (size_t i = 0; i < FsmDatas.size(); i++)
		{
			if (FsmDatas[i].StateName == UpperName)
			{
				MsgAssert("�̹� �����ϴ� ������Ʈ�� �����Ϸ� �߽��ϴ�.");
				return;
			}
		}

		if (nullptr == _Update)
		{
			MsgAssert("FSM State�� ������Ʈ �Լ��� nullptr�� ����Ϸ� �߽��ϴ�");
			return;
		}

		std::function<void()> StartFunc = nullptr;

		if (nullptr != _Start)
		{
			StartFunc = std::bind(_Start, ClassPtr);
		}

		std::function<void(float)> UpdateFunc = std::bind(_Update, ClassPtr, std::placeholders::_1);

		std::function<void()> EndFunc = nullptr;

		if (nullptr != _End)
		{
			EndFunc = std::bind(_End, ClassPtr);
		}

		FsmDatas.push_back(ClassFSM<ClassType>::FSMParameter(
			UpperName,
			StartFunc,
			UpdateFunc,
			EndFunc
		));
	}

	void Update(float _DeltaTime)
	{
		if (nullptr == CurState)
		{
			MsgAssert("���� FSM ������Ʈ�� �������� �ʰ� ������Ʈ�� �����߽��ϴ�.");
			return;
		}

		if (nullptr == CurState->UpdateFunc)
		{
			MsgAssert("FSM State�� Update �Լ��� nullptr �Դϴ�");
		}

		CurState->UpdateFunc(_DeltaTime);
	}

	void ChangeState(const std::string_view& _Name)
	{
		if (nullptr != CurState)
		{
			PrevState = CurState;
			CurState = nullptr;
		}

		std::string UpperName = GameEngineString::ToUpper(_Name);

		for (size_t i = 0; i < FsmDatas.size(); i++)
		{
			if (FsmDatas[i].StateName == UpperName)
			{
				CurState = &FsmDatas[i];
			}
		}

		if (nullptr == CurState)
		{
			MsgAssert("�������� �ʴ� ������Ʈ�� �����Ϸ� �߽��ϴ�");
			return;
		}

		if (nullptr != CurState->StartFunc)
		{
			CurState->StartFunc();
		}

		if (nullptr == PrevState)
		{
			return;
		}

		if (nullptr != PrevState->EndFunc)
		{
			PrevState->EndFunc();
		}
	}

protected:
	
private:
	std::vector<FSMParameter> FsmDatas;

	ClassType* ClassPtr = nullptr;

	FSMParameter* CurState = nullptr;
	FSMParameter* PrevState = nullptr;
};

