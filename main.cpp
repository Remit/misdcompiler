#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

extern FILE *yyin;
extern FILE *yyout;
extern int yyparse(void);

int main(int argc, char *argv[]) {
	if( argc < 3 ) {
		cout << "You need to specify input and output files." << endl;
		exit(0);
	}

	FILE *fp = fopen(argv[1],"r");
	if( !fp ) {
		cout << "Could not open the file for reading." << endl;
		exit(0);
	}

	FILE *out_fp = fopen(argv[2],"w");
	if( ! out_fp ) {
		cout << "Could not open the file for writing." << endl;
		exit(0);
	}

	yyin = fp;
	yyout = out_fp;

	yyparse();

	fclose(fp);
	fclose(out_fp);

	cout << "All done!" << endl;
	return 0;
}
