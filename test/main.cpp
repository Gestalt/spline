#include <gmock/gmock.h>
#include <iostream>
#include <exception>

using namespace std;
using namespace testing;

const std::vector<float> getNearestPoints(const std::vector<float>& src, float target, int N) {
    int size = src.size();

    if (N > size || N > 3) {
        throw std::exception();
    }

    if (target < src.front()) {
        throw std::exception();
    }

    if (target > src.back()) {
        throw std::exception();
    }

    int index = -1;
    for (int i = 0; i < size; i++) {
        if (target < src[i]) {
            break;
        } else {
            index = i;
        }
    }

    assert(index != -1);

    int L = index;
    int R = index + 1;

    std::vector<float> res;

    float half = 0.5f * (src[L] + src[R]);

    if (N == 1) {
        if (target > half) {
            res.push_back(src[R]);
        } else {
            res.push_back(src[L]);
        }
    } else if (N == 2) {
        res.push_back(src[L]);
        res.push_back(src[R]);
    } else if (N == 3) {
        if (target >= half) {
            if (R + 1 < size) {
                res.push_back(src[L]);
                res.push_back(src[R]);
                res.push_back(src[R + 1]);
            } else {
                res.push_back(src[L - 1]);
                res.push_back(src[L]);
                res.push_back(src[R]);
            }
        } else {
            if (L - 1 > 0) {
                res.push_back(src[L - 1]);
                res.push_back(src[L]);
                res.push_back(src[R]);
            } else {
                res.push_back(src[L]);
                res.push_back(src[R]);
                res.push_back(src[R + 1]);
            }
        }
    } else {
        throw std::exception();
    }

    return res;
}

class TableBasedFunction {
    public:
        explicit TableBasedFunction(int numOfPoints = 0)
            : points(std::vector<float>()) {
            if (numOfPoints != 0) {
                points.reserve(numOfPoints);
            }
        }
        const std::vector<float>& getPoints() {
            return points;
        }
        void appendPoint(float point) {
            points.push_back(point);
        }
        void init() {
            std::sort(points.begin(), points.end());
            points.erase(std::unique(points.begin(), points.end()),
                    points.end());
        }
    private:
        std::vector<float> points;
};

class ATableBasedFunction: public Test {
public:
    void SetUp() {
    }
};

MATCHER(isSorted, "") {
  std::vector<float>::const_iterator first = arg.begin();
  std::vector<float>::const_iterator last = arg.end();

    if (first == last) {
        return true;
    }
    std::vector<float>::const_iterator next = first;
    while (++next!=last) {
        if (*next<*first) {
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

    function.appendPoint(0.f);
    function.appendPoint(2.f);
    function.appendPoint(1.f);

    function.init();

    ASSERT_THAT(function.getPoints(), isSorted());
}

TEST_F(ATableBasedFunction, DeletesDuplicatedArgumentsAtInitialization) {
    TableBasedFunction function;

    function.appendPoint(0.f);
    function.appendPoint(1.f);
    function.appendPoint(1.f);

    function.init();

    ASSERT_THAT(function.getPoints(), ElementsAre(0.f, 1.f));
}

class GetNearestPoints: public Test {
public:
    std::vector<float> vec;

    void SetUp() {
        vec.push_back(0.f);
        vec.push_back(1.f);
        vec.push_back(2.f);
        vec.push_back(3.f);
        vec.push_back(4.f);
        vec.push_back(5.f);
        vec.push_back(6.f);
        vec.push_back(7.f);
        vec.push_back(8.f);
        vec.push_back(9.f);
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

    ASSERT_THAT(getNearestPoints(vec, 5.1f, 1), ElementsAre(5.f));
    ASSERT_THAT(getNearestPoints(vec, 5.9f, 1), ElementsAre(6.f));
}

TEST_F(GetNearestPoints, ReturnsTwoBetweenPointsForLinearRequest) {

    ASSERT_THAT(getNearestPoints(vec, 5.1f, 2), ElementsAre(5.f, 6.f));
}

TEST_F(GetNearestPoints, ReturnsThreeNearestPointsForParabolicRequest) {

    ASSERT_THAT(getNearestPoints(vec, 5.1f, 3), ElementsAre(4.f, 5.f, 6.f));
    ASSERT_THAT(getNearestPoints(vec, 5.9f, 3), ElementsAre(5.f, 6.f, 7.f));
}

TEST_F(GetNearestPoints, ReturnsCorrectPointsAtUpperBoundForParabolicRequest) {

    ASSERT_THAT(getNearestPoints(vec, 8.9f, 3), ElementsAre(7.f, 8.f, 9.f));
}

TEST_F(GetNearestPoints, ReturnsCorrectPointsAtLowerBoundForParabolicRequest) {

    ASSERT_THAT(getNearestPoints(vec, 0.1f, 3), ElementsAre(0.f, 1.f, 2.f));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
