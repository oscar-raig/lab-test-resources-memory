
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <string.h>
#include <stdlib.h>

int PrintResourceUsage( const struct rusage* const usage )
{

	if ( usage == NULL )
	{
		printf("Error : PrintResourceUsage pointer is NULL\n");
		return -1;
	}
	printf ("Maximum Resident set size     %u\n",usage->ru_maxrss);
	printf ("integral unshared stack size  %u\n",usage->ru_isrss); 
	printf ("block input operations        %u\n",usage->ru_inblock);
	
	printf ("user time used seconds   %u\n", usage->ru_utime.tv_sec); 
	printf ("user time used microseconds   %u\n", usage->ru_utime.tv_usec); 
}

int main()
{
	struct rusage usage;
	
	


	printf("Programa de testeig de la memòria \n");
	
	
	int i = 0;
	for ( i = 0 ; i < 10000000 ; i++ )
	{
		char * p = (char * )malloc (10000);
		sprintf (p,"Iteration %u", i );
		
		printf("message : (%s)\n",p);
		
		memset(&usage,0,sizeof(struct rusage));
		
		int result = getrusage(RUSAGE_SELF, &usage);
		if ( result == -1 )
		{
			printf ( "Error : main : problems calling getrusage\n" );
			return -1;
		}
		
		result = PrintResourceUsage( &usage );
		
		if ( result == -1 )
		{
			printf ( "Error : main : problems calling PrintResourceUsage\n" );
			return -1;
		}
	}
	
	return 0;
}
