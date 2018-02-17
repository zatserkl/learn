// mrl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

FILE *ifp, *ofp;
char line[4095];

int _tmain(int argc, _TCHAR* argv[])
{
	ifp = fopen("d:\\Work\\Zond\\2010.03.24_1018\\1.txt", "rt");
    ofp = fopen("d:\\Work\\Zond\\2010.03.24_1018\\1", "wb");
    int cnt = 0;
	while(fgets(line, sizeof(line), ifp) != NULL)
	{
        cnt++;
        
        if((cnt > 4)&&(cnt < 6))
        {
            //printf("%s", line);
            int x = 0;
            int i = 0;
            char *p;
            p = strtok(line, " ");
            //printf(p);
            do
            {
                if(i)
                {
                    p = strtok('\0', " ");
                    if(p)
                    {
                        if(*p == '\n')
                            break;
                        else
                        {
                            x = atoi(p);
                            char(x);
                            fwrite(&p, sizeof(char), 1, ofp);
                        }
                    }
                }
                i++;
            } while(p);
        }
	}
    fcloseall();
	return 0;
}

