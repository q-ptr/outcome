///              _                           
///   ___  _   _| |_ ___ ___  _ __ ___   ___    
///  / _ \| | | | __/ __/ _ \| '_ ` _ \ / _ \   outcome - status, result & error handling
/// | (_) | |_| | || (_| (_) | | | | | |  __/   -----------------------------------------
///  \___/ \__,_|\__\___\___/|_| |_| |_|\___|   https://github.com/q-ptr/outcome
/// 
/// SPDX-FileCopyrightText: 2023 q-ptr
/// SPDX-License-Identifier: MIT

#include <cstdint>


extern "C" int LLVMFuzzerInitialize(int *argc, char ***argv)
{
	(void) argc;
	(void) argv;

	return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t data_size)
{
	(void) data;
	(void) data_size;

	return 0;
}

//temporary...
int main()
{
	return 0;
}
