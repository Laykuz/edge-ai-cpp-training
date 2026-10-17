#include <iostream>
#include <vector>

using namespace std;

// Structure for x and y coordinates.
struct Point {
    int x;
    int y;
};

// Polygon class (Rule of Five).
class Polygon {
public:
    // 1. Default constructor.
    Polygon() : nPoints(0), points(nullptr) {}

    // 2. Constructor.
    Polygon(const int nPoints, const Point* points) : nPoints(nPoints) {
        this->points = new Point[nPoints];
        for (int i = 0; i < nPoints; ++i) {
            this->points[i] = points[i];
        }
    }

    // 3. Copy constructor.
    Polygon(const Polygon& other) : nPoints(other.nPoints) {
        if (other.nPoints > 0 && other.points != nullptr) {
            points = new Point[nPoints];
            for (int i = 0; i < nPoints; ++i) {
                points[i] = other.points[i];
            }
        } else {
            points = nullptr;
        }
    }

    // 4. Move constructor.
    Polygon(Polygon&& other) noexcept : nPoints(other.nPoints), points(other.points) {
        other.nPoints = 0;
        other.points = nullptr; // Clear the source pointer after transferring ownership.
    }

    // 5. Destructor.
    ~Polygon() {
        delete[] points; // Release dynamically allocated memory.
    }

    // 6. Copy assignment operator.
    Polygon& operator=(const Polygon& other) {
        if (this != &other) { // Prevent self-assignment.
            delete[] points;  // Release existing memory.

            nPoints = other.nPoints;
            if (other.nPoints > 0 && other.points != nullptr) {
                points = new Point[nPoints];
                for (int i = 0; i < nPoints; ++i) {
                    points[i] = other.points[i];
                }
            } else {
                points = nullptr;
            }
        }
        return *this;
    }

    // 7. Move assignment operator.
    Polygon& operator=(Polygon&& other) noexcept {
        if (this != &other) {
            delete[] points; // Release existing memory.

            nPoints = other.nPoints; // Take ownership of the pointer.
            points = other.points;

            other.nPoints = 0; // Reset the source object.
            other.points = nullptr;
        }
        return *this;
    }

    // Getter functions.
    int GetNPoints() const {
        return nPoints;
    }

    Point* GetPoints() const {
        return points;
    }

private:
    int nPoints = 0;          // Number of vertices.
    Point* points = nullptr;  // Dynamically allocated array.
};

// Create and return a temporary square object.
Polygon getSquare() {
    Point points[4] = { {0, 0}, {1, 0}, {1, 1}, {0, 1} };
    Polygon p(4, points);
    return p; // Eligible for NRVO (Named Return Value Optimization) or move construction.
}

int main() {
    Polygon a;
    a = getSquare(); // Calls move assignment for the temporary object.

    Polygon b = a;   // Calls the copy constructor (deep copy).

    Polygon c;
    c = a;           // Calls copy assignment (deep copy).

    // Print the result.
    int nPoints = c.GetNPoints();
    Point* points = c.GetPoints();

    for (int i = 0; i < nPoints; ++i) {
        cout << "(" << points[i].x << ", " << points[i].y << ")" << endl;
    }

    return 0;
}
