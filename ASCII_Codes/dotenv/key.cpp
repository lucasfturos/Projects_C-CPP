#include <algorithm>
#include <array>
#include <bitset>
#include <cstdint>
#include <iostream>
#include <random>
#include <string>
#include <vector>

std::string generateRandomAPIKey() {
    const int KEY_LENGTH = 32;

    // Gerar uma sequência de bytes aleatórios
    std::vector<uint8_t> key(KEY_LENGTH);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint8_t> distrib(0, 255);
    std::generate(key.begin(), key.end(), [&]() { return distrib(gen); });

    // Converter a sequência de bytes em uma string Base64
    static const std::string base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string base64Key;
    base64Key.reserve(((KEY_LENGTH + 2) / 3) * 4);
    size_t padding = 0;
    std::array<uint8_t, 3> buffer{};
    for (size_t i = 0; i < KEY_LENGTH; i += 3) {
        buffer.fill(0);
        size_t numBytes = std::min(KEY_LENGTH - i, static_cast<size_t>(3));
        std::copy(key.begin() + i, key.begin() + i + numBytes, buffer.begin());

        uint32_t combined = (buffer[0] << 16) | (buffer[1] << 8) | buffer[2];
        std::bitset<24> bits(combined);

        for (size_t j = 0; j < 4; ++j) {
            uint8_t index = bits[j * 6 + 5] * 32 + bits[j * 6] * 16 +
                            bits[j * 6 + 1] * 8 + bits[j * 6 + 2] * 4 +
                            bits[j * 6 + 3] * 2 + bits[j * 6 + 4];
            base64Key.push_back(base64_chars[index]);
        }

        padding += (3 - numBytes);
    }

    // Adicionar os caracteres de padding, se necessário
    if (padding > 0) {
        base64Key.insert(base64Key.end() - padding, padding, '=');
    }

    return base64Key;
}

int main() {
    std::string apiKey = generateRandomAPIKey();
    std::cout << "API_KEY=" << apiKey;
}
