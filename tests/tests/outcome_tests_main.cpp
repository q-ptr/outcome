///              _                           
///   ___  _   _| |_ ___ ___  _ __ ___   ___    
///  / _ \| | | | __/ __/ _ \| '_ ` _ \ / _ \   outcome - status, result & error handling
/// | (_) | |_| | || (_| (_) | | | | | |  __/   -----------------------------------------
///  \___/ \__,_|\__\___\___/|_| |_| |_|\___|   https://github.com/q-ptr/outcome
/// 
/// SPDX-FileCopyrightText: 2023 q-ptr
/// SPDX-License-Identifier: MIT

#include <fmt/core.h>
#include <qptr/status.hpp>
#include <qptr/result.hpp>
#include <qptr/outcome/version.hpp>


qptr::result<int> division1(int dividend, int divisor)
{
	if (0 == divisor)
	{
		return qptr::fail(qptr::status::INVALID_ARG, "cannot divide {} by {} : division by zero", dividend, divisor);
	}
	else
	{
		return dividend / divisor;
	}
}

qptr::result<int> division2(int dividend, int divisor)
{
	QPTR_RESULT_REQUIRE(divisor, !=, 0)

	return dividend / divisor;
}

template <>
struct fmt::formatter<semver::version>
{
	static constexpr auto parse(const format_parse_context &ctx)
	{
		return ctx.begin();
	}

	template <typename format_context>
	auto format(const semver::version &version, format_context &ctx)
	{
		if (semver::prerelease::alpha == version.prerelease_type)
		{
			return format_to(ctx.out(), "{}.{}.{}-alpha.{}", version.major, version.minor, version.patch, 
			                 version.prerelease_number);
		}
		else
		if (semver::prerelease::beta == version.prerelease_type)
		{
			return format_to(ctx.out(), "{}.{}.{}-beta.{}", version.major, version.minor, version.patch, 
			                 version.prerelease_number);
		}
		else
		if (semver::prerelease::rc == version.prerelease_type)
		{
			return format_to(ctx.out(), "{}.{}.{}-rc.{}", version.major, version.minor, version.patch, 
			                 version.prerelease_number);
		}
		else
		{
			return format_to(ctx.out(), "{}.{}.{}", version.major, version.minor, version.patch);
		}
	}
};

int main()
{
	qptr::status   s1;
	qptr::status   s2(qptr::status::BUSY);
	qptr::status   s3(qptr::status::INVALID_CALL, "the call is not valid in this context");
	qptr::status   s4(qptr::status::INVALID_ARG, "invalid argument : {}", 123);

	fmt::print("s1 = {}\n", s1);
	fmt::print("s2 = {}\n", s2);
	fmt::print("s3 = {}\n", s3);
	fmt::print("s4 = {}\n", s4);

	auto  res11 = division1(6, 3);
	auto  res12 = division1(5, 0);
	auto  res21 = division2(6, 3);
	auto  res22 = division2(5, 0);

	fmt::print("res11 = {}\n", res11);
	fmt::print("res12 = {}\n", res12);
	fmt::print("res21 = {}\n", res21);
	fmt::print("res22 = {}\n", res22);

	return 0;
}
