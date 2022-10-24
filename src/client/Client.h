/* This file is part of the tiny-chat.
   Copyright (c) 2021 Marina G. Zhuravlyova
   Licensed under the zLib license.
   Refer to the LICENSE file included.
*/

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <windows.h>
#include <time.h>

using namespace std;

#pragma comment (lib, "ws2_32.lib")
#define MSG 1000

int start_client(int argc, char* argv[]);

