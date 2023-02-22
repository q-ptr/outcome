//              _                           
//   ___  _   _| |_ ___ ___  _ __ ___   ___    
//  / _ \| | | | __/ __/ _ \| '_ ` _ \ / _ \   outcome - status, result & error handling
// | (_) | |_| | || (_| (_) | | | | | |  __/   -----------------------------------------
//  \___/ \__,_|\__\___\___/|_| |_| |_|\___|   https://github.com/q-ptr/outcome
// 
// SPDX-FileCopyrightText: 2023 q-ptr
// SPDX-License-Identifier: MIT

#pragma once


#include <semver.hpp>


namespace qptr::outcome
{

static inline const std::string           VERSION_NAME          = "qptr.outcome";
static inline const std::string           VERSION_DESCRIPTION   = "status, result & error handling";
static inline const std::string           VERSION_URL           = "https://github.com/q-ptr/outcome";

static inline constexpr uint8_t           VERSION_MAJOR         = 0;
static inline constexpr uint8_t           VERSION_MINOR         = 0;
static inline constexpr uint8_t           VERSION_PATCH         = 1;
static inline constexpr auto              VERSION_PREREL_TYPE   = semver::prerelease::alpha;
static inline constexpr uint8_t           VERSION_PREREL_NUMBER = 1;

static inline constexpr semver::version   VERSION               = semver::version 
{
	VERSION_MAJOR, 
	VERSION_MINOR, 
	VERSION_PATCH, 
	VERSION_PREREL_TYPE, 
	VERSION_PREREL_NUMBER
};

}//namespace qptr::outcome
