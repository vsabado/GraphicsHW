import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;

import static java.lang.Math.*;

class Coords {
    float x;
    float y;
    float z;

    Coords(float x, float y, float z) {
        this.x = x;
        this.y = y;
        this.z = z;
    }

    Coords(Coords coords) {
        this.x = coords.x;
        this.y = coords.y;
        this.z = coords.z;
    }

    public float getX() {
        return x;
    }

    public void setX(float x) {
        this.x = x;
    }

    public float getY() {
        return y;
    }

    public void setY(float y) {
        this.y = y;
    }

    public float getZ() {
        return z;
    }

    public void setZ(float z) {
        this.z = z;
    }

    void printValues() {
        System.out.println("x: " + this.x + ", y: " + this.y + ", z: " + this.z);
    }

}


public class Calculate {
    private Random rand = new Random();

    // Generate random values for x, y, z
    private Coords generateRandomValues() {
        return new Coords(rand.nextInt(20), rand.nextInt(30), rand.nextInt(40));
    }

    //==============================================================================================
    //Transformation
    //==============================================================================================
    private Coords translateValues(Coords coords, Coords translateBy) {
        return new Coords(coords.x + translateBy.x, coords.y + translateBy.y, coords.z + translateBy.z);
    }

    private void performTranslation() {
        System.out.println("=======================================    PERFORMING TRANSFORMATION FUNCTION   =========================================================");
        Coords coords = generateRandomValues();
        Coords translateBy = generateRandomValues();
        System.out.println("Coordinate values to translate: ");
        coords.printValues();
        System.out.println("Coordinate values to translate by ");
        translateBy.printValues();
        System.out.println("Resulting translation (x', y', z') : ");
        Coords result = translateValues(coords, translateBy);
        result.printValues();
    }

    // Scale x, y, z values
    private Coords scaleValues(Coords coords, Coords scaleBy) {
        return new Coords(coords.x * scaleBy.x, coords.y * scaleBy.y, coords.z * scaleBy.z);
    }

    private void performScale() {
        System.out.println("=======================================    PERFORMING SCALE FUNCTION   =========================================================");
        Coords coords = generateRandomValues();
        Coords scaleBy = generateRandomValues();
        System.out.println("Coordinate values to scale: ");
        coords.printValues();
        System.out.println("Coordinate values to scale by ");
        scaleBy.printValues();
        System.out.println("Resulting scale (x', y', z') : ");
        Coords result = scaleValues(coords, scaleBy);
        result.printValues();
    }

    // Rotate x, y, z values
    private Coords rotateXAroundX(Coords coords, double theta) {
        coords.y = (float) ((cos(theta) * coords.y) - (sin(theta) * coords.z));
        coords.z = (float) ((sin(theta) * coords.y) + (cos(theta) * coords.z));
        return coords;
    }

    private Coords rotateZAroundZ(Coords coords, double theta) {
        coords.x = (float) ((cos(theta) * coords.x) - (sin(theta) * coords.y));
        coords.y = (float) ((sin(theta) * coords.x) + (cos(theta) * coords.y));
        return coords;
    }


    private Coords rotateYAroundY(Coords coords, double theta) {
        coords.x = (float) ((cos(theta) * coords.x) + (sin(theta) * coords.z));
        coords.z = (float) ((-sin(theta) * coords.x) + (cos(theta) * coords.z));
        return coords;
    }

    private Coords projectionPlane(Coords coords) {
        System.out.println("=======================================    PERFORMING PROJECTION PLANE   =========================================================");
        int arbitraryD = 5;
        System.out.println("Value of d is: " + arbitraryD);
        float xp = ((coords.x * arbitraryD) / coords.z);
        float yp = ((coords.y * arbitraryD) / coords.z);
        return new Coords(xp, yp, coords.z);
    }
    //==============================================================================================
    //Clippings
    //==============================================================================================
    private void performRotation() {
        System.out.println("=======================================    PERFORMING ROTATION FUNCTION   =========================================================");
        Coords coords = generateRandomValues();
        Coords result = new Coords(0, 0, 0);
        double theta = Math.toRadians(rand.nextInt(90));
        System.out.println("Coordinate values to rotate: ");
        coords.printValues();
        System.out.println("Theta to rotate by " + theta);
        System.out.println("Rotate around X-axis values: ");
        result = rotateXAroundX(coords, theta);
        result.printValues();
        System.out.println("Rotate around Y-axis values: ");
        result = rotateYAroundY(coords, theta);
        result.printValues();
        System.out.println("Rotate around Z-axis values: ");
        result = rotateZAroundZ(coords, theta);
        result.printValues();
    }

