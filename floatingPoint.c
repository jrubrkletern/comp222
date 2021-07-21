#include <stdio.h>
#include <math.h>

/*************************/
void floattoieee()
{
	/* declare local variables */
float inputNumber;
int sign;
float myExponent = 0;
float dec_number;
int exponentArray[150];
int myTempArray[150];
int mantissa[150];
	/* prompt for floating point decimal number */
printf("Enter floating point decimal number\n");
scanf("%f", &inputNumber);

printf("Input decimal is %f \n", inputNumber);
	/* Check for 0--if so, print result */
if(inputNumber == 0.0) {
printf("Biased Exponent: 00000000 \nMantissa = 00000000000000000000000 \nIEEE-754: 00000000\n\n");
return;
}


	/* Print sign: if number>0, sign is 0, else 1 */
	/* take absolute value of number before generating significand */
if(inputNumber > 0) {
sign = 0;


} else { sign = 1;
				inputNumber = -inputNumber;
				}
 printf("Sign is: %d \n", sign);

	/* Normalize number:
	while number >2, divide by 2, increment exponent
	while number <1, multiply by 2, decrement exponent
	*/
float tempNumber = inputNumber;


	while(tempNumber >= 2) {
		tempNumber = tempNumber/2;
		myExponent++;
}

	while(tempNumber < 1) {
	tempNumber = tempNumber*2;
	myExponent--;


	}



printf("Biased Exponent is: ");
    /* Bias exponent by 127 and print each bit in binary with 8-iteration for-loop*/
		int temp_exp = myExponent + 127;

			int myIterator = 0;
			while (temp_exp > 0) {

				myTempArray[myIterator] = temp_exp % 2;

				temp_exp = temp_exp/2;

				myIterator++;
			}

			for(int i = 7; i >= 0; i--) {
				int j = 0;

				exponentArray[7-i] = myTempArray[i];

				printf("%d", exponentArray[7-i]);
				j++;
			}


		printf("\nMantissa is:");

		int mantissaNumber = 0;
    /* Hide 1 and print significand in binary with 23-iteration for-loop*/
		tempNumber = tempNumber -1;


			for(int i = 0; i <= 22; i++) {
				if(tempNumber >= (float)0.5*(1.0/((float)(pow(2,i))))) {
						mantissa[i] = 1;
						mantissaNumber = mantissaNumber + (pow(2,22-i));
						tempNumber = tempNumber - (((0.5)* (1.0/((float)(pow(2,i))))));
					printf("1");

				} else { mantissa[i] = 0;
					printf("0");
				}


			}
		printf("\n");


myExponent = 0;
for(int i = 0; i <= 7; i++) {


myExponent = myExponent + (exponentArray[i]*pow(2,30-i));

}

	/* Print IEEE-754 representation */
int ieee_number;

if(sign != 1) {
ieee_number = myExponent + mantissaNumber;
}
else {
		int complimentArray[150];
		complimentArray[0] = 0;

		for(int i = 1; i <= 8; i++) {

				complimentArray[i] = ((exponentArray[i-1] + 1 ) % 2);

	}

for(int i = 9; i <= 31; i++) {


	complimentArray[i] = ((mantissa[i-9]+1)%2);
}

complimentArray[31] = ((mantissa[22]+1)%2);

if(complimentArray[31] = 0) {
	complimentArray[31] = 1;

} else if(complimentArray[31] = 1) {
	int k = 31;

	while(complimentArray[k-1] != 0) {
		k = k-1;

		complimentArray[k+1] = 0;

	}
	complimentArray[k] = 0;
	complimentArray[k-1] = 1;

for(int i = 0; i <= 31; i++) {

	ieee_number = ieee_number + complimentArray[i]*pow(2,31-i);
}
ieee_number = -ieee_number;
}
for(int i = 0; i <= 0; i++) {
}
}

	printf("IEEE-754: %x \n\n", ieee_number);

  return;
}

/***********************************************************************/

void ieetofloat()
{
  /* declare local variables */
int ieee_number;
int sign;
  /* prompt for IEEE-754 representation */
	printf("Enter IEEE-754 Hexadecimal number.\n");
	scanf("%x", &ieee_number);
		printf("IEEE-754 number is: %x.\n", ieee_number);
	/* check for special cases: 0, -0, +infinity, -infinity, NaN,
		if so, print and return */
		//+0
		if(ieee_number == 0x00000000) {
			printf("Number is +0!\n\n");
			return;

			//-0
		}
		if(ieee_number == 0x80000000) {
			printf("Number is -0!\n\n");
			return;


		}
		//+infintiy
		if(ieee_number == 0x7F800000) {
			printf("Number is positive-infinity!\n\n");
			return;


		}
		//-infinity
		if(ieee_number == 0xFF800000) {
			printf("Number is negative-infinity!\n\n");
			return;


		}
		//NaN

		if(ieee_number == 0xFFFFFFFF) {
			printf("Input is not a number!\n\n");
			return;
		}

		if(ieee_number > 0x7F800000) {
			printf("Input is not a number!\n\n");
			return;


		}
	/* Mask sign from number: if sign=0, print "+", else print "-" */

	sign = (ieee_number & 0x80000000)/(pow(2,31));
	if(sign !=0 ) {
	printf("Sign is -\n");
}
	else printf("Sign is +\n");



	/* Mask biased exponent and significand from number */
	/* If biased exponent=0, number is denormalized with unbiased exponent of -126,
		print denormalized number as fraction * 2^(-126), return */
int myExponent;

myExponent = (((ieee_number & 0x7F800000) / pow(2,23))-127);

int denormalized = 0;
if(myExponent == -127) {
denormalized = 1;
	myExponent = -126;
}

printf("Exponent: %d\n", myExponent);
	/* Unbias exponent by subtracting 127 and print */
	/* Add hidden 1 and print normalized decimal number */
float significand;
significand = (ieee_number & 0x007FFFFF)/pow(2,23);



//printf("printing significand: %f", significand);
float new_significand;
new_significand = 1+ significand;
float normed;
normed = new_significand;

if(denormalized != 1) {
printf("Normalized decimal: %f\n", normed);

} else {

	normed = normed - 1;

	printf("Normalized decimal: %f\n", normed);
	myExponent = 0;
}




while(myExponent != 0) {

if(myExponent > 0) {
normed = normed*2;

	myExponent--;
}
if(myExponent < 0) {

normed = normed/2;
	myExponent++;
}


}
if(denormalized != 1) {
if(sign != 1) {
printf("Number in decimal form is: %f\n\n", normed);
} else {
	normed = -normed;
printf("Number in decimal form is: %f\n\n", normed);
}

} else {
	if(sign == 1) {
	printf("Number is denormalized, decimal form is: -%f * 2^(-126)\n\n", normed);
} else {
	printf("Number is denormalized, decimal form is: %f * 2^(-126)\n\n", normed);

}
}

	/* Print decimal number */


	 return;

}

int main()
{
	int choice = 0;
	/* until user chooses to quit, print menu,
	select choice via switch statement and call appropriate function*/
	while(choice != 3) {
	scanf("%d", &choice);

	switch(choice) {
		case 1: floattoieee(); break;
		case 2: ieetofloat(); break;

		default:
		break;


		}
	}
	return 0;
}
