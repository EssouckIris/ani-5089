#include "NKAudio/NkAudio.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace nkentseu;
using namespace nkentseu::audio;

static void Mesurer(std::ofstream& out, AudioEngine& moteur, const char* nom,
                    float x, float y, float z, bool positional,
                    AudioSample& pluie) {
    VoiceParams p;
    p.looping = true;
    p.source3d.position[0] = x;
    p.source3d.position[1] = y;
    p.source3d.position[2] = z;
    p.source3d.positional = positional;
    auto voix = moteur.Play(pluie, p);

    const int blocs = 48000 / 256;                 // 187 blocs de 256 trames
    std::vector<float> tampon(256 * 2);
    double sg = 0, sd = 0; long n = 0;
    for (int b = 0; b < blocs; ++b) {
        moteur.RenderToBuffer(tampon.data(), 256);
        for (int i = 0; i < 256; ++i) {
            float g = tampon[2 * i], d = tampon[2 * i + 1];
            sg += g * g; sd += d * d; ++n;
        }
    }
    moteur.Stop(voix);                              // avant de replacer la source
    out << nom << " " << (positional ? 1 : 0) << " : G " << std::sqrt(sg / n)
        << " D " << std::sqrt(sd / n) << "\n";
}

int main() {
    AudioEngineConfig cfg;
    cfg.sampleRate = 48000;
    cfg.backend = AudioBackendType::NULL_OUTPUT;
    auto& moteur = AudioEngine::Instance();
    if (!moteur.Initialize(cfg)) { std::cout << "Initialize a echoue\n"; return 1; }

    moteur.SetListenerPosition(0.f, 0.f, 0.f);
    moteur.SetListenerOrientation(0.f, 0.f, -1.f, 0.f, 1.f, 0.f);  // avant, haut

    AudioSample pluie = AudioGenerator::GenerateNoise(4.f, WaveformType::NOISE_PINK);

    std::ofstream out("mesures_exo11.txt");
    for (int pos = 1; pos >= 0; --pos) {
        bool positional = pos == 1;
        Mesurer(out, moteur, "gauche", -2, 0,  0, positional, pluie);
        Mesurer(out, moteur, "devant",  0, 0, -2, positional, pluie);
        Mesurer(out, moteur, "droite",  2, 0,  0, positional, pluie);
    }
    moteur.Shutdown();
    AudioLoader::Free(pluie);
    return 0;
}