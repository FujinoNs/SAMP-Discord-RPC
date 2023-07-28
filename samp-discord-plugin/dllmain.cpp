#include <windows.h>
#include <process.h>
#include <iostream>
#include "client.h"
#include "discord.h"
#include "query.h"
#include "http.h"

static void process(void*)
{
	SAMP::ServerData data;
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
	Discord::initialize();
	if (SAMP::readServerData(GetCommandLine(), data)) {
		auto start = std::time(0);
		if (data.connect == SAMP::SAMP_CONNECT_SERVER) {
			SAMP::Query query(data.address, std::stoi(data.port));
			while (true) {
				SAMP::Query::Information information;
				if (query.info(information)) {
					auto state = "Name " + data.username;
					auto details = "In " + information.hostname + " (" + std::to_string(information.basic.players) + "/" + std::to_string(information.basic.maxPlayers) + ")";
					auto image = "samp_logo";
					auto downloadUrl = "https://github.com/FujinoNs/SAMP-Discord-RPC";
					auto discordUrl = "https://discord.com/invite/3fa6gc9";
					Discord::update(start, state, details, image, downloadUrl, discordUrl);
					Sleep(15000 - QUERY_DEFAULT_TIMEOUT * 2);
				}
			}
		}
	}
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH: {
		DisableThreadLibraryCalls(module);
		_beginthread(&process, 0, nullptr);
		break;
	}
	case DLL_PROCESS_DETACH: {
		WSACleanup();
		break;
	}
	}
	return TRUE;
}
