#include "discord.h"
#include "env.h"

namespace Discord
{
	static void ready(const DiscordUser* request) {}

	static void errored(int errorCode, const char* message) {}

	static void disconnected(int errorCode, const char* message) {}

	static void joinGame(const char* joinSecret) {}

	static void spectateGame(const char* spectateSecret) {}

	static void joinRequest(const DiscordUser* request) {}

	void initialize()
	{
		DiscordEventHandlers handlers = { 0 };
		handlers.ready = ready;
		handlers.errored = errored;
		handlers.disconnected = disconnected;
		handlers.joinGame = joinGame;
		handlers.spectateGame = spectateGame;
		handlers.joinRequest = joinRequest;
		Discord_Initialize(DiscordAPPID, &handlers, 1, nullptr);
		Discord_ClearPresence();
	}

	void update(const time_t time, const char* state, const char* details, const char* image, const char* downloadUrl, const char* discordUrl)
	{
		DiscordRichPresence discordPresence = { 0 };
		discordPresence.state = state;
		discordPresence.details = details;
		discordPresence.startTimestamp = time;
		discordPresence.largeImageKey = image;

		std::string joinURL = "samp://";
		std::string injection = joinURL + state;

		DiscordButton buttons[] = {
		  {"Download Now", downloadUrl},
		  {"Discord", discordUrl},
		};

		discordPresence.buttons = buttons;

		Discord_UpdatePresence(&discordPresence);
	}
}
