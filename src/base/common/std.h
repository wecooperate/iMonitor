//******************************************************************************
/*++
  Copyright (C) 2012-2022 https://github.com/wecooperate

  This file is part of iMonitor.
 
  iMonitor is free software, you can redistribute it and/or modify
  it under the GNU Affero General Public License Version 3, or any later version.
  
  For other usage or business cooperation, please contact iMonitor@qq.com.
  
--*/
//******************************************************************************
#ifndef __std_a44201cc_112c_41d1_b1f2_bd95f15f40cb__
#define __std_a44201cc_112c_41d1_b1f2_bd95f15f40cb__
//******************************************************************************
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
//******************************************************************************
#include <type_traits>
#include <string>
#include <map>
#include <vector>
#include <list>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <memory>
#include <functional>
#include <atomic>
#include <unordered_map>
#include <mutex>
//******************************************************************************
using std::move;
using std::forward;
using std::string;
using std::list;
using std::vector;
using std::map;
using std::unordered_map;
using std::set;
using std::unordered_set;
using namespace std::placeholders;
//******************************************************************************
#ifndef BIT
#define BIT(n) (1 << n)
#endif
//******************************************************************************
#ifndef CONCAT
#define CONCAT_BASE(a, b) a##b
#define CONCAT(a, b)	  CONCAT_BASE(a, b)
#endif
//******************************************************************************
class cxSafeObject
{
	cxSafeObject(const cxSafeObject&) = delete;
	cxSafeObject& operator=(const cxSafeObject&) = delete;

public:
	cxSafeObject(void) = default;
};
//******************************************************************************
template<typename T>
struct cxSingleton
{
	template<typename... Args>
	static T* Instance(Args&&... args)
	{
		static std::once_flag lock;
		static T* instance = nullptr;

		while (!instance) {
			std::call_once(lock, [=]() {
				static T __instance__(std::forward<Args>(args)...);
				instance = &__instance__;
			});
		}

		return instance;
	}

	template<typename... Args>
	static T* InstanceNoLock(Args&&... args)
	{
		static T __instance__(std::forward<Args>(args)...);
		return &__instance__;
	}

	template<typename... Args>
	static T& RefInstance(Args... args)
	{
		return *Instance(std::forward<Args>(args)...);
	}

	template<typename... Args>
	static T& RefInstanceNoLock(Args... args)
	{
		return *InstanceNoLock(std::forward<Args>(args)...);
	}
};
//******************************************************************************
#define SINGLETON_(class, ...)			  ((class*)cxSingleton<class>::Instance(__VA_ARGS__))
#define SINGLETON_NOLOCK_(class, ...)	  ((class*)cxSingleton<class>::InstanceNoLock(__VA_ARGS__))
#define SINGLETON_REF_(class, ...)		  ((class&)cxSingleton<class>::RefInstance(__VA_ARGS__))
#define SINGLETON_REF_NOLOCK_(class, ...) ((class&)cxSingleton<class>::RefInstanceNoLock(__VA_ARGS__))
//******************************************************************************
template<typename R, typename C, typename IsMutable, typename... Args>
struct lambda_type_info
{
	using is_mutable = IsMutable;
	using type = R(Args...);
	using return_type = R;

	enum { arity = sizeof...(Args) };

	template<size_t i, typename = typename std::enable_if<arity != 0>::type>
	struct arg
	{
		typedef typename std::decay<typename std::tuple_element<i, std::tuple<Args...>>::type>::type type;
	};
};

template<typename T, typename = void>
struct lambda_type
{
	static constexpr bool is_lambda = false;
};

template<typename T>
struct lambda_type<T, typename std::enable_if<std::is_same<decltype(void(&T::operator())), void>::value>::type> : lambda_type<decltype(&T::operator())>
{
	static constexpr bool is_lambda = true;
};

template<typename R, typename C, typename... Args>
struct lambda_type<R (C::*)(Args...)> : lambda_type_info<R, C, std::true_type, Args...>
{
};

template<typename R, typename C, typename... Args>
struct lambda_type<R (C::*)(Args...) const> : lambda_type_info<R, C, std::false_type, Args...>
{
};
//******************************************************************************
#endif
