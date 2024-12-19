#include "../libft/headers/libft.h"
#include <errno.h>
#include <string.h>

int main(void)
{
ft_putstr_fd(strerror(ENAMETOOLONG), 2);
return(0);
}