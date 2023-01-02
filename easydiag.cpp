#include "easydiag.h"
#include <cmath>

Beam::Beam(double l) {
    length = l;
}

PointLoad::PointLoad() {};
PointLoad::PointLoad(double v, double d) {
    value = v;
    distance = d;
}

PointMoment::PointMoment() {};
PointMoment::PointMoment(double v, double d) {
    value = v;
    distance = d;
}

DistributedLoad::DistributedLoad() {};
DistributedLoad::DistributedLoad(double val1, double val2, double d, double l) {
    q1 = val1;
    q2 = val2;
    distance = d;
    length = l;
}

Context::Context() {};
Context::Context(Beam b,
                 std::vector<PointLoad> v,
                 std::vector<PointLoad> h,
                 std::vector<DistributedLoad> d,
                 std::vector<PointMoment> m) {
    beam = b;
    verticalLoads = v;
    horizontalLoads = h;
    distributedLoads = d;
    pointMoments = m;
}

std::vector<std::pair<double, double>> Context::hPoints() {
    std::vector<double> hp;
    std::vector<std::pair<double,double>> pairs;

    for (PointLoad &h : horizontalLoads) {
        hp.push_back(h.distance);
    };

    if (!std::count(hp.begin(),hp.end(),0)) {
        hp.push_back(0);
    }

    double randomDist;
    while (randomDist<=beam.length) {
        hp.push_back(randomDist);
        randomDist += 0.3;
    }

    hp.push_back(beam.length);

    std::sort(hp.begin(), hp.end());
    for (int i = 0; i < hp.size()-1; i++) {
        std::pair<double, double> pair;
        if (i+1<=hp.size() && hp[i] != hp[i+1]) {
            pair.first = hp[i];
            pair.second = hp[i+1];
        }
        pairs.push_back(pair);
    }
    return pairs;
}

std::vector<std::pair<double, double>> Context::vPoints() {
    std::vector<double> vp;
    std::vector<std::pair<double,double>> pairs;

    for (PointLoad &v : verticalLoads) {
        vp.push_back(v.distance);
    };
    for (DistributedLoad &q : distributedLoads) {
        vp.push_back(q.distance);
        vp.push_back(q.distance+q.length);
    }

    if (!std::count(vp.begin(),vp.end(),0)) {
        vp.push_back(0);
    }

    double randomDist;
    while (randomDist<=beam.length) {
        vp.push_back(randomDist);
        randomDist += 0.30;
    }

    vp.push_back(beam.length);

    std::sort(vp.begin(), vp.end());
    for (int i = 0; i < vp.size()-1; i++) {
        std::pair<double, double> pair;
        if (i+1<=vp.size() && vp[i] != vp[i+1]) {
            pair.first = vp[i];
            pair.second = vp[i+1];
        }
        pairs.push_back(pair);
    }
    return pairs;
}

std::vector<std::pair<double,double>> Context::mPoints() {
    std::vector<double> mp = {0};
    std::vector<std::pair<double,double>> pairs;

    for (PointLoad &v : verticalLoads) {
        mp.push_back(v.distance);
    };
    for (DistributedLoad &q : distributedLoads) {
        mp.push_back(q.distance);
        mp.push_back(q.distance+q.length);
    };
    for (PointMoment &m : pointMoments) {
        mp.push_back(m.distance);
    };

    if (!std::count(mp.begin(),mp.end(),0)) {
        mp.push_back(0);
    }

    double randomDist;
    while (randomDist<=beam.length) {
        mp.push_back(randomDist);
        randomDist += 0.30;
    }

    mp.push_back(beam.length);

    std::sort(mp.begin(), mp.end());
    for (int i = 0; i < mp.size()-1; i++) {
        std::pair<double, double> pair;
        if (i+1<=mp.size() && mp[i] != mp[i+1]) {
            pair.first = mp[i];
            pair.second = mp[i+1];
        }
        pairs.push_back(pair);
    }
    return pairs;
}

double Context::pointH(double x) {
    double hValue = 0;
    for (PointLoad &hl : horizontalLoads) {
        if (x == beam.length) {
            hValue -= hl.value;
        }
        else if (hl.distance<=x) {
            hValue -= hl.value;
        }
    }
    return hValue;
}

double Context::pointV(double x) {
    double vValue = 0;
    for (PointLoad &vl : verticalLoads) {
        if (x>=vl.distance) {
            vValue += vl.value;
        }
    }
    for (DistributedLoad &dl : distributedLoads) {
        // loads with w(x) = k
        double p1 = x-dl.distance;
        if (x<=dl.distance+dl.length && x>dl.distance) {
            // rectangular or trapezoid
            if (dl.q1==dl.q2 || (dl.q1 != dl.q2 && dl.q1 != 0 && dl.q2 != 0)) {
                vValue += (dl.q1)*p1;
            }
            // trapezoid
            if (dl.q1 != dl.q2 && dl.q1 !=0 && dl.q2 != 0) {
                vValue += ((dl.q2-dl.q1)/(2*dl.length))*pow(p1,2);
            }
            // triangular
            if (dl.q1 == 0 || dl.q2 == 0) {
                if (dl.q1==0) {
                    vValue += dl.q2/(2*dl.length)*pow(p1,2);
                }
                if (dl.q2==0) {
                    vValue += -dl.q1/(2*dl.length)*pow(p1,2)+dl.q1*p1;
                }
            }
        }
        if (x>dl.distance+dl.length) {
            // rectangular or trapezoid
            if (dl.q1==dl.q2 || (dl.q1 != dl.q2 && dl.q1 != 0 && dl.q2 != 0)) {
                vValue += (dl.q1)*dl.length;
            }
            // trapezoid
            if (dl.q1 != dl.q2 && dl.q1 !=0 && dl.q2 != 0) {
                vValue += (dl.q2-dl.q1)*dl.length/2;
            }
            // triangular
            if (dl.q1 == 0 || dl.q2 == 0) {
                if (dl.q1==0) {
                    vValue += (dl.q2*dl.length)/2;
                }
                if (dl.q2==0) {
                    vValue += (dl.q1*dl.length)/2;
                }
            }
        }
    }
    return vValue;
}

