#include <iostream>
using namespace std;

#include "functions.h"

int j = 0;

void print_to_21(){
	for (int i = 0; i <= 21; i++){
		j = i;
		while (j >= 0){
			cout << " ";
			j--;
		}
		cout << i << endl;	
	}
}