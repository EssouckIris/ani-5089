using System;

class Program
{
    static void Main()
    {
        double[] distances = { 0.30, 1.0, 3.0 };
        double[] deplacements = { 6.0, 2.0, 0.7 };

        double somme = 0;

        for (int i = 0; i < deplacements.Length; i++)
        {
            Console.WriteLine(
                $"À {distances[i]:0.##} m : {deplacements[i]:0.0} cm");

            somme += deplacements[i];
        }

        double moyenne = somme / deplacements.Length;

        Console.WriteLine($"Moyenne : {moyenne:0.0} cm");
    }
}