#include <stdio.h>

#include <array_utils.h>

int main(){
	
	//creating array rand
	int size = 128;
	int rand[size];

	//populated with random ints
	randomize_array(rand, size);

	//pointer to tenth entry
	int* tenth = rand+9;

	//print seven entries after 10th entry
	printf("\n");
	print_array(tenth, 7);
	
	//sum of array and print
	printf("Sum of rand array: %d\n", sum_array(rand, size));

	//mean of array and print
	printf("Mean of rand array: %f\n", mean_array(rand, size));

	//pointers
	int* first = &rand[0];
	int* thirtythird = &rand[32];
	int* sixtyfifth = &rand[64];
	int* ninetyseventh = &rand[96];

	//number of entries after pointer
	int num = 32;

	//first pointer
	printf("Sum of 32 entries after first: %d\n", sum_array(first, num));
	printf("Mean of 32 entries after first: %f\n", mean_array(first, num));

	//thirty third pointer
	printf("Sum of 32 entries after thirty third: %d\n", sum_array(thirtythird, num));
	printf("Mean of 32 entries after thirty third: %f\n", mean_array(thirtythird, num));
	
	//sixty fifth pointer
	printf("Sum of 32 entries after sixty fifth: %d\n", sum_array(sixtyfifth, num));
	printf("Mean of 32 entries after sixty fifth: %f\n", mean_array(sixtyfifth, num));
	
	//ninety seventh pointer
	printf("Sum of 32 entries after ninety seventh: %d\n", sum_array(ninetyseventh, num));
	printf("Mean of 32 entries after ninety seventh: %f\n", mean_array(ninetyseventh, num));

    return 0;
}
