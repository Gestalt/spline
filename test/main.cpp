#include <gmock/gmock.h>

#include "Defs.h"
#include "TableBasedFunction.h"
#include "Interpolation.h"
#include "NeighborInterpolation.h"
#include "LinearInterpolation.h"
#include "QuadricInterpolation.h"
#include "InterpolationFactory.h"
#include "InterpolationException.h"
#include "Point.h"

using namespace std;
using namespace testing;

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

    ASSERT_THROW(function.getNearestPoints(-1.f, 1), InterpolationException);
    ASSERT_THROW(function.getNearestPoints(10.f, 1), InterpolationException);
}

TEST_F(GetNearestPoints, ThrowsErrorIfTooMuchPointsRequested) {

    ASSERT_THROW(function.getNearestPoints(0.f, 11), InterpolationException);
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

TEST(ATableBasedFunction, ThrowsErrorOnAppendingDecreasingArgument) {
    TableBasedFunction function;

    function.appendPoint(Point(0.f, 0.f));
    function.appendPoint(Point(2.f, 0.f));

    ASSERT_THROW(function.appendPoint(Point(1.f, 0.f)), InterpolationException);
}

TEST(ATableBasedFunction, ThrowsErrorOnAppendingDuplicatedArgument) {
    TableBasedFunction function;

    function.appendPoint(Point(0.f, 0.f));

    ASSERT_THROW(function.appendPoint(Point(0.f, 0.f)), InterpolationException);
}

TEST(ANeighborInterpolation, ReturnsNearestValueNextToArgument) {
    sp::shared_ptr<TableBasedFunction> function = sp::make_shared<TableBasedFunction>();
    function->appendPoint(Point(1.f, 1.f));
    function->appendPoint(Point(2.f, 2.f));

    NeighborInterpolation spline;

    ASSERT_THAT(spline.interpolate(function, 1.1f), FloatEq(1.f));
    ASSERT_THAT(spline.interpolate(function, 1.9f), FloatEq(2.f));
}

TEST(ALinearInterpolation, ReturnsValueOnLineBetweenPoints) {
    sp::shared_ptr<TableBasedFunction> function = sp::make_shared<TableBasedFunction>();
    function->appendPoint(Point(1.f, 1.f));
    function->appendPoint(Point(3.f, 3.f));

    LinearInterpolation spline;

    ASSERT_THAT(spline.interpolate(function, 2.f), FloatEq(2.f));
}

TEST(AQuadricInterpolation, ReturnsValueOnParabola) {
    sp::shared_ptr<TableBasedFunction> function = sp::make_shared<TableBasedFunction>();
    function->appendPoint(Point(1.f, 1.f));
    function->appendPoint(Point(2.f, 4.f));
    function->appendPoint(Point(4.f, 16.f));

    QuadricInterpolation spline;

    ASSERT_THAT(spline.interpolate(function, 3.f), FloatEq(9.f));
}

TEST(AInterpolationFactory, ThrowsErrorAtRequestingUnknownAlgorithm) {

    ASSERT_THROW(InterpolationFactory::instance()->create(std::string("Unknown")), InterpolationException);
}

TEST(AInterpolationFactory, ReturnsRequiredAlgorithm) {

    sp::shared_ptr<Interpolation> neighborInterpolation = InterpolationFactory::instance()->create(std::string("Neighbor"));
    ASSERT_TRUE(sp::dynamic_pointer_cast<NeighborInterpolation>(neighborInterpolation));

    sp::shared_ptr<Interpolation> linearInterpolation = InterpolationFactory::instance()->create(std::string("Linear"));
    ASSERT_TRUE(sp::dynamic_pointer_cast<LinearInterpolation>(linearInterpolation));

    sp::shared_ptr<Interpolation> quadricInterpolation = InterpolationFactory::instance()->create(std::string("Quadric"));
    ASSERT_TRUE(sp::dynamic_pointer_cast<QuadricInterpolation>(quadricInterpolation));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
