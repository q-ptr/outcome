///              _                           
///   ___  _   _| |_ ___ ___  _ __ ___   ___    
///  / _ \| | | | __/ __/ _ \| '_ ` _ \ / _ \   outcome - status, result & error handling
/// | (_) | |_| | || (_| (_) | | | | | |  __/   -----------------------------------------
///  \___/ \__,_|\__\___\___/|_| |_| |_|\___|   https://github.com/q-ptr/outcome
/// 
/// SPDX-FileCopyrightText: 2023 q-ptr
/// SPDX-License-Identifier: MIT

#pragma once


#include <qptr/outcome/status.hpp>


#define QPTR_STATUS_REQUIRE   QPTR_OUTCOME_STATUS_REQUIRE


namespace qptr
{

using status = outcome::status;

}//namespace qptr
