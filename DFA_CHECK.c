// #include <iostream>
// #include <string>
// #include <stdlib.h>
// #include <new>
// using namespace std;
 
// int main() {
//     string *states, *final, *trap, **transition,input, tmp;
//     char *alf, temp;
//     int nos, nots, nofs, noa, i, j, current, flag;
//     cout << "Enter the number of states, number of final states and"
//          << " the number of trap states.\n";
//     cin >> nos >> nofs >> nots;
//     cout << "Enter the number of symbols in the alphabet:\n";
//     cin >> noa;
 
//     states = new string[nos];
//     final = new string[nofs];
//     trap = new string[nots];
//     alf = new char[noa+1];
 
//     cout << "\nEnter the states (initial state first)\n";
//     for (i = 0; i < nos; i++)
//         cin >> states[i];
 
//     cout << "Enter the final states:\n";
//     for (i = 0; i < nofs; i++)
//         cin >> final[i];
 
//     cout << "Enter the trap states:\n";
//     for (i = 0; i < nots; i++)
//         cin >> trap[i];
 
//     cout << "Enter the alphabet for the DFA:\n";
//     for (i = 0; i < noa; i++)
//         cin >> alf[i];
 
//     transition = new string *[nos];
//     for (i = 0; i < nos; i++)
//         transition[i] = new string[noa];
 
//     cout << "Enter the transition for the given states:";
//     for (i = 0; i < nos; i++) {
//         cout << "\nFor state " << states[i] << endl;
//         for (j = 0; j < noa; j++) {
//             cout << "On input " << alf[j] << " to state : ";
//             cin >> transition[i][j];
//         }
//     }
//     cout << "The transition table you entered is :\n";
//     cout << "state\t";
//     for (i = 0; i < noa; i++)
//         cout << alf[i] << "\t";
//     for (i = 0; i < nos; i++) {
//         cout << endl << states[i] << "\t";
//         for (j = 0; j < noa; j++)
//             cout << transition[i][j] << "\t";
//     }
 
//     while (true) {
//         current = 0, flag = 0;// current will keep track of the current state
 
//         cout << "\nEnter the input string( enter exit to terminate) : ";
// 	cin >> input;
// 	if (input.compare("exit") == 0)
//             exit(0);
// 	for (i = 0; i < input.length(); i++) {

//             temp = input.at(i);
// 	    for (j = 0; j < noa; j++) {
// 	        if (alf[j] == temp) {
// 	            break;
// 	        }
// 	    }

//             tmp = transition[current][j];
// 	    for (int k = 0; k < nos; k++)
// 	        if (states[k].compare(tmp) == 0) {
// 	             current = k;
// 	             break;
// 	         }
// 	    for (j = 0; j < nots; j++)
// 	        if (states[current].compare(trap[j]) == 0) {
// 	            cout << "The input string has been rejected";
//                     flag = 1;
// 	            break;
// 	        }
 
//             if (flag == 1)
//                 break;
// 	}
 
// 	    if (flag == 1)
//                 continue;
 
// 	    for (i = 0; i < nofs; i++)
// 	        if (states[current].compare(final[i]) == 0) {
// 	            cout << "The input has been accepted by the DFA";
//                     flag = 1;
//                     break;
//                 }
 
//             if (flag == 1)
//                 cout << "The input has been rejected by the DFA";
//     }
//     return 0;
// }
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char **states, **final, **trap, **transition, *input, *tmp;
    char *alf, temp;
    int nos, nots, nofs, noa, i, j, current, flag;
    printf("Enter the number of states, number of final states and the number of trap states.\n");
    scanf("%d %d %d", &nos, &nofs, &nots);
    printf("Enter the number of symbols in the alphabet:\n");
    scanf("%d", &noa);

    states = (char**)malloc(nos * sizeof(char*));
    final = (char**)malloc(nofs * sizeof(char*));
    trap = (char**)malloc(nots * sizeof(char*));
    alf = (char*)malloc((noa+1) * sizeof(char));
    transition = (char**)malloc(nos * sizeof(char*));
    input = (char*)malloc(100 * sizeof(char));
    tmp = (char*)malloc(100 * sizeof(char));

    printf("\nEnter the states (initial state first)\n");
    for (i = 0; i < nos; i++) {
        states[i] = (char*)malloc(100 * sizeof(char));
        scanf("%s", states[i]);
    }

    printf("Enter the final states:\n");
    for (i = 0; i < nofs; i++) {
        final[i] = (char*)malloc(100 * sizeof(char));
        scanf("%s", final[i]);
    }

    printf("Enter the trap states:\n");
    for (i = 0; i < nots; i++) {
        trap[i] = (char*)malloc(100 * sizeof(char));
        scanf("%s", trap[i]);
    }

    printf("Enter the alphabet for the DFA:\n");
    for (i = 0; i < noa; i++)
        scanf(" %c", &alf[i]);
    alf[noa] = '\0';
    printf("Enter the transition for the given states: \n");
    for (i = 0; i < nos; i++) {
        transition[i] = (char**)malloc(noa * sizeof(char*));
        printf("For state %s\n",states[i]);
        for (j = 0; j < noa; j++) {
            transition[i][j] = (char*)malloc(100 * sizeof(char));
            printf("On input %c to state: ", alf[j]);
            scanf("%s", transition[i][j]);
        }
    }

    printf("The transition table you entered is:\n");
    printf("state\t");
    for (i = 0; i < noa; i++)
        printf("%c\t", alf[i]);
    for (i = 0; i < nos; i++) {
        printf("\n%s\t", states[i]);
        for (j = 0; j < noa; j++)
            printf("%s\t", transition[i][j]);
    }

    while (1) {
        current = 0, flag = 0;

        printf("\nEnter the input string (enter exit to terminate): ");
	    scanf("%s", input);

	    if (strcmp(input, "exit") == 0)
            exit(0);

	    for (i = 0; i < strlen(input); i++) {
            temp = input[i];
	        for (j = 0; j < noa; j++) {
	            if (alf[j] == temp) {
	                break;
	            }
	        }

            strcpy(tmp, transition[current][j]);
	        for (int k = 0; k < nos; k++) {
	            if (strcmp(states[k], tmp) == 0) {
	                 current = k;
	                 break;
	             }
	        }

	        for (j = 0; j < nots; j++) {
	            if (strcmp(states[current], trap[j]) == 0) {
	                printf("The input string has been rejected");
                    flag = 1;
	                break;
	            }
	        }

            if (flag == 1)
                break;
	    }

	    if (flag == 1)
            continue;

	    for (i = 0; i < nofs; i++) {
	        if (strcmp(states[current], final[i]) == 0) {
	            printf("The input has been accepted by the DFA");
                flag = 1;
                break;
            }
        }

        if (flag == 0)
            printf("The input has been rejected by the DFA");
    }

    free(input);
    free(tmp);
    free(alf);
    for (i = 0; i < nos; i++) {
        free(states[i]);
        for (j = 0; j < noa; j++)
            free(transition[i][j]);
        free(transition[i]);
    }
    for (i = 0;i< nofs; i++)
        free(final[i]);
    for (i = 0; i < nots; i++)
        free(trap[i]);
    free(states);
    free(final);
    free(trap);
    free(transition);

    return 0;
}