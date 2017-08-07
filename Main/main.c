#include <stdio.h>
#include <apc.h>
#include <dlist.h>

int main()
{
	int option;
	char arr[200], ch;
	
	do 
	{
		// Read the option
		printf("1. Addition\n2. Subtraction\n3. Multiplication\n4. Division\nEnter the option: ");
		scanf("%d", &option);

		dlist_t *head3 = NULL;
		dlist_t *head4 = NULL, *ptr;

		// Read 1st number
		printf("Enter the number 1: ");
		scanf("%s", arr);

		// Slice the number
		slicing_data(arr, &head3);

		// Read the 2nd data
		printf("Enter the number 2: ");
		scanf("%s", arr);

		// Slice the number
		slicing_data(arr, &head4);

		switch (option)
		{

			case 1:

				// Addition
				ptr = apc_addition(head3, head4);
				dl_print_list(ptr);
				break;

			case 2:

				// Subtraction
				ptr = apc_subtraction(head3, head4);
				dl_print_list(ptr);
				break;
			
			case 3:

				// Multiplication
				ptr = apc_multiplication(head3, head4);
				dl_print_list(ptr);
				break;
			
			case 4:

				// Division
				apc_division(head3, head4);
				//printf("ptr = %d\n", ptr->data);	
				break;
		}
		printf("Do you want to continue: ");
		scanf("\n%c", &ch);
	}while (ch == 'y');
	return 0;
}
