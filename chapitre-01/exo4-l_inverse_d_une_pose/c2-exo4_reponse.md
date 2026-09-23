using System;

struct Pose
{
    public double Px, Py, Pz;
    public double Qx, Qy, Qz, Qw;

    public Pose(
        double px, double py, double pz,
        double qx, double qy, double qz, double qw)
    {
        Px = px;
        Py = py;
        Pz = pz;

        Qx = qx;
        Qy = qy;
        Qz = qz;
        Qw = qw;
    }
}

class Program
{
    // Applique la rotation du quaternion à un point
    static (double x, double y, double z) Rotation(
        Pose pose, double x, double y, double z)
    {
        double rx =
            (1 - 2 * (pose.Qy * pose.Qy + pose.Qz * pose.Qz)) * x
            + 2 * (pose.Qx * pose.Qy - pose.Qz * pose.Qw) * y
            + 2 * (pose.Qx * pose.Qz + pose.Qy * pose.Qw) * z;

        double ry =
            2 * (pose.Qx * pose.Qy + pose.Qz * pose.Qw) * x
            + (1 - 2 * (pose.Qx * pose.Qx + pose.Qz * pose.Qz)) * y
            + 2 * (pose.Qy * pose.Qz - pose.Qx * pose.Qw) * z;

        double rz =
            2 * (pose.Qx * pose.Qz - pose.Qy * pose.Qw) * x
            + 2 * (pose.Qy * pose.Qz + pose.Qx * pose.Qw) * y
            + (1 - 2 * (pose.Qx * pose.Qx + pose.Qy * pose.Qy)) * z;

        return (rx, ry, rz);
    }

    // Rotation puis translation
    static (double x, double y, double z) RotationPuisTranslation(
        Pose pose, double x, double y, double z)
    {
        var r = Rotation(pose, x, y, z);

        return (
            r.x + pose.Px,
            r.y + pose.Py,
            r.z + pose.Pz
        );
    }

    // Translation puis rotation
    static (double x, double y, double z) TranslationPuisRotation(
        Pose pose, double x, double y, double z)
    {
        // Translation d'abord
        double tx = x + pose.Px;
        double ty = y + pose.Py;
        double tz = z + pose.Pz;

        // Puis rotation
        return Rotation(pose, tx, ty, tz);
    }

    static void Main()
    {
        // Pose : px py pz qx qy qz qw
        string[] poseData = Console.ReadLine().Split();

        double px = double.Parse(poseData[0]);
        double py = double.Parse(poseData[1]);
        double pz = double.Parse(poseData[2]);

        double qx = double.Parse(poseData[3]);
        double qy = double.Parse(poseData[4]);
        double qz = double.Parse(poseData[5]);
        double qw = double.Parse(poseData[6]);

        Pose pose = new Pose(px, py, pz, qx, qy, qz, qw);

        // Point : x y z
        string[] pointData = Console.ReadLine().Split();

        double x = double.Parse(pointData[0]);
        double y = double.Parse(pointData[1]);
        double z = double.Parse(pointData[2]);

        var resultat1 =
            RotationPuisTranslation(pose, x, y, z);

        var resultat2 =
            TranslationPuisRotation(pose, x, y, z);

        Console.WriteLine(
            $"Rotation puis translation : {resultat1.x:F4} {resultat1.y:F4} {resultat1.z:F4}");

        Console.WriteLine(
            $"Translation puis rotation : {resultat2.x:F4} {resultat2.y:F4} {resultat2.z:F4}");
    }
}