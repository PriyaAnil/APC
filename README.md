# APC
Arbitrary-precision arithmetic, also called bignum arithmetic, multiple precision arithmetic, or sometimes infinite-precision arithmetic, indicates that calculations are performed on numbers whose digits of precision are limited only by the available memory of the host system. This contrasts with the faster fixed precision arithmetic found in most arithmetic logic unit (ALU) hardware, which typically offers between 8 and 64 bits of precision.

ALGORITHM

Start
Get the inputs as a string
Slice the string into a string of 9 characters each, covert it string into integer and insert into a linked list
Addition:
Get the two lists 
Move to the last node of each
Add each node
Extract the carry from the result 
Add to the previous node
Store the result in a new list

Subtraction:
Get the two lists
Count the number of nodes
If list 2 has more number of nodes the swap the list
Else compare the data of each node
If list 2 data is greater then swap  the list
Move to the last node of each
Subtract each node along with the borrow if needed and subtract 1 from the previous node of list 1
Store the result in a list

Multiplication:
Get the two lists
Count the number of nodes
If list 2 has more number of nodes then swap the list
Move to the last node of list 2
Use each node as a limit to add list 1 data repeatedly
Store the result in a list

Division:
Get the two lists
Count the number of nodes
If list 2 has more number of nodes return 0
Else compare the data and if list 2 data is greater return 0
Get as many nodes as in list 2 from list 1, compare the datas
If data of list 1 is less get the next node from list 1 
Subtract list 1 with list 2 till list one data is less than list 2 data
Store the result in a list add the next node of list 1 to result and subtract with list 2 again
Count the number of times the subtraction is performed 
Insert the count in a new list which is the quotient i.ee the final answer  


Note: Division not implemented completely

