#include "c-echo.h"
#include "gtest/gtest.h"

TEST(EchoTest, HelloWorld) {
    char* test_val[3]; test_val[0] = "./c-echo"; test_val[1] = "hello"; test_val[2] = "world";
    EXPECT_EQ("hello world", echo(3,test_val));
}


TEST(EchoTest, YinjieXie) {
    char* test_val[3]; test_val[0] = "./c-echo"; test_val[1] = "Yinjie"; test_val[2] = "Xie";
    EXPECT_EQ("Yinjie Xie", echo(3,test_val));
}

TEST(EchoTest, ID) {
    char* test_val[2]; test_val[0] = "./c-echo"; test_val[1] = "862140304";
    EXPECT_EQ("862140304", echo(2,test_val));
}

TEST(EchoTest, Address) {
    char* test_val[2]; test_val[0] = "./c-echo"; test_val[1] = "Riverside";
    EXPECT_EQ("Riverside", echo(2,test_val));
}


TEST(EchoTest, EmptyString) {
    char* test_val[1]; test_val[0] = "./c-echo";
    EXPECT_EQ("", echo(1,test_val));
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();

}
