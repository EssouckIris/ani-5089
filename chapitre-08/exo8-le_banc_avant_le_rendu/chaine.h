#pragma once

// Une chaine d'echange simulee : un anneau d'images, un drapeau d'emprunt,
// et deux methodes qui REFUSENT (elles rendent faux) au lieu de planter.
// De la comptabilite, pas du dessin : ni fenetre, ni carte graphique, ni casque.

class Chaine {
public:
    static const int kMaxImages = 8;   // le maximum que la carte accepte (mon choix)

    // Une chaine plus grande que le maximum (ou vide) est refusee : Creer rend faux.
    // Le programme decide quoi faire de ce refus.
    static bool Creer(int images, Chaine &resultat) {
        if (images < 1 || images > kMaxImages) {
            return false;
        }
        resultat.mImages = images;
        resultat.mSuivant = 0;
        resultat.mEmprunte = false;
        return true;
    }

    // Preter l'image que l'anneau designe. Refuse si une image est deja sortie.
    bool Emprunter(int &index) {
        if (mEmprunte) {
            return false;               // double emprunt : refuse, rien ne change
        }
        mEmprunte = true;
        index = mSuivant;
        return true;
    }

    // Rendre l'image empruntee, puis faire avancer l'anneau.
    // Refuse si rien n'est emprunte.
    bool Rendre(int &index) {
        if (!mEmprunte) {
            return false;               // rendu sans emprunt : refuse, rien ne change
        }
        index = mSuivant;
        mEmprunte = false;
        mSuivant = (mSuivant + 1) % mImages;   // l'anneau avance au RENDU, pas a l'emprunt
        return true;
    }

    int Images() const { return mImages; }

private:
    int mImages = 0;        // la taille de l'anneau
    int mSuivant = 0;       // l'image que l'anneau designe
    bool mEmprunte = false; // une image est-elle sortie ?
};