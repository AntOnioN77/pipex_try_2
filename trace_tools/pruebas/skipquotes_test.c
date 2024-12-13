void skipquotes(char **str)
{
	char *tmp;


	if(**str == 39)
	{
		tmp = *str;
		while(*tmp != '\0')
		{
			tmp++;
			if(*tmp == 39)
			{
				*str= tmp + 1;
				return ;
			}
			if(*tmp == '"')
			{
				*str= tmp + 1;
				return ;
			}
		}
	}
}


#include <stdio.h>
int main(void)
{
    char test1[] = "'Hello' World";
    char test2[] = "\"Hello\" World";
    char test3[] = "No quotes here";
    char test4[] = "'Single quote";
    char *ptr1 = test1;
    char *ptr2 = test2;
    char *ptr3 = test3;
    char *ptr4 = test4;

    skipquotes(&ptr1);
    printf("Test 1: %s\n", ptr1); // Expected output: " World"

    skipquotes(&ptr2);
    printf("Test 2: %s\n", ptr2); // Expected output: " World"

    skipquotes(&ptr3);
    printf("Test 3: %s\n", ptr3); // Expected output: "No quotes here"

    skipquotes(&ptr4);
    printf("Test 4: %s\n", ptr4); // Expected output: "Single quote"

    return 0;
}