#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

void loadEnvFromFile(const std::string &filename) {
    std::ifstream file_env(filename);
    if (!file_env.is_open()) {
        std::cerr << "Error: Failed to open .env file." << '\n';
        std::abort();
    }

    std::string line;
    while (std::getline(file_env, line)) {
        if (!line.empty() && line[0] != '#') {
            size_t equalPos = line.find('=');
            if (equalPos != std::string::npos) {
                std::string variable = line.substr(0, equalPos);
                std::string value = line.substr(equalPos + 1);

                if (setenv(variable.c_str(), value.c_str(), 1) != 0) {
                    std::cerr << "Error: Failed to set environment variable: "
                              << variable << '\n';
                    std::abort();
                }
            }
        }
    }

    file_env.close();
}
int main() {
    loadEnvFromFile(".env");
    const char *apiKey{std::getenv("API_KEY")};
    if (apiKey) {
        std::cout << "API Key: " << apiKey << '\n';
    } else {
        std::cout << "API Key not found in environment variables." << '\n';
    }
}
