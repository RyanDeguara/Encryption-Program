/*
Compiler Used: Visual Studio Code
Program to display a menu to enter any code, encrypt and decrypt the code, display the number of times it was encrypted successfully and unsuccessfully and to also exit the program. Must use functions with pass by reference.
Only valid code to enter is 1 2 3 4
*/
#include <stdio.h>

//declare symbolic name
#define SIZE 4

//declare functions
void enter_code(int *);
void encrypt_code(int *, int *, int *, int *, int *);
void decrypt_code(int *, int*);
void count_code(int *, int *);
void exitprogram(int *);

int main(void) { //start main

    //declare variables
    int access_code[SIZE] = {4, 5, 2, 3};
    int input_code[SIZE];
    int i;
    int option = 0;
    int oper;
    int counter = 1;
    int counter2 = 1;
    int counter3 = 1;
    int correct_counter = 0;
    int incorrect_counter = 0;
    int incorrect_counter2 = 0;

    //do..while loop to atleast execute once to infinite.
    do
    { //open do..while
    
        //display menu
        printf("\n1. Enter any code");
        printf("\n2. Encrypt code entered and verify if correct");
        printf("\n3. Decrypt code");
        printf("\n4. Display the number of time the encrypted code entered matches the authorised code (i) Successfully (ii) Incorrectly");
        printf("\n5. Exit Program");

        //Ask user to input options 1-5
        printf("\n\nPlease select an option above by entering a number from 1-5.\n");
        scanf("%d", &oper);
        printf("\n");

        //input validation
        if (oper > 5 || oper < 1) //if any input entered thats not between 1-5 do the following:
        { //start if
            printf("\nPlease enter a valid operator (1-5)\n");
        } //end if

        //clear input buffer
        getchar();

        //switch statement for cases 1,2,3,4
        switch(oper)
        { //start switch

            //if user enters 1 do the following:
            case 1:
            { //start case 1

                enter_code(input_code); //call function

                //reset counters
                counter = 1;
                counter2 = 1;
                counter3 = 1;
                incorrect_counter = 0;

                //exit case 1
                break;

            } //end case 1

            //if user enters 2 do the following:
            case 2:
            { //start case 2

                //include counter for validation
                counter = counter + 1;

                //validation for when option 2 has been selected more than once
                if (counter > 2)
                { //start if

                    printf("\nYou have already encrypted your code, please do not select option 2 or 3\n");

                    //exit case 2 if
                    break;

                } //end if
                else //if not already selected
                { //start else

                    //call encryption function
                    encrypt_code(input_code, access_code, &correct_counter, &incorrect_counter, &incorrect_counter2);

                    //alter counter values for validation
                    counter3 = 2;
                    counter2 = 1;
                } //end else

                //exit case 2
                break;

            } //end case 2

            //if user inputs 3 do the following:
            case 3:
            { //start case 3

                //include counter for validation
                counter2 = counter2 + 1;

                if (counter2 > 2 || counter3 != 2 || incorrect_counter > 0) /*validation counters not allowing the user to decrypt code if not yet encrypted, entered the wrong code or have already decrypted the code.*/
                { //start if
                    printf("\nYou have already decrypted your code, have not encrypted the code yet or have entered the wrong code.\n");

                    //assign counter new value for validation
                    counter2 = 2;
                } //end if
                else if (counter2 == 2) //otherwise call decryption function
                { //start else if

                    //call decryption function
                    decrypt_code(input_code, access_code); 

                } //end else if

                //exit case 3
                break;

            } //end case 3

            //if user enters 4 do the following:
            case 4:
            { //start case 4

                //call counter function
                count_code(&correct_counter, &incorrect_counter2);

                //exit case 4
                break;

            } //end case 4

            //if user enters 5 do the following:
            case 5:
            { //start case 5

                //call exitprogram function
                exitprogram(&option);

                break;

            } //end case 5
        } //end switch
    } //end do
    while (option != 1); //end do..while if user entered option 5 and user entered Y/y

    return 0;
} //end main

