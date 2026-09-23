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
    // Applique la pose : rotation du point puis translation
    static (double x, double y, double z) AppliquerPose(
        Pose pose,
        double x, double y, double z)
    {
        // Rotation par le quaternion
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

        // Translation
        rx += pose.Px;
        ry += pose.Py;
        rz += pose.Pz;

        return (rx, ry, rz);
    }

    static void Main()
    {
        // Lecture de la pose :
        // position : px py pz
        // quaternion : qx qy qz qw
        string[] poseData = Console.ReadLine().Split();

        double px = double.Parse(poseData[0]);
        double py = double.Parse(poseData[1]);
        double pz = double.Parse(poseData[2]);

        double qx = double.Parse(poseData[3]);
        double qy = double.Parse(poseData[4]);
        double qz = double.Parse(poseData[5]);
        double qw = double.Parse(poseData[6]);

        Pose pose = new Pose(px, py, pz, qx, qy, qz, qw);

        // Lecture du point
        string[] pointData = Console.ReadLine().Split();

        double x = double.Parse(pointData[0]);
        double y = double.Parse(pointData[1]);
        double z = double.Parse(pointData[2]);

        var resultat = AppliquerPose(pose, x, y, z);

        // Affichage
        Console.WriteLine($"{resultat.x:F4} {resultat.y:F4} {resultat.z:F4}");
    }
}