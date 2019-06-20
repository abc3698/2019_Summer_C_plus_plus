#pragma once
#include <iostream>
#include <vector>
#include <string>
using std::cout;
using std::endl;
using std::string;

/***********************************************************************/
/*                        포인터 예제 코드                             */
/***********************************************************************/

namespace pointer
{
	/***********************************************************************/
	/*                                예제 1                               */
	/***********************************************************************/
	namespace ex1
	{		
		void Point_Ex_01()
		{
			int a = 10;
			cout << "a : " << a << endl;

			int *pa = &a;
			cout << "pa : " << pa << endl;
			cout << "*pa : " << *pa << endl;

			cout << "sizeof(a) : " << sizeof(a) << "Byte" << endl;
			cout << "sizeof(pa) : " << sizeof(pa) << "Byte" << endl;
			cout << "sizeof(*pa) : " << sizeof(*pa) << "Byte" << endl;
		}

		void Run()
		{
			Point_Ex_01();
		}

	}

	/***********************************************************************/
	/*                                예제 2                               */
	/***********************************************************************/
	namespace ex2
	{		
		void Point_Ex_02_Swap(int a, int b)
		{
			int temp = a;
			a = b;
			b = temp;
		}

		void Point_Ex_02_Ref_Swap(int *a, int *b)
		{
			int temp = *a;
			*a = *b;
			*b = temp;
		}

		void Run()
		{
			int a = 10;
			int b = 20;
			cout << "Call by value Before Value a : " << a << " b : " << b << endl;
			Point_Ex_02_Swap(a, b);
			cout << "After by value Before Value a : " << a << " b : " << b << endl;

			cout << "Call by value Before Value a : " << a << " b : " << b << endl;
			Point_Ex_02_Ref_Swap(&a, &b);
			cout << "After by value Before Value a : " << a << " b : " << b << endl;
		}
	}

	/***********************************************************************/
	/*                                예제 3                               */
	/***********************************************************************/
	namespace ex3
	{
		class foo
		{
		private:
			std::vector<int> intVec;

		public:
			void PushValue(int val) { intVec.push_back(val); }
			void Print()
			{
				for (auto& val : intVec)
					cout << "val : " << val << endl;
			}

			const int VectorSize() { return intVec.size(); }

			
		};

		void Do_Something(foo f)
		{
			int a = 10;
			f.PushValue(a);
		}

		void Do_Something_ref(foo *f)
		{
			int a = 10;
			f->PushValue(a);
		}

		void Run()
		{
			foo f;
			Do_Something(f);
			cout << "f vector size : " << f.VectorSize() << endl;
			f.Print();
			Do_Something_ref(&f);
			cout << "f vector size : " << f.VectorSize() << endl;
			f.Print();
		}
	}

	/***********************************************************************/
	/*                                예제 4                               */
	/***********************************************************************/
	namespace ex4
	{
		void Change(void *pData, int type)
		{
			switch (type)
			{
			case 0: // int
			{
				int *pval = (int*)pData;
				cout << "Int Type - " << *pval << endl;
				break;
			}

			case 1: // double
			{
				double *pval = (double*)pData;
				cout << "double Type - " << *pval << endl;
				break;
			}

			case 2: // char*
			{
				string* pval = (string*)pData;
				cout << "string Type - " << *pval << endl;
				break;
			}
			}
		}

		void Run()
		{
			int a = 10;
			double b = 3.14;
			string str = "Hello World";
			Change(&a, 0);
			Change(&b, 1);
			Change(&str, 2);
		}
	}

	/***********************************************************************/
	/*                                예제 5                               */
	/***********************************************************************/

	namespace ex5
	{
		int add(int a, int b)
		{
			return a + b;
		}

		int minus(int a, int b)
		{
			return a - b;
		}


		int(*GetOperator(int mode))(int, int)
		{
			if (mode == 0)
				return add;
			else
				return minus;
		}
		
		typedef int(*FP)(int, int);

		FP GetOperator2(int mode)
		{
			if (mode == 0)
				return add;
			else
				return minus;
		}
		void Run()
		{
			int a = 10;
			int b = 10;

			int(*fp)(int, int);
			fp = add;
							
			cout << "using add Function - " << a << " + "<< b << " = " << add(a, b) << endl;

			cout << "using Function Point - " << a << " + " << b << " = " << fp(a, b) << endl;

			fp = minus;

			cout << "using Minus Function - " << a << " + " << b << " = " << minus(a, b) << endl;

			cout << "using Function Point - " << a << " + " << b << " = " << fp(a, b) << endl;					

			cout << "using Returning Function Point - " << a << " + " << b << " = " << GetOperator(0)(a, b) << endl;
			cout << "using Returning Function Point - " << a << " - " << b << " = " << GetOperator(1)(a, b) << endl;

			cout << "using Returning Function Point2 - " << a << " + " << b << " = " << GetOperator2(0)(a, b) << endl;
			cout << "using Returning Function Point2 - " << a << " - " << b << " = " << GetOperator2(1)(a, b) << endl;
			
		}
	}

	/***********************************************************************/
	/*                                예제 6                               */
	/***********************************************************************/
	namespace ex6
	{
		struct Calculator
		{
			int val1;
			int val2;
			int(*fp[2])(int, int);
		}typedef cal;

		namespace Another
		{
			int add(int a, int b)
			{
				return a + b;
			}

			int minus(int a, int b)
			{
				return a - b;
			}
		}

		namespace UI
		{
			void Operate(cal *c)
			{
				int mode;
				while (1)
				{
					std::cin >> mode;

					switch (mode)
					{
					case 0:
						cout << "Add" << endl;
						cout << c->val1 << " + " << c->val2 << " = " << c->fp[0](c->val1, c->val1) << endl;
						break;
					case 1:
						cout << "Minus" << endl;
						cout << c->val1 << " + " << c->val2 << " = " << c->fp[1](c->val1, c->val1) << endl;
						break;
					case -1:
						return;
					}
				}
			}
		}				

		void Run()
		{
			int right = 10;
			int left = 20;

			cal c;
			c.val1 = right;
			c.val2 = left;
			c.fp[0] = Another::add;
			c.fp[1] = Another::minus;

			UI::Operate(&c);
		}
	}
}

namespace pointer
{
	namespace DIY
	{
		/***********************************************************************/
		/*               하나의 Structure 와 Pointer를 이용하여                */
		/* int과 double를 모두 처리할수 있는 계산기(더하기, 빼기)를 구현하시오 */
		/***********************************************************************/		

		struct Calculator
		{
			
		};

		void Test(Calculator *c)
		{
			int int_a = 10;
			int int_b = 8;

			double double_a = 3.14;
			double double_b = 2.04;
		
		}

		void Run()
		{
			Calculator cal;			
			Test(&cal);
		}
	}

}




