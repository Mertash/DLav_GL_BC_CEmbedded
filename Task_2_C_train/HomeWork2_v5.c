#include <stdio.h>
#include <math.h>



/*variant 5

z1 = 1-1/4*((sin((2A)))^2)+cos(2A)

z2 = (cos((A)))^2+(cos((A)))^4

//z2 = cos((A))^2 * (1+(cos((A)))^2)

*/
unsigned int VARIANT = 5;
double PI = 3.141592653;
 
double z1 = 0.0; //Grad value z1
double z2 = 0.0; //Grad value z2

double ARC_z1 = 0.0; //Arc value z1
double ARC_z2 = 0.0; //Arc value z2


double ALPHA = 0.0; //Grad value angle


int main()
{
 
double ARC_COEF = PI/180;// use for convert Grad to Arc value

double ARC_ALPHA = ARC_COEF * ALPHA; //Arc value angle

// TEST func start///

	ARC_z1 = sin(PI); // sin(PI)=sin(180*)=0 arc
	ARC_z2 = cos(PI); // cos(PI)=cos(180*)=-1 arc
	printf("TEST func start\n");
	printf("Sin(PI) =%.10f arc\n",ARC_z1 );//Print sin arc value
	printf("Cos(PI) =%.10f arc\n",ARC_z2 );//Print cos arc value

    z1 = ARC_z1*180/PI; //convert Arc to Grad value
    z2 = ARC_z2*180/PI; //convert Arc to Grad value
    
    printf("Sin(PI) =%.10f grad\n",z1 );//Print sin grad value
	printf("Cos(PI) =%.10f grad\n",z2 );//Print cos grad value

    printf("TEST func stop\n\n");
// TEST func stop ///


// Work func start//
    printf("Variant %d func start\n\n", VARIANT);
    printf("Value angle Alpha = %.10f \n", ALPHA);
    
	ARC_z1 = 1 - (((sin(2*ARC_ALPHA))*(sin(2*ARC_ALPHA)))/4) + cos(2*ARC_ALPHA); 

	printf("ARC_z1 =%.10f rad\n",ARC_z1 );

    z1 = ((ARC_z1*180)/PI);

    printf("z1 =%.10f grad\n",z1 );

	ARC_z2 = (cos(ARC_ALPHA)*cos(ARC_ALPHA)) * (1+(cos(ARC_ALPHA)*cos(ARC_ALPHA)));

    printf("ARC_z2 =%.10f rad\n",ARC_z2 );
	
	z2 = ((ARC_z2*180)/PI);

    printf("z2 =%.10f grad\n",z2 );

// Work func stop//

	return 0;
}

