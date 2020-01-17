
#include <iostream>
#include <time.h>

using namespace std;

int main()
{
	int number[9] = {};
	int number_guess[3] = {};
	
	srand((unsigned int)time(0));

	for (int i = 0; i < 9; i++) {
		number[i] = i + 1;
	}
	int idx1, idx2, temp;
	for (int i = 0; i < 100; i++) {
		idx1 = rand() % 8;
		idx2 = rand() % 8;

		temp = number[idx1];
		number[idx1] = number[idx2];
		number[idx2] = temp;
	}
	
	cout << number[0] << number[1] << number[2] << endl;
	bool flag = false;
	
	while (flag != 1) {
		cout << "숫자를 입력하시오" << endl;
		cin >> temp;
		if (temp == 0)
			break;
		for (int i = 2; i >= 0; i--) {
			number_guess[i] = temp % 10;
			temp /= 10;
		}
		if (number_guess[0] == number[0] && number_guess[1] == number[1] && number_guess[2] == number[2]) {
			cout << "정답입니다." << endl;
			flag = true;
		}

		int strike = 0, ball = 0;
		
		for (int i = 0; i < 3; i++) {
			if (number_guess[i] == number[i]) {
				strike++;
			}
			for (int j = 0; j < 3; j++) {				
				if (i != j && number_guess[i] == number[j]) {
					ball++;
				}
			}
		}

		if (strike == 0 && ball == 0) {
			cout << "OUT" << endl;
		}
		else
			cout << strike << "Strike  " << ball << "ball" << endl;

	}

	return 0;
}