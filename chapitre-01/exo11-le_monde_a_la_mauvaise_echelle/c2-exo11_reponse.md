using System;
class Program
{
    static void Main()
    {
        double longueurSalle = 10;
        double largeurSalle = 8;
        double hauteurSalle = 3;
        double longueurTable = 2;
        double largeurTable = 1;
        double hauteurTable = 0.8;
        double longueurChaise = 0.5;
        double largeurChaise = 0.5;
        double hauteurChaise = 1;

        Console.Write("Entrez le facteur : ");
        double facteur = double.Parse(Console.ReadLine());

        Console.WriteLine("\n--- Dimensions après multiplication ---");

        Console.WriteLine("Salle :");
        Console.WriteLine("Longueur : " + (longueurSalle * facteur) + " m");
        Console.WriteLine("Largeur : " + (largeurSalle * facteur) + " m");
        Console.WriteLine("Hauteur : " + (hauteurSalle * facteur) + " m");
        Console.WriteLine("\nTable :");
        Console.WriteLine("Longueur : " + (longueurTable * facteur) + " m");
        Console.WriteLine("Largeur : " + (largeurTable * facteur) + " m");
        Console.WriteLine("Hauteur : " + (hauteurTable * facteur) + " m");   Console.WriteLine("\nChaise :");
        Console.WriteLine("Longueur : " + (longueurChaise * facteur) + " m");
        Console.WriteLine("Largeur : " + (largeurChaise * facteur) + " m");
        Console.WriteLine("Hauteur : " + (hauteurChaise * facteur) + " m");
    }
}