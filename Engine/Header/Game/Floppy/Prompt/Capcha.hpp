#pragma once

#include "SDK/SDK.hpp"

namespace Game {
	class Capcha
	{
	public:
		CString question;
		CString answer;
		static Capcha generateCapcha()
		{
			srand(time(nullptr)); // initialisation de rand
			int choice = rand_a_b(0, 1);
			switch (choice)
			{
			case 0:
				return generateOperationCapcha('+');
				break;
			case 1:
				return generateOperationCapcha('-');
				break;
			default:
				return generateOperationCapcha('+');
				break;
			}
		}

	private:
		static int rand_a_b(int a, int b) {
			return static_cast<int>((rand() / (double)RAND_MAX) * (b - a) + a);
		}

		static Capcha generateOperationCapcha(char _operator)
		{
			Capcha c;
			int a = rand_a_b(1000, 7000);
			int b = rand_a_b(1, 9);
			int res = 0;
			switch(_operator)
			{
			case '+':
				res = a + b;
				break;
			case '-':
				res = a - b;
				break;
			case '*':
				res = a * b;
				break;
			default:
				res = a + b;
			}
			char c_q[50];
			snprintf(c_q, 20, "%i %c %i = ____", a, _operator, b);
			char c_a[20];
			snprintf(c_a, 20, "%i", res);
			c.answer = CString(c_a);
			c.question = CString(c_q);
			return c;
		}
	};
}