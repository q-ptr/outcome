//              _                           
//   ___  _   _| |_ ___ ___  _ __ ___   ___    
//  / _ \| | | | __/ __/ _ \| '_ ` _ \ / _ \   outcome - status, result & error handling
// | (_) | |_| | || (_| (_) | | | | | |  __/   -----------------------------------------
//  \___/ \__,_|\__\___\___/|_| |_| |_|\___|   https://github.com/q-ptr/outcome
// 
// SPDX-FileCopyrightText: 2023 q-ptr
// SPDX-License-Identifier: MIT

#pragma once


#include <qptr/outcome/status.hpp>
#include <qptr/outcome/status_code.hpp>
#include <tl/expected.hpp>


//needs descriptive variable names (op1, op2) to generate descriptive error messages...
#define QPTR_OUTCOME_RESULT_REQUIRE(op1, op, op2)                                                                      \
if (!((op1) op (op2)))                                                                                                 \
{                                                                                                                      \
	return qptr::outcome::fail(qptr::outcome::status(qptr::outcome::status::INVALID_ARG,                                \
	                                                 "requirement failed at {}:{} => ({} {} {}) with ({} {} {})",       \
	                                                 __FILE__, __LINE__, # op1, # op, # op2, op1, # op, op2));          \
}

#define QPTR_OUTCOME_RESULT_TRY(op)                                                                                    \
do {                                                                                                                   \
	auto   res = op;                                                                                                    \
	                                                                                                                    \
	if (!res)                                                                                                           \
	{                                                                                                                   \
		return qptr::outcome::fail(res.error());                                                                         \
	}                                                                                                                   \
} while (false);                                                                                                       \

#define QPTR_OUTCOME_RESULT_TRY_EX(op, ret)                                                                            \
do {                                                                                                                   \
	auto   res = op;                                                                                                    \
	                                                                                                                    \
	if (!res)                                                                                                           \
	{                                                                                                                   \
		return qptr::outcome::fail(res.error());                                                                         \
	}                                                                                                                   \
	else                                                                                                                \
	{                                                                                                                   \
		ret = res.value();                                                                                               \
	}                                                                                                                   \
} while (false);                                                                                                       \


namespace qptr::outcome
{

template <class T>
using result = tl::expected<T, status>;

tl::unexpected<typename std::decay_t<status>> fail(status &&sts)
{
	return tl::unexpected<typename std::decay_t<status>>(std::forward<status>(sts));
}

tl::unexpected<typename std::decay_t<status>> fail(status_code code)
{
	return tl::unexpected<typename std::decay_t<status>>(std::forward<status>(status(code)));
}

tl::unexpected<typename std::decay_t<status>> fail(status_code code, const char* message)
{
	return tl::unexpected<typename std::decay_t<status>>(std::forward<status>(status(code, message)));
}

#if defined(QPTR_OUTCOME_STATUS_HAS_FMT_MESSAGE)
template <typename... T>
tl::unexpected<typename std::decay_t<status>> fail(status_code code, fmt::format_string<T...> fmt, T &&... args)
{
	return tl::unexpected<typename std::decay_t<status>>(std::forward<status>(status(code, fmt, args...)));
}
#endif //#if defined(QPTR_OUTCOME_STATUS_HAS_FMT_MESSAGE)

}//namespace qptr::outcome


#if defined(QPTR_OUTCOME_STATUS_HAS_FMT_MESSAGE)

template <class T>
struct fmt::formatter<qptr::outcome::result<T>>
{
	static constexpr auto parse(const format_parse_context &ctx)
	{
		return ctx.begin();
	}

	template <typename format_context>
	auto format(const qptr::outcome::result<T> &result, format_context &ctx)
	{
		if (result)
		{
			return format_to(ctx.out(), "{}", result.value());
		}
		else
		{
			return format_to(ctx.out(), "{}", result.error());
		}
	}
};

#endif //#if defined(QPTR_OUTCOME_STATUS_HAS_FMT_MESSAGE)