    private ArrayList<Integer> determineOutcodes(Coords obj) {
        int arbitraryMin = 10;
        int arbitraryMax = 30;
        int minX = arbitraryMin;
        int maxX = arbitraryMax;
        int minY = arbitraryMin;
        int maxY = arbitraryMax;
        ArrayList<Integer> resultingOutcode = new ArrayList<>();
/*
First bit set 1: Point lies to left of window x < xmin
Seond bit set 1: Point lies to right of window x > xmax
Third bit set 1: Point lies below window y < ymin
Fourt bit set 1: Point lies above window y > ymax
 */
        if (obj.x < minX)
            resultingOutcode.add(1);
        else
            resultingOutcode.add(0);
        if (obj.x > maxX)
            resultingOutcode.add(1);
        else
            resultingOutcode.add(0);
        if (obj.y < minY)
            resultingOutcode.add(1);
        else
            resultingOutcode.add(0);
        if (obj.y > maxY)
            resultingOutcode.add(1);
        else
            resultingOutcode.add(0);
        return resultingOutcode;
    }

    private boolean acceptLineSegment(ArrayList<Integer> out1, ArrayList<Integer> out2) {
        System.out.println("=======================================    Determining whether to accept   =========================================================");
        System.out.println("outcode 1: " + Arrays.toString(out1.toArray()));
        System.out.println("outcode 2: " + Arrays.toString(out2.toArray()));
        for (int i = 0; i < out1.size(); i++) {
            if (out1.get(i) != 0 || out2.get(i) != 0) {
                return false;
            }
        }
        return true;
    }

    private boolean discardLineSegment(ArrayList<Integer> out1, ArrayList<Integer> out2) {
        System.out.println("=======================================    Determining whether to discard   =========================================================");
        System.out.println("outcode 1: " + Arrays.toString(out1.toArray()));
        System.out.println("outcode 2: " + Arrays.toString(out2.toArray()));
        for (int i = 0; i < out1.size(); i++) {
            if (out1.get(i) == 1 && out2.get(i) == 1) {
                return true;
            }
        }
        return false;
    }

    private boolean performClippingAlgorithm(Coords c1, Coords c2) {
        System.out.println("Starting values: ");
        c1.printValues();
        c2.printValues();
        int arbitraryMin = 10;
        int arbitraryMax = 30;
        int minX = arbitraryMin;
        int maxX = arbitraryMax;
        int minY = arbitraryMin;
        int maxY = arbitraryMax;

        while(!acceptLineSegment(determineOutcodes(c1), determineOutcodes(c2))){
            if (c1.x < minX)
                c1.x++;
            if(c2.x > maxX)
                c2.x--;
            if(c1.y < minY)
                c1.y++;
            if(c2.y > maxX)
                c2.y++;

            if (c2.x < minX)
                c2.x++;
            if(c1.x > maxX)
                c1.x--;
            if(c2.y < minY)
                c2.y++;
            if(c1.y > maxX)
                c1.y++;
        }
        System.out.println("Successfully clipped. Final values: ");
        c1.printValues();
        c2.printValues();
        return true;
    }


    //==============================================================================================
    //Shading
    //==============================================================================================
    private float getEuclidean(float x, float y, float z) {
        return (float) sqrt((x * x) + (y * y) + (z * z));
    }

    private float getDotProduct(float x1, float y1, float z1, float x2, float y2, float z2) {
        return ((x1 * x2) + (y1 * y2) + (z1 * z2));
    }

    private Coords getCrossProduct(float x1, float y1, float z1, float x2, float y2, float z2) {
        return new Coords((y1 * z2) - (z1 * y2), (z1 * x2) - (x1 * z2), (x1 * y2) - (y1 * x2));
    }

