using System;

class Program
{
    static void Main()
    {
        string[] temoignages =
        {
            "L'image qui bouge rapidement me donne une sensation de malaise et un léger vertige.",
            "Les mouvements de la caméra me donnent une impression d'instabilité et un peu mal à la tête.",
            "Je ressens surtout une fatigue visuelle et une légère nausée."
        };

        for (int i = 0; i < temoignages.Length; i++)
        {
            Console.WriteLine($"Personne {i + 1} :");
            Console.WriteLine(temoignages[i]);
            Console.WriteLine();
        }
    }
}