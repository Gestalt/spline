#include <gmock/gmock.h>

using namespace std;
using namespace testing;

TEST(SimpleTest, Test) {
    ASSERT_TRUE(true);
}

class TestClass {
public:
   virtual ~TestClass() {}
   virtual void init(const string&) = 0;
};

class SimpleFixture: public Test {
public:

};

class SimpleStub: public TestClass {
public:
   MOCK_METHOD1(init, void(const string&));
};

TEST_F(SimpleFixture, SimpleFixtureStubTest) {
   SimpleStub stub;

   EXPECT_CALL(stub, init("init"));

   stub.init("init");
}

int main(int argc, char **argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
