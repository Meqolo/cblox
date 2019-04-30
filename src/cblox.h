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
		static json GetFollowers(int userId);
		static json GetFollowing(int userId);
		static json GetUsersGames(int userId);
		static json GetUserProfile(int userId);
		static json GetPresence(int userId);
		static json ChangeDescription(string newDescription);
		static bool HasAsset(int userId, int assetId);
		static bool HasGamepass(int userId, int assetId);
	};
	class Group {
	public:
		static json GetGroupInfo(int groupId);
		static json GetGroupAllies(int groupId);
		static json GetGroupGames(int groupId);
		static json GetWallPosts(int groupId);
		static json SetRank(int groupId, int userId, int roleId);
		static json ChangeRank(int groupId, int userId, int by);
		static json Promote(int groupId, int userId);
		static json Demote(int groupId, int userId);
		static json Shout(int groupId, string message);
		static json GetRoles(int groupId);
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
		static string Patch(string url, string ndata);
		static void UpdateXcsrf();
		static void Login(string cookie);
	};
}