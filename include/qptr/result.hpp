///              _                           
///   ___  _   _| |_ ___ ___  _ __ ___   ___    
///  / _ \| | | | __/ __/ _ \| '_ ` _ \ / _ \   outcome - status, result & error handling
/// | (_) | |_| | || (_| (_) | | | | | |  __/   -----------------------------------------
///  \___/ \__,_|\__\___\___/|_| |_| |_|\___|   https://github.com/q-ptr/outcome
/// 
/// SPDX-FileCopyrightText: 2023 q-ptr
/// SPDX-License-Identifier: MIT

#pragma once


#include <qptr/outcome/result.hpp>
#include <qptr/outcome/status_code.hpp>
#include <qptr/status.hpp>


#define QPTR_RESULT_REQUIRE   QPTR_OUTCOME_RESULT_REQUIRE
#define QPTR_RESULT_TRY       QPTR_OUTCOME_RESULT_TRY
#define QPTR_RESULT_TRY_EX    QPTR_OUTCOME_RESULT_TRY_EX


namespace qptr
{

template <class T>
using result = outcome::result<T>;

tl::unexpected<typename std::decay_t<status>> fail(status &&sts)
{
	return tl::unexpected<typename std::decay_t<status>>(std::forward<status>(sts));
}

tl::unexpected<typename std::decay_t<status>> fail(outcome::status_code code)
{
	return tl::unexpected<typename std::decay_t<status>>(std::forward<status>(status(code)));
}

tl::unexpected<typename std::decay_t<status>> fail(outcome::status_code code, const char* message)
{
	return tl::unexpected<typename std::decay_t<status>>(std::forward<status>(status(code, message)));
}

template <typename... T>
tl::unexpected<typename std::decay_t<status>> fail(outcome::status_code code, fmt::format_string<T...> fmt, 
                                                   T &&... args)
{
#if defined(QPTR_OUTCOME_STATUS_HAS_FMT_MESSAGE)
	return tl::unexpected<typename std::decay_t<status>>(std::forward<status>(status(code, fmt, args...)));
#else
	(void) fmt;

	return tl::unexpected<typename std::decay_t<status>>(std::forward<status>(status(code)));
#endif
}

}//namespace qptr
