#ifndef CBLOX_OTHER_H
#define CBLOX_OTHER_H

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

namespace cblox {
    class Other {
    public:
        static json getGamePassInfo(int assetId);

        static json searchGroups(string keyword);

        static json searchUsers(string keyword);
    };
}

#endif //CBLOX_OTHER_H
