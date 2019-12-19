#include "../include/cliqueCreator.h"

int main(int argc, char *argv[]){
	CliqueCreator tmp_oCliqueCreator;
	int count = 1;
	
	for( int j = 50; j <= 100; j+=5 )
		for ( double l = 0.01; l <= 0.1001; l+=0.01 )
			for(int i = 10; i <= 40; i+=5 )
				for( int m = 1; m <= 25; m++ )
				{
					tmp_oCliqueCreator.createClique("experiment",i,i,j,j,l,m);
					count++;
					if ( count % 100 == 0 )
						printf("%d-",count);
				}
	return 0;
}