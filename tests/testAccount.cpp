#include <Account.h>

#include <gtest/gtest.h>

TEST(Account, AccountTestAll)
{
	Account dimka(1, 1000);
	
	EXPECT_EQ(dimka.id(), 1);
	EXPECT_EQ(dimka.GetBalance(), 1000);
	EXPECT_THROW(dimka.ChangeBalance(200), std::runtime_error);
	EXPECT_EQ(dimka.GetBalance(), 1000);
	EXPECT_EQ(dimka.id(), 1);

	EXPECT_NO_THROW(dimka.Lock());
	EXPECT_THROW(dimka.Lock(), std::runtime_error);
	EXPECT_EQ(dimka.GetBalance(), 1000);
	EXPECT_NO_THROW(dimka.ChangeBalance(200));
	EXPECT_EQ(dimka.GetBalance(), 1200);

	EXPECT_EQ(dimka.id(), 1);

	EXPECT_NO_THROW(dimka.Unlock());
	EXPECT_NO_THROW(dimka.Unlock()); // !!! why?

	EXPECT_EQ(dimka.GetBalance(), 1200);

	EXPECT_EQ(dimka.id(), 1);

	EXPECT_THROW(dimka.ChangeBalance(200), std::runtime_error);
}

