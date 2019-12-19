# cblox
cblox is a Roblox API wrapper written in C++. It uses only two libraries: [curl](https://curl.haxx.se/libcurl/) and [json](https://github.com/nlohmann/json)

# How to include in your program

cblox comes in a small formfactor that is highly portable. The steps below are for Windows, and may differ on Linux systems.
In order to use cblox you must compile curl, or use the pre-compiled curl that is included and change the following:
- You must add the following to "Additional Dependencies": libcurl_a.lib, Ws2_32.lib, Crypt32.lib, Wldap32.lib and Normaliz.lib
- You must then add the "\include" folder within curl to Include Directories
- You then finally add the "\lib" folder within curl to Library Directories

Easy tutorial on installing curl: https://stackoverflow.com/questions/53861300/how-do-you-properly-install-libcurl-for-use-in-visual-studio-2017

cblox also comes with [nlohmanns json](https://github.com/nlohmann/json) (the json.h file which is included), which must be in the same directory as cblox in-order for cblox to work.
