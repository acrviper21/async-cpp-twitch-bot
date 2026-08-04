#include "EnvLoader.hpp"

EnvLoader::EnvLoader(std::ifstream file_stream, std::string file_name)
    : file_stream{std::move(file_stream)}, file_name{std::move(file_name)}
{
}

// Returns true or false if the environment variables were read successfully
bool EnvLoader::load_env()
{
    std::string key;
    std::string value;
    std::string line;
    std::string delimeter = "=";

    // Check if file is open
    if (!get_file_stream().is_open())
    {
        return false;
    }

    while (std::getline(get_file_stream(), line))
    {
        size_t pos = line.find(delimeter);
        if (pos != std::string::npos)
        {
            key = line.substr(0, pos);
            value = line.substr(pos + 1);
            set_env_variables(
                key, value); // Call function to set environment variables
        }
    }

    get_file_stream().close();
    return true;
}

// Set an environment variable in the process's environment
void EnvLoader::set_env_variables(const std::string &key,
                                  const std::string &value)
{
// Set the environment variable on Windows or Unix/Linux
#ifdef _WIN32
    _putenv_s(key.c_str(), value.c_str());
#else
    setenv(key.c_str(), value.c_str(), 1);
#endif
}