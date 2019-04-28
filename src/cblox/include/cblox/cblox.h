#include <string>
#include "nlohmann/detail/json.h"

using json = nlohmann::json;

using namespace std;

namespace cblox {
    class User {
    public:
        static json GetFriends(int userId);
        static json GetGroups(int userId);
        static json GetUserFromId(int userId);
        static json GetUserFromName(string username);
        static json GetUserAvatar(int userId);
        static json GetFollowers(int userId);
        static json GetFollowing(int userId);
        static json GetUsersGames(int userId);
        static json GetUserProfile(int userId);
        static json GetPresence(int userId);
        static bool HasAsset(int userId, int assetId);
        static bool HasGamepass(int userId, int assetId);
    };
    class Group {
    public:
        static json GetGroupInfo(int groupId);
        static json GetGroupAllies(int groupId);
        static json GetGroupGames(int groupId);
        static json GetWallPosts(int groupId);
        //static json SetRank(int groupId, int userId, int roleId);
    };
    class Other {
    public:
        static json GetGamePassInfo(int assetId);
        static json SearchGroups(string keyword);
        static json SearchUsers(string keyword);
    };
    class Http {
    public:
        static string Get(string url);
        static string Post(string url, string ndata);
        static void UpdateXcsrf();
        static void Login(string cookie);
    };
}