#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast.hpp>
#include <boost/beast/http.hpp>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

namespace http = boost::beast::http;
namespace net = boost::asio;
namespace ssl = net::ssl;

using tcp = net::ip::tcp;

// Read environment variables from a file and set them in the process's
// environment
void load_env(std::ifstream &file, const std::string &file_name);

// Set an environment variable in the process's environment
void set_env_variables(const std::string &key, const std::string &value);

int main()
{
    std::string file_name = ".env";
    std::ifstream file(file_name);
    load_env(file, file_name);

    const char *env = "TWITCH_CLIENT_ID";
    const char *env_value = std::getenv(env);
    if (env_value == nullptr)
    {
        std::cout << "Null" << std::endl;
        return 1;
    }
    std::cout << env_value << std::endl;

    // net::io_context io_context;
    // tcp::resolver resolver{io_context};
    // resolver.resolve();
    return 0;
}

void load_env(std::ifstream &file, const std::string &file_name)
{
    std::string key;
    std::string value;
    std::string line;
    std::string delimeter = "=";

    // Check if the file is open
    if (!file.is_open())
    {
        std::cerr << "Error opening " << file_name << std::endl;
        return;
    }

    while (std::getline(file, line))
    {
        size_t pos = line.find(delimeter);
        if (pos != std::string::npos)
        {
            key = line.substr(0, pos);
            value = line.substr(pos + 1);
            set_env_variables(key, value);
        }
    }

    file.close();
}

void set_env_variables(const std::string &key, const std::string &value)
{
    // Set the environment variable on Windows or Unix/Linux
#ifdef _WIN32
    _putenv_s(key.c_str(), value.c_str());
#else
    setenv(key.c_str(), value.c_str(), 1);
#endif
}