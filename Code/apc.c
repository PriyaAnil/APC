#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlist.h>
#include <apc.h>

// Reverse string
void reverse_str(char *string)
{
	// calculate length
	int length = strlen(string), index = 0;

	char temp;

	// swapping
	while (index < length/2)
	{
		temp = string[index];

		string[index] = string[length - 1 - index];

		string[length - 1 - index] = temp;

		index++;
	}
}

// Slicing data
void slicing_data(char *string, dlist_t **head)
{
	int length = strlen(string);
	char buff[10];
	int index, value;

	// slicing the data by 9 digits
	while ((length - 1) >= 0)
	{
		// get 9 characters
		for (index = 0; index < 9 && (length - 1) >= 0; index++)
		
			buff[index] = string[--length];

		buff[index] = '\0';

		// reverse the string
		reverse_str(buff);

		// convert into value
		sscanf(buff, "%d", &value);

		// store into list
		dl_insert_first(head, value);
	}
}

// Swap list
void swap_list(dlist_t **ptr_1, dlist_t **ptr_2)
{
	dlist_t *temp = *ptr_1;

	*ptr_1 = *ptr_2;

	*ptr_2 = temp;
}

// Get carry
int get_carry(int *ptr_value)
{
	int carry;

	carry = *ptr_value / 1000000000;

	*ptr_value = *ptr_value % 1000000000;

	return carry;
}


/* APC Addition */
dlist_t *apc_addition(dlist_t *head_1, dlist_t *head_2)
{
	// head2 is null and head1 is not null then return head1
	if (head_2 == NULL && head_1 != NULL)

		return head_1;

	// head1 is null and head2 is not null then return head2
	if (head_1 == NULL && head_2 != NULL)

		return head_2;

	int carry = 0, value, count_1 = 0, count_2 = 0;

	dlist_t *ptr_1 = head_1, *ptr_2 = head_2, *head_3 = NULL;

	// to reach last node of head1
	while (ptr_1->link != NULL)
	{
		ptr_1 = ptr_1->link;

		count_1++;
	}

	// to reach last node of head2
	while (ptr_2->link != NULL)
	{
		ptr_2 = ptr_2->link;
	
		count_2++;
	}

	// any list having value 0 then return another list
	if (count_1 == 0 && head_1->data == 0)

		return head_2;

	else if (count_2 == 0 && head_2->data == 0)

		return head_1;

	// take lowest no. of node list into ptr2
	if (count_1 < count_2)
	{
		swap_list(&ptr_1, &ptr_2);
	}

	// sum node by node upto one list reaches null
	while (ptr_1 != NULL && ptr_2 != NULL)
	{
		// add both node data and carry
		value = carry + ptr_1->data + ptr_2->data;

		// get carry
		carry = get_carry(&value);

		// insert value to ans list
		dl_insert_first(&head_3, value);

		// move to prev nodes of list1 and list2
		ptr_1 = ptr_1->prev;
		ptr_2 = ptr_2->prev;
	}

	// copying remaining data upto null
	while (ptr_1 != NULL)
	{
		// add carry and node data
		value = carry + ptr_1->data;

		// get carry
		carry = get_carry(&value);

		// insert that value to ans list
		dl_insert_first(&head_3, value);

		// move to prev node
		ptr_1 = ptr_1->prev;
	}

	// at last carry is present insert that carry to ans list
	if (carry)

		dl_insert_first(&head_3, carry);

	// return ans list
	return head_3;
}


