double[] frequences = { 72, 90, 120 };

foreach (double hz in frequences)
{
    double dureeImage = 1000.0 / hz;
    double reste = dureeImage - 8.0;

    Console.WriteLine($"{hz} Hz : {reste:F1} ms");
}