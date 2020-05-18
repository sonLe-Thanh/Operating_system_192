#include "readline.h"
#include <stdio.h>
//Return string length
int string_length_1(char * str){
    int length=0;
    while (str[length]!='\0'){
        length++;
    }
    return length-1;
}
//Increase after each time called
int count_exec(){
    static int counter=0;
    return counter++;
}
int read_line(char * str){
    char temp[10000][100];
    static int line=0;
    //Read all the line 
    while (fgets(temp[line], 100, stdin)!=NULL) {
        line++;
    }
    int counter=count_exec();
    //If this is not the last line
    if (counter!=line-1){
        str=temp[counter];
        //printf("%s\n",str);
        return string_length_1(str);
    }
    //If this is the last line
    else {
        str=temp[counter];
        //printf("%s\n",str);
        return -1;
    }
    return -1;
}
