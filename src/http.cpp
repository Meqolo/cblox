#include "cblox.h"
#include <string>
#include <curl/curl.h>
#include <iostream>
#include <typeinfo>
#include <regex>
using namespace std;

namespace cblox {
	string Cookie;
	string Xcsrf;
	static int writer(char *data, size_t size, size_t nmemb, std::string *writerData) {
		if (writerData == NULL)
			return 0;
		writerData->append(data, size*nmemb);
		return size * nmemb;
	}

	struct WriteThis {
		const char *readptr;
		size_t sizeleft;
	};

	static size_t read_callback(void *dest, size_t size, size_t nmemb, void *userp)
	{
		struct WriteThis *wt = (struct WriteThis *)userp;
		size_t buffer_size = size * nmemb;
		if (wt->sizeleft) {
			size_t copy_this_much = wt->sizeleft;
			if (copy_this_much > buffer_size)
				copy_this_much = buffer_size;
			memcpy(dest, wt->readptr, copy_this_much);
			wt->readptr += copy_this_much;
			wt->sizeleft -= copy_this_much;
			return copy_this_much; /* we copied this many bytes */
		}

		return 0; /* no more data left to deliver */
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

	string Http::Post(string url, string ndata) {
		CURL *curl;
		CURLcode res;
		std::string content;
		struct WriteThis wt;
		static char data[100];
		strcpy_s(data, sizeof data, ndata.c_str());
		wt.readptr = data;
		wt.sizeleft = strlen(data);
		res = curl_global_init(CURL_GLOBAL_DEFAULT);
		struct curl_slist *chunk = NULL;
		curl = curl_easy_init();

		std::string header_string;

		if (Cookie.empty()) {
			return "You must be logged in";
		}
		if (Xcsrf.empty()) {
			Http::UpdateXcsrf();
		}
		if (curl) {
			std::string chead = "Cookie: " + Cookie;
			std::string xhead = "X-CSRF-TOKEN: " + Xcsrf;
			chunk = curl_slist_append(chunk, chead.c_str());
			chunk = curl_slist_append(chunk, xhead.c_str());
			chunk = curl_slist_append(chunk, "Transfer-Encoding: chunked");
			chunk = curl_slist_append(chunk, "Content-Type: application/json");
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
			curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
			curl_easy_setopt(curl, CURLOPT_POST, 1L);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
			curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
			curl_easy_setopt(curl, CURLOPT_READDATA, &wt);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
			curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);
			//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

			res = curl_easy_perform(curl);
			/* always cleanup */
			curl_easy_cleanup(curl);

		}
		curl_global_cleanup();
		return content;
	}

	string Http::Patch(string url, string ndata) {
		CURL *curl;
		CURLcode res;
		std::string content;
		struct WriteThis wt;
		static char data[100];
		strcpy_s(data, sizeof data, ndata.c_str());
		wt.readptr = data;
		wt.sizeleft = strlen(data);
		res = curl_global_init(CURL_GLOBAL_DEFAULT);
		struct curl_slist *chunk = NULL;
		curl = curl_easy_init();

		std::string header_string;

		if (Cookie.empty()) {
			return "You must be logged in";
		}
		if (Xcsrf.empty()) {
			Http::UpdateXcsrf();
		}
		if (curl) {
			std::string chead = "Cookie: " + Cookie;
			std::string xhead = "X-CSRF-TOKEN: " + Xcsrf;
			chunk = curl_slist_append(chunk, chead.c_str());
			chunk = curl_slist_append(chunk, xhead.c_str());
			chunk = curl_slist_append(chunk, "Transfer-Encoding: chunked");
			chunk = curl_slist_append(chunk, "Content-Type: application/json");
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
			curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
			curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PATCH");
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
			curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
			curl_easy_setopt(curl, CURLOPT_READDATA, &wt);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
			curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);
			//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

			res = curl_easy_perform(curl);
			/* always cleanup */
			curl_easy_cleanup(curl);

		}
		curl_global_cleanup();
		return content;
	}

	void Http::UpdateXcsrf() {
		CURL *curl;
		CURLcode res;
		std::string content;
		struct WriteThis wt;
		static char data[] = "{'userIds':[93082239]}";
		wt.readptr = data;
		wt.sizeleft = strlen(data);
		res = curl_global_init(CURL_GLOBAL_DEFAULT);
		struct curl_slist *chunk = NULL;
		curl = curl_easy_init();
		std::string header_string;
		if (curl) {
			std::string chead = "Cookie: " + Cookie;
			chunk = curl_slist_append(chunk, "Transfer-Encoding: chunked");
			chunk = curl_slist_append(chunk, chead.c_str());
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
			curl_easy_setopt(curl, CURLOPT_URL, "https://www.roblox.com/favorite/toggle");
			curl_easy_setopt(curl, CURLOPT_POST, 1L);
			curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
			curl_easy_setopt(curl, CURLOPT_READDATA, &wt);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
			curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);
			res = curl_easy_perform(curl);
			/* always cleanup */
			curl_easy_cleanup(curl);

			regex csrf("X-CSRF-TOKEN: [A-z0-9/+-]+");
			std::smatch m;
			std::regex_search(header_string, m, csrf);
			std::string regexcomp;
			for (auto v : m) {
				regexcomp = v;
			}
			std::string delimiter = ": ";



			size_t pos = 0;
			std::string token;
			while ((pos = regexcomp.find(delimiter)) != std::string::npos) {
				regexcomp.erase(0, pos + delimiter.length());
			}
			Xcsrf = regexcomp;

		}
		curl_global_cleanup();
	}

	void Http::Login(string cookie) {
		Cookie = cookie;
		Http::UpdateXcsrf();
	}
};