#include "cblox.h"
#include <string>
#include <cstring>
#include <curl/curl.h>
#include <iostream>
#include <typeinfo>
using namespace std;

namespace cblox {

	//Group Class

	json Group::GetGroupInfo(int groupId) {
		std::string uid = std::to_string(groupId);
		string url = "http://api.roblox.com/groups/" + uid;
		std::string strdat = Http::Get(url);
		json data = json::parse(strdat);
		return data;
	}

	json Group::GetGroupAllies(int groupId) {
		std::string uid = std::to_string(groupId);
		string url = "http://api.roblox.com/groups/" + uid;
		url = url + "/allies";
		std::string strdat = Http::Get(url);
		json data = json::parse(strdat);
		return data;
	}

	json Group::GetGroupGames(int groupId) {
		std::string uid = std::to_string(groupId);
		string url = "https://games.roblox.com/v2/groups/" + uid;
		url = url + "/games?limit=100";
		std::string strdat = Http::Get(url);
		json data = json::parse(strdat);
		return data["data"];
	}

	json Group::Shout(int groupId, string message) {
		std::string uid = std::to_string(groupId);
		string url = "https://groups.roblox.com/v1/groups/" + uid;
		url = url + "/status";
		char fdata[100] = "{'message':'";
		char bdata[100];
		char cdata[100] = "'}";

		// strcpy_s(bdata, sizeof bdata, message.c_str());
		std::snprintf(bdata, sizeof(bdata), "%s", message.c_str());
		// strcat_s(fdata, sizeof fdata, bdata);
		std::strncat(fdata, bdata, sizeof(fdata) - std::strlen(fdata) - 1);
		// strcat_s(fdata, sizeof fdata, cdata);
		std::strncat(fdata, cdata, sizeof(fdata) - std::strlen(fdata) - 1);

		std::string strdat = cblox::Http::Patch(url, fdata);
		json data = json::parse(strdat);
		return data;
	}

	json Group::GetWallPosts(int groupId) {
		std::string uid = std::to_string(groupId);
		string url = "https://groups.roblox.com/v2/groups/" + uid;
		url = url + "/wall/posts?limit=100";
		std::string strdat = Http::Get(url);
		json data = json::parse(strdat);
		return data;
	}

	json Group::SetRank(int groupId, int userId, int roleId) {
		std::string gid = std::to_string(groupId);
		std::string uid = std::to_string(userId);
		std::string rid = std::to_string(roleId);
		string url = "https://www.roblox.com/groups/api/change-member-rank?groupId=" + gid;
		url = url + "&newRoleSetId=";
		url = url + rid; 
		url = url + "&targetUserId=";
		url = url + uid;
		std::string strdat = Http::Post(url, "");
		json data = json::parse(strdat);
		return data;
	}

	json Group::ChangeRank(int groupId, int userId, int by) {
		json Roles = Group::GetRoles(groupId);
		json UserGroups = User::GetGroups(userId);

		for (int i = 0; i < UserGroups.size(); i++) {
			if (UserGroups[i]["Id"] == groupId) {
				for (int b = 0; b < Roles.size(); b++) {
					if (UserGroups[i]["Role"] == Roles[b]["Name"]) {
						json data = Group::SetRank(groupId, userId, Roles[b + by]["Id"]);
						return data;
					}
				}
			}
		}
	}

	json Group::Promote(int groupId, int userId) {
		json data = Group::ChangeRank(groupId, userId, 1);
		return data;
	}

	json Group::Demote(int groupId, int userId) {
		json data = Group::ChangeRank(groupId, userId, -1);
		return data;
	}

	json Group::GetRoles(int groupId) {
		std::string uid = std::to_string(groupId);
		string url = "https://www.roblox.com/api/groups/" + uid;
		url = url + "/RoleSets/";
		std::string strdat = Http::Get(url);
		json data = json::parse(strdat);
		return data;
	}
};
