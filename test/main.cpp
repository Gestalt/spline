#include <gmock/gmock.h>
#include <iostream>
#include <exception>

#include "TableBasedFunction.h"
#include "Interpolation.h"
#include "NeighborInterpolation.h"
#include "LinearInterpolation.h"
#include "QuadricInterpolation.h"
#include "InterpolationFactory.h"

using namespace std;
using namespace testing;

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
    TableBasedFunction function;

    void SetUp() {
        function.appendPoint(Point(0.f, 0.f));
        function.appendPoint(Point(1.f, 0.f));
        function.appendPoint(Point(2.f, 0.f));
        function.appendPoint(Point(3.f, 0.f));
        function.appendPoint(Point(4.f, 0.f));
        function.appendPoint(Point(5.f, 0.f));
        function.appendPoint(Point(6.f, 0.f));
        function.appendPoint(Point(7.f, 0.f));
        function.appendPoint(Point(8.f, 0.f));
        function.appendPoint(Point(9.f, 0.f));
    }
};

TEST_F(GetNearestPoints, ThrowsErrorForOutOfRangeRequest) {

    ASSERT_THROW(function.getNearestPoints(-1.f, 1), std::exception);
    ASSERT_THROW(function.getNearestPoints(10.f, 1), std::exception);
}

TEST_F(GetNearestPoints, ThrowsErrorIfTooMuchPointsRequested) {

    ASSERT_THROW(function.getNearestPoints(0.f, 11), std::exception);
}

TEST_F(GetNearestPoints, ThrowsErrorForHigherOrderRequest) {

    ASSERT_THROW(function.getNearestPoints(0.f, 4), std::exception);
}

TEST_F(GetNearestPoints, ReturnsOneNearestPointForNeighborRequest) {

    ASSERT_THAT(function.getNearestPoints(5.1f, 1), ElementsAre(
        Point(5.f, 0.f)
    ));

    ASSERT_THAT(function.getNearestPoints(5.9f, 1), ElementsAre(
        Point(6.f, 0.f)
    ));
}

TEST_F(GetNearestPoints, ReturnsTwoBetweenPointsForLinearRequest) {

    ASSERT_THAT(function.getNearestPoints(5.1f, 2), ElementsAre(
        Point(5.f, 0.f),
        Point(6.f, 0.f)
    ));
}

TEST_F(GetNearestPoints, ReturnsThreeNearestPointsForParabolicRequest) {

    ASSERT_THAT(function.getNearestPoints(5.1f, 3), ElementsAre(
        Point(4.f, 0.f),
        Point(5.f, 0.f),
        Point(6.f, 0.f)
    ));

    ASSERT_THAT(function.getNearestPoints(5.9f, 3), ElementsAre(
        Point(5.f, 0.f),
        Point(6.f, 0.f),
        Point(7.f, 0.f)
    ));
}

TEST_F(GetNearestPoints, ReturnsCorrectPointsAtUpperBoundForParabolicRequest) {

    ASSERT_THAT(function.getNearestPoints(8.9f, 3), ElementsAre(
        Point(7.f, 0.f),
        Point(8.f, 0.f),
        Point(9.f, 0.f)
    ));
}

TEST_F(GetNearestPoints, ReturnsCorrectPointsAtLowerBoundForParabolicRequest) {

    ASSERT_THAT(function.getNearestPoints(0.1f, 3), ElementsAre(
        Point(0.f, 0.f),
        Point(1.f, 0.f),
        Point(2.f, 0.f)
    ));
}

TEST(ANeighborInterpolation, ReturnsNearestValueNextToArgument) {
    TableBasedFunction function;

    function.appendPoint(Point(1.f, 1.f));
    function.appendPoint(Point(2.f, 2.f));

    NeighborInterpolation spline;

    ASSERT_THAT(spline.interpolate(&function, 1.1f), FloatEq(1.f));
    ASSERT_THAT(spline.interpolate(&function, 1.9f), FloatEq(2.f));
}


TEST(ALinearInterpolation, ReturnsValueOnLineBetweenPoints) {
    TableBasedFunction function;
    function.appendPoint(Point(1.f, 1.f));
    function.appendPoint(Point(3.f, 3.f));

    LinearInterpolation spline;

    ASSERT_THAT(spline.interpolate(&function, 2.f), FloatEq(2.f));
}

TEST(AQuadricInterpolation, ReturnsValueOnParabola) {
    TableBasedFunction function;
    function.appendPoint(Point(1.f, 1.f));
    function.appendPoint(Point(2.f, 4.f));
    function.appendPoint(Point(4.f, 16.f));

    QuadricInterpolation spline;

    ASSERT_THAT(spline.interpolate(&function, 3.f), FloatEq(9.f));
}

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
