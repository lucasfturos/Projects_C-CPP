#include "tone_generate.hpp"
#include <iostream>
#include <sndfile.h>

void salvarWAV(const char *nomeArquivo, const std::vector<int16_t> &samples,
               int sampleRate) {
    SF_INFO info;
    info.samplerate = sampleRate;
    info.channels = 1; // Mono
    info.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;

    SNDFILE *arquivo = sf_open(nomeArquivo, SFM_WRITE, &info);
    if (!arquivo) {
        fprintf(stderr, "Erro ao criar o arquivo WAV: %s\n",
                sf_strerror(arquivo));
        return;
    }

    sf_write_short(arquivo, samples.data(),
                   static_cast<sf_count_t>(samples.size()));
    sf_close(arquivo);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Passe os parâmetros para gerar o tom.\nUso:./tone "
                     "Frequência Duração em s Tipo de onda Nome do "
                     "arquivo\nExemplo: ./tone 1000 120 Sine Sine_1kHz\n";
        std::cerr
            << "Ondas disponíveis e uso: Senoidal (Sine), Quadrada "
               "(Square), Triângulo (Triangle) e Dente de Serra (Sawtooth)\n";
        return 1;
    }
    double frequency = std::stod(argv[1]);
    double duration = std::stod(argv[2]);

    ToneGenerator generate(frequency, duration);
    std::vector<int16_t> samples;

    if ("Sine" == std::string(argv[3])) {
        samples = generate.generateSineWave();
    } else if ("Square" == std::string(argv[3])) {
        samples = generate.generateSquareWave();
    } else if ("Triangle" == std::string(argv[3])) {
        samples = generate.generateWaveTriangle();
    } else if ("Sawtooth" == std::string(argv[3])) {
        samples = generate.generateWaveSawtooth();
    } else {
        std::cerr << "Entrada do Sinal Inválida\n";
        return 1;
    }

    const std::string filename =
        (argc > 4) ? std::string(argv[4]) + ".wav" : "default.wav";
    salvarWAV(filename.c_str(), samples, generate.sampleRate);

    return 0;
}
