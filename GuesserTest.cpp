/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};


TEST(GuesserTest, smoke_test)
{
    ASSERT_EQ( 1+1, 2 );
}

TEST(GuesserTest, match_empty)
{
	Guesser guesser("");
	bool actual = guesser.match("");
    ASSERT_TRUE(actual);
}

TEST(GuesserTest, match)
{
	Guesser guesser("secret");
	bool actual = guesser.match("secret");
    ASSERT_TRUE(actual);
}

TEST(GuesserTest, match_one_different)
{
	Guesser guesser("secret");
	bool actual = guesser.match("secr3t");
    ASSERT_FALSE(actual);
}

TEST(GuesserTest, match_two_different)
{
	Guesser guesser("secret");
	bool actual = guesser.match("s3cr3t");
    ASSERT_FALSE(actual);
}

TEST(GuesserTest, match_three_different)
{
	Guesser guesser("secret");
	bool actual = guesser.match("s3kr3t");
    ASSERT_FALSE(actual);
}

TEST(GuesserTest, match_locked)
{
	Guesser guesser("secret");
	bool actual = guesser.match("s3kr3tasdadalkasdsd");
	actual = guesser.match("secret");
    ASSERT_FALSE(actual);
}

TEST(GuesserTest, match_long_guess)
{
	Guesser guesser("secret");
	bool actual = guesser.match("s3kr3tasdadalkasdsdasdadasdasdasjndiajsdlnaklkn");
    ASSERT_FALSE(actual);
}

TEST(GuesserTest, remaining_reset)
{
	Guesser guesser("1");
	bool actual = guesser.match("2");
	actual = guesser.match("2");
	actual = guesser.match("1");
	actual = guesser.match("2");
    ASSERT_FALSE(actual);
}

TEST(GuesserTest, remaining_three)
{
	Guesser guesser("secret");
    ASSERT_EQ( guesser.remaining(), 3 );
}

TEST(GuesserTest, remaining_zero)
{
	Guesser guesser("secret");
    bool actual = guesser.match("secret1");
	actual = guesser.match("secret1");
	actual = guesser.match("secret1");
	actual = guesser.match("secret");
    ASSERT_FALSE(actual);
}

TEST(GuesserTest, secret_truncate_32)
{
	Guesser guesser("onetwothreefourfivesixseveneightnine");
    bool actual = guesser.match("onetwothreefourfivesixseveneight");
	ASSERT_TRUE(actual);
}