using System;

class Program
{
    static void Main()
    {
        // Champ de vision de l'œil gauche
        double gauche = -54.00;
        double droite = 39.86;
        double bas = -53.57;
        double haut = 42.00;

        // Calcul des dimensions
        double largeur = droite - gauche;
        double hauteur = haut - bas;
        double surface = largeur * hauteur;

        Console.WriteLine("Champ de vision - œil gauche");
        Console.WriteLine($"Gauche : {gauche:F2}°");
        Console.WriteLine($"Droite : {droite:F2}°");
        Console.WriteLine($"Bas : {bas:F2}°");
        Console.WriteLine($"Haut : {haut:F2}°");

        Console.WriteLine();
        Console.WriteLine($"Largeur : {largeur:F2}°");
        Console.WriteLine($"Hauteur : {hauteur:F2}°");
        Console.WriteLine($"Surface approximative : {surface:F2} degrés²");

        Console.WriteLine();
        Console.WriteLine(
            "Si on remplaçait ce champ asymétrique par un champ " +
            "symétrique de même surface, le champ de vision serait " +
            "réparti différemment autour de l’œil, ce qui pourrait " +
            "réduire la couverture utile de certaines zones et " +
            "augmenter celle d’autres zones."
        );
    }
}