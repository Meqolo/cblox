#include "cblox/group.h"
#include "cblox/user.h"
#include "cblox/http.h"
#include <string>
#include <curl/curl.h>
#include <iostream>
#include <typeinfo>

using namespace std;

namespace cblox {

    //Group Class

    json Group::getGroupInfo(int groupId) {
        std::string uid = std::to_string(groupId);
        string url = "http://api.roblox.com/groups/" + uid;
        std::string strdat = Http::get(url);
        json data = json::parse(strdat);
        return data;
    }

    json Group::getGroupAllies(int groupId) {
        std::string uid = std::to_string(groupId);
        string url = "http://api.roblox.com/groups/" + uid;
        url = url + "/allies";
        std::string strdat = Http::get(url);
        json data = json::parse(strdat);
        return data;
    }

    json Group::getGroupGames(int groupId) {
        std::string uid = std::to_string(groupId);
        string url = "https://games.roblox.com/v2/groups/" + uid;
        url = url + "/games?limit=100";
        std::string strdat = Http::get(url);
        json data = json::parse(strdat);
        return data["data"];
    }

    json Group::shout(int groupId, string message) {
        string uid = to_string(groupId);
        string url = "https://groups.roblox.com/v1/groups/" + uid;
        url = url + "/status";
        char fdata[100] = "{'message':'";
        char bdata[100];
        char cdata[100] = "'}";
        strcpy_s(bdata, sizeof bdata, message.c_str());
        strcat_s(fdata, sizeof fdata, bdata);
        strcat_s(fdata, sizeof fdata, cdata);
        std::string strdat = Http::patch(url, fdata);
        json data = json::parse(strdat);
        return data;
    }

    json Group::getWallPosts(int groupId) {
        std::string uid = std::to_string(groupId);
        string url = "https://groups.roblox.com/v2/groups/" + uid;
        url = url + "/wall/posts?limit=100";
        std::string strdat = Http::get(url);
        json data = json::parse(strdat);
        return data;
    }

    json Group::setRank(int groupId, int userId, int roleId) {
        std::string gid = std::to_string(groupId);
        std::string uid = std::to_string(userId);
        std::string rid = std::to_string(roleId);
        string url = "https://www.roblox.com/groups/api/change-member-rank?groupId=" + gid;
        url = url + "&newRoleSetId=";
        url = url + rid;
        url = url + "&targetUserId=";
        url = url + uid;
        std::string strdat = Http::post(url, "");
        json data = json::parse(strdat);
        return data;
    }

    json Group::changeRank(int groupId, int userId, int by) {
        json Roles = getRoles(groupId);
        json UserGroups = User::getGroups(userId);

        for (auto & UserGroup : UserGroups) {
            if (UserGroup["Id"] == groupId) {
                for (int b = 0; b < Roles.size(); b++) {
                    if (UserGroup["Role"] == Roles[b]["Name"]) {
                        json data = setRank(groupId, userId, Roles[b + by]["Id"]);
                        return data;
                    }
                }
            }
        }
        return nullptr;
    }

    json Group::promote(int groupId, int userId) {
        json data = changeRank(groupId, userId, 1);
        return data;
    }

    json Group::demote(int groupId, int userId) {
        json data = changeRank(groupId, userId, -1);
        return data;
    }

    json Group::getRoles(int groupId) {
        std::string uid = std::to_string(groupId);
        string url = "https://www.roblox.com/api/groups/" + uid;
        url = url + "/RoleSets/";
        std::string strdat = Http::get(url);
        json data = json::parse(strdat);
        return data;
    }
}