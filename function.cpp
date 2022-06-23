#include "function.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>

using namespace std;

unsigned int sut( vector<int>& x, int * C, int k, int hash, vector<int>& y)
{
    int n = x.size();
    int i, j, l;
    
    j = n;
    
    for ( i = 0; i < n; i++ )
    {
        if ( C[i] == 0 )
        {
            j = i;
            break;
        }
    }
    l = 0;
    if ( j + k - 1 < n )
        while ( l < k ) y[l++] = x[j++];
    
    int f, p, c;
	f = 0;
    while ( j < n )
    {
        p = j - k; 
		c = p + 1;
        if ( C[p] == 0 && C[c] == 0 )
            y[l++]=x[j++];
        if ( C[p] == 1 && C[c] == 0 )
        {
			vector<int> xc(x.begin()+c-1,x.begin()+c+k-2);
			vector<int> xf(x.begin()+f-1,x.begin()+f+k-2);
            if ( xc == xf)	y[l++] = x[j++];
            else
            {
                y[l++] = hash;
                for ( i = c; i < c + k - 1; i++ )
                    y[l++] = x[i];
                y[l++] = x[j++];
            }
        }
        if ( C[p] == 1 && C[c] == 1 )	j++;
        if ( C[p] == 0 && C[c] == 1 )
        {
            j++;
            f = c;
        }
	}
    return l;
}

