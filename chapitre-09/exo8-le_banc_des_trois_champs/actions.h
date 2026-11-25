#pragma once

// Etat d'une action : trois champs.
struct EtatAction {
    bool courant = false;   // l'action est-elle tenue a cette image ?
    bool change  = false;   // courant differ-t-il de l'image precedente ?
    bool actif   = false;   // une source est-elle liee a l'action ?
};

// Met a jour l'etat. 'presse' vient de la touche, 'lie' dit si une touche est liee.
// change se calcule sur courant (l'etat), pas sur la touche.
inline void Mettre(EtatAction& e, bool presse, bool lie) {
    const bool precedent = e.courant;
    e.actif = lie;
    e.courant = lie ? presse : false;    // action non liee : toujours faux
    e.change = (e.courant != precedent);
}