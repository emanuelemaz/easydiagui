#ifndef EASYDIAG_H
#define EASYDIAG_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <limits>
#include <algorithm>

/**
 * @brief
 * This class defines the beam.
 * @param length The length of the beam
*/
class Beam {
    public:
        double length;
        Beam(double l=0);
};

/**
 * @brief
 * This class defines point loads.
 * @param value The value of the point load, expressed in N, kN, kg,...
 * @param distance The distance from the starting point of the beam, taken from left.
*/
class PointLoad {
    public:
        double value;
        double distance;
        PointLoad();
        PointLoad(double v, double d);
};
/**
 * @brief
 * This class defines point moments.
 * @param value The value of the point moments, expressed in Nm, kNm, kgm,...
 * @param distance The distance from the starting point of the beam, taken from left.
*/
class PointMoment {
    public:
        double value;
        double distance;
        PointMoment();
        PointMoment(double v, double d);
};

/**
 * @brief
 * This class defines distributed loads.
 * @param q1 The value of the load at the left-most point, expressed in N/m, kN/m, kg/m,...
 * @param q1 The value of the load at the right-most point, expressed in N/m, kN/m, kg/m,...
 * @param distance The distance from the starting point of the beam, taken from left.
 * @param length The length of the load;
*/
class DistributedLoad {
    public:
        double q1;
        double q2;
        double distance;
        double length;
        DistributedLoad();
        DistributedLoad(double val1, double val2, double d, double l);
};

/**
 * @brief
 * This class defines a context of calculations. It must be provided of a Beam instance and other vectors.
 * @param beam The beam used within the calculations.
 * @param horizontalLoads The vector of PointLoad instances relative to the beam.
 * @param verticalLoads The vector of PointLoad instances relative to the beam.
 * @param distributedLoads The vector of DistributedLoad instances relative to the beam.
 * @param pointMoments The vector of PointMoment instances relative to the beam.
 * @param dx This value is used for the approximation of the graph.
*/
class Context {
    public:
        Beam beam;
        std::vector<PointLoad> verticalLoads;
        std::vector<PointLoad> horizontalLoads;
        std::vector<DistributedLoad> distributedLoads;
        std::vector<PointMoment> pointMoments;
        double dx = 0.0005;
        Context();
        Context(Beam b,
                std::vector<PointLoad> v,
                std::vector<PointLoad> h,
                std::vector<DistributedLoad> d,
                std::vector<PointMoment> m);

    /**
    * @brief
    * This function retrives the nodes of the beam only considering horizontal loads.
    */
    std::vector<std::pair<double, double>> hPoints();
    /**
    * @brief
    * This function retrives the nodes of the beam only considering vertical and linearly variable loads.
    */
    std::vector<std::pair<double, double>> vPoints();
    /**
    * @brief
    * This function retrives the nodes of the beam only considering vertical loads, linearly variable loads and point moments.
    */
    std::vector<std::pair<double,double>> mPoints();
   /**
    * @brief
    * This function calculates the value of the normal force in the point x, where x is the distance from the starting point of the beam, taken from left.
    */
    double pointH(double x);
    /**
    * @brief
    * This function calculates the value of the shear force in the point x, where x is the distance from the starting point of the beam, taken from left.
    */
    double pointV(double x);
    /**
    * @brief
    * This function calculates the value of the bending moment in the point x, where x is the distance from the starting point of the beam, taken from left.
    */
    double pointM(double x);
    /**
    * @brief
    * This function calculates the horizontal force every dx points. It returns a pair of XY coordinates.
    */
    std::pair<std::vector<double>,std::vector<double>> getHpair();
    /**
    * @brief
    * This function calculates the shear force every dx points. It returns a pair of XY coordinates.
    */
    std::pair<std::vector<double>,std::vector<double>> getTpair();
    /**
    * @brief
    * This function calculates the bending moment every dx points. It returns a pair of XY coordinates.
    */
    std::pair<std::vector<double>,std::vector<double>> getMpair();

};


#endif // EASYDIAG_H
