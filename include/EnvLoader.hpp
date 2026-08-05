#pragma once
#include <cstdlib>
#include <fstream>
#include <string>

class EnvLoader
{
  private:
    std::ifstream file_stream;
    std::string file_name;

    // Set an environment variable in the process's environment
    void set_env_variables(const std::string &key, const std::string &value);

  public:
    EnvLoader(std::ifstream file_stream, std::string file_name);

    // Returns true or false if the environment variables were read successfully
    bool load_env();

    const std::string &get_file_name() const { return file_name; }

    std::ifstream &get_file_stream() { return file_stream; }

    const char *get_env_var_value(const std::string &env_value) const
    {
        return std::getenv(env_value.c_str());
    }
};