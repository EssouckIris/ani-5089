using System;
using System.Diagnostics;
using System.Threading;

class Program
{
    static void Main()
    {
        long plusLongueTicks = 0;
        int depasse11ms = 0;

        for (int i = 0; i < 1000; i++)
        {
            Stopwatch chrono = Stopwatch.StartNew();

            // Boucle de dessin : ici, on efface simplement la console.
            Console.Clear();

            chrono.Stop();

            double dureeMs =
                chrono.ElapsedTicks * 1000.0 / Stopwatch.Frequency;

            if (chrono.ElapsedTicks > plusLongueTicks)
                plusLongueTicks = chrono.ElapsedTicks;

            if (dureeMs > 11.0)
                depasse11ms++;
        }

        double plusLongueMs =
            plusLongueTicks * 1000.0 / Stopwatch.Frequency;

        Console.WriteLine($"Plus longue image : {plusLongueMs:F1} ms");
        Console.WriteLine($"Images > 11 ms : {depasse11ms}");
    }
}