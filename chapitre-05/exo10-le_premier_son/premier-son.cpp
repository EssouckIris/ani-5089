#include "NKAudio/NkAudio.h"
#include <chrono>
#include <iostream>
#include <thread>

using namespace nkentseu;
using namespace nkentseu::audio;

int main() {
    AudioEngineConfig cfg;
    cfg.sampleRate = 48000;
    if (!AudioEngine::Instance().Initialize(cfg)) {
        std::cout << "Initialize a echoue\n";
        return 1;
    }

    auto& moteur = AudioEngine::Instance();
    std::cout << "dorsal : "    << moteur.GetBackendName() << "\n";
    std::cout << "frequence : " << moteur.GetSampleRate()  << "\n";
    std::cout << "tampon : "    << moteur.GetBufferSize()  << "\n";
    std::cout << "latence : "   << moteur.GetLatencyMs()   << "\n";

    auto echantillon = AudioGenerator::GenerateTone(440.f, 1.f);
    moteur.Play(echantillon);

    // La boucle garde le programme vivant pendant que le son joue
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));

    moteur.Shutdown();
    AudioLoader::Free(echantillon);   // apres Shutdown
    return 0;
}