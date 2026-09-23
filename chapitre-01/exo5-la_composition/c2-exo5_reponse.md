using System;

class Program
{
    static void Main()
    {
        double[] valeurs = { 63, 61, 64, 62, 65, 60 };

        double somme = 0;
        double min = valeurs[0];
        double max = valeurs[0];

        foreach (double valeur in valeurs)
        {
            somme += valeur;

            if (valeur < min)
                min = valeur;

            if (valeur > max)
                max = valeur;
        }

        double moyenne = somme / valeurs.Length;
        double ecart = max - min;

        Console.WriteLine($"Moyenne : {moyenne:F1} mm");
        Console.WriteLine($"Écart min-max : {ecart:F1} mm");
    }
}