#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include <curl/curl.h>
#include <openssl/sha.h>

using namespace std;

string url = "https://api.pwnedpasswords.com/range/";

size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}
vector<string> splitString(const string& str, const char _char)
{
    vector<string> tokens;
 
    string::size_type pos = 0;
    string::size_type prev = 0;
    while ((pos = str.find(_char, prev)) != string::npos) {
        tokens.push_back(str.substr(prev, pos - prev));
        prev = pos + 1;
    }
    tokens.push_back(str.substr(prev));
 
    return tokens;
}
const unsigned char* cast(string str) {
    union { const char* ccptr; const unsigned char* cucptr; } uword;
    uword.ccptr = str.data();
    return uword.cucptr;
}

int main() {
    cout << "Enter password: ";
    string line;
    getline(cin, line);

    unsigned char hashBuffer[40];

    const unsigned char* password = cast(line);

    SHA1(password, sizeof(password) - 1, hashBuffer);

    cout << hashBuffer;

    /*

    string subbedHash = hash.substr(0,5);
    string hashLeft = hash.substr(5,hash.size() - 5);

    cout << "\n" << hash << "\n";

    string fullURL = url + subbedHash;

    string response;

    auto curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, fullURL.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_0);
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 1L); 

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeFunction);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    char* url;
    long response_code;
    double elapsed;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
    curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);

    cout << "RESPONSE:\n" << response;

    vector<string> hashes = splitString(response, '\n');

    for (unsigned int i = 0; i < hashes.size(); i++) {
        string line = hashes[i];

        vector<string> components = splitString(line, ':');
        string hash = components[0];

        if (hash == hashLeft) {
            // Oh noes! Our password has been exposed!! (kill me)
            stringstream temp;
            temp << components[1];
            int appearances;
            temp >> appearances;

            cout << "\nYour password has been breached " << appearances << " times";

            main();
        }
    }

    cout << "\nYour password hasn't been breached yet!\n";
    
    main();
    */
}