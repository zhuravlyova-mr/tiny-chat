/* This file is part of the tiny-chat.
   Copyright (c) 2021 Marina G. Zhuravlyova
   Licensed under the zLib license.
   Refer to the LICENSE file included.
*/

/* CLient
   Command args: <port> <IP-address>
   allowed commands: HELLO, login, message, ping, logout;
   allowed logins/passwords: bob/123, paul/456, jim/diam01, storm/qw123, guest/passw.
*/

#pragma once
#include "Client.h"
#include "parser.h"

string uuid, login;
TinyParser d;
TinyParser sender;
int flag; //is_logout
SOCKET cli_sock;
DWORD client_id;
DWORD id;
HANDLE thr; //thread handle
DWORD thrID;


vector<pair<string, string>> make_message(int port, int& flag) {
	string str, str1, str2;
	vector<pair<string, string>> message;
	message.clear();
	cin >> str;
	message.push_back({ "\"id\"", to_string(cli_sock) + to_string(thrID) });
	if (str == "HELLO") {
		message.push_back({ "\"command\"", "\"HELLO\"" });
	}
	else if (str == "login") {
		message.push_back({ "\"command\"", "\"login\"" });
		cout << "login: ";
		cin >> login;
		message.push_back({ "\"login\"", "\"" + login + "\"" });
		cout << "password: ";
		cin >> str1;
		message.push_back({ "\"password\"", "\"" + str1 + "\"" });
	}
	else if (str == "message") {
		message.push_back({ "\"command\"", "\"message\"" });
		cout << "body: ";
		cin >> str2;
		message.push_back({ "\"body\"", str2 });
		message.push_back({ "\"sender_login\"", "\"" + login + "\"" });
		message.push_back({ "\"session\"", uuid });
	}
	else if (str == "ping") {
		message.push_back({ "\"command\"", "\"ping\"" });
		message.push_back({ "\"session\"", uuid });
	}
	else if (str == "logout") {
		message.push_back({ "\"command\"", "\"logout\"" });
		message.push_back({ "\"session\"", uuid });
		flag = 1;
	}
	else {
		message.clear();
		return message;
	}
	return message;
}

DWORD WINAPI from_server(PVOID arg) {
	char* msg = new char[MSG];
	char* msg_to_parse = new char[MSG];
	char* serv_repl = nullptr;
	vector<pair<string, string>> message;
	int session = 0;
	while (1)
	{
		memset(msg, '\0', MSG);
		memset(msg_to_parse, '\0', MSG);
		int numbytes = recv(cli_sock, msg, MSG, 0);

		if (!numbytes || numbytes == SOCKET_ERROR) {
			cout << "\nClient leaves (may be server not found).\n";
			CloseHandle(thr);
			closesocket(cli_sock);
			break;
		}
		else if (numbytes > 0) {
			strcpy(msg_to_parse, msg);
			d.Parse(msg_to_parse);
			message = d.GetData();
			if (!session && message.size() >= 4 && message[3].first == "\"session\"") {
				uuid = message[3].second; session = 1;
			}
			cout << msg << "\n";
			if (flag) {
				closesocket(cli_sock);
				break;
			}
			cout << "command: ";
		}
	}
	return 0;
}

int start_client(int argc, char* argv[]) {
	struct  sockaddr_in addr;
	WSADATA ws;
	id = time(0);
	char* mess = nullptr;
	int last_len = MSG;
	WSAStartup(MAKEWORD(2, 2), &ws);
	int port = atoi(argv[1]);
	uuid = "\"\"";
	login = "\"\"";
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(argv[2]);

	cli_sock = socket(AF_INET, SOCK_STREAM, 0);
	if ((connect(cli_sock, (struct sockaddr*)&addr, sizeof(addr))) != 0) {
		cout << "Server not found\n";
		shutdown(cli_sock, 2);
		return 0;
	}

	thr = CreateThread(NULL, 0, from_server, NULL, 0, &thrID);
	cout << "Client " << to_string(cli_sock) + to_string(thrID) << "\n";
	int res = 0;
	client_id = 0;

	while (1) {
		if (WaitForSingleObject(thr, 1) == WAIT_OBJECT_0) break; //when logout thread becomes signaled
		sender = make_message(port, flag);
		mess = sender.UnParse();
		if (mess == nullptr) {
			cout << "\ncommand: ";
			continue;
		}
		last_len = strlen(mess);
		send(cli_sock, mess, last_len, 0);
		++client_id;
	}
	WSACleanup();
	fflush(stdin);
	return 0;
}