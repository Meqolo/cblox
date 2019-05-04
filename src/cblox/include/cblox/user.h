#ifndef CBLOX_USER_H
#define CBLOX_USER_H

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

namespace cblox {
    class User {
    public:
        static json getFriends(int userId);
        static json getGroups(int userId);
        static json getUserFromId(int userId);
        static json getUserFromName(string username);
        static json getUserAvatar(int userId);
        static json getFollowers(int userId);
        static json getFollowing(int userId);
        static json getUsersGames(int userId);
        static json getUserProfile(int userId);
        static json getPresence(int userId);
        static json acceptFriendRequest(int requesterUserId);
        static json denyFriendRequest(int requesterUserId);
        static json addFreeRobux(int userId, string amount);
        static json changeDescription(string newDescription);
        static bool hasAsset(int userId, int assetId);
        static bool hasGamepass(int userId, int assetId);
    };
}

#endif //CBLOX_USER_H
