#include <gmock/gmock.h>
#include <iostream>
#include <exception>

using namespace std;
using namespace testing;

struct Point {
    Point(float x_, float y_)
        : x(x_), y(y_) {
        }
    float x;
    float y;
};

bool operator==(const Point& lhs, const Point& rhs) {

    return lhs.x == rhs.x && lhs.y == rhs.y; // float cmp
}

const std::vector<Point> getNearestPoints(const std::vector<Point>& src, float arg, int N) {
//check for 0 size
    int size = src.size();

    if (N > size || N > 3) {
        throw std::exception();
    }

    if (arg < src.front().x) {
        throw std::exception();
    }

    if (arg > src.back().x) {
        throw std::exception();
    }

    int index = -1;
    for (int i = 0; i < size; i++) {
        if (arg < src[i].x) {
            break;
        } else {
            index = i;
        }
    }

    assert(index != -1);

    int L = index;
    int R = index + 1;

    std::vector<Point> res;

    float half = 0.5f * (src[L].x + src[R].x);

    if (N == 1) {
        if (arg > half) {
            res.push_back(Point(src[R].x, src[R].y));
        } else {
            res.push_back(Point(src[L].x, src[L].y));
        }
    } else if (N == 2) {
        res.push_back(Point(src[L].x, src[L].y));
        res.push_back(Point(src[R].x, src[R].y));
    } else if (N == 3) {
        if (arg >= half) {
            if (R + 1 < size) {
                res.push_back(Point(src[L].x, src[L].y));
                res.push_back(Point(src[R].x, src[R].y));
                res.push_back(Point(src[R+1].x, src[R+1].y));
            } else {
                res.push_back(Point(src[L-1].x, src[L-1].y));
                res.push_back(Point(src[L].x, src[L].y));
                res.push_back(Point(src[R].x, src[R].y));
            }
        } else {
            if (L - 1 > 0) {
                res.push_back(Point(src[L-1].x, src[L-1].y));
                res.push_back(Point(src[L].x, src[L].y));
                res.push_back(Point(src[R].x, src[R].y));
            } else {
                res.push_back(Point(src[L].x, src[L].y));
                res.push_back(Point(src[R].x, src[R].y));
                res.push_back(Point(src[R+1].x, src[R+1].y));
            }
        }
    } else {
        throw std::exception();
    }

    return res;
}

bool sortPointsPredicate(const Point& lhs, const Point& rhs) {
    return lhs.x < rhs.x;
}

bool equalPointsPredicate(const Point& lhs, const Point& rhs) {
    return lhs.x == rhs.x;
}

class TableBasedFunction {
    public:
        explicit TableBasedFunction(int numOfPoints = 0)
            : points(std::vector<Point>()) {
            if (numOfPoints != 0) {
                points.reserve(numOfPoints);
            }
        }
        const std::vector<Point>& getPoints() const {
            return points;
        }
        void appendPoint(const Point& point) {
            points.push_back(point);
        }
        void init() {
            std::sort(points.begin(), points.end(), sortPointsPredicate);
            points.erase(std::unique(points.begin(), points.end(), equalPointsPredicate),
                    points.end());
        }
    private:
        std::vector<Point> points;
};

class ATableBasedFunction: public Test {
public:
    void SetUp() {
    }
};

MATCHER(isSortedByArguments, "") {
  std::vector<Point>::const_iterator first = arg.begin();
  std::vector<Point>::const_iterator last = arg.end();

    if (first == last) {
        return true;
    }
    std::vector<Point>::const_iterator next = first;
    while ( ++next != last ) {
        if ( (*next).x < (*first).x ) {
            return false;
        }
        ++first;
  }
  return true;
}



TEST_F(ATableBasedFunction, IsEmptyWhenCreated) {
    TableBasedFunction function;

    ASSERT_THAT(function.getPoints().size(), Eq(0u));
}

TEST_F(ATableBasedFunction, SortsArgumentsAtInitialization) {
    TableBasedFunction function;

    function.appendPoint(Point(0.f, 0.f));
    function.appendPoint(Point(2.f, 0.f));
    function.appendPoint(Point(1.f, 0.f));

    function.init();

    ASSERT_THAT(function.getPoints(), isSortedByArguments());
}