    private Coords normalize(Coords coords) {
        float euclidean = getEuclidean(coords.x, coords.y, coords.z);
        return new Coords(coords.x / euclidean, coords.y / euclidean, coords.z / euclidean);
    }

    private double getDiffuse(float dotProduct) {
        return (acos(dotProduct) * (180 / PI));
    }

    private Coords getIdealReflection(Coords c1, Coords c2) {
        float scalar = (c1.x * c2.x) + (c1.y * c2.y) + (c1.z * c2.z);
        return new Coords(2 * scalar * (c1.x - c2.x), 2 * scalar * (c1.x - c2.x), 2 * scalar * (c1.z - c2.z));
    }

    private double specularTerm(double ax, double bx, double cx, double ay, double by, double cy, double p) {
        double ks = 0.01;
        double Is = 0.01;
        System.out.println("The ax, ay, and az values are: " + ax + "," + bx + "," + cx + "," + ay + "," + by + "," + cy + "," + p);
        double scalar = pow((ax * ay) + (bx * by) + (cx * cy), p);
        return scalar;
    }

    private void performAllClippings() {
        System.out.println("=======================================  Determining outcodes   =========================================================");

        Coords obj1 = generateRandomValues();
        System.out.println("Coordinate values to check outcodes for: ");
        obj1.printValues();

        ArrayList<Integer> out1 = determineOutcodes(obj1);
        System.out.println("Outcode1: " + Arrays.toString(out1.toArray()));

        Coords obj2 = generateRandomValues();
        System.out.println("Coordinate values to check outcodes for: ");
        obj2.printValues();

        ArrayList<Integer> out2 = determineOutcodes(obj2);
        System.out.println("Outcode2: " + Arrays.toString(out2.toArray()));

        if (discardLineSegment(out1, out2)) {
            System.out.println("Discarded, will not clip. Run again to generate new outcodes");
        } else {
            System.out.println("Not discarded");
            if (acceptLineSegment(out1, out2)) {
                System.out.println("Accepted");
            } else {
                System.out.println("Not Accepted");
                System.out.println("Clipping succssful: " + performClippingAlgorithm(obj1, obj2));
            }
        }
    }

    private void performAllTranslations() {
        performTranslation();
        performScale();
        performRotation();
        Coords result = projectionPlane(new Coords(generateRandomValues()));
        System.out.println("Xp: " + result.x + ", Yp: " + result.y);
    }

    private void performAllShading() {
        System.out.println("=======================================  Normalize   =========================================================");
        Coords coords = new Coords(15, 26, 5);
        System.out.println("Values to normalize: ");
        coords.printValues();
        Coords coords2 = new Coords(7, 14, 14);
        Coords result2 = normalize(coords2);
        coords2.printValues();
        Coords result = normalize(coords);
        System.out.println("Normalized values: ");
        result.printValues();
        result2.printValues();

        System.out.println("=======================================  Dot product   =========================================================");
        System.out.println("Values to get dotproduct for: ");
        result.printValues();
        result2.printValues();
        System.out.println("Dot product: " + getDotProduct(result.x, result.y, result.z, result2.x, result2.y, result.z));
        System.out.println("=======================================  Cross product   =========================================================");
        Coords crossProduct = getCrossProduct(coords.x, coords.y, coords.z, coords2.x, coords2.y, coords2.z);
        crossProduct.printValues();
        System.out.println("=======================================  Diffuse Term   =========================================================");
        System.out.println("Diffuse term(angle): " + getDiffuse(getDotProduct(result.x, result.y, result.z, result2.x, result2.y, result.z)));
        System.out.println("=======================================  Ideal Reflection   =========================================================");
        Coords idealRefelection = getIdealReflection(result, result2);
        idealRefelection.printValues();
        System.out.println("=======================================  Specular Reflection   =========================================================");
        System.out.println("Scalar: " + specularTerm(1, 2, 3, 2, 2, 2, 0.5));
    }

    public static void main(String[] args) {
        System.out.println("=======================================  Perform translations   ========================================================");
        new Calculate().performAllTranslations();
        System.out.println("=======================================  Perform clippings   ========================================================");
        new Calculate().performAllClippings();
        System.out.println("=======================================  Perform shadings   ========================================================");
        new Calculate().performAllShading();
    }
}