/* APC Subtraction */
dlist_t *apc_subtraction(dlist_t *head_1, dlist_t *head_2)
{
	int borrow = 1000000000, value, count_1 = 0, count_2 = 0, flag = 0;

	dlist_t *ptr_1 = head_1, *ptr_2 = head_2, *head_3 = NULL;

	// to reach last node of list1
	while (ptr_1->link != NULL)
	{
		ptr_1 = ptr_1->link;

		count_1++;
	}

	// to reach last node of list2
	while (ptr_2->link != NULL)
	{
		ptr_2 = ptr_2->link;

		count_2++;
	}

	// no. of nodes of list1 and 2 are equal 
	if(count_1 == count_2)
	{
		dlist_t *p_1 = head_1, *p_2 = head_2;

		// both list data are equal
		while (p_1 != NULL && p_1->data == p_2->data)
		{
			p_1 = p_1->link;
			p_2 = p_2->link;			
		}		

		// the ptr reaches null then return ans as zero
		if (p_1 == NULL)
		{
			dl_insert_first(&head_3, 0);
			
			return head_3;
		}

		// which list data is maximun take that into ptr1 and set the flag
		else if (p_2->data > p_1->data)
		{
			flag = 1;
			swap_list(&ptr_1, &ptr_2);
		}
	}

	// count2 having max no. of nodes then swap ptr1 and ptr2
	if (count_1 < count_2)
	{
		flag = 1;
		swap_list(&ptr_1, &ptr_2);
	}

	// do the subtraction upto any one ptr reaches null 
	while (ptr_1 != NULL && ptr_2 != NULL)
	{
		// ptr1 data is lessthan ptr2 data then borrow
		if (ptr_1->data < ptr_2->data)
		{
			// add the borrow to ptr1 data
			ptr_1->data = ptr_1->data + borrow;

			// subtract 1 from the prev data
			if (ptr_1->prev != NULL)
			{
				ptr_1->prev->data = ptr_1->prev->data - 1;

				flag = 1;
			}
		}

		// subtracted result
		value = ptr_1->data - ptr_2->data;

		// insert result to res list
		dl_insert_first(&head_3, value);

		// move ptr1 and ptr2 to prev nodes
		ptr_1 = ptr_1->prev;
		ptr_2 = ptr_2->prev;
	}

	// copying remaining data upto ptr1 prev reaches null
	while (ptr_1 != NULL)
	{
		dl_insert_first(&head_3, ptr_1->data);

		ptr_1 = ptr_1->prev;
	}

	while (head_3 != NULL && head_3->data == 0)
	{
		ptr_1 = head_3;
		head_3 = head_3->link;
		free(ptr_1);
	}
	if (flag)

		head_3->data = head_3->data * -1;

	// return result list
	return head_3;
}


// Add zeros
void add_zeros(dlist_t **head, int limit)
{
	dlist_t *n_head = NULL, *pans = NULL;
	int index;

	// multiply that many times
	for (index = 0; index < limit; index++)
	{
		n_head = apc_addition(*head, n_head);
	}

	// update the head
	*head = n_head;
}

// Calculate the limits
void calculate_limits(int value, int *limit_1, int *limit_2)
{
	// last 5 digits
	*limit_1 = value % 100000;

	// remaining digits
	*limit_2 = value / 100000;
}


