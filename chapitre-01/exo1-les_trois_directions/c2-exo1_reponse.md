using System;

class Program
{
    // Direction Avant
    static (double x, double y, double z) Avant()
    {
        return (0.0, 0.0, 1.0);
    }

    // Direction Haut
    static (double x, double y, double z) Haut()
    {
        return (0.0, 1.0, 0.0);
    }

    // Direction Droite
    static (double x, double y, double z) Droite()
    {
        return (1.0, 0.0, 0.0);
    }

    // Produit scalaire
    static double ProduitScalaire(
        (double x, double y, double z) a,
        (double x, double y, double z) b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    static void Main()
    {
        // Lecture des trois réels
        double x = double.Parse(Console.ReadLine());
        double y = double.Parse(Console.ReadLine());
        double z = double.Parse(Console.ReadLine());

        var point = (x, y, z);

        // Affichage avec quatre décimales
        Console.WriteLine($"{ProduitScalaire(point, Avant()):F4}");
        Console.WriteLine($"{ProduitScalaire(point, Haut()):F4}");
        Console.WriteLine($"{ProduitScalaire(point, Droite()):F4}");
    }
}