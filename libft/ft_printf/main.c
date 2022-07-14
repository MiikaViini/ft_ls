/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:10:04 by mviinika          #+#    #+#             */
/*   Updated: 2022/05/11 13:47:28 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"
#include <limits.h>

int main()
{
	long long joo = 922337203685477580;
	int i = 42;
	int a = 0;
	static unsigned int uin = 238;
	static char c = 'G';
	static char *str = "Hello World";

	unsigned long long juuuuuuu = 18446744073709551615;

		unsigned int  uu = INT_MAX;
		
		long intmax = LONG_MAX;

		unsigned long  guu = ULONG_MAX;
	
	/* Binary tests*/

	ft_printf("MY :[% .1Lf]\n",  -999.999999999);
	printf("OG :[% .1Lf]\n",  -999.999999999);
	return (0);
	ft_printf("MY :[%hb]\n" ,SHRT_MIN);
	printf("OG :[%010.0b]\n", 0);
	ft_printf("MY :[%hb]\n" ,SHRT_MAX);

	ft_printf("MY :[%b]\n" , INT_MIN);

	ft_printf("MY :[%b]\n",INT_MAX);

	ft_printf("MY :[%lb]\n" ,LONG_MIN);

	ft_printf("MY :[%lb]\n" ,LONG_MAX);

	ft_printf("MY :[%llb]\n" ,LLONG_MIN);

	ft_printf("MY :[%llb]\n" ,LLONG_MAX);

	ft_printf("MY :[%b]\n", -16);

	ft_printf("MY :[%b]\n" , 16);

	ft_printf("MY :[%b]\n", -60600);

	ft_printf("MY :[%b]\n" , 60600);

	ft_printf("MY :[%hb]\n", -123);

	ft_printf("MY :[%+hb]\n" , 123);

	ft_printf("MY :[%b]\n", -55645646);

	ft_printf("MY :[%b]\n" , 55645646);

	ft_printf("MY :[%b]\n", 0);

	ft_printf("MY :[%#-+*b]\n" ,10, -0);

	ft_printf("MY :[%*b]\n",15 , -1);

	ft_printf("MY :[%10hb]\n" ,SHRT_MIN);
	//printf("OG :[%010.0b]\n", 0);
	ft_printf("MY :[%10hb]\n" ,SHRT_MAX);

	ft_printf("MY :[%*b]\n" ,90, INT_MIN);

	ft_printf("MY :[%*b]\n",90 ,INT_MAX);

	ft_printf("MY :[%-15lb]\n" ,LONG_MIN);

	ft_printf("MY :[%-15lb]\n" ,LONG_MAX);

	ft_printf("MY :[%0#+-*b]\n" ,90,LLONG_MIN);

	ft_printf("MY :[%0#+-*b]\n",90 ,LLONG_MAX);

	ft_printf("MY :[%b]\n", -16);

	ft_printf("MY :[%b]\n" , 16);

	ft_printf("MY :[%b]\n", -60600);

	ft_printf("MY :[%b]\n" , 60600);

	ft_printf("MY :[%hb]\n", -123);

	ft_printf("MY :[%+hb]\n" , 123);

	ft_printf("MY :[%b]\n", -55645646);

	ft_printf("MY :[%b]\n" , 55645646);

	ft_printf("MY :[%b]\n", 0);

	/* floats and doubles */
	ft_printf("MY :[%0#.1f]\n", -3.141593);
	printf("OG :[%0#.1f]\n",-3.141593);

	ft_printf("MY :[%0#10.1f]\n", -3.141593);
	printf("OG :[%0#10.1f]\n", -3.141593);



	ft_printf("MY :[%010f]\n", 1.000000);
	printf("OG :[%010f]\n",1.000000);

	ft_printf("MY :[%0#10.1f]\n", -3.141593);
	printf("OG :[%0#10.1f]\n", -3.141593);


	ft_printf("MY :[%#10.1f]\n", 3.141593);
	printf("OG :[%#10.1f]\n",3.141593);

	ft_printf("MY :[%#10.1f]\n", -3.141593);
	printf("OG :[%#10.1f]\n", -3.141593);



	ft_printf("MY :[%015.1lf]\n", -958.125);
	printf("OG :[%015.1lf]\n",-958.125);

	ft_printf("MY :[%015.1lf]\n", 958.125);
	printf("OG :[%015.1lf]\n",958.125);

	ft_printf("MY :[%#0lf]\n", -958.125);
	printf("OG :[%#0lf]\n",-958.125);


	ft_printf("MY :[%#10.f]\n",   3.141593);
	printf("OG :[%#10.f]\n",   3.141593);

	ft_printf("MY :[%#.f]\n",   -3.141593);
	printf("OG :[%#.f]\n",   -3.141593);

	ft_printf("MY :[%#-10.f]\n",  -6.393847);
	printf("OG :[%#-10.f]\n",  -6.393847);


	ft_printf("MY :[% #10.0lf]\n", -6.393847);
	printf("OG :[% #10.0lf]\n", -6.393847);

	ft_printf("MY :[% #.f]\n",   3.141593);
	printf("OG :[% #.f]\n",   3.141593);

	ft_printf("MY :[% #.f]\n",   -3.141593);
	printf("OG :[% #.f]\n",   -3.141593);

	ft_printf("MY :[% -10.5f]\n",  -6.393847);
	printf("OG :[% -10.5f]\n",  -6.393847);

	ft_printf("MY :[% -10.5f]\n",  6.393847);
	printf("OG :[% -10.5f]\n",  6.393847);



	ft_printf("MY :[% 10f]\n",  6.393847);
	printf("OG :[% 10f]\n",  6.393847);


	ft_printf("MY :%10f\n",  6.393847);
	printf("OG :%10f\n",  6.393847);

	ft_printf("MY :[%10f]\n",  -6.393847);
	printf("OG :[%10f]\n",  -6.393847);

	ft_printf("MY :[% f]\n",  -999.99);
	printf("OG :[% 10f]\n",  -999.99);

	ft_printf("MY :[%10f]\n", -1.000000);
	printf("OG :[%10f]\n",-1.000000);

	ft_printf("MY :[%010.0lf]\n", -6.393847);
	printf("OG :[%010.0lf]\n", -6.393847);

	ft_printf("MY :[%.f]\n", 1.5);
	printf("OG :[%.f]\n", 1.5);

	ft_printf("MY :[%.f]\n", 9.50000);
	printf("OG :[%.f]\n", 9.50000);

	ft_printf("MY :[%.15f]\n", 1.00002);
	printf("OG :[%.15f]\n", 1.00002);


	ft_printf("MY :[%.15f]\n", 1.56423335);
	printf("OG :[%.15f]\n", 1.56423335);


	ft_printf("MY :[%.15f]\n", 1.5643339);
	printf("OG :[%.15f]\n", 1.5643339);

	ft_printf("MY :[%0#10.1f]\n", -958.125000);
	printf("OG :[%0#10.1f]\n", -958.125000);
	
	ft_printf("MY :[%f]\n", 3.1);
	printf("OG :[%f]\n", 3.1);

	ft_printf("MY :[%10f]\n", 0.876509);
	printf("OG :[%10f]\n", 0.876509);

	ft_printf("MY :[%f]\n", -958.125000);
	printf("OG :[%f]\n", -958.125000);

	ft_printf("MY :[%f]\n", -0.100000);
	printf("OG :[%f]\n", -0.100000);

	ft_printf("MY :[%f]\n", -1.100000);
	printf("OG :[%f]\n", -1.100000);

	ft_printf("MY :[%.f]\n", -199.9);
	printf("OG :[%.f]\n", -199.9);

	ft_printf("MY :[%10.1f]\n", -199.9);
	printf("OG :[%10.1f]\n", -199.9);

	ft_printf("MY :[%f]\n", 0.100000);
	printf("OG :[%f]\n", 0.100000);

	ft_printf("MY :[%10f]\n", 0.876509);
	printf("OG :[%10f]\n", 0.876509);

	ft_printf("MY :[%Lf]\n", -958.125000l);
	printf("OG :[%Lf]\n", -958.125000l);

	ft_printf("MY :[%Lf]\n", -0.100000l);
	printf("OG :[%Lf]\n", -0.100000l);

	ft_printf("MY :[%Lf]\n", -1.100000l);
	printf("OG :[%Lf]\n", -1.100000l);

	ft_printf("MY :[%.Lf]\n", -199.9l);
	printf("OG :[%.Lf]\n", -199.9l);

	ft_printf("MY :[%10.1Lf]\n", -199.9l);
	printf("OG :[%10.1Lf]\n", -199.9l);

	ft_printf("MY :[%Lf]\n", 0.100000l);
	printf("OG :[%Lf]\n", 0.100000l);

	ft_printf("MY :[%f]\n", 1.100000);
	printf("OG :[%f]\n", 1.100000);

	ft_printf("MY :[%.f]\n", -99.500000);
	printf("OG :[%.f]\n", -99.500000);

	ft_printf("MY :[%10.1f]\n", 199.9);
	printf("OG :[%10.1f]\n", 199.9);

	ft_printf("MY :[%#.f]\n", 9.400000);
	printf("OG :[%#.f]\n", 9.400000);

	ft_printf("MY :[%.f]\n", 2.500000);
	printf("OG :[%.f]\n", 2.500000);

	ft_printf("MY :[%.1f]\n", 1.500000);
	printf("OG :[%.1f]\n", 1.500000);

	ft_printf("MY :[%.2f]\n", 958.125000);
	printf("OG :[%.2f]\n", 958.125000);

	ft_printf("MY :[%f]\n", 99.500000);
	printf("OG :[%f]\n", 99.500000);

	ft_printf("MY :[%f]\n", -0.0);
	printf("OG :[%f]\n", -0.0);


	/*integers */


	ft_printf("MY :[%010.0d]\n", 0);
	printf("OG :[%010.0d]\n", 0);

	ft_printf("MY :[%010.4d]\n", 111);
	printf("OG :[%010.4d]\n", 111);

	ft_printf("MY :[%+7d]\n", 0);
	printf("OG :[%+7d]\n", 0);

	ft_printf("MY :[%+*d]\n", -15,0);
	printf("OG :[%+*d]\n", -15,0);

	ft_printf("MY :[%hhd]\n", -2147483648);
	printf("OG :[%hhd]\n", -2147483648);

	ft_printf("MY :[%010hhd]\n", -2147483648);
	printf("OG :[%010hhd]\n", -2147483648);

	ft_printf("MY :[%#015.0x]\n", -2147483648);
	printf("OG :[%#015.0x]\n", -2147483648);

	ft_printf("MY :[%#10.0hx]\n", 1);
	printf("OG :[%#10.0hx]\n", 1);

	ft_printf("MY :[%#010.0hx]\n", 1);
	printf("OG :[%#010.0hx]\n", 1);

	ft_printf("MY :[%010.0hhi]\n", 0);
	printf("OG :[%010.0hhi]\n", 0);

	ft_printf("MY :[%010.0hhi]\n", -2147483648);
	printf("OG :[%010.0hhi]\n", -2147483648);

	ft_printf("MY :[%010.0hhi]\n", 0);
	printf("OG :[%010.0hhi]\n", 0);

	ft_printf("MY :[%5d]\n", -12);
	printf("OG :[%5d]\n", -12);

	ft_printf("MY :[%-5d]\n", -12);
	printf("OG :[%-5d]\n", -12);

	ft_printf("MY :[%-05d]\n", -12);
	printf("OG :[%-05d]\n", -12);

	ft_printf("MY :[%+10.5d]\n", -12);
	printf("OG :[%+10.5d]\n", -12);

	ft_printf("MY :[%+10.5d]\n", -12);
	printf("OG :[%+10.5d]\n", -12);

	ft_printf("MY :[%+10.5d]\n", 4242);
	printf("OG :[%+10.5d]\n", 4242);

	ft_printf("MY :MY [%.5d]\n", 42);
	printf("OG :OG [%.5d]\n", 42);

	ft_printf("MY :[%05d]\n", 42);
	printf("OG :[%05d]\n", 42);

	ft_printf("MY :[%5d]\n", -42);
	printf("OG :[%5d]\n", -42);

	ft_printf("MY :MY [%05d]\n", 42);
	printf("OG :OG [%05d]\n", 42);

	ft_printf("MY :[%03.2d]\n", -1);
	printf("OG :[%03.2d]\n", -1);

	ft_printf("MY :[%#10.4d]\n", 0);
		printf("OG :[%#10.4d]\n", 0);

		 ft_printf("MY :[%#10.2d]\n", 0);
		printf("OG :[%#10.2d]\n", 0);


		ft_printf("MY :[%#3.3d]\n", 111);
		printf("OG :[%#3.3d]\n", 111);


		ft_printf("MY :[%#2.3d]\n", 111);
		printf("OG :[%#2.3d]\n", 111);

		ft_printf("MY :[%#.3d]\n", 1111);
		printf("OG :[%#.3d]\n", 1111);

		ft_printf("MY :[%#d]\n", 1111);
		printf("OG :[%#d]\n", 1111);

		ft_printf("MY :[%-+#d]\n", 1111);
		printf("OG :[%-+#d]\n", 1111);

		ft_printf("MY :[%#3.3d]\n", 111);
		printf("OG :[%#3.3d]\n", 111);


		ft_printf("MY :[%#*.*d]\n",12,12, 111);
		printf("OG :[%#*.*d]\n",12,12, 111);

		ft_printf("MY :[%#.*d]\n",12, 1111);
		printf("OG :[%#.*d]\n",12, 1111);

		ft_printf("MY :[%0#*d]\n",-12, 1111);
		printf("OG :[%0#*d]\n",-12, 1111);

		ft_printf("MY :[%#d]\n", 1111);
		printf("OG :[%#d]\n", 1111);

		ft_printf("MY :[%-+#d]\n", 1111);
		printf("OG :[%-+#d]\n", 1111);

	ft_printf("MY :[%#ho]\n",  2147483648);
	printf("OG :[%#ho]\n",  2147483648);

	ft_printf("MY :[%#010.0hx]\n",  2147483648);
	printf("OG :[%#010.0hx]\n",  2147483648);

	 

	 ft_printf("MY :[%20s]\n", str);
	 printf("OG :[%20s]\n", str);
	 ft_printf("MY :[%s]\n", str);
	 printf("OG :[%s]\n", str);
	 ft_printf("MY :[% 10.10u]\n", 10);
	 printf("OG :[% 10.10u]\n", 10);
	 ft_printf("MY :[%+10.10u]\n", 10);
	 printf("OG :[%+10.10u]\n", 10);
	  ft_printf("MY :[%- 15.10u]\n", 10);
	 printf("OG :[%- 15.10u]\n", 10);

	 ft_printf("MY :[%#0 15u]\n", 10);
	 printf("OG :[%#0 15u]\n", 10);

	 ft_printf("MY :[%#10.10u]\n", -1231231);
	 printf("OG :[%#10.10u]\n", -1231231);
	 ft_printf("MY :[%010.10d]\n", 10);
	// ft_printf("MY :[%20c]\n", 60);

	/*hexa*/
	
	 ft_printf("MY :[%#-10.5x]\n", 60);
	 printf("OG :[%#-10.5x]\n", 60);

	 ft_printf("MY :[%#12.15x]\n", 60);
	 printf("OG :[%#12.15x]\n", 60);

	 ft_printf("MY :[%#10.11x]\n", 60);
	 printf("OG :[%#10.11x]\n", 60);

	 ft_printf("MY :[%#10.5x]\n", 60);
	 printf("OG :[%#10.5x]\n", 60);

	 ft_printf("MY :[%#-15.12x]\n", 150);
	 printf("OG :[%#-15.12x]\n", 150);

	 ft_printf("MY :[%#-x]\n", 60);
	 printf("OG :[%#-x]\n", 60);
	//  ft_printf("MY :[%c]\n", '\0');
	//  printf("OG :[%10c]\n", 60);
	 ft_printf("MY :[%10c]\n", 70);
	 printf("OG :[%10c]\n", 70);
	 ft_printf("MY :[%20.s]\n", str);

	/* percent*/

	 ft_printf("MY :[%%]\n");
	 printf("OG :[%%]\n");

	 ft_printf("MY :[%050%]\n");
	 printf("OG :[%050%]\n");

	 ft_printf("MY :[%-50%]\n");
	 printf("OG :[%-50%]\n");

	 ft_printf("MY :[%     %]\n");
	 printf("OG :[%     %]\n");

	 ft_printf("MY :[%#%]\n");
	 printf("OG :[%#%]\n");

	 ft_printf("MY :[%*s]\n", -32, "abc");
		printf("OG :[%*s]\n", -32, "abc");

	
	 ft_printf("MY :[%2.3o]\n", 0);
		printf("OG :[%2.3o]\n", 0);


	 ft_printf("MY :[%2.2o]\n", 0);
		printf("OG :[%2.2o]\n", 0);

	 ft_printf("MY :[%2.1o]\n", 0);
		printf("OG :[%2.1o]\n", 0);

	 ft_printf("MY :[%#2.1o]\n", 0);
		printf("OG :[%#2.1o]\n", 0);

	 ft_printf("MY :[%-#2.1x]\n", 0);
		printf("OG :[%-#2.1x]\n", 0);

	 ft_printf("MY :[%2.2x]\n", 0);
		printf("OG :[%2.2x]\n", 0);

	 ft_printf("MY :[%2.1o]\n", 0);
		printf("OG :[%2.1o]\n", 0);

	 ft_printf("MY :[%#2.1o]\n", 0);
		printf("OG :[%#2.1o]\n", 0);

	 ft_printf("MY :[%-#2.1o]\n", 0);
		printf("OG :[%-#2.1o]\n", 0);

	 ft_printf("MY :[%-#2.2o]\n", 0);
		printf("OG :[%-#2.2o]\n", 0);

	 ft_printf("MY :[%#010.0lo]\n", 0);
		printf("OG :[%#010.0lo]\n",  0);

	 ft_printf("MY :[%-2.1o]\n", 0);
		printf("OG :[%-2.1o]\n", 0);

	 ft_printf("MY :[%-2.2o]\n", 0);
		printf("OG :[%-2.2o]\n", 0);

	 ft_printf("MY :[%-1.0d]\n", 0);
		printf("OG :[%-1.0d]\n", 0);

	 ft_printf("MY :[% -6.4d]\n", 0);
		printf("OG :[% -6.4d]\n", 0);

	 ft_printf("MY :[% -3.0d]\n", 0);
		printf("OG :[% -3.0d]\n", 0);



	 ft_printf("MY :[% -0.2d]\n", 0);
		printf("OG :[% -0.2d]\n", 0);

	 ft_printf("MY :[% -1.2d]\n", 0);
		printf("OG :[% -1.2d]\n", 0);

	 ft_printf("MY :[% -1.1d]\n", 0);
		printf("OG :[% -1.1d]\n", 0);

	 ft_printf("MY :[% -1d]\n", 0);
		printf("OG :[% -1d]\n", 0);

		 ft_printf("MY :[% -1.0d]\n", 0);
		printf("OG :[% -1.0d]\n", 0);

	 ft_printf("MY :[% -0.0d]\n", 0);
		printf("OG :[% -0.0d]\n", 0);


	 ft_printf("MY :[% +6d]\n", 33333);
		printf("OG :[% +6d]\n", 33333);

		 ft_printf("MY :[%+1.0d]\n", 33333);
		printf("OG :[%+1.0d]\n", 33333);

	 ft_printf("MY :[%0p]\n", -10);
		printf("OG :[%0p]\n", -10);

	 ft_printf("MY :[%p]\n", -10);
		printf("OG :[%p]\n", -10);

	 ft_printf("MY :[%-20p]\n", 10);
		printf("OG :[%-20p]\n", 10);

	 ft_printf("MY :[%20p]\n", 10);
		printf("OG :[%20p]\n", 10);



	 ft_printf("MY :[%s  %x    %X %c %u  %p  ]\n", str, uin, uin, c,uin, &i);
		printf("OG :[%s  %x    %X %c %u  %p  ]\n", str, uin, uin, c,uin, &i);

	 ft_printf("MY :[%010d]\n", 3);
		printf("OG :[%010d]\n", 3);
	 
	 ft_printf("MY :[%#10.8hho]\n", (unsigned char)250);
		printf("OG :[%#10.8hho]\n", (unsigned char)250);
	 ft_printf("MY :% 03d\n", 0);
		printf("OG :% 03d\n", 0);

	 ft_printf("MY :%.5p\n", 5);
		printf("OG :%.5p\n", 5);

	 ft_printf("MY :%p\n", 0);
		printf("OG :%p\n", 0);
	 ft_printf("MY :{%0*.*d}\n",-20,-15, 42);
		printf("OG :{%0*.*d}\n",-20,-15, 42);



	 ft_printf("MY :[%.5x]\n", 21);
		printf("OG :[%.5x]\n", 21);

		ft_printf("MY :[%b]\n", -21);
		printf("OG :[%b]\n", 21, 21);

		 ft_printf("MY :[%#10.2o]\n", 111);
		printf("OG :[%#10.2o]\n", 111);


		 ft_printf("MY :[%#10.3o]\n", 111);
		printf("OG :[%#10.3o]\n", 111);


		 ft_printf("MY :[%#10.10o]\n", 111);
		printf("OG :[%#10.10o]\n", 111);

		 ft_printf("MY :[%#10.4o]\n", 1111);
		printf("OG :[%#10.4o]\n", 1111);

		 ft_printf("MY :[%#10.2o]\n", 111);
		printf("OG :[%#10.2o]\n", 111);


		 ft_printf("MY :[%#3.3o]\n", 111);
		printf("OG :[%#3.3o]\n", 111);

 		ft_printf("MY :[%#3o]\n", 111);
		printf("OG :[%#3o]\n", 111);

		ft_printf("MY :[%#4o]\n", 111);
		printf("OG :[%#4o]\n", 111);

		ft_printf("MY :[%4o]\n", 111);
		printf("OG :[%4o]\n", 111);


		ft_printf("MY :[%5o]\n", 111);
		printf("OG :[%5o]\n", 111);

		ft_printf("MY :[%-#3o]\n", 111);
		printf("OG :[%-#3o]\n", 111);

		ft_printf("MY :[%-#4o]\n", 111);
		printf("OG :[%-#4o]\n", 111);

		ft_printf("MY :[%-4o]\n", 111);
		printf("OG :[%-4o]\n", 111);


		ft_printf("MY :[%-5o]\n", 111);
		printf("OG :[%-5o]\n", 111);


		 ft_printf("MY :[%#2.3o]\n", 111);
		printf("OG :[%#2.3o]\n", 111);

		 ft_printf("MY :[%#.3o]\n", 1111);
		printf("OG :[%#.3o]\n", 1111);

		 ft_printf("MY :[%#10.2o]\n", 0);
		printf("OG :[%#10.2o]\n", 0);


		 ft_printf("MY :[%#10.3o]\n", 0);
		printf("OG :[%#10.3o]\n", 0);


		 ft_printf("MY :[%#10.10o]\n", 0);
		printf("OG :[%#10.10o]\n", 0);

		 ft_printf("MY :[%#10.4o]\n", 0);
		printf("OG :[%#10.4o]\n", 0);

		 ft_printf("MY :[%#10.2o]\n", 0);
		printf("OG :[%#10.2o]\n", 0);


		ft_printf("MY :[%#3.3o]\n", 111);
		printf("OG :[%#3.3o]\n", 111);


		ft_printf("MY :[%#2.3o]\n", 111);
		printf("OG :[%#2.3o]\n", 111);

		ft_printf("MY :[%#.3o]\n", 1111);
		printf("OG :[%#.3o]\n", 1111);

		ft_printf("MY :[%#o]\n", 1111);
		printf("OG :[%#o]\n", 1111);

		ft_printf("MY :[%-+#o]\n", 1111);
		printf("OG :[%-+#o]\n", 1111);

		ft_printf("MY :[%#3.3o]\n", 111);
		printf("OG :[%#3.3o]\n", 111);


		ft_printf("MY :[%#*.*o]\n",12,12, 111);
		printf("OG :[%#*.*o]\n",12,12, 111);

		ft_printf("MY :[%#.*o]\n",12, 1111);
		printf("OG :[%#.*o]\n",12, 1111);

		ft_printf("MY :[%0#*o]\n",-12, 1111);
		printf("OG :[%0#*o]\n",-12, 1111);

		ft_printf("MY :[%#o]\n", 1111);
		printf("OG :[%#o]\n", 1111);

		ft_printf("MY :[%-+#o]\n", 1111);
		printf("OG :[%-+#o]\n", 1111);


		short jukk = 32766;	
		ft_printf("MY :[%hd]\n", jukk);
		printf("OG :[%hd]\n", jukk);

		ft_printf("MY :[%#010.0lX]\n",  2147483648);
		printf("OG :[%#010.0lX]\n",  2147483648);

		
		
		ft_printf("MY :[%U]\n", uu);
		printf("OG :[%U]\n", uu );

		ft_printf("MY :[%jd]\n", intmax);
		printf("OG :[%jd]\n", intmax );

		ft_printf("MY :[%ji]\n", intmax);
		printf("OG :[%ji]\n", intmax );

		ft_printf("MY :[%lU]\n", guu);
		printf("OG :[%lU]\n", guu );


		ft_printf("MY :[%10.10llu]\n", juuuuuuu);
		printf("OG :[%10.10llu]\n", juuuuuuu );

		ft_printf("MY :[%llU]\n", juuuuuuu);
		printf("OG :[%llU]\n", juuuuuuu );

		ft_printf("MY :[%#010.0lX]\n",  2147483648);
		printf("OG :[%#010.0lX]\n",  2147483648);

	ft_printf("MY :[% +0.0d]\n", 0);
	printf("OG :[% +0.0d]\n", 0);

	ft_printf("MY :[% +0.1d]\n", 0);
	printf("OG :[% +0.1d]\n", 0);

	ft_printf("MY :[% 2.1d]\n", 0);
	printf("OG :[% 2.1d]\n", 0);

	ft_printf("MY :[%05.10%]\n");
	printf("OG :[%05.10%]\n");

	ft_printf("MY :[% 04.d]\n", 0);
	printf("OG :[% 04.d]\n", 0);

	ft_printf("MY :[% 04d]\n", 0);
	printf("OG :[% 04d]\n", 0);

	ft_printf("MY :[% 04.4d]\n", 0);
	printf("OG :[% 04.4d]\n", 0);

	ft_printf("MY :[% 04.d]\n", 123);
	printf("OG :[% 04.d]\n", 123);

	ft_printf("MY :[% 04d]\n", 123);
	printf("OG :[% 04d]\n", 123);

	ft_printf("MY :[% 04.4d]\n", 123);
	printf("OG :[% 04.4d]\n", 123);

	ft_printf("MY :[% 05d]\n", 123);
	printf("OG :[% 05d]\n", 123);

	ft_printf("MY :[% 04.1d]\n", 0);
	printf("OG :[% 04.1d]\n", 0);

	ft_printf("MY :[% 04.2d]\n", 0);
	printf("OG :[% 04.2d]\n", 0);

	ft_printf("MY :[% 04.0d]\n", 0);
	printf("OG :[% 04.0d]\n", 0);

	ft_printf("MY :[%+0.0d]\n", 0);
	printf("OG :[%+0.0d]\n", 0);

	ft_printf("MY :[% +0.1d]\n", 0);
	printf("OG :[% +0.1d]\n", 0);

	ft_printf("MY :[% +0.15d]\n", INT_MAX);
	printf("OG :[% +0.15d]\n", INT_MAX);

	ft_printf("MY :[%- +0.15d]\n", INT_MAX);
	printf("OG :[%- +0.15d]\n", INT_MAX);

	ft_printf("MY :[%-0.15d]\n", INT_MAX);
	printf("OG :[%-0.15d]\n", INT_MAX);

	ft_printf("MY :[%-15.15d]\n", INT_MAX);
	printf("OG :[%-15.15d]\n", INT_MAX);

	ft_printf("MY :[% +0.15d]\n", INT_MAX);
	printf("OG :[% +0.15d]\n", INT_MAX);

	ft_printf("MY :[%- +0.15d]\n", 0);
	printf("OG :[%- +0.15d]\n", 0);

	ft_printf("MY :[%-0.15d]\n", 0);
	printf("OG :[%-0.15d]\n", 0);

	ft_printf("MY :[%-15.15d]\n", 0);
	printf("OG :[%-15.15d]\n", 0);


	//system("leaks a.out");
	return 0;
}