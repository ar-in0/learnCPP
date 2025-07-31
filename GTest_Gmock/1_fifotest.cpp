#include "queue-utils.h"
#include <gtest/gtest.h>


// fixture class. Objects of this class 
// will be reused across tests.
class QueueTest : public testing::Test {
protected:
    QueueTest() {
        // q0_ remains empty
        q1_.Enqueue(1);
        q2_.Enqueue(2);
        q2_.Enqueue(3);
    }
    // destructor/ TearDown() not necessary, implicit destructor will be called.
     // ~QueueTest() override = default;
   
     Queue<int> q0_;
     Queue<int> q1_;
     Queue<int> q2_;
};


// Write tests using the fixture
// TEST_F(<fixture_class_name>, <test_name>)
// For each test defined with TEST_F(), GoogleTest will 
// 1. create a fresh test fixture (i.e. object of that class) at runtime, 
// 2. immediately initialize it via SetUp(), 
// 3. run the test, 
// 4. clean up by calling TearDown(), 
// 5. and then delete the test fixture.
TEST_F(QueueTest, IsEmptyInitially) {
    EXPECT_EQ(q0_.Size(), 0);
}

TEST_F(QueueTest, DequeueWorks) {
    int* n = q0_.Dequeue();
    EXPECT_EQ(n, nullptr);

    n = q1_.Dequeue();
    ASSERT_NE(n, nullptr);
    EXPECT_EQ(*n, 1);
    EXPECT_EQ(q1_.Size(), 0); // after dequeue, the queue is empty.
    delete n;

    n = q2_.Dequeue();
    ASSERT_NE(n, nullptr);
    EXPECT_EQ(*n, 2);
    EXPECT_EQ(q2_.Size(), 1);
    delete n;
}