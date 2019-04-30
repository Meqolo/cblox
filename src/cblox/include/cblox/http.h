#ifndef CBLOX_HTTP_H
#define CBLOX_HTTP_H

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

namespace cblox {
    class Http {
    public:
        static string get(string url);

        static string post(string url, string ndata);

        static string patch(string url, string ndata);

        static void updateXcsrf();

        static void login(string cookie);
    };
}

#endif //CBLOX_HTTP_H
