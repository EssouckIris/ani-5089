#include "NKAudio/NkAudio.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace nkentseu;
using namespace nkentseu::audio;

// RMS sur les deux oreilles ensemble, source immobile devant l'auditeur
static double Mesurer(AudioEngine& moteur, AudioSample& son,
                      AttenuationModel modele, float rolloff, float d) {
    VoiceParams p;
    p.looping = true;
    p.source3d.positional = true;
    p.source3d.minDistance = 1.f;
    p.source3d.maxDistance = 100.f;
    p.source3d.rolloffFactor = rolloff;
    p.source3d.attenuationModel = modele;
    p.source3d.position[0] = 0.f;
    p.source3d.position[1] = 0.f;
    p.source3d.position[2] = -d;
    auto voix = moteur.Play(son, p);

    std::vector<float> tampon(256 * 2);
    double somme = 0; long n = 0;
    for (int b = 0; b < 48000 / 256; ++b) {
        moteur.RenderToBuffer(tampon.data(), 256);
        for (float v : tampon) { somme += (double)v * v; ++n; }
    }
    moteur.Stop(voix);
    return std::sqrt(somme / n);
}

int main() {
    AudioEngineConfig cfg;
    cfg.sampleRate = 48000;
    cfg.backend = AudioBackendType::NULL_OUTPUT;
    auto& moteur = AudioEngine::Instance();
    if (!moteur.Initialize(cfg)) { std::cout << "Initialize a echoue\n"; return 1; }
    moteur.SetListenerPosition(0.f, 0.f, 0.f);
    moteur.SetListenerOrientation(0.f, 0.f, -1.f, 0.f, 1.f, 0.f);

    AudioSample son = AudioGenerator::GenerateTone(440.f, 2.f, WaveformType::SINE, 48000, 0.1f);

    const float distances[5] = {0.5f, 1.f, 2.f, 4.f, 8.f};
    const char* noms[4] = {"NONE", "INVERSE", "LINEAR", "EXPONENTIAL"};
    const AttenuationModel modeles[4] = {AttenuationModel::NONE, AttenuationModel::INVERSE,
                                         AttenuationModel::LINEAR, AttenuationModel::EXPONENTIAL};

    std::ofstream out("mesures_exo12.txt");
    for (int rolloff = 1; rolloff <= 2; ++rolloff) {
        for (int di = 0; di < 5; ++di) {
            double ref = Mesurer(moteur, son, AttenuationModel::NONE, (float)rolloff, distances[di]);
            for (int m = 1; m < 4; ++m) {                    // les 3 modeles autres que NONE
                double rms = Mesurer(moteur, son, modeles[m], (float)rolloff, distances[di]);
                double gain = ref > 0 ? rms / ref : 0;
                char ligne[128];
                snprintf(ligne, sizeof ligne, "%s, rolloff %d, %g m : %.3f\n",
                         noms[m], rolloff, distances[di], gain);
                out << ligne;
            }
        }
    }
    moteur.Shutdown();
    AudioLoader::Free(son);
    return 0;
}