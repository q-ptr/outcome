///              _                           
///   ___  _   _| |_ ___ ___  _ __ ___   ___    
///  / _ \| | | | __/ __/ _ \| '_ ` _ \ / _ \   outcome - status, result & error handling
/// | (_) | |_| | || (_| (_) | | | | | |  __/   -----------------------------------------
///  \___/ \__,_|\__\___\___/|_| |_| |_|\___|   https://github.com/q-ptr/outcome
/// 
/// SPDX-FileCopyrightText: 2023 q-ptr
/// SPDX-License-Identifier: MIT

#if defined(QPTR_OUTCOME_STATUS_HAS_MESSAGE) || defined(QPTR_OUTCOME_STATUS_HAS_FMT_MESSAGE)

#pragma once


#include <qptr/outcome/status_code.hpp>
#include <cstdlib>
#include <cstring>
#include <new>


#define QPTR_OUTCOME_STATUS_HAS_MESSAGE


namespace qptr::outcome::detail
{

struct status_message final
{
	status_code   status_code_;
	char          status_string_[1];

	static inline status_message *alloc_mem(size_t len)
	{
		return (status_message *)malloc(sizeof(status_message) + len);
	}

	static inline void free_mem(status_message *message)
	{
		if (nullptr != message)
		{
			free(message);
		}
	}

	static inline status_message *create(status_code code, const char *string, size_t string_len = (size_t)-1)
	{
		if ((size_t)-1 == string_len)
		{
			string_len = std::strlen(string);
		}

		status_message   *message = alloc_mem(string_len);

		if (nullptr != message)
		{
			message->status_code_ = code;
			memcpy(message->status_string_, string, string_len + 1);
		}

		return message;
	}

	inline void destroy()
	{
		free_mem(this);
	}
};

}//namespace qptr::outcome::detail

#endif // #ifdef QPTR_OUTCOME_STATUS_HAS_MESSAGE
