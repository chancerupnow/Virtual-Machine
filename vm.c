// Name: Chance Rupnow
// Class: COP 3402
// Date: 9/16/22
// Assignment: PM/0 Virtual Machine (VM)

// include necessary libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// define constants
#define ARRAY_SIZE 500

// declare functions
int base(int* pas, int bp, int l);

int main() {
    // declare cpu values
    int bp;
    int sp = 0;
    int pc;

    // declare ir values
    int op;
    int l;
    int m;

    // declare halt value
    int halt;

    // intialize pas[]
    int* pas = (int*)malloc(ARRAY_SIZE * sizeof(int));
    
    // set all pas[] values to 0
    for(int i = 0; i < ARRAY_SIZE; i++) {
        pas[i] = 0;
    }

    // initialize file reader
    FILE *fp = fopen("input.txt", "r");

    // set val for reading input
    int val;

    // loop through file and read input
    while(1) {

        // scan val
        fscanf(fp, "%d", &val);

        // set pas[i] to val
        pas[sp] = val;

        // increment sp
        sp++;

        // if end of file, break loop
        if(feof(fp)) {
            break;
        }
    }
    // decrement sp as it was incrememnted after last value
    sp--;

    /* TEST
    // test pas values
    for(int j = 0; j < ARRAY_SIZE; j++) {
        printf("%d ", pas[j]);
    }

    // TEST
    // test sp value
    printf("\n%d \n", sp);
    */

    // close file pointer
    fclose(fp);

    // set initial values
    bp = sp + 1;
    pc = 0;
    halt = 1;
    char opcode[3] = "NUL";
    // ir values still null

    // this value will serve as our stack bottom, used for printing stack later
    int bot = bp;

    // this value will serve as our overall instruction count
    // it will be used for printing later
    int ct = 0;

    // print initial values
    printf("\t\tPC\tBP\tSP\tstack\n");
    printf("Initial values:\t%d\t%d\t%d\n", pc, bp, sp);

    // while statement with halt value
    while(halt == 1) {

        // fetch cycle
        // set ir values
        op = pas[pc];
        l = pas[pc+1];
        m = pas[pc+2];

        // increment pc
        pc += 3;

        // execution cycle
        switch(op) {
            case 1:
                sp += 1;
                pas[sp] = m;
                opcode[0] = 'L';
                opcode[1] = 'I';
                opcode[2] = 'T';
                break;
            case 2:
                switch(m) {
                    case 0:
                        sp = bp - 1;
                        bp = pas[sp+2];
                        pc = pas[sp+3];
                        opcode[0] = 'R';
                        opcode[1] = 'T';
                        opcode[2] = 'N';
                        break;
                    case 1:
                        pas[sp-1] = pas[sp-1] + pas[sp];
                        sp = sp-1;
                        opcode[0] = 'A';
                        opcode[1] = 'D';
                        opcode[2] = 'D';
                        break;
                    case 2:
                        pas[sp-1] = pas[sp-1] - pas[sp];
                        sp = sp-1;
                        opcode[0] = 'S';
                        opcode[1] = 'U';
                        opcode[2] = 'B';
                        break;
                    case 3:
                        pas[sp-1] = pas[sp-1] * pas[sp];
                        sp = sp-1;
                        opcode[0] = 'M';
                        opcode[1] = 'U';
                        opcode[2] = 'L';
                        break;
                    case 4:
                        pas[sp-1] = pas[sp-1] / pas[sp];
                        sp = sp-1;
                        opcode[0] = 'D';
                        opcode[1] = 'I';
                        opcode[2] = 'V';
                        break;
                    case 5:
                        pas[sp-1] = pas[sp-1] == pas[sp];
                        sp = sp-1;
                        opcode[0] = 'E';
                        opcode[1] = 'Q';
                        opcode[2] = 'L';
                        break;
                    case 6:
                        pas[sp-1] = pas[sp-1] != pas[sp];
                        sp = sp-1;
                        opcode[0] = 'N';
                        opcode[1] = 'E';
                        opcode[2] = 'Q';
                        break;
                    case 7:
                        pas[sp-1] = pas[sp-1] < pas[sp];
                        sp = sp-1;
                        opcode[0] = 'L';
                        opcode[1] = 'S';
                        opcode[2] = 'S';
                        break;
                    case 8:
                        pas[sp-1] = pas[sp-1] <= pas[sp];
                        sp = sp-1;
                        opcode[0] = 'L';
                        opcode[1] = 'E';
                        opcode[2] = 'Q';
                        break;
                    case 9:
                        pas[sp-1] = pas[sp-1] > pas[sp];
                        sp = sp-1;
                        opcode[0] = 'G';
                        opcode[1] = 'T';
                        opcode[2] = 'R';
                        break;
                    case 10:
                        pas[sp-1] = pas[sp-1] >= pas[sp];
                        sp = sp-1;
                        opcode[0] = 'G';
                        opcode[1] = 'E';
                        opcode[2] = 'Q';
                        break;
                }
                break;
            case 3:
                sp += 1;
                pas[sp] = pas[base(pas, bp, l) + m];
                opcode[0] = 'L';
                opcode[1] = 'O';
                opcode[2] = 'D';
                break;
            case 4:
                pas[base(pas, bp, l) + m] = pas[sp];
                sp = sp-1;
                opcode[0] = 'S';
                opcode[1] = 'T';
                opcode[2] = 'O';
                break;
            case 5:
                pas[sp+1] = base(pas, bp, l); // static link
                pas[sp+2] = bp; // dynamic link
                pas[sp+3] = pc; // return address
                bp = sp+1;
                pc = m;
                opcode[0] = 'C';
                opcode[1] = 'A';
                opcode[2] = 'L';
                break;
            case 6:
                sp = sp+m;
                opcode[0] = 'I';
                opcode[1] = 'N';
                opcode[2] = 'C';
                break;
            case 7:
                pc = m;
                opcode[0] = 'J';
                opcode[1] = 'M';
                opcode[2] = 'P';
                break;
            case 8:
                if (pas[sp] == 0) {
                    pc = m;
                }
                sp = sp-1;
                opcode[0] = 'J';
                opcode[1] = 'P';
                opcode[2] = 'C';
                break;
            case 9:
                switch(m) {
                    case 1:
                        printf("Output : %d\n", pas[sp]);
                        opcode[0] = 'W';
                        opcode[1] = 'R';
                        opcode[2] = 'T';
                        break;
                    case 2:
                        sp = sp+1;
                        printf("Input : ");
                        scanf("%d", &pas[sp]);
                        printf("%d\n", pas[sp]);
                        opcode[0] = 'R';
                        opcode[1] = 'E';
                        opcode[2] = 'D';
                        break;
                    case 3:
                        halt = 0;
                        opcode[0] = 'H';
                        opcode[1] = 'L';
                        opcode[2] = 'T';
                        break;
                }
                break;
            default:
                opcode[0] = 'E';
                opcode[1] = 'R';
                opcode[2] = 'R';
                break;
        }

        // print register values
        printf("%d  %s  %d  %d\t%d\t%d\t%d\t", ct, opcode, l, m, pc, bp, sp);

        // print stack values
        for(int i = bot; i <= sp; i++) {
            if(bp > bot && i == bp) {
                printf("| ");
            }
            printf("%d ", pas[i]);
        }

        // newline
        printf("\n");

        // increment ct
        ct++;
        
    }

    // end program
    return 0;
}

// intialize base function
int base(int* pas, int bp, int l)
{
    // arb = activation record base
    int arb = bp;

    //find base L levels down
    while (l > 0) {
        arb = pas[arb];
        l--;
    }
    
    return arb;
}