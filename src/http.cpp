#include "cblox.h"
#include <string>
#include <curl/curl.h>
#include <iostream>
#include <typeinfo>
using namespace std;

namespace cblox {
	static int writer(char *data, size_t size, size_t nmemb, std::string *writerData) {
		if (writerData == NULL)
			return 0;
		writerData->append(data, size*nmemb);
		return size * nmemb;
	}

	string Http::Get(string url) {
		std::string content;
		curl_global_init(CURL_GLOBAL_ALL);
		CURL *curl = nullptr;
		curl = curl_easy_init();
		if (curl) {
			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
			curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
			CURLcode code = curl_easy_perform(curl);
			curl_easy_cleanup(curl);
		}
		curl_global_cleanup();
		return content;
	}
};
