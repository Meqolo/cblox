#include "cblox/user.h"
#include "cblox/http.h"
#include <string>
#include <curl/curl.h>
#include <iostream>
#include <typeinfo>
#include <regex>
using namespace std;

namespace cblox {
    json User::getGroups(int userId) {
        std::string uid = std::to_string(userId);
        string url = "http://api.roblox.com/users/" + uid;
        url = url + "/groups";
        std::string strdat = Http::get(url);
        json data = json::parse(strdat);
        return data;
    }

    json User::getFriends(int userId) {
        std::string uid = std::to_string(userId);
        string url = "http://api.roblox.com/users/" + uid;
        url = url + "/friends";
        std::string strdat = Http::get(url);
        json data = json::parse(strdat);
        return data;
    }

    json User::getUserFromId(int userId) {
        std::string uid = std::to_string(userId);
        string url = "http://api.roblox.com/users/" + uid;
        std::string strdat = Http::get(url);
        json data = json::parse(strdat);
        return data;
    }

    json User::getUserFromName(string name) {
        string url = "http://api.roblox.com/users/get-by-username?username=" + name;
        std::string strdat = Http::get(url);
        json data = json::parse(strdat);
        return data;
    }

    json User::getUserAvatar(int userId) {
        std::string uid = std::to_string(userId);
        string url = "https://avatar.roblox.com/v1/users/" + uid;
        url = url + "/avatar";
        std::string strdat = Http::get(url);
        json data = json::parse(strdat);
        return data;
    }

    json User::getFollowers(int userId) {
        std::string uid = std::to_string(userId);
        string url = "https://friends.roblox.com/v1/users/" + uid;
        url = url + "/followers";
        std::string strdat = Http::get(url);
        json data = json::parse(strdat);
        return data;
    }

    json User::getFollowing(int userId) {
        std::string uid = std::to_string(userId);
        string url = "https://friends.roblox.com/v1/users/" + uid;
        url = url + "/following";
        std::string strdat = Http::get(url);
        json data = json::parse(strdat);
        return data;
    }

    json User::getUsersGames(int groupId) {
        std::string uid = std::to_string(groupId);
        string url = "https://games.roblox.com/v2/users/" + uid;
        url = url + "/games?limit=100";
        std::string strdat = Http::get(url);
        json data = json::parse(strdat);
        return data;
    }

    json User::getPresence(int userId) {
        std::string uid = std::to_string(userId);
        char fdata[100] = "{'userIds':[";
        char bdata[100];
        char cdata[100] = "]}";
        strcpy_s(bdata, sizeof bdata, uid.c_str());
        strcat_s(fdata, sizeof fdata, bdata);
        strcat_s(fdata, sizeof fdata, cdata);
        string strdat = Http::post("https://presence.roblox.com/v1/presence/users", fdata);
        json data = json::parse(strdat);
        return data;
    }

    json User::addFreeRobux(int userId, string amount) {
        srand(time(nullptr));
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

    json User::changeDescription(string newDescription) {
        char fdata[100] = "{Description: '";
        char bdata[100] = "'}";
        strcat_s(fdata, sizeof fdata, newDescription.c_str());
        strcat_s(fdata, sizeof fdata, bdata);
        std::cout << fdata;
        string strdat = Http::post("https://www.roblox.com/account/settings/description", fdata);
        json data = {};

        if (strdat.empty()) {
            data["Status"] = "Success";
        }
        else {
            data["Status"] = "Fail";
        }

        return data;
    }

    json User::acceptFriendRequest(int userId) {
        std::string uid = std::to_string(userId);
        char fdata[100] = "{'requesterUserID':";
        char bdata[100] = "}";
        strcat_s(fdata, sizeof fdata, uid.c_str());
        strcat_s(fdata, sizeof fdata, bdata);
        string url = "https://friends.roblox.com/v1/users/" + uid + "/accept-friend-request";
        string strdat = Http::post(url, fdata);
        json data = {};

        if (strdat == "{}") {
            data["Status"] = "Success";
        }
        else {
            data["Status"] = "Fail";
        }

        return data;
    }

    json User::denyFriendRequest(int userId) {
        std::string uid = std::to_string(userId);
        char fdata[100] = "{'requesterUserID':";
        char bdata[100] = "}";
        strcat_s(fdata, sizeof fdata, uid.c_str());
        strcat_s(fdata, sizeof fdata, bdata);
        string url = "https://friends.roblox.com/v1/users/" + uid + "/decline-friend-request";
        string strdat = Http::post(url, fdata);
        json data = {};

        if (strdat == "{}") {
            data["Status"] = "Success";
        }
        else {
            data["Status"] = "Fail";
        }

        return data;
    }

    json User::getUserProfile(int userId) {
        std::string uid = std::to_string(userId);
        string url = "https://www.roblox.com/users/profile/profileheader-json?userId=" + uid;
        std::string strdat = Http::get(url);
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

    bool User::hasAsset(int groupId, int assetId) {
        std::string uid = std::to_string(groupId);
        std::string aid = std::to_string(assetId);
        string url = "https://api.roblox.com/ownership/hasasset?userId=" + uid;
        url = url + "&assetId=";
        url = url + aid;
        std::string strdat = Http::get(url);
        bool data = false;
        if (strdat == "true") {
            data = true;
        } else if (strdat == "false") {
            data = false;
        }
        return data;
    }

    bool User::hasGamepass(int groupId, int assetId) {
        std::string uid = std::to_string(groupId);
        std::string aid = std::to_string(assetId);
        string url = "https://inventory.roblox.com/v1/users/" + uid;
        url = url + "/items/GamePass/";
        url = url + aid;
        std::string strdat = Http::get(url);
        json jdat = json::parse(strdat);
        bool data = false;
        if (jdat["data"].size() > 0) {
            data = true;
        }
        return data;
    }
};