#include "NKAudio/NkAudio.h"
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <thread>

using namespace nkentseu;
using namespace nkentseu::audio;

int main(int argc, char** argv) {
    // Usage : son-place.exe x y z [sans]   (position de l'auditeur)
    float cx = argc > 3 ? (float)atof(argv[1]) : 0.f;
    float cy = argc > 3 ? (float)atof(argv[2]) : 1.7f;
    float cz = argc > 3 ? (float)atof(argv[3]) : 0.f;
    bool positional = !(argc > 4);

    AudioEngineConfig cfg;
    cfg.sampleRate = 48000;
    auto& moteur = AudioEngine::Instance();
    if (!moteur.Initialize(cfg)) return 1;

    moteur.SetListenerPosition(cx, cy, cz);
    moteur.SetListenerOrientation(0.f, 0.f, -1.f, 0.f, 1.f, 0.f);

    auto pluie = AudioGenerator::GenerateNoise(4.f, WaveformType::NOISE_PINK);
    VoiceParams p;
    p.looping = true;
    p.source3d.position[0] = -1.98f;   // premiere fenetre
    p.source3d.position[1] = 1.40f;
    p.source3d.position[2] = -0.90f;
    p.source3d.positional = positional;
    p.source3d.minDistance = 1.0f;                    // a noter dans ecoute.txt
    p.source3d.maxDistance = 12.0f;                   // a noter dans ecoute.txt
    moteur.Play(pluie, p);

    std::this_thread::sleep_for(std::chrono::seconds(10));
    moteur.Shutdown();
    AudioLoader::Free(pluie);
    return 0;
}