/* APC Multiplication*/
dlist_t *apc_multiplication(dlist_t *head_1, dlist_t *head_2)
{
	dlist_t *result_1 = NULL, *result_2 = NULL, *result_t = NULL, *final_ans = NULL;

	dlist_t *ptr_1 = head_1, *ptr_2 = head_2, *pans = NULL;

	int count_1 = 0, count_2 = 0, count = 0, limit_1 = 0, limit_2 = 0, flag = 0, index, jdx;

	// to reach last nod of list1
	while (ptr_1->link != NULL)
	{
		ptr_1 = ptr_1->link;
		count_1++;
	}

	// to reach last nod of list2
	while (ptr_2->link != NULL)
	{
		ptr_2 = ptr_2->link;
		count_2++;
	}

	// count1 is lessthan the count2 then swap ptrs
	if (count_1 < count_2)
	{
		swap_list(&ptr_1, &ptr_2);

		ptr_1 = head_2;
	}

	// any one of the data is zero then return zero as result
	if (count_1 == 0 && head_1->data == 0)
	{
		dl_insert_first(&final_ans, 0);

		return final_ans;
	}

	else if (count_2 == 0 && head_2->data == 0)
	{
		dl_insert_first(&final_ans, 0);

		return final_ans;
	}

	// multiply upto ptr2 reaches null
	while (ptr_2 != NULL)
	{
		result_1 = NULL, result_2 = NULL;

		// calculate limits
		calculate_limits(ptr_2->data, &limit_1, &limit_2);	

		// multiply by limit1
		for (index = 0; index < limit_1; index++)
		{
			result_1 = apc_addition(ptr_1, result_1);
		}

		// multiply by limit2
		for (index = 0; index < limit_2; index++)
		{
			result_2 = apc_addition(ptr_1, result_2);	
		}

		// add zeros to ans2
		if (result_2 != NULL)

			add_zeros(&result_2, 100000);

		// add both ans found by limit1 and limit2
		result_t = apc_addition(result_1, result_2);

		// flag is 1
		if (flag)
		{
			count++;

			// insert 0 value upto count
			for (jdx = 0; jdx < count; jdx++)

				dl_insert_last(&result_t, 0);
		}

		else

			flag = 1;

		// add prev and new multiplication values
		final_ans = apc_addition(result_t, final_ans);

		// move ptr to prev node
		ptr_2 = ptr_2->prev;
	}

	// return multiplication res
	return final_ans;
}

int get_quotient(dlist_t **head4, dlist_t *head2)
{
	int count = 0;

	// Repeatative subtraction
	while ((*head4)->data >= head2->data)
	{
		*head4 = apc_subtraction(*head4, head2);
		count++;
	}

	// Return the quotient
	return count;
}
dlist_t *apc_division(dlist_t *head1, dlist_t *head2)
{
	dlist_t *ptr1 = head1, *ptr2 = head2, *head3 = NULL, *quotient = NULL, *head4 = NULL;

	int count1 = 0, count2 = 0, flag = 0, index, jdx;

	// to reach last nod of list1
	while (ptr1->link != NULL)
	{
		ptr1 = ptr1->link;
		count1++;
		
	}

	// Point ptr1 back to the head
	ptr1 = head1;

	// to reach last nod of list2
	while (ptr2->link != NULL)
	{
		ptr2 = ptr2->link;
		count2++;
	}

	// Point ptr2 back to the head
	ptr2 = head2;

	// If divident is smaller than divisor
	if (count1 < count2)
	{
		// Insert 0
		dl_insert_first(&head3, 0);
		dl_print_list(head3);		
		return head3;
	}

	// If both the numbers are 0
	else if (count1 == 0 && count2 == 0 && head1->data == 0 && head2->data == 0)
	{
		printf("Error\n");
		return NULL;
	}

	// If the divisor is 0
	else if (count2 == 0 && head2->data == 0)
	{
		printf("Error\n");
		return NULL;
	}

	// If divident is smaller than divisor
	else if (count1 == count2 && head1->data < head2->data)
	{
		dl_insert_first(&head3, 0);
		dl_print_list(head3);		
		
		return head3;
	}

	else
	{	
		int count;
		dlist_t *ptr3 = head4, *quotient = NULL, *ptr4 = head1;

		while (1)
		{
			// If list2 has more than one node
			if (count2 > 0)
			{
				// Copy the count2 number of nodes from list 1
				for (index = 0; index <= count2; count2++)
				{
					dl_insert_last(&head4, ptr1->data);
					dl_print_list(head4);
					ptr1 = ptr1->link;
				}
			}

			// If only one node is present in each list
			else if (count1 == 0 && count2 == 0)
			{
				dl_insert_last(&head4, ptr4->data);

				// Get the quotient
				count = get_quotient(&head4, head2);
				dl_insert_last(&quotient, count);

				if (head4->data == 0 || head4->data < head2->data)
				{
					dl_print_list(quotient);
					break;
				}

			}	
		}
	}

}
