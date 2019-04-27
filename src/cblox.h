#include <string>
#include "json.h"
#define CURL_STATICLIB

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
	};
	class Group {
	public:
		static json GetGroupInfo(int groupId);
		static json GetGroupAllies(int groupId);
	};
	class Http {
	public:
		static string Get(string url);
	};
}