TEST_F(ATableBasedFunction, DeletesDuplicatedArgumentsAtInitialization) {
    TableBasedFunction function;

    function.appendPoint(Point(0.f, 0.f));
    function.appendPoint(Point(1.f, 0.f));
    function.appendPoint(Point(1.f, 0.f));

    function.init();

    ASSERT_THAT(function.getPoints(), ElementsAre(
        Point(0.f, 0.f),
        Point(1.f, 0.f)
    ));
}


class GetNearestPoints: public Test {
public:
    std::vector<Point> vec;

    void SetUp() {
        vec.push_back(Point(0.f, 0.f));
        vec.push_back(Point(1.f, 0.f));
        vec.push_back(Point(2.f, 0.f));
        vec.push_back(Point(3.f, 0.f));
        vec.push_back(Point(4.f, 0.f));
        vec.push_back(Point(5.f, 0.f));
        vec.push_back(Point(6.f, 0.f));
        vec.push_back(Point(7.f, 0.f));
        vec.push_back(Point(8.f, 0.f));
        vec.push_back(Point(9.f, 0.f));
    }
};

TEST_F(GetNearestPoints, ThrowsErrorForOutOfRangeRequest) {

    ASSERT_THROW(getNearestPoints(vec, -1.f, 1), std::exception);
    ASSERT_THROW(getNearestPoints(vec, 10.f, 1), std::exception);
}

TEST_F(GetNearestPoints, ThrowsErrorIfTooMuchPointsRequested) {

    ASSERT_THROW(getNearestPoints(vec, 0.f, 11), std::exception);
}

TEST_F(GetNearestPoints, ThrowsErrorForHigherOrderRequest) {

    ASSERT_THROW(getNearestPoints(vec, 0.f, 4), std::exception);
}

TEST_F(GetNearestPoints, ReturnsOneNearestPointForNeighborRequest) {

    ASSERT_THAT(getNearestPoints(vec, 5.1f, 1), ElementsAre(
        Point(5.f, 0.f)
    ));

    ASSERT_THAT(getNearestPoints(vec, 5.9f, 1), ElementsAre(
        Point(6.f, 0.f)
    ));
}

TEST_F(GetNearestPoints, ReturnsTwoBetweenPointsForLinearRequest) {

    ASSERT_THAT(getNearestPoints(vec, 5.1f, 2), ElementsAre(
        Point(5.f, 0.f),
        Point(6.f, 0.f)
    ));
}

TEST_F(GetNearestPoints, ReturnsThreeNearestPointsForParabolicRequest) {

    ASSERT_THAT(getNearestPoints(vec, 5.1f, 3), ElementsAre(
        Point(4.f, 0.f),
        Point(5.f, 0.f),
        Point(6.f, 0.f)
    ));

    ASSERT_THAT(getNearestPoints(vec, 5.9f, 3), ElementsAre(
        Point(5.f, 0.f),
        Point(6.f, 0.f),
        Point(7.f, 0.f)
    ));
}

TEST_F(GetNearestPoints, ReturnsCorrectPointsAtUpperBoundForParabolicRequest) {

    ASSERT_THAT(getNearestPoints(vec, 8.9f, 3), ElementsAre(
        Point(7.f, 0.f),
        Point(8.f, 0.f),
        Point(9.f, 0.f)
    ));
}

TEST_F(GetNearestPoints, ReturnsCorrectPointsAtLowerBoundForParabolicRequest) {

    ASSERT_THAT(getNearestPoints(vec, 0.1f, 3), ElementsAre(
        Point(0.f, 0.f),
        Point(1.f, 0.f),
        Point(2.f, 0.f)
    ));
}

class Interpolation {
    public:
        virtual ~Interpolation() {}
        virtual const float interpolate(TableBasedFunction* function, float argument) const = 0;
};

class NeighborInterpolation : public Interpolation {    public:
        const float interpolate(TableBasedFunction* function, float argument) const {
            if (!function) {
                assert(false);
                return 0.f;
            }
            const std::vector<Point>& points = function->getPoints();
            const std::vector<Point> res = getNearestPoints(points, argument, 1);

            if (!res.empty()) {
                return res.front().y;
            }

            assert(false);

            return 0.f;
        }
};TEST(ANeighborInterpolation, ReturnsNearestValueNextToArgument) {
    TableBasedFunction function;

    function.appendPoint(Point(1.f, 1.f));
    function.appendPoint(Point(2.f, 2.f));

    NeighborInterpolation spline;

    ASSERT_THAT(spline.interpolate(&function, 1.1f), FloatEq(1.f));
    ASSERT_THAT(spline.interpolate(&function, 1.9f), FloatEq(2.f));
}

