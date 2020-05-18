#include "findsubstr.h"

int string_length(char *str){
    int length=0;
    while (str[length]!='\0'){
        length++;
    }
    return length;
}
int find_sub_string(const char *str, const char *sub){
    int a=string_length(str);
    int b=string_length(sub);
    //Compare two strings to find substring
    for (int i=0;i<=a-b;i++){
        int j;
        for (j=0;j<b;j++)
            //If one charater of str does not match charater in sub, break
            if (str[i+j]!=sub[j])
                break;
        //If it has finished the above loop, this mean that the pattern in sub is found in str a position i
        if (j==b)
            return i;
    }
    //If none of the loop satisfield, str does not contain sub
    return -1;
}
