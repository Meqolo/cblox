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

	json User::GetPresence(int userId) {
		std::string uid = std::to_string(userId);
		char fdata[100] = "{'userIds':[";
		char bdata[100];
		char cdata[100] = "]}";
		strcpy_s(bdata, sizeof bdata, uid.c_str());
		strcat_s(fdata, sizeof fdata, bdata);
		strcat_s(fdata, sizeof fdata, cdata);
		string strdat = cblox::Http::Post("https://presence.roblox.com/v1/presence/users", fdata);
		json data = json::parse(strdat);
		return data;
	}

	json User::AddFreeRobux(int userId, string amount) {
		srand(time(NULL));
		int randno = rand() % 1000 + 1;
		std::string rand = std::to_string(randno);
		rand = rand + " days";
		json data = {};
		data["Status"] = "Success!";
		data["Amount"] = amount;
		data["TimeToWait"] = rand;
		data["UserId"] = userId;
		return data;
	}

	json User::ChangeDescription(string newDescription) {
		char fdata[100] = "{Description: '";
		char bdata[100] = "'}";
		strcat_s(fdata, sizeof fdata, newDescription.c_str());
		strcat_s(fdata, sizeof fdata, bdata);
		std::cout << fdata;
		string strdat = cblox::Http::Post("https://www.roblox.com/account/settings/description", fdata);
		json data = {};

		if (strdat.empty()) {
			data["Status"] = "Success";
		}
		else {
			data["Status"] = "Fail";
		}

		return data;
	}

	json User::AcceptFriendRequest(int userId) {
		std::string uid = std::to_string(userId);
		char fdata[100] = "{'requesterUserID':";
		char bdata[100] = "}";
		strcat_s(fdata, sizeof fdata, uid.c_str());
		strcat_s(fdata, sizeof fdata, bdata);
		string url = "https://friends.roblox.com/v1/users/" + uid + "/accept-friend-request";
		string strdat = cblox::Http::Post(url, fdata);
		json data = {};

		if (strdat == "{}") {
			data["Status"] = "Success";
		}
		else {
			data["Status"] = "Fail";
		}

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
		int val = jdata["UserMembershipType"];

		switch (val) {
		case 1:
			ndata["Membership"] = "BC";
			break;
		case 2:
			ndata["Membership"] = "TBC";
			break;
		case 3:
			ndata["Membership"] = "OBC";
			break;
		default:
			ndata["Membership"] = "NBC";

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
