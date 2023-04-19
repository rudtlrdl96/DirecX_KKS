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
			MsgAssert("FSM의 ClassPtr을 nullptr로 설정하려 했습니다");
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
			MsgAssert("FSM을 초기화하지 않고 사용하려 했습니다");
			return;
		}

		std::string UpperName = GameEngineString::ToUpper(_Name);

		for (size_t i = 0; i < FsmDatas.size(); i++)
		{
			if (FsmDatas[i].StateName == UpperName)
			{
				MsgAssert("이미 존재하는 스테이트를 생성하려 했습니다.");
				return;
			}
		}

		if (nullptr == _Update)
		{
			MsgAssert("FSM State의 업데이트 함수를 nullptr로 등록하려 했습니다");
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
			MsgAssert("현재 FSM 스테이트를 세팅하지 않고 업데이트를 실행했습니다.");
			return;
		}

		if (nullptr == CurState->UpdateFunc)
		{
			MsgAssert("FSM State의 Update 함수가 nullptr 입니다");
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
			MsgAssert("존재하지 않는 스테이트로 변경하려 했습니다");
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

