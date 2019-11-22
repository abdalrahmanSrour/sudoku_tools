#ifndef _TEST_H_
#define _TEST_H_

#define TEST_START()                 \
    do                               \
    {                                \
        number_of_test = 0;          \
        number_of_correct_tests = 0; \
        DBG("\n\n");                 \
    } while (0);

#define TEST_FINISH()                                                              \
    do                                                                             \
    {                                                                              \
        DBG("Test finish");                                                        \
        DBGF("Test result: %d/%d\n\n", number_of_correct_tests, number_of_test); \
    } while (0);

#define FAIL_EQ(a, b)                                                          \
    do                                                                         \
    {                                                                          \
        number_of_test++;                                                      \
        DBGF("Test #%d\n", number_of_test);                                    \
        if (a != b)                                                            \
        {                                                                      \
            DBGF("%s:%d: failed\n", __FILE__, __LINE__);                       \
            DBGF("%s = %d while %s = %d so %s != %s\n", #a, a, #b, b, #a, #b); \
        }                                                                      \
        else                                                                   \
        {                                                                      \
            number_of_correct_tests++;                                         \
        }                                                                      \
    } while (0);

#define FAIL_NE(a, b)                                                       \
    do                                                                      \
    {                                                                       \
        number_of_test++;                                                   \
        DBGF("Test #%d\n", number_of_test);                                 \
        if (a == b)                                                         \
        {                                                                   \
            DBGF("%s:%d: failed\n", __FILE__, __LINE__);                    \
            DBGF("%s = %d and %s = %d so %s = %s\n", #a, a, #b, b, #a, #b); \
        }                                                                   \
        else                                                                \
        {                                                                   \
            number_of_correct_tests++;                                      \
        }                                                                   \
    } while (0);

#define FAIL_STR_EQ(a, b)                                                   \
    do                                                                      \
    {                                                                       \
        number_of_test++;                                                   \
        DBGF("Test #%d\n", number_of_test);                                 \
        if (strcmp(a, b))                                                   \
        {                                                                   \
            DBGF("%s:%d: failed\n", __FILE__, __LINE__);                    \
            DBGF("%s = %d and %s = %d so %s = %s\n", #a, a, #b, b, #a, #b); \
        }                                                                   \
        else                                                                \
        {                                                                   \
            number_of_correct_tests++;                                      \
        }                                                                   \
    } while (0);

#endif /* _TEST_H_ */
