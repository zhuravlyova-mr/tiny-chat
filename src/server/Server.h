/* This file is part of the tiny-chat.
   Copyright (c) 2021 Marina G. Zhuravlyova
   Licensed under the zLib license.
   Refer to the LICENSE file included.
*/
//Server
//Command args: <port>

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib,"ws2_32.lib") 

using namespace std;

#define VMAX 20
#define TINYMES 100
#define MSG 1000

int start_work(int argc, char* argv[]);