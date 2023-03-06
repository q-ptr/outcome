///              _                           
///   ___  _   _| |_ ___ ___  _ __ ___   ___    
///  / _ \| | | | __/ __/ _ \| '_ ` _ \ / _ \   outcome - status, result & error handling
/// | (_) | |_| | || (_| (_) | | | | | |  __/   -----------------------------------------
///  \___/ \__,_|\__\___\___/|_| |_| |_|\___|   https://github.com/q-ptr/outcome
/// 
/// SPDX-FileCopyrightText: 2023 q-ptr
/// SPDX-License-Identifier: MIT

#include <catch_amalgamated.hpp>


int main(int argc, char *argv[])
{
	int   nResult = Catch::Session().run(argc, argv);

	return nResult;
}

TEST_CASE("predef", "[predef]")
{
	REQUIRE(1 == 1);

	SECTION("test_section")
	{
		REQUIRE(1 == sizeof(uint8_t));
	}
}
