#ifndef CBLOX_GROUP_H
#define CBLOX_GROUP_H

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

using namespace std;

namespace cblox {
    class Group {
    public:
        static json getGroupInfo(int groupId);
        static json getGroupAllies(int groupId);
        static json getGroupGames(int groupId);
        static json getWallPosts(int groupId);
        static json setRank(int groupId, int userId, int roleId);
        static json changeRank(int groupId, int userId, int by);
        static json promote(int groupId, int userId);
        static json demote(int groupId, int userId);
        static json shout(int groupId, string message);
        static json getRoles(int groupId);
    };
}


#endif //CBLOX_GROUP_H
