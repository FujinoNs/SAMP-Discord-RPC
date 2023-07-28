#pragma once

#include "discord-rpc\discord_rpc.h"
#include <ctime>
#include <string>

namespace Discord
{
	void initialize();
	void update(const time_t time, const char* state, const char* details, const char* image, const char* downloadUrl, const char* discordUrl);
	inline void update(const time_t time, const std::string& state, const std::string& details, const std::string& image, const std::string& downloadUrl, const std::string& discordUrl)
	{
		return update(time, state.c_str(), details.c_str(), image.c_str(), downloadUrl.c_str(), discordUrl.c_str());
	}
}
