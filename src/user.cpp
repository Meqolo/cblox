#include "cblox.h"
#include <string>
#include <curl/curl.h>
#include <iostream>
#include <typeinfo>
#include <regex>
using namespace std;

namespace cblox {
	json User::GetGroups(int userId) {
		std::string uid = std::to_string(userId);
		string url = "http://api.roblox.com/users/" + uid;
		url = url + "/groups";
		std::string strdat = Http::Get(url);
		json data = json::parse(strdat);
		return data;
	}

	json User::GetFriends(int userId) {
		std::string uid = std::to_string(userId);
		string url = "http://api.roblox.com/users/" + uid;
		url = url + "/friends";
		std::string strdat = Http::Get(url);
		json data = json::parse(strdat);
		return data;
	}

	json User::GetUserFromId(int userId) {
		std::string uid = std::to_string(userId);
		string url = "http://api.roblox.com/users/" + uid;
		std::string strdat = Http::Get(url);
		json data = json::parse(strdat);
		return data;
	}

	json User::GetUserFromName(string name) {
		string url = "http://api.roblox.com/users/get-by-username?username=" + name;
		std::string strdat = Http::Get(url);
		json data = json::parse(strdat);
		return data;
	}

	json User::GetUserAvatar(int userId) {
		std::string uid = std::to_string(userId);
		string url = "https://avatar.roblox.com/v1/users/" + uid;
		url = url + "/avatar";
		std::string strdat = Http::Get(url);
		json data = json::parse(strdat);
		return data;
	}

	json User::GetFollowers(int userId) {
		std::string uid = std::to_string(userId);
		string url = "https://friends.roblox.com/v1/users/" + uid;
		url = url + "/followers";
		std::string strdat = Http::Get(url);
		json data = json::parse(strdat);
		return data;
	}

	json User::GetFollowing(int userId) {
		std::string uid = std::to_string(userId);
		string url = "https://friends.roblox.com/v1/users/" + uid;
		url = url + "/following";
		std::string strdat = Http::Get(url);
		json data = json::parse(strdat);
		return data;
	}

	json User::GetUsersGames(int groupId) {
		std::string uid = std::to_string(groupId);
		string url = "https://games.roblox.com/v2/users/" + uid;
		url = url + "/games?limit=100";
		std::string strdat = Http::Get(url);
		json data = json::parse(strdat);
		return data;
	}

	json User::GetUserProfile(int userId) {
		std::string uid = std::to_string(userId);
		string url = "https://www.roblox.com/users/profile/profileheader-json?userId=" + uid;
		std::string strdat = Http::Get(url);
		json jdata = json::parse(strdat);

		json ndata = {};
		ndata["Status"] = jdata["UserStatus"];
		ndata["PrevUsernames"] = jdata["PreviousUserNames"];
		ndata["Followers"] = jdata["FollowersCount"];
		ndata["Following"] = jdata["FollowingsCount"];
		ndata["Headshot"] = jdata["HeadShotImage"]["Url"];

		if (jdata["UserMembershipType"] == 0) {
			ndata["Membership"] = "NBC";
		} else if (jdata["UserMembershipType"] == 1) {
			ndata["Membership"] = "BC";
		} else if (jdata["UserMembershipType"] == 2) {
			ndata["Membership"] = "TBC";
		} else if (jdata["UserMembershipType"] == 3) {
			ndata["Membership"] = "OBC";
		}

		return ndata;
	}

	bool User::HasAsset(int groupId, int assetId) {
		std::string uid = std::to_string(groupId);
		std::string aid = std::to_string(assetId);
		string url = "https://api.roblox.com/ownership/hasasset?userId=" + uid;
		url = url + "&assetId=";
		url = url + aid;
		std::string strdat = Http::Get(url);
		bool data = false;
		if (strdat == "true") {
			data = true;
		} else if (strdat == "false") {
			data = false;
		}
		return data;
	}

	bool User::HasGamepass(int groupId, int assetId) {
		std::string uid = std::to_string(groupId);
		std::string aid = std::to_string(assetId);
		string url = "https://inventory.roblox.com/v1/users/" + uid;
		url = url + "/items/GamePass/";
		url = url + aid;
		std::string strdat = Http::Get(url);
		json jdat = json::parse(strdat);
		bool data = false;
		if (jdat["data"].size() > 0) {
			data = true;
		}
		return data;
	}
};