class LinearInterpolation : public Interpolation {
    public:
        const float interpolate(TableBasedFunction* function, float argument) const {
            if (!function) {
                assert(false);
                return 0.f;
            }
            const std::vector<Point>& points = function->getPoints();
            const std::vector<Point> res = getNearestPoints(points, argument, 2);

            if (!res.empty()) {
                assert(res.size() == 2);

                float x = argument;

                float x0 = res[0].x;
                float x1 = res[1].x;

                float y0 = res[0].y;
                float y1 = res[1].y;

                float c = (x - x0) / (x1 - x0);

                float y = y0 * (1 - c) + y1 * c;

                return y;
            }

            assert(false);

            return 0.f;
        }
};

TEST(ALinearInterpolation, ReturnsValueOnLineBetweenPoints) {
    TableBasedFunction function;
    function.appendPoint(Point(1.f, 1.f));
    function.appendPoint(Point(3.f, 3.f));

    LinearInterpolation spline;

    ASSERT_THAT(spline.interpolate(&function, 2.f), FloatEq(2.f));
}

class QuadricInterpolation : public Interpolation {
    public:
        const float interpolate(TableBasedFunction* function, float argument) const {
            if (!function) {
                assert(false);
                return 0.f;
            }
            const std::vector<Point>& points = function->getPoints();
            const std::vector<Point> res = getNearestPoints(points, argument, 3);

            if (!res.empty()) {
                assert(res.size() == 3);

                float x = argument;

                float x0 = res[0].x;
                float x1 = res[1].x;
                float x2 = res[2].x;

                float y0 = res[0].y;
                float y1 = res[1].y;
                float y2 = res[2].y;

                float c0 = ((x - x1) * (x - x2)) / ((x0 - x1) * (x0 - x2));
                float c1 = ((x - x0) * (x - x2)) / ((x1 - x0) * (x1 - x2));
                float c2 = ((x - x0) * (x - x1)) / ((x2 - x0) * (x2 - x1));

                float y = y0 * c0 + y1 * c1 + y2 * c2;

                return y;
            }

            assert(false);

            return 0.f;
        }
};

TEST(AQuadricInterpolation, ReturnsValueOnParabola) {
    TableBasedFunction function;
    function.appendPoint(Point(1.f, 1.f));
    function.appendPoint(Point(2.f, 4.f));
    function.appendPoint(Point(4.f, 16.f));

    QuadricInterpolation spline;

    ASSERT_THAT(spline.interpolate(&function, 3.f), FloatEq(9.f));
}

class InterpolationFactory {
    public:
        static Interpolation* create(const std::string& type) {
            if (type == std::string("Neighbor")) {
                return new NeighborInterpolation();
            }

            if (type == std::string("Linear")) {
                return new LinearInterpolation();
            }

            if (type == std::string("Quadric")) {
                return new QuadricInterpolation();
            }

            throw std::exception();
        }
};

TEST(AInterpolationFactory, ThrowsErrorAtRequestingUnknownAlgorithm) {

    ASSERT_THROW(InterpolationFactory::create(std::string("Unknown")), std::exception);
}

TEST(AInterpolationFactory, ReturnsRequiredAlgorithm) {

    Interpolation* neighborInterpolation = InterpolationFactory::create(std::string("Neighbor"));

    ASSERT_TRUE(dynamic_cast<NeighborInterpolation*>(neighborInterpolation));

    delete neighborInterpolation;

    Interpolation* linearInterpolation = InterpolationFactory::create(std::string("Linear"));

    ASSERT_TRUE(dynamic_cast<LinearInterpolation*>(linearInterpolation));

    delete linearInterpolation;

    Interpolation* quadricInterpolation = InterpolationFactory::create(std::string("Quadric"));

    ASSERT_TRUE(dynamic_cast<QuadricInterpolation*>(quadricInterpolation));

    delete quadricInterpolation;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