double Context::pointM(double x) {
    double mValue = 0;
    for (PointLoad &vl : verticalLoads) {
        if (x>=vl.distance) {
            mValue += vl.value*(x-vl.distance);
        }
    }
    for (DistributedLoad &dl : distributedLoads) {
        double p1 = x-dl.distance;
        if (x<=dl.distance+dl.length && x>dl.distance) {
            // rectangular or trapezoid
            if (dl.q1==dl.q2 || (dl.q1 != dl.q2 && dl.q1 != 0 && dl.q2 != 0)) {
                mValue += (dl.q1/2)*pow(p1,2);
            }
            // trapezoid
            if (dl.q1 != dl.q2 && dl.q1 !=0 && dl.q2 != 0) {
                mValue += ((dl.q2-dl.q1)/(6*dl.length))*pow(p1,3);
            }
            if (dl.q1 == 0 || dl.q2 == 0) {
                if (dl.q1==0) {
                    mValue += dl.q2/(6*dl.length)*pow(p1,3);
                }
                if (dl.q2==0) {
                    mValue += -dl.q1/(6*dl.length)*pow(p1,3)+(dl.q1/2)*pow(p1,2);
                }
            }
        }
        if (x>dl.distance+dl.length) {
            // rectangular or trapezoid
            if (dl.q1==dl.q2 || (dl.q1 != dl.q2 && dl.q1 != 0 && dl.q2 != 0)) {
                mValue += (dl.q1/2)*pow(dl.length,2)+dl.q1*dl.length*(p1-dl.length);
            }
            // trapezoid
            if (dl.q1 != dl.q2 && dl.q1 !=0 && dl.q2 != 0) {
                mValue += (dl.q2-dl.q1)/6*pow(dl.length,2)+((dl.q2-dl.q1)*dl.length/2)*(p1-dl.length);
            }
            // triangular
            if (dl.q1 == 0 || dl.q2 == 0) {
                if (dl.q1==0) {
                    mValue += ((dl.q2*dl.length)/2)*(p1-dl.length)+(dl.q2/6)*pow(dl.length,2);
                }
                if (dl.q2==0) {
                    mValue += ((dl.q1*dl.length)/2)*(p1-dl.length)+(dl.q1/3)*pow(dl.length,2);
                }
            }
        }
    }
    for (PointMoment &m : pointMoments) {
        if (x>= m.distance) {
            mValue += m.value;
        }
    }
    return -mValue;
}

std::pair<std::vector<double>,std::vector<double>> Context::getHpair() {
    std::vector<std::pair<double,double>> hPair;

    for (std::pair<double, double> &segment : hPoints()) {
        double dist = 0;
        hPair.push_back(std::pair<double,double>(segment.first, pointH(segment.first)));
        hPair.push_back(std::pair<double,double>(segment.second, pointH(segment.second)));
        while (dist < segment.second) {
            hPair.push_back(std::pair<double,double>(dist, pointH(dist)));
            dist += dx;
        }
    }
    hPair.insert(hPair.begin(), std::pair<double,double>(0,0));

    std::sort(hPair.begin(),hPair.end());

    std::vector<double> xH, yH;
    for (std::pair<double,double> &point : hPair) {
        xH.push_back(point.first);
        yH.push_back(point.second);
    }
    return std::make_pair(xH,yH);
}

std::pair<std::vector<double>,std::vector<double>> Context::getTpair() {
    std::vector<std::pair<double,double>> tPair;
    for (std::pair<double, double> &segment : vPoints()) {
        double dist = 0;
        tPair.push_back(std::pair<double,double>(segment.first, pointV(segment.first)));
        tPair.push_back(std::pair<double,double>(segment.second, pointV(segment.second)));
        while (dist < segment.second) {
            tPair.push_back(std::pair<double,double>(dist, pointV(dist)));
            dist += dx;
        }
    }
    tPair.insert(tPair.begin(), std::pair<double,double>(0,0));

    std::sort(tPair.begin(),tPair.end());

    std::vector<double> xT, yT;
    for (std::pair<double,double> &point : tPair) {
        xT.push_back(point.first);
        yT.push_back(point.second);
    }
    return std::make_pair(xT,yT);
}

std::pair<std::vector<double>,std::vector<double>> Context::getMpair() {
    std::vector<std::pair<double,double>> mPair;

    for (std::pair<double, double> &segment : mPoints()) {
        double dist = 0;
        mPair.push_back(std::pair<double,double>(segment.first, pointM(segment.first)));
        mPair.push_back(std::pair<double,double>(segment.second, pointM(segment.second)));
        while (dist < segment.second) {
            mPair.push_back(std::pair<double,double>(dist, pointM(dist)));
            dist += dx;
        }
    }
    mPair.insert(mPair.begin(), std::pair<double,double>(0,0));

    std::sort(mPair.begin(),mPair.end());

    std::vector<double> xM, yM;
    for (std::pair<double,double> &point : mPair) {
        xM.push_back(point.first);
        yM.push_back(point.second);
    }

    return std::make_pair(xM,yM);
}
