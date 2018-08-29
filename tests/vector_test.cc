#include <gtest/gtest.h>
#include <cc/vector.h>

using ::testing::Test;
using ::testing::InitGoogleTest;
using ::testing::UnitTest;
using ::testing::TestInfo;
using ::testing::TestPartResult;

TEST(VectorTest, InitializationTest)
{
    DECLARE_VECTOR(int, vec);
    struct vec v;
    EXPECT_EQ(vector_init(&v), 0);
    EXPECT_EQ(vector_len(&v), 0ULL);
    EXPECT_EQ(vector_capacity(&v), VECTOR_INIT_SIZE);
    vector_free(&v);
}

TEST(VectorTest, PushbackTest)
{
    DECLARE_VECTOR(int, vec);
    struct vec v;
    EXPECT_EQ(vector_init(&v), 0);

    for (size_t i = 0; i < VECTOR_INIT_SIZE; ++i) {
        EXPECT_EQ(vector_push(&v, &i), 0);
    }

    EXPECT_EQ(vector_len(&v), VECTOR_INIT_SIZE);
    EXPECT_EQ(vector_capacity(&v), VECTOR_INIT_SIZE);
    vector_free(&v);
}

TEST(VectorTest, ResizeTest)
{
    DECLARE_VECTOR(int, vec);
    struct vec v;
    EXPECT_EQ(vector_init(&v), 0);

    for (size_t i = 0; i < VECTOR_INIT_SIZE*2; ++i) {
        EXPECT_EQ(vector_push(&v, &i), 0);
    }

    EXPECT_EQ(vector_len(&v), VECTOR_INIT_SIZE*2);
    EXPECT_EQ(vector_capacity(&v), VECTOR_INIT_SIZE*VECTOR_RESIZE_FACTOR);
    vector_free(&v);
}

TEST(VectorTest, PushNothingTest)
{
    DECLARE_VECTOR(int, vec);
    struct vec v;
    EXPECT_EQ(vector_init(&v), 0);
    EXPECT_NE(vector_push(&v, NULL), 0); 
    vector_free(&v);
}

int
main(int argc, char *argv[])
{
    InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
