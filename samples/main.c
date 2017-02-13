#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "misd.h"


bool make_map,new_opcode,flag;
char * asm_filename;
char * chr;
char line[LINE_SIZE];
char opcode[10],operand[10];
char map_filename[256],output_filename[256];
FILE * asm_file;
FILE * map_file;
FILE * output_file;
int mem_point,op_count;
int i,j,k,l,m,n,o,p,s;

typedef struct {
    char label[80];     //label of this operator
    int opcode;         //code of operation
    int op[3];          //operands
    bool tag[3];        //tags
    char jmp_label[80]; //symbolic jump label for jwt and jnw
    int jmp_adr;        //jump address
    bool q;             //output queue using flag

} cmd;


cmd prog[MEM_LENGTH];


void print_bin(int num, int l)
{
    int j,k;
    int c[32];
    for (j=l-1;j>=0;j--) {
        c[j]= num%2;
        num/=2;
    }
    for (j=0;j<l;j++) {
        fprintf(output_file, "%d", c[j]);
    }
}

int main(int argc, char *argv[])
{



    printf("MISD assembler, version 1.00. Copyright: Bauman State Technical University\n");
    printf("Usage: misdasm [options] asm_file [output_file] [map_file]\n");
    printf("Options: -m - Generate map file\n");

    if (argc > 1) {
        if (argv[1]=='-m'){
            make_map=true;
        } else {
            make_map=false;
            asm_filename=argv[1];
            asm_file = fopen(asm_filename, "r");
            if (asm_file == NULL) {
                printf("Failure to open asm file.");
                exit(EXIT_FAILURE);
            }
        }
    } else {
        printf("Error in argument list\n");
        exit(EXIT_FAILURE);
    }

    /////////////////////////////////////////
    //           Try to open files
    /////////////////////////////////////////

    if (argc > 2) {
        strcpy(output_filename,argv[2]);
     } else {
        chr = strchr(asm_filename, '.');
        if (chr==NULL) {
            strncat(output_filename,asm_filename,strlen(asm_filename));
            strcpy(map_filename,output_filename);
            strncat(output_filename,".mo",3);
            strncat(map_filename,".map",4);
        } else {
            strncpy(output_filename, asm_filename,(int)chr-(int)asm_filename);
            strcpy(map_filename,output_filename);
            strncat(output_filename,".mo",3);
            strncat(map_filename,".map",4);
        }

    }
    output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
       printf("Failure to open output file.");
       exit(EXIT_FAILURE);
    }

    if (make_map) {
        if (argc > 3) {
            strcpy(map_filename[0],argv[3]);
        }
        map_file = fopen(map_filename, "rw");
        if (output_file == NULL) {
            printf("Failure to open map file.");
            exit(EXIT_FAILURE);
        }
    }

    /////////////////////////////////////////
    //           Start to translate
    /////////////////////////////////////////

    //Memory point
    mem_point = 0;
    //New opcode is ready
    new_opcode = false;
    s=0; //string number

    //Create program image
    while (!feof(asm_file)) {
        line[0]='\0';
        fgets(line, LINE_SIZE, asm_file);

        //Try to find comments
        j = (int)strchr(line,';')-(int)&line;
        if (j>=0) {line[j]='\0';}

        //Search spaces
        i=0; //translation pointer
        while ((line[i]==' ')||(line[i]=='\t')) {
            i++;
        }
        //Try to find label
        j = (int)strchr(line+i,' ')-(int)&line;
        if (j<0) {j=strlen(line);}
        k = (int)strchr(line+i,':')-(int)&line;
        if ((j>=k)&&(k>=0)) {
            strncpy(prog[mem_point].label,line+i,k-i);
            i=k+1;
        }
        while (((line[i]==' ')||(line[i]=='\t'))&&(line[i]!='\0')) {
            i++;
        }

        //Try to find opcode
        j = (int)strchr(line+i,' ')-(int)&line;
        if (j>0) {
            if ((j-i)>10) {
                printf("Error in string [%d] near: %s\n",s,line+i);
                exit(EXIT_FAILURE);
            }
            strncpy(opcode,line+i,j-i);
            opcode[j-i]='\0';
            i=j;
            new_opcode = true;
            prog[mem_point].tag[0]=true;
            prog[mem_point].tag[1]=true;
            prog[mem_point].tag[2]=true;
            op_count = 0;
            //printf("%s\n",prog[mem_point].opcode);
            if (strcmp(opcode,"add")==0) {
                 prog[mem_point].opcode=ADD;
                 op_count=ADD_C;
                 prog[mem_point].q=false;
            }
            if (strcmp(opcode,"del")==0) {
                 prog[mem_point].opcode=DEL;
                 op_count=DEL_C;
                 prog[mem_point].q=false;
            }
            if (strcmp(opcode,"search")==0) {
                prog[mem_point].opcode=SEARCH;
                op_count=SEARCH_C;
                prog[mem_point].q=false;
           }
            if (strcmp(opcode,"min")==0) {
                prog[mem_point].opcode=MIN;
                op_count=MIN_C;
                prog[mem_point].q=false;
           }
            if (strcmp(opcode,"max")==0) {
                prog[mem_point].opcode=MAX;
                op_count=MAX_C;
                prog[mem_point].q=false;
           }
            if (strcmp(opcode,"power")==0) {
                prog[mem_point].opcode=POWER;
                op_count=POWER_C;
                prog[mem_point].q=true; //power is queued mandatory
           }
            if (strcmp(opcode,"dels")==0) {
                prog[mem_point].opcode=DELS;
                op_count=DELS_C;
                prog[mem_point].q=false;
           }
            if (strcmp(opcode,"and")==0) {
                prog[mem_point].opcode=AND;
                op_count=AND_C;
                prog[mem_point].q=false;
           }
            if (strcmp(opcode,"or")==0) {
                prog[mem_point].opcode=OR;
                op_count=OR_C;
                prog[mem_point].q=false;
           }
            if (strcmp(opcode,"not")==0) {
                prog[mem_point].opcode=NOT;
                op_count=NOT_C;
                prog[mem_point].q=false;
           }
            if (strcmp(opcode,"gr")==0) {
                prog[mem_point].opcode=GR;
                op_count=GR_C;
                prog[mem_point].q=false;
           }
            if (strcmp(opcode,"greq")==0) {
                prog[mem_point].opcode=GREQ;
                op_count=GREQ_C;
                prog[mem_point].q=false;
           }
            if (strcmp(opcode,"ls")==0) {
                prog[mem_point].opcode=LS;
                op_count=LS_C;
                prog[mem_point].q=false;
           }
            if (strcmp(opcode,"lseq")==0) {
                prog[mem_point].opcode=LSEQ;
                op_count=LSEQ_C;
                prog[mem_point].q=false;
           }
            if (strcmp(opcode,"sq")==0) {
                prog[mem_point].opcode=SQUIZ;
                op_count=SQUIZ_C;
                prog[mem_point].q=false;
           }
            if (strcmp(opcode,"jwt")==0) {
                prog[mem_point].opcode=JWT;
                op_count=JWT_C;
                prog[mem_point].tag[0]=false;
           }
            if (strcmp(opcode,"jnw")==0) {
                prog[mem_point].opcode=JNW;
                op_count=JNW_C;
                prog[mem_point].tag[0]=true;
           }

            //for queueing commands


            if (strcmp(opcode,"addq")==0) {
                 prog[mem_point].opcode=ADD;
                 op_count=ADD_C;
                 prog[mem_point].q=true;
            }
            if (strcmp(opcode,"delq")==0) {
                 prog[mem_point].opcode=DEL;
                 op_count=DEL_C;
                 prog[mem_point].q=true;
            }
            if (strcmp(opcode,"searchq")==0) {
                prog[mem_point].opcode=SEARCH;
                op_count=SEARCH_C;
                prog[mem_point].q=true;
           }
            if (strcmp(opcode,"minq")==0) {
                prog[mem_point].opcode=MIN;
                op_count=MIN_C;
                prog[mem_point].q=true;
           }
            if (strcmp(opcode,"maxq")==0) {
                prog[mem_point].opcode=MAX;
                op_count=MAX_C;
                prog[mem_point].q=true;
           }
            if (strcmp(opcode,"powerq")==0) {
                prog[mem_point].opcode=POWER;
                op_count=POWER_C;
                prog[mem_point].q=true;
           }
            if (strcmp(opcode,"delsq")==0) {
                prog[mem_point].opcode=DELS;
                op_count=DELS_C;
                prog[mem_point].q=true;
           }
            if (strcmp(opcode,"andq")==0) {
                prog[mem_point].opcode=AND;
                op_count=AND_C;
                prog[mem_point].q=true;
           }
            if (strcmp(opcode,"orq")==0) {
                prog[mem_point].opcode=OR;
                op_count=OR_C;
                prog[mem_point].q=true;
           }
            if (strcmp(opcode,"notq")==0) {
                prog[mem_point].opcode=NOT;
                op_count=NOT_C;
                prog[mem_point].q=true;
           }
            if (strcmp(opcode,"grq")==0) {
                prog[mem_point].opcode=GR;
                op_count=GR_C;
                prog[mem_point].q=true;
           }
            if (strcmp(opcode,"greqq")==0) {
                prog[mem_point].opcode=GREQ;
                op_count=GREQ_C;
                prog[mem_point].q=true;
           }
            if (strcmp(opcode,"lsq")==0) {
                prog[mem_point].opcode=LS;
                op_count=LS_C;
                prog[mem_point].q=true;
           }
            if (strcmp(opcode,"lseqq")==0) {
                prog[mem_point].opcode=LSEQ;
                op_count=LSEQ_C;
                prog[mem_point].q=true;
           }
            if (strcmp(opcode,"sqq")==0) {
                prog[mem_point].opcode=SQUIZ;
                op_count=SQUIZ_C;
                prog[mem_point].q=true;
           }


            if (op_count==0) {
                printf("Unknown opcode in string [%d] near: %s\n",s,line+i);
                exit(EXIT_FAILURE);
            }


        //try to find ops

        for (k=0;k<op_count;k++) {
            while ((line[i]==' ')||(line[i]=="\t")) i++;
            if (i>=strlen(line)) {
                printf("Operands are not corresponds to opcode in string [%d]\n",s);
                exit(EXIT_FAILURE);

            }
            j = (int)strchr(line+i,' ')-(int)&line;
            l = (int)strchr(line+i,',')-(int)&line;

            //find minimum positive

            if (j<0) {j=strlen(line);}
            if ((l>0)&&(l<j)) {j=l;}
            if (j<=i) {
                    printf("Operands are not corresponds to opcode in string [%d]\n",s);
                    exit(EXIT_FAILURE);
            }


            if (prog[mem_point].opcode==JWT) {
                if (prog[mem_point].tag[0]) {
                // if jnw
                    strncpy(prog[mem_point].jmp_label,line+i,j-i);

                    l = (int)strchr(prog[mem_point].jmp_label,'\t')-(int)&(prog[mem_point].jmp_label);
                    if (l>=0) {prog[mem_point].jmp_label[l]='\0';}

                    l = (int)strchr(prog[mem_point].jmp_label,' ')-(int)&(prog[mem_point].jmp_label);
                    if (l>=0) {prog[mem_point].jmp_label[l]='\0';}


                    if (prog[mem_point].jmp_label[0]=='?') {
                        printf("JNW command should have operand in string [%d]\n",s);
                        exit(EXIT_FAILURE);

                    } else {
                        prog[mem_point].tag[1] = true;
                    }
                } else {
                // if jwt
                    strncpy(prog[mem_point].jmp_label,line+i,j-i);

                    l = (int)strchr(prog[mem_point].jmp_label,'\t')-(int)&(prog[mem_point].jmp_label);
                    if (l>=0) {prog[mem_point].jmp_label[l]='\0';}

                    l = (int)strchr(prog[mem_point].jmp_label,' ')-(int)&(prog[mem_point].jmp_label);
                    if (l>=0) {prog[mem_point].jmp_label[l]='\0';}


                    if (prog[mem_point].jmp_label[0]=='?') {
                        prog[mem_point].tag[1] = false;
                    } else {
                        prog[mem_point].tag[1] = true;
                    }
                }
                prog[mem_point].tag[2] = true;

            } else {
                //if a number
                strncpy(operand,line+i,j-i);
                if (operand[0]=='?') {
                    prog[mem_point].tag[k] = false;
                } else {
                    prog[mem_point].op[k] = atoi(operand);
                    prog[mem_point].tag[k] = true;
                }
            }
            i=j+1;
        }



        if (new_opcode) {
            new_opcode = false;
            mem_point++;
            opcode[0]='\0';
        }

        }

        s++;
    }

    //Solve internal links

    for (i=0; i<mem_point; i++) {
        if ((prog[i].opcode==JWT)&&(prog[i].jmp_label[0]!='?')) {
            flag=false;
            for (j=0; j<mem_point; j++) {
                if (strcmp(prog[i].jmp_label,prog[j].label)==0) {
                    prog[i].jmp_adr=j;
                    flag=true;
                }
            }
            if (!flag) {
                printf("Jump address unknown in string [%s]\n",prog[i].jmp_label);
                exit(EXIT_FAILURE);
            }
        }
    }


    //Make output bit file

    for (i=0; i<mem_point; i++) {
        switch (prog[i].opcode) {
        // format 1
        case DELS: case MAX: case MIN: case POWER: case SQUIZ: {
            print_bin(0,32);
            print_bin(0,32);
            //queue
            if (prog[i].q) {
                print_bin(1,1);
            } else {
                print_bin(0,1);
            }
            print_bin(prog[i].op[0],7);
            print_bin(prog[i].opcode,5);
            for (j=2;j>=0;j--) {
                if (prog[i].tag[j]) {
                    print_bin(1,1);
                } else {
                    print_bin(0,1);
                }

            }
            fprintf(output_file,"\n");
            break;
        }
        // format 2
        case DEL: case SEARCH: {
            print_bin(0,32);
            print_bin(prog[i].op[1],32);
            //queue
            if (prog[i].q) {
                print_bin(1,1);
            } else {
                print_bin(0,1);
            }
            print_bin(prog[i].op[0],7);
            print_bin(prog[i].opcode,5);
            for (j=2;j>=0;j--) {
                if (prog[i].tag[j]) {
                    print_bin(1,1);
                } else {
                    print_bin(0,1);
                }

            }
            fprintf(output_file,"\n");
            break;
        }
        // format 3
        case ADD: {
            print_bin(prog[i].op[2],32);
            print_bin(prog[i].op[1],32);
            //queue
            if (prog[i].q) {
                print_bin(1,1);
            } else {
                print_bin(0,1);
            }
            print_bin(prog[i].op[0],7);
            print_bin(prog[i].opcode,5);
            for (j=2;j>=0;j--) {
                if (prog[i].tag[j]) {
                    print_bin(1,1);
                } else {
                    print_bin(0,1);
                }

            }
            fprintf(output_file,"\n");
            break;
        }
        // format 4
        case AND: case OR: case NOT: {
            print_bin(0,32);
            print_bin(0,16);
            print_bin(prog[i].op[2],8);
            print_bin(prog[i].op[1],8);
            //queue
            if (prog[i].q) {
                print_bin(1,1);
            } else {
                print_bin(0,1);
            }
            print_bin(prog[i].op[0],7);
            print_bin(prog[i].opcode,5);
            for (j=2;j>=0;j--) {
                if (prog[i].tag[j]) {
                    print_bin(1,1);
                } else {
                    print_bin(0,1);
                }

            }
            fprintf(output_file,"\n");
            break;
        }
        // format 5
        case LS: case LSEQ: case GR: case GREQ: {
            print_bin(0,24);
            print_bin(prog[i].op[2],32);
            print_bin(prog[i].op[1],8);
            //queue
            if (prog[i].q) {
                print_bin(1,1);
            } else {
                print_bin(0,1);
            }
            print_bin(prog[i].op[0],7);
            print_bin(prog[i].opcode,5);
            for (j=2;j>=0;j--) {
                if (prog[i].tag[j]) {
                    print_bin(1,1);
                } else {
                    print_bin(0,1);
                }

            }
            fprintf(output_file,"\n");
            break;
        }
        // format 6
        case JNW: {
            print_bin(0,32);
            print_bin(0,8);
            print_bin(prog[i].jmp_adr,32);
            print_bin(prog[i].opcode,5);
            for (j=2;j>=0;j--) {
                if (prog[i].tag[j]) {
                    print_bin(1,1);
                } else {
                    print_bin(0,1);
                }

            }
            fprintf(output_file,"\n");
            break;
        }
      }

    }

    for (i=mem_point; i<255; i++) {
        for (j=0; j<80; j++) {
            fprintf(output_file,"0");
        }
        fprintf(output_file,"\n");
    }

    //Important! For ISE to avoid BRAM packing!!!
    fprintf(output_file,"11011100101110111100010011010101111001101111011111101110010111011110001001101010");


    //Make a map file



    /////////////////////////////////////////
    //           Try to close files
    /////////////////////////////////////////

    fclose(asm_file);
    fclose(output_file);
    if (make_map) {
       fclose(map_file);
    }
    return 0;
}

