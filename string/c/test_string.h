#ifdef TEST_STRING
#define CTEST_MAIN
#include "ctest.h"

// int main(int argc, char const *argv[])
// {
//     String s = "123452356";
//     String ss = "345";
//     String t = "23";
//     String v = "ab";
//     int pos = 0;
//     string_index(&s, &ss, &pos);
//     printf("pos:%d\n", pos);
//     string_replace(&s, &t,&v);
//     printf("s:%s\n", s);
//     printf("string:%s len:%ld size:%ld\n", s, strlen(s), sizeof(s));
    
//     return 0;
// }

CTEST(stack_string, stack_string_test) {
    char * cs = "1234567qwert";
    char * ct = "12";
    char * cv = "ab";
    String s, s1, t,v;

    ASSERT_EQUAL(OK, string_assign(&s, cs));

    ASSERT_EQUAL(OK, string_assign(&t, ct));

    ASSERT_EQUAL(OK, string_assign(&v, cv));

    ASSERT_EQUAL(false, string_empty(&s));
    
    ASSERT_NOT_EQUAL(0, string_length(&s));
    
    ASSERT_EQUAL(OK, string_copy(&s, &s1));
    
    ASSERT_EQUAL(false, string_empty(&s1));
    
    ASSERT_EQUAL(string_length(&s), string_length(&s1));

    ASSERT_EQUAL(true, string_compare(&s, &s1));
    
    ASSERT_EQUAL(OK, string_concat(&s, &s1));

    ASSERT_EQUAL(string_length(&s1)*2, string_length(&s));

    ASSERT_EQUAL(OK, string_delete(&s, 2, 3));

    ASSERT_EQUAL(OK, string_clear(&s));

    ASSERT_EQUAL(true, string_empty(&s));
    
    ASSERT_EQUAL(0, string_length(&s));
    
    ASSERT_EQUAL(OK, string_destroy(&s));

    ASSERT_EQUAL(WRONG_INPUT, string_replace(&s, &t, &v));
}

int main(int argc, char const *argv[])
{
    int result = ctest_main(argc, argv);
    return result;
}

#endif
