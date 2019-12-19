#include "definitions.h"
#include <cstdio>

class CliqueCreator{
	public:
		List<Tuple2<int,int> > edgesForRandom;
		void createClique( char *filename, int size1, int size2, int inputSize1, int inputSize2, double density, int id );
		void createCliqueByRandomization( char *filename, int size1, int size2, int inputSize1, int inputSize2, double density, int id, int randomizationIterate );
		void createMatrixForSample( int size1, int size2, int inputSize1, int inputSize2, double density );
		inline void clearEdgesForRandom()
		{
			edgesForRandom.clear();
		}
};


void CliqueCreator::createMatrixForSample( int size1, int size2, int inputSize1, int inputSize2, double density )
{
	Array<bool> LayerA_bool( inputSize1 );	
	Array<bool> LayerB_bool( inputSize2 );
	List<Tuple2<int,int> > edges;

	for( int i = 0; i < inputSize1; i++ ){
		LayerA_bool[ i ] = false;
	}
	for( int i = 0; i < inputSize2; i++ ){
		LayerB_bool[ i ] = false;
	}

	int count = 0;
	while( count != size1 ){
		int random = randomNumber( 0, inputSize1 - 1 );
		if( LayerA_bool[ random ] == false ){
			LayerA_bool[ random ] = true;
			count++;
		}
	}
	count = 0;
	while( count != size2 ){
		int random = randomNumber( 0, inputSize2 - 1 );
		if( LayerB_bool[ random ] == false ){
			LayerB_bool[ random ] = true;
			count++;
		}
	}

	Array2D<int> isEdge( 0, inputSize1, 0, inputSize2, 0 );
	for( int i = 0; i < inputSize1; i++ ){
		if( LayerA_bool[ i ] == true ){
			for( int j = 0; j < inputSize2; j++ ){
				if( LayerB_bool[ j ] == true ){
					Tuple2<int,int> tup( i, j );
					isEdge( i, j ) = 1;
					edges.pushBack( tup );
				}
			}
		}
	}
	
	int edgeNumber = (int)( (double)inputSize1 * (double)inputSize2 * (double)density );
	count = 0;
	while( count != edgeNumber ){
		int random = randomNumber( 0, inputSize1 - 1 );
		int random2 = randomNumber( 0, inputSize2 - 1 );
		Tuple2<int,int> tup( random, random2 );
		/*while( edges2.empty() != true ){ 
			Tuple2<int,int> tup_t = edges2.popFrontRet();
			if( tup_t.m_x1 == random && tup_t.m_x2 == random2 )
				istrue = true;
		}*/
		if( isEdge( random, random2 ) == 0 ){
			edges.pushBack( tup );
			isEdge( random, random2 ) = 1;
			count++;
		}
		/*if ( count % 1000 == 0 )
			printf("%d-",count);*/
	}
	edgesForRandom = edges;
}

