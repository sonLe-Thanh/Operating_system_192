// main . c
#include <stdio.h> 
#include "readline.h" 
#include "findsubstr.h"

int main(int argc, char * argv[]) { 
	// Implement mygrep
	FILE *fFile;
    char temp[100];
    char * fileName=argv[1];
    char * word=argv[2];
    
    //Open the file
    fFile = fopen(fileName,"r");
    if(fFile == NULL)
    {
    	//If the file is not openable
        printf("file is not present in this directory\n");
        return 0;
    }
    while(fgets(temp,100,fFile)!= NULL)
    {
    	//If there is a sub string in the recently inputted line, print it
        if(find_sub_string(temp,word)>=0)
        {	
            printf("%s",temp);
        }
    }
    fclose(fFile);
    return 0;
}

