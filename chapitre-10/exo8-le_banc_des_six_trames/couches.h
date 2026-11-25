#pragma once

// Espace de reference de la couche de projection.
enum EspaceCouche { ESPACE_STAGE, ESPACE_LOCAL };

// Une vue par oeil : pose (lacet en degres) et presence de la chaine.
struct VueOeil {
    float lacetDeg = 0.f;
    bool chaine = false;
};

// Couche de projection : l'espace, et une vue par oeil.
struct CoucheProjection {
    EspaceCouche espace = ESPACE_STAGE;
    VueOeil gauche;
    VueOeil droite;
};