void CliqueCreator::createCliqueByRandomization( char *filename, int size1, int size2, int inputSize1, int inputSize2, double density, int id, int randomizationIterate ){

	List<Tuple2<int,int> > edges = edgesForRandom;
	List<Tuple2<int,int> > edges2;
	List<Tuple2<int,int> >::iterator itEdges;
	
	cout << endl << edges.size() << " - ";
	if ( edgesForRandom.empty() )
	{
		return;
	}

	edges2 = edges;

	int count = 0;
	while( count != randomizationIterate ){
		
		int random_X = randomNumber( 0, inputSize1 - 1 );
		int random_Y = randomNumber( 0, inputSize1 - 1 );

		if( random_X != random_Y )
		{
			for ( itEdges = edges2.begin() ; itEdges != edges2.end(); itEdges++ )
			{
				if ( (*itEdges).m_x1 == random_X )
				{
					(*itEdges).m_x1 = inputSize1;
				}
			}

			for ( itEdges = edges2.begin() ; itEdges != edges2.end(); itEdges++ )
			{
				if ( (*itEdges).m_x1 == random_Y )
				{
					(*itEdges).m_x1 = random_X;
				}
			}

			for ( itEdges = edges2.begin() ; itEdges != edges2.end(); itEdges++ )
			{
				if ( (*itEdges).m_x1 == inputSize1 )
				{
					(*itEdges).m_x1 = random_Y;
				}
			}

			count++;
		}
	}

	cout << edges2.size() << " - ";

	count = 0;
	while( count != randomizationIterate ){
		
		int random_X = randomNumber( 0, inputSize2 - 1 );
		int random_Y = randomNumber( 0, inputSize2 - 1 );

		if( random_X != random_Y )
		{
			for ( itEdges = edges2.begin() ; itEdges != edges2.end(); itEdges++ )
			{
				if ( (*itEdges).m_x2 == random_X )
				{
					(*itEdges).m_x2 = inputSize2;
				}
			}

			for ( itEdges = edges2.begin() ; itEdges != edges2.end(); itEdges++ )
			{
				if ( (*itEdges).m_x2 == random_Y )
				{
					(*itEdges).m_x2 = random_X;
				}
			}

			for ( itEdges = edges2.begin() ; itEdges != edges2.end(); itEdges++ )
			{
				if ( (*itEdges).m_x2 == inputSize2 )
				{
					(*itEdges).m_x2 = random_Y;
				}
			}

			count++;
		}
	}
	
	cout << edges2.size() << " - ";

	edges = edges2;
	edges2.clear();

	FILE *fptr;
	char fileName[512];
	char fileName2[512];
	// experiment_60x60_100_0.100000_37_bimax.txt
	sprintf( fileName2, "%s_%dx%d_%d_%lf_%d_", filename, size1, size2, inputSize1, density, id );

	sprintf( fileName, "%s_mica.txt", fileName2 );
	if( ( fptr = std::fopen( fileName, "w" ) ) != NULL ){
		//fprintf( fptr, "%d %d %d %d %d\n", edges.size(), inputSize1, inputSize2, size1, size2 );
		edges2 = edges;
		while( edges2.empty() != true ){ 
			Tuple2<int,int> tup_t = edges2.popFrontRet();
			fprintf( fptr, "%d %d\n", tup_t.m_x1, tup_t.m_x2 );
		}
		fclose( fptr );
	}
	else{
		cout << " File can not be opened\n";
	}


	sprintf( fileName, "%s_gurobi.txt", fileName2 );
	if( ( fptr = std::fopen( fileName, "w" ) ) != NULL ){
		//fprintf( fptr, "%d %d %d %d %d\n", edges.size(), inputSize1, inputSize2, size1, size2 );
		edges2 = edges;
		while( edges2.empty() != true ){ 
			Tuple2<int,int> tup_t = edges2.popFrontRet();
			fprintf( fptr, "%d %d\n", tup_t.m_x1, inputSize1 + tup_t.m_x2 );
		}
		fclose( fptr );
	}
	else{
		cout << " File can not be opened\n";
	}

	sprintf( fileName, "%s_bimax.txt", fileName2 );
	if( ( fptr = std::fopen( fileName, "w" ) ) != NULL ){
		Array2D<int> adjMatrix( 0, inputSize1, 0, inputSize2, 0 );
		edges2 = edges;
		while( edges2.empty() != true ){ 
			Tuple2<int,int> tup_t = edges2.popFrontRet();
			adjMatrix( tup_t.m_x1, tup_t.m_x2 ) = 1;
		}
		fprintf( fptr, "%d %d %d %d\n", inputSize1, inputSize2, 2, 2 );
		for( int i = 0; i < inputSize1; i++ ){
			for( int j = 0; j < inputSize2; j++ ){
				if( j != inputSize2 - 1 )
					fprintf( fptr, "%d\t", adjMatrix( i, j ) );
				else{
					if( i != inputSize1 - 1 ){
						fprintf( fptr, "%d\n", adjMatrix( i, j ) );
					}
					else{
						fprintf( fptr, "%d", adjMatrix( i, j ) );
					}
				}
			}
		}
		fclose( fptr );
	}
	else{
		cout << " File can not be opened\n";
	}
}

