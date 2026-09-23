Plus longue image : 2.4 ms
Images > 11 ms : 0

Le temps moyen du rendu est donc d’environ :

Rendu ≈ 2 ms par image

Si le rendu doit être exécuté deux fois dans la même image :

 2 * 2ms = 4ms $$

Le double rendu coûterait donc environ :

Rendu double ≈ 4 ms
3. Temps restant pour le reste du programme

Pour une expérience fluide à environ 90 images par seconde, le budget par image est :

1000\90 = 11 ms 

Temps utilisé par le double rendu :

4 ms

Temps restant :

 11 - 4 = 7ms 

Il resterait donc environ :

7 ms pour la logique, la physique, les calculs et les traitements.