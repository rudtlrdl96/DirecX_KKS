#pragma once
#include <string>
#include <functional>
#include <atomic>
#include <thread>

class GameEngineThread
{
public:
	GameEngineThread();
	GameEngineThread(std::string _ThreadName, std::function<void(GameEngineThread*)> _CallBack);
	~GameEngineThread();

	void Start(std::string _ThreadName, std::function<void(GameEngineThread*)> _CallBack);

	void Join();

	static void ThreadEnd() 
	{
		End = true;
	}

	static bool IsThreadEnd()
	{
		return End;
	}

protected:

private:
	static std::atomic_bool End;
	static void ThreadBaseFunction(GameEngineThread* Thread, std::string Name);

	std::thread Thread;
	std::function<void(GameEngineThread*)> CallBack;
};

