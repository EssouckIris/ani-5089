using System;
using System.Diagnostics;

class Program
{
    static void Main()
    {
        const int images = 1000;

        Stopwatch chrono = new Stopwatch();
        long totalTicks = 0;

        for (int i = 0; i < images; i++)
        {
            chrono.Restart();

           
            Console.Clear();
            
            chrono.Stop();
            totalTicks += chrono.ElapsedTicks;
        }

        double renduMs =
            totalTicks * 1000.0 /
            Stopwatch.Frequency /
            images;

        double renduDeuxFois = renduMs * 2.0;
        double budget = 1000.0 / 90.0;
        double reste = budget - renduDeuxFois;

        Console.WriteLine($"Rendu seul : {renduMs:F2} ms");
        Console.WriteLine($"Rendu deux fois (estimé) : {renduDeuxFois:F2} ms");
        Console.WriteLine($"Temps restant sur {budget:F1} ms : {reste:F2} ms");

        if (reste < 0)
            Console.WriteLine("Conclusion : le rendu doit être réduit.");
        else
            Console.WriteLine("Conclusion : le budget restant est positif.");
    }
}