#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isMatch(const char *s, const char *p){
    if(*p == '\0'){
        return *s == '\0';
    }

    bool firstMatch = (*s != '\0') && (*s == *p || *p == '.');

    if(*(p + 1) == '*'){
        return isMatch(s, p + 2) || (firstMatch && isMatch(s + 1, p));
    }else{
        return firstMatch && isMatch(s + 1, p + 1);
    }
}

int main(){

    const char *s1 = "aa";
    const char *p1 = "a*";
    printf("Test 1: %s\n", isMatch(s1, p1) ? "true" : "false");

    const char *s2 = "aa";
    const char *p2 = "a*";
    printf("Test 2: %s\n", isMatch(s2, p2) ? "true" : "false");

    const char *s3 = "ab";
    const char *p3 = ".*";
    printf("Test 3: %s\n", isMatch(s3, p3) ? "true" : "false");

    const char *s4 = "aab";
    const char *p4 = "c*a*b";
    printf("Test 4: %s\n", isMatch(s4, p4) ? "true" : "false");

    const char *s5 = "mississippi";
    const char *p5 = "mis*is*p*.";
    printf("Test 5: %s\n", isMatch(s5, p5) ? "true" : "false");

    return 0;
}