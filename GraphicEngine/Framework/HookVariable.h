#pragma once
#include <functional>

template <class DataType>
class HookVariable
{
private:
	DataType value;
	std::function<void()> hook;
public:
	HookVariable(const DataType val, std::function<void()> func = nullptr)
		: value(val), hook(func) {}
	HookVariable(std::function<void()> func = nullptr)
		: value(), hook(func) {}
	
	void SetHook(std::function<void()> func)
	{
		hook = func;
	}

	HookVariable& operator=(const DataType &val)
	{
		value = val;
		try { hook(); } catch (const std::bad_function_call& e) {}
		return (*this);
	}
	HookVariable& operator+=(const DataType &val)
	{
		value = value + val;
		try { hook(); } catch (const std::bad_function_call& e) {}
		return (*this);
	}
	HookVariable& operator-=(const DataType &val)
	{
		value = value - val;
		try { hook(); } catch (const std::bad_function_call& e) {}
		return (*this);
	}
	HookVariable& operator*=(const DataType &val)
	{
		value = value * val;
		try { hook(); } catch (const std::bad_function_call& e) {}
		return (*this);
	}
	HookVariable& operator/=(const DataType &val)
	{
		value = value / val;
		try { hook(); } catch (const std::bad_function_call& e) {}
		return (*this);
	}
	HookVariable& operator%=(const DataType &val)
	{
		value = value % val;
		try { hook(); } catch (const std::bad_function_call& e) {}
		return (*this);
	}
	HookVariable operator+(const DataType &val) const
	{
		return HookVariable(value + val, hook);
	}
	HookVariable operator-(const DataType &val) const
	{
		return HookVariable(value - val, hook);
	}
	HookVariable operator*(const DataType &val) const
	{
		return HookVariable(value * val, hook);
	}
	HookVariable operator/(const DataType &val) const
	{
		return HookVariable(value / val, hook);
	}
	HookVariable operator%(const DataType &val) const
	{
		return HookVariable(value % val, hook);
	}
	HookVariable operator+() const
	{
		return HookVariable(value, hook);
	}
	HookVariable operator-() const
	{
		return HookVariable(-value, hook);
	}
	HookVariable& operator++()
	{
		++value;
		return (*this);
	}
	HookVariable operator++(int)
	{
		return HookVariable(value++, hook);
	}
	HookVariable& operator--()
	{
		--value;
		return (*this);
	}
	HookVariable operator--(int)
	{
		return HookVariable(value--, hook);
	}
	bool operator!() const
	{
		return !value;
	}
	bool operator==(const HookVariable &v) const
	{
		return value == v.value;
	}
	bool operator!=(const HookVariable &v) const
	{
		return value != v.value;
	}
	bool operator>(const HookVariable &v) const
	{
		return value > v.value;
	}
	bool operator<(const HookVariable &v) const
	{
		return value < v.value;
	}
	bool operator>=(const HookVariable &v) const
	{
		return value >= v.value;
	}
	bool operator<=(const HookVariable &v) const
	{
		return value <= v.value;
	}
	operator DataType() const
	{
		return value;
	}
};