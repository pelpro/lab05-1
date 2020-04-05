#include <Transaction.h>
#include <Account.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::AtLeast;
using ::testing::Return;
using ::testing::DoAll;


class MockAccount: public Account {
public:
	MockAccount(int id, int sum) : Account(id, sum) {}
	MOCK_METHOD0(GetBalance, int());
	MOCK_METHOD1(ChangeBalance, void(int diff));
	MOCK_METHOD0(Lock, void());
	MOCK_METHOD0(Unlock, void());
	MOCK_METHOD0(id, int());
};

TEST(Transaction, TransactionMakeMock)
{
        MockAccount petya(1, 1000), vasya(2, 1000);
        Transaction transaction;

        EXPECT_CALL(petya, Lock())
                .Times(1);
        EXPECT_CALL(vasya, Lock())
                .Times(1);
        EXPECT_CALL(vasya, ChangeBalance(500))
                .Times(1);
        EXPECT_CALL(petya, ChangeBalance(-501))
                .Times(1);
        EXPECT_CALL(petya, Unlock())
                .Times(1);
        EXPECT_CALL(vasya, Unlock())
                .Times(1);

        transaction.Make(petya, vasya, 500);
}
TEST(Transaction, TransactionMake)
{
        Account petya(1, 1000), vasya(2, 1000);
        Transaction transaction;

        transaction.Make(petya, vasya, 500);
        EXPECT_EQ(petya.GetBalance(), 499);
        EXPECT_EQ(vasya.GetBalance(), 1500);
}


TEST(Transaction, SmallTransaction)
{
	MockAccount petya(1, 1000), vasya(2, 1000);
	Transaction transaction;
	EXPECT_THROW(transaction.Make(petya, vasya, 90), std::logic_error);
}

TEST(Transaction, NegativeTransaction)
{
        MockAccount petya(1, 1000), vasya(2, 1000);
        Transaction transaction;
        EXPECT_THROW(transaction.Make(petya, vasya, -90), std::invalid_argument);
}

TEST(Transaction, InvalidTransaction)
{
        MockAccount petya(1, 1000), vasya(2, 1000);
        Transaction transaction;
        EXPECT_THROW(transaction.Make(petya, petya, 190), std::logic_error);
}

TEST(Transaction, NotEnoughFundsTransaction)
{
        Account petya(1, 1000), vasya(2, 1000);
        Transaction transaction;
        transaction.Make(petya, vasya, 1900);

	EXPECT_EQ(petya.GetBalance(), 1000);
        EXPECT_EQ(vasya.GetBalance(), 1000);

}