void enter_code(int *input_code)
{ //start enter code function

    //declare i
    int i;

    printf("Please enter your 4 digit code (1 at a time):\n");

    //input for array
    for (i=0; i<SIZE; i++)
    { //start for

        scanf("%d/n", &*(input_code+i));

    } //end for

    //for loop to go through all elements of the array - validation
    for (i=0; i<SIZE; i++)
    { //start for 
        while (*(input_code+i) > 9 || *(input_code+i) < 0) //tell user to re-enter the correct digit until entered correctly
        { //start while

            printf("Please re-enter the invalid digit (Must be a single digit between 0-9): ");

            scanf("%d/n", &*(input_code+i));

        } //end while
    } //end for

    printf("\nYou have entered your 4 digits\n");

} //end enter code function

void encrypt_code(int *input_code, int *access_code, int *correct_counter, int *incorrect_counter, int *incorrect_counter2)
{ //start encryption function

    //declare variables
    int i, temp;
    int counter = 0;

    printf("\nEncryption enitiating...");

    //encryption algorithm
    temp = *(input_code+0);
    *(input_code+0) = *(input_code+2);
    *(input_code+2) = temp;
    temp = *(input_code+1);
    *(input_code+1) = *(input_code+3);
    *(input_code+3) = temp;

    //add 1 to each number, if number is equal to 10 reset to 0
    for(i=0; i<SIZE; i++)
    { //start for 

        *(input_code+i) = *(input_code+i)+ 1; //increment by 1

        //if equal to 10 reset to 0
        if(*(input_code+i) == 10)
        { //start if

            *(input_code+i) = 0;
            
        } //end if

    } //end for 

    //include counter to check if the entered code is equal to the access code
    for (i=0; i<SIZE; i++)
    { //start for 

        if (*(access_code+i) == *(input_code+i))
        { //start if 

            counter = counter + 1;

        } //end if

    } //end for

    //if all 4 integers are equal to the access code:
    if (counter == 4)
    { //start if

        printf("\nCorrect Code entered\n");

        //include counter for option 4 successful encryption
        *(correct_counter) = *(correct_counter) + 1;

    } //end if
    else //if the 4 integers are not equal to the access code:
    { //start else

        printf("\nWrong Code entered\n");

        //include counter for validation
        *(incorrect_counter) = *(incorrect_counter) + 1;

        //include counter for option 4 unsuccessful encryption
        *(incorrect_counter2) = *(incorrect_counter2) + 1;

    } //end else

} //end encryption function

void decrypt_code(int *input_code, int *access_code)
{ //start decryption function

    //declare variables
    int i, temp;
    int counter = 0;
    
    printf("Decryption enitiating...");

    //minus 1 from every value in array and if reaches -1 change value to 9
    for(i=0; i<SIZE; i++)
    { //start for

        //minus 1 from every value
        *(input_code+i) = *(input_code+i) - 1;

        //if value equals -1 change value to 9
        if(*(input_code+i) == -1)
        { //start if

            *(input_code+i) = 9;

        } //end if

    } //end for

    //decryption algorithm
    temp = *(input_code+0);
    *(input_code+0) = *(input_code+2);
    *(input_code+2) = temp;
    temp = *(input_code+1);
    *(input_code+1) = *(input_code+3);
    *(input_code+3) = temp;

    printf("\nDecrypted code: ");

    //display values of array after decryption
    for (i=0; i<SIZE; i++)
    { //start for 

        printf("%d ", *(input_code+i));

    } //end for

    printf("\n");

} //end decryption function

void count_code(int *correct_counter, int *incorrect_counter2)
{ //start display counter function

    printf("(i) Entered Successfully: %d\n", *(correct_counter));
    printf("(ii) Entered Incorrectly: %d\n", *(incorrect_counter2));

} //end display counter function

void exitprogram(int *option)
{ //start exitprogram function

    //declare variable
    char leave_program;

    //prompt the user to enter yes or no
    printf("\nWould you like to exit the program (Y/N)?\n");
    scanf("%c", &leave_program);

    //clear input buffer
    while ((getchar() != '\n'));

    if (leave_program == 'Y' || leave_program == 'y') //if entered y/Y exit program/make option equal to 1
    { //start if

        *option = 1;
        printf("\nYou selected 5 and then selected yes, you have exited the program.\n");

    } //end if
    else if (leave_program == 'N' || leave_program == 'n') //if user entered n/N do no leave program/make option equal to 0
    { //start else if

        *option = 0;
        printf("\nYou selected not to leave the program\n");

    } //end else if
    else //if user entered an invalid option
    { //start else

        *option = 0;
        printf("\nYou selected the wrong option, please select 5 again and enter Y for yes or N for no.\n");

    } //end else

} //end exitprogram function