#include "lib/libft/libft.h"

int	ft_strchrs_ind(char *haystack, char *needles)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	while (haystack[i])
	{
    	tmp = i;
        j = 0;
		while (haystack[i] == needles[j])
		{
			if (j + 1 == ft_strlen(needles))
				return (tmp);
            else
            {
                i = tmp;
                break ;
            }
            i++;
			j++;
		}
		i++;
	}
	return (0);
}

#include <stdio.h>

int main()
{
    int i;

    i = ft_strchrs_ind("merhaba dunya ben misra", "dunya");
    printf("SONUC: %i\n", i);
}

// merhaba dünya ben && mısra