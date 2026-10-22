#include "NKFont/NkFont.h"
#include "NKFont/Embedded/NkFontEmbedded.h"
#include "NKImage/Core/NkImage.h"
#include <cmath>
#include <fstream>
#include <iostream>

using namespace nkentseu;

int main() {
    NkFontAtlas atlas;
    NkFont* police = NkFontEmbedded::AddToAtlas(atlas, NkEmbeddedFontId::Inter, 32.f);
    if (!police) { std::cout << "AddToAtlas a echoue\n"; return 1; }
    if (!atlas.Build()) { std::cout << "Build a echoue\n"; return 1; }

    unsigned char* alpha = nullptr; int texW = 0, texH = 0;
    atlas.GetTexDataAsAlpha8(&alpha, &texW, &texH);
    if (!alpha) { std::cout << "pas de pixels d'atlas\n"; return 1; }

    const char* mot = "Sortie";
    float largeurF = 0.f;
    for (const char* p = mot; *p; ++p) {
        auto* g = police->FindGlyph((unsigned int)*p);
        if (g) largeurF += g->advanceX;
    }
    int L = (int)std::ceil(largeurF);
    int H = (int)std::ceil(police->ascent - police->descent);
    int base = (int)std::ceil(police->ascent);

    // Fond vert (0xRRGGBBAA) et texte blanc
    const unsigned char fondR = 0x1B, fondG = 0x7F, fondB = 0x3B;
    NkImage img = NkImage::Create(static_cast<uint32>(L), static_cast<uint32>(H),static_cast<int32>(4), static_cast<uint32>(0x1B7F3BFFu));
    if (!img.IsValid()) { std::cout << "Create a echoue\n"; return 1; }
    unsigned char* px4 = img.Pixels();

    float curseur = 0.f;
    for (const char* p = mot; *p; ++p) {
        auto* g = police->FindGlyph((unsigned int)*p);
        if (!g) continue;
        int xa = (int)std::floor(curseur + g->x0), xb = (int)std::ceil(curseur + g->x1);
        int ya = (int)std::floor(base + g->y0),    yb = (int)std::ceil(base + g->y1);
        for (int py = ya; py < yb; ++py) {
            for (int px = xa; px < xb; ++px) {
                if (px < 0 || px >= L || py < 0 || py >= H) continue;
                float fx = (px + 0.5f - (curseur + g->x0)) / (g->x1 - g->x0);
                float fy = (py + 0.5f - (base + g->y0)) / (g->y1 - g->y0);
                if (fx < 0 || fx > 1 || fy < 0 || fy > 1) continue;
                float u = g->u0 + fx * (g->u1 - g->u0);
                float v = g->v0 + fy * (g->v1 - g->v0);
                int ax = (int)(u * texW), ay = (int)(v * texH);
                if (ax < 0 || ax >= texW || ay < 0 || ay >= texH) continue;
                float c = alpha[ay * texW + ax] / 255.0f;
                unsigned char* d = px4 + ((size_t)py * L + px) * 4;
                d[0] = (unsigned char)(fondR + (255 - fondR) * c);
                d[1] = (unsigned char)(fondG + (255 - fondG) * c);
                d[2] = (unsigned char)(fondB + (255 - fondB) * c);
                d[3] = 255;
            }
        }
        curseur += g->advanceX;
    }

    img.SavePNG("panneau.png");
    std::ofstream out("panneau_tailles.txt");
    out << "atlas : " << texW << " x " << texH << "\n";
    out << "image : " << L << " x " << H << "\n";
    std::cout << "atlas : " << texW << " x " << texH << ", image : " << L << " x " << H << "\n";
    return 0;
}