void CliqueCreator::createClique( char *filename, int size1, int size2, int inputSize1, int inputSize2, double density, int id ){
	
	Array<bool> LayerA_bool( inputSize1 );	
	Array<bool> LayerB_bool( inputSize2 );
	List<Tuple2<int,int> > edges;

	for( int i = 0; i < inputSize1; i++ ){
		LayerA_bool[ i ] = false;
	}
	for( int i = 0; i < inputSize2; i++ ){
		LayerB_bool[ i ] = false;
	}

	int count = 0;
	while( count != size1 ){
		int random = randomNumber( 0, inputSize1 - 1 );
		if( LayerA_bool[ random ] == false ){
			LayerA_bool[ random ] = true;
			count++;
		}
	}
	count = 0;
	while( count != size2 ){
		int random = randomNumber( 0, inputSize2 - 1 );
		if( LayerB_bool[ random ] == false ){
			LayerB_bool[ random ] = true;
			count++;
		}
	}

	Array2D<int> isEdge( 0, inputSize1, 0, inputSize2, 0 );
	for( int i = 0; i < inputSize1; i++ ){
		if( LayerA_bool[ i ] == true ){
			for( int j = 0; j < inputSize2; j++ ){
				if( LayerB_bool[ j ] == true ){
					Tuple2<int,int> tup( i, j );
					isEdge( i, j ) = 1;
					edges.pushBack( tup );
				}
			}
		}
	}

	int edgeNumber = (int)( (double)inputSize1 * (double)inputSize2 * (double)density );
	count = 0;
	while( count != edgeNumber ){
		List<Tuple2<int,int> > edges2 = edges;
		int random = randomNumber( 0, inputSize1 - 1 );
		int random2 = randomNumber( 0, inputSize2 - 1 );
		Tuple2<int,int> tup( random, random2 );
		/*while( edges2.empty() != true ){ 
			Tuple2<int,int> tup_t = edges2.popFrontRet();
			if( tup_t.m_x1 == random && tup_t.m_x2 == random2 )
				istrue = true;
		}*/
		if( isEdge( random, random2 ) == 0 ){
			edges.pushBack( tup );
			isEdge( random, random2 ) = 1;
			count++;
		}
		/*if ( count % 1000 == 0 )
			printf("%d-",count);*/
	}
	
	FILE *fptr;
	char fileName[512];
	char fileName2[512];
	// experiment_60x60_100_0.100000_37_bimax.txt
	sprintf( fileName2, "%s_%dx%d_%d_%lf_%d_", filename, size1, size2, inputSize1, density, id );

	sprintf( fileName, "%s_cplex.txt", fileName2 );
	if( ( fptr = std::fopen( fileName, "w" ) ) != NULL ){
		fprintf( fptr, "%d %d %d %d %d\n", edges.size(), inputSize1, inputSize2, size1, size2 );
		List<Tuple2<int,int> > edges2 = edges;
		while( edges2.empty() != true ){ 
			Tuple2<int,int> tup_t = edges2.popFrontRet();
			fprintf( fptr, "%d %d\n", tup_t.m_x1, tup_t.m_x2 );
		}
		fclose( fptr );
	}
	else{
		cout << " File can not be opened\n";
	}


	sprintf( fileName, "%s_gurobi.txt", fileName2 );
	if( ( fptr = std::fopen( fileName, "w" ) ) != NULL ){
		//fprintf( fptr, "%d %d %d %d %d\n", edges.size(), inputSize1, inputSize2, size1, size2 );
		List<Tuple2<int,int> > edges2 = edges;
		while( edges2.empty() != true ){ 
			Tuple2<int,int> tup_t = edges2.popFrontRet();
			fprintf( fptr, "%d %d\n", tup_t.m_x1, inputSize1 + tup_t.m_x2 );
		}
		fclose( fptr );
	}
	else{
		cout << " File can not be opened\n";
	}

	sprintf( fileName, "%s_bimax.txt", fileName2 );
	if( ( fptr = std::fopen( fileName, "w" ) ) != NULL ){
		Array2D<int> adjMatrix( 0, inputSize1, 0, inputSize2, 0 );
		List<Tuple2<int,int> > edges2 = edges;
		while( edges2.empty() != true ){ 
			Tuple2<int,int> tup_t = edges2.popFrontRet();
			adjMatrix( tup_t.m_x1, tup_t.m_x2 ) = 1;
		}
		fprintf( fptr, "%d %d %d %d\n", inputSize1, inputSize2, 2, 2 );
		for( int i = 0; i < inputSize1; i++ ){
			for( int j = 0; j < inputSize2; j++ ){
				if( j != inputSize2 - 1 )
					fprintf( fptr, "%d\t", adjMatrix( i, j ) );
				else{
					if( i != inputSize1 - 1 ){
						fprintf( fptr, "%d\n", adjMatrix( i, j ) );
					}
					else{
						fprintf( fptr, "%d", adjMatrix( i, j ) );
					}
				}
			}
		}
		fclose( fptr );
	}
	else{
		cout << " File can not be opened\n";
	}
}