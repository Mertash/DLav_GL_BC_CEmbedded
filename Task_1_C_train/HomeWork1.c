#include <stdio.h>


int GROUP_NUMBER = 5;
char* FULL_NAME = "Lavriv Dmytro Leonidovych";
char* EMAIL = "ldlavriv@gmail.com";
char* REP_LINK = "https://github.com/Mertash/DLav_GL_BC_CEmbedded.git";
char* GOOGL_DRIVE_LINK = "https://drive.google.com/drive/folders/1K1V7YZwifmBObhR0MoM-8uD4yD8v6hwv?usp=share_link";


int main()
{

	printf( "Group number - %d\n\r"
			"Full name - %s\n\r"
			"Email - %s\n\r"
			"Repository link - %s\n\r"
			"Google share folder link - %s\n\r",GROUP_NUMBER, FULL_NAME, EMAIL, REP_LINK, GOOGL_DRIVE_LINK );

	return 0;
}