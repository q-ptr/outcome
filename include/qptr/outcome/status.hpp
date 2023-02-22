//              _                           
//   ___  _   _| |_ ___ ___  _ __ ___   ___    
//  / _ \| | | | __/ __/ _ \| '_ ` _ \ / _ \   outcome - status, result & error handling
// | (_) | |_| | || (_| (_) | | | | | |  __/   -----------------------------------------
//  \___/ \__,_|\__\___\___/|_| |_| |_|\___|   https://github.com/q-ptr/outcome
// 
// SPDX-FileCopyrightText: 2023 q-ptr
// SPDX-License-Identifier: MIT

#pragma once


#include <qptr/outcome/status_code.hpp>
#include <qptr/outcome/detail/status_message.hpp>
#include <cstdint>
#if defined(QPTR_OUTCOME_STATUS_HAS_FMT_MESSAGE)
	#include <boost/predef.h>
	#ifdef BOOST_COMP_MSVC
		#pragma warning(disable: 6285 26437 26450 26451 26495 26498 26812)
	#endif
	#include <fmt/core.h>
#endif


//needs descriptive variable names (op1, op2) to generate descriptive error messages...
#define QPTR_OUTCOME_STATUS_REQUIRE(op1, op, op2)                                                                      \
if (!((op1) op (op2)))                                                                                                 \
{                                                                                                                      \
	return qptr::outcome::status(qptr::outcome::status::INVALID_ARG,                                                    \
	                             "requirement failed at {}:{} => ({} {} {}) with ({} {} {})",                           \
	                             __FILE__, __LINE__, # op1, # op, # op2, op1, # op, op2);                               \
}


namespace qptr::outcome
{

class [[nodiscard]] status final
{
public:

	static const status_code   OK                          = 0;
	static const status_code   UNKNOWN                     = 1;
	static const status_code   INVALID_ARG                 = 2;
	static const status_code   INVALID_CALL                = 3;
	static const status_code   NOT_INITIALIZED             = 4;
	static const status_code   NOT_SUPPORTED               = 5;
	static const status_code   NOT_FOUND                   = 6;
	static const status_code   NOT_IMPLEMENTED             = 7;
	static const status_code   NOT_AVAILABLE               = 8;
	static const status_code   OPERATION_FAILED            = 9;
	static const status_code   MEM_ALLOC_FAILED            = 10;
	static const status_code   DUPLICATE                   = 11;
	static const status_code   RETRY                       = 12;
	static const status_code   DENIED                      = 13;
	static const status_code   BUSY                        = 14;
	static const status_code   TIMEOUT                     = 15;
	static const status_code   CANCELLED                   = 16;
	static const status_code   NO_MORE_ITEMS               = 17;
	static const status_code   NO_MORE_DATA                = 18;
	static const status_code   EXPIRED                     = 19;
	static const status_code   TOO_SMALL                   = 20;
	static const status_code   TOO_BIG                     = 21;
	static const status_code   TOO_FEW_ITEMS               = 22;
	static const status_code   TOO_MANY_ITEMS              = 23;
	static const status_code   OUT_OF_BOUNDS               = 24;
	static const status_code   OPEN_FAILED                 = 25;
	static const status_code   CREATE_FAILED               = 26;
	static const status_code   CLOSE_FAILED                = 27;
	static const status_code   END_OF_FILE                 = 28;
	static const status_code   WRITE_FAILED                = 29;
	static const status_code   READ_FAILED                 = 30;
	static const status_code   IO_ERROR                    = 31;

	static const status_code   USER_CODE_START             = 100;

#if defined(QPTR_OUTCOME_STATUS_HAS_FMT_MESSAGE)
	template <typename... T>
	using   fmt_format_string = fmt::format_string<T...>;
#else
	template <typename... T>
	using   fmt_format_string = std::string_view;
#endif

	status() : data_(status_code_data(OK))
	{
	}

	explicit status(status_code code) : data_(status_code_data(code))
	{
	}

	status(status_code code, const char *string) : data_(status_code_data(OK))
	{
		set(code, string);
	}

	template <typename... T>
	status(status_code code, fmt_format_string<T...> fmt, T &&... args) : data_(status_code_data(OK))
	{
		set(code, fmt, args...);
	}

	status(const status &status) : data_(status_code_data(OK))
	{
		if (is_code_only(status.data_))
		{
			set(status.get_code());
		}
		else
		{
			set(status.get_code(), status.get_message());
		}
	}

	status(status &&status) noexcept
	{
		data_        = status.data_;
		status.data_ = status_code_data(OK);
	}

	status &operator=(const status &status)
	{
		if (is_code_only(status.data_))
		{
			set(status.get_code());
		}
		else
		{
			set(status.get_code(), status.get_message());
		}

		return *this;
	}

	status &operator=(status &&status) noexcept
	{
		if (this != &status)
		{
			free_mem();
			data_        = status.data_;
			status.data_ = status_code_data(OK);
		}

		return *this;
	}

	~status()
	{
		set(OK);
	}

	bool is_ok() const
	{
		return (OK == get_code());
	}

	explicit operator bool() const
	{
		return is_ok();
	}

	explicit operator status_code() const
	{
		return get_code();
	}

	explicit operator const char *() const
	{
		return get_message();
	}

	status_code get_code() const
	{
#if defined(QPTR_OUTCOME_STATUS_HAS_MESSAGE)
		if (is_code_only(data_))
		{
			return data_to_code(data_);
		}
		else
		{
			return data_to_message(data_)->status_code_;
		}
#else
		if (is_code_only(data_))
		{
			return data_to_code(data_);
		}
		else
		{
			return OK;
		}
#endif
	}

	const char *get_message() const
	{
#if defined(QPTR_OUTCOME_STATUS_HAS_MESSAGE)
		if (is_code_only(data_))
		{
			return "";
		}
		else
		{
			return data_to_message(data_)->status_string_;
		}
#else
		return "";
#endif
	}

	bool has_message() const
	{
#if defined(QPTR_OUTCOME_STATUS_HAS_MESSAGE)
		return !is_code_only(data_);
#else
		return false;
#endif
	}

	void set(status_code code)
	{
		free_mem();
		data_ = status_code_data(code);
	}

	void set(status_code code, const char *string)
	{
#if defined(QPTR_OUTCOME_STATUS_HAS_MESSAGE)
		free_mem();

		data_ = message_to_data(code, string);
#else
		(void) string;

		data_ = status_code_data(code);
#endif
	}

	template <typename... T>
	void set(status_code code, fmt_format_string<T...> fmt, T &&... args)
	{
#if defined(QPTR_OUTCOME_STATUS_HAS_FMT_MESSAGE)
		free_mem();

		size_t   string_length = fmt::formatted_size(fmt, args...);
		auto     *message      = detail::status_message::alloc_mem(string_length);

		if (nullptr == message)
		{
			data_ = status_code_data(code);

			return;
		}

		fmt::format_to_n(message->status_string_, string_length, fmt, args...);
		message->status_code_                  = code;
		message->status_string_[string_length] = 0;
		
		data_ = message_to_data(message);
#elif defined(QPTR_OUTCOME_STATUS_HAS_MESSAGE)
		set(code, fmt.data());
#else
		(void) fmt;

		set(code);
#endif
	}

private:

	uintptr_t   data_;

	static inline bool is_code_only(uintptr_t data)
	{
		return (data & 1) == 0;
	}

	static inline uintptr_t status_code_data(status_code code)
	{
		return static_cast<uintptr_t>(code) << 1;
	}

	static inline status_code data_to_code(uintptr_t data)
	{
		return static_cast<status_code>(data >> 1);
	}

#if defined(QPTR_OUTCOME_STATUS_HAS_MESSAGE)
	static inline uintptr_t message_to_data(detail::status_message *message)
	{
		return reinterpret_cast<uintptr_t>(message) + 1;
	}

	static inline uintptr_t message_to_data(status_code code, const char *string, size_t string_length = (size_t)-1)
	{
		auto   *message = detail::status_message::create(code, string, string_length);

		if (nullptr == message)
		{
			return status_code_data(code);
		}

		return message_to_data(message);
	}

	static inline detail::status_message *data_to_message(uintptr_t data)
	{
		return reinterpret_cast<detail::status_message *>(data - 1);
	}
#endif

	inline void free_mem()
	{
#if defined(QPTR_OUTCOME_STATUS_HAS_MESSAGE)
		if (!is_code_only(data_))
		{
			data_to_message(data_)->destroy();
		}
#endif
	}
};

}//namespace qptr::outcome


#if defined(QPTR_OUTCOME_STATUS_HAS_FMT_MESSAGE)
template <>
struct fmt::formatter<qptr::outcome::status>
{
	static constexpr auto parse(const format_parse_context &ctx)
	{
		return ctx.begin();
	}

	template <typename format_context>
	auto format(const qptr::outcome::status &status, format_context &ctx)
	{
		if (status.is_ok())
		{
			return format_to(ctx.out(), "status(OK)");
		}
		else
		if (!status.has_message())
		{
			return format_to(ctx.out(), "status({})", status.get_code());
		}
		else
		{
			return format_to(ctx.out(), "status({}, {})", status.get_code(), status.get_message());
		}
	}
};
#endif
