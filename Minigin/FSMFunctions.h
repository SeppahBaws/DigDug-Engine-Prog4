#pragma once
#include <functional>

namespace dae
{
	class FSMActionBase
	{
	public:
		virtual ~FSMActionBase() {}
		virtual void Execute() {}
	};

	class FSMConditionBase
	{
	public:
		virtual ~FSMConditionBase() {}
		virtual bool Evaluate() { return false; }
	};

	template<typename... args>
	class FSMAction : public FSMActionBase
	{
	public:
		FSMAction(void(*fp)(args...), args... arguments)
			: m_Function(fp), m_Arguments(arguments...)
		{}
		~FSMAction() {}

		void Execute() override
		{
			CallFunction(std::index_sequence_for<args...>());
		}

	private:
		template<std::size_t... Is>
		void CallFunction(std::index_sequence<Is...>)
		{
			m_Function(std::get<Is>(m_Arguments)...);
		}

	private:
		std::function<void(args...)> m_Function;
		std::tuple<args...> m_Arguments;
	};

	template<typename... args>
	class FSMCondition : public FSMConditionBase
	{
	public:
		FSMCondition(bool(*fp)(args...), args... arguments)
			: m_Function(fp), m_Arguments(arguments...)
		{}
		~FSMCondition() {}

		bool Evaluate() override
		{
			return CallFunction(std::index_sequence_for<args...>());
		}

	private:
		template<std::size_t... Is>
		bool CallFunction(std::index_sequence<Is...>)
		{
			return m_Function(std::get<Is>(m_Arguments)...);
		}

	private:
		std::function<bool(args...)> m_Function;
		std::tuple<args...> m_Arguments;
	};
}
