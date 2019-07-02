#pragma once
#include <initializer_list>
#include <vector>
#include <cassert>
namespace CONSTRUCTOR
{
	/***********************************************************************/
	/*			  				멤버 초기화 리스트 예제 			       */
	/***********************************************************************/
	namespace MEMBER_INITIALIZATION_LIST
	{
		class Matrix
		{
		private:
			int nrows;
			int ncols;
		public:
			Matrix(int nrows, int ncols) : nrows(nrows), ncols(ncols) {}
		};

		class Solver
		{
		public:
			// Error
			/*Solver(int nrows, int ncols)
			{
				matrix = Matrix(nrows, ncols);
			}*/
			Solver(int nrows, int ncols) : matrix(nrows, ncols) {}

		private:
			Matrix matrix;
		};
	}

	namespace COPY_CONSTRUCTOR
	{
		/***********************************************************************/
		/*			  				  복사 생성자 예제 						   */
		/***********************************************************************/
		namespace ex1
		{
			class Matrix
			{
			public:
				int nrows;
				int ncols;
			public:
				Matrix(int nrows, int ncols) : nrows(nrows), ncols(ncols) {}
				// 정의하지 않아도 암묵적으로 복사 생성자를 생성
				// 얕은 복사가 일어남
				//Matrix(const Matrix & rhs) : nrows(rhs.nrows), ncols(rhs.ncols) {}
			};

			void Run()
			{
				Matrix m(1, 1);
				cout << "m.ncols : " << m.ncols << endl;
				cout << "m.nrows : " << m.nrows << endl;

				Matrix m2(m);
				cout << "m2.ncols : " << m2.ncols << endl;
				cout << "m2.nrows : " << m2.nrows << endl;
			}
		}

		/***********************************************************************/
		/*                     아래 코드는 에러를 발생시킨다                   */
		/*                   에러 원인과 해결방안을 제시하시오                 */
		/***********************************************************************/
		namespace DIY
		{
			class foo
			{
			public:
				double *pd;
				//std::unique_ptr<double> pd;
			public:
				foo(double val) : pd(new double) { *pd = val; }
				
				~foo() { delete pd; }
			};

			void Run()
			{
				foo f(10.0);
				cout << "f.pd : " << f.pd << " f.*pd : " << *f.pd << endl;
				foo f2(f);

				cout << "f2.pd : " << f2.pd << " f2.*pd : " << *f2.pd << endl;
			}
		}
	}

	namespace EXPLICIT
	{
		/***********************************************************************/
		/*			  				   explicit 예제 1						   */
		/***********************************************************************/
		namespace ex1
		{
			class Foo
			{
			public:
				int m_foo;
				Foo(int foo) : m_foo(foo) {}
			};

			void Print_Foo(Foo f) // 암시적 변환으로 인하여 자동으로 형 변환을 함
			{
				cout << f.m_foo << endl;
			}

			void Run()
			{
				int num = 43;
				Print_Foo(num);
			}
		}

		/***********************************************************************/
		/*			  				   explicit 예제 2						   */
		/***********************************************************************/
		namespace ex2
		{
			class Foo
			{
			public:
				int m_foo;
				explicit Foo(int foo) : m_foo(foo) {} // 암시적 변화를 막음
			};

			void Print_Foo(Foo f)
			{
				cout << f.m_foo << endl;
			}

			void Run()
			{
				int num = 43;
				// Error
				//Print_Foo(num);
			}
		}
	}

	namespace Delegating
	{
		/***********************************************************************/
		/*			  				   위임 생성자 예제 					   */
		/***********************************************************************/
		class Matrix_Modern
		{
		public:
			int nrows;
			int ncols;
		public:
			Matrix_Modern(int nrows, int ncols) : nrows{ nrows }, ncols{ ncols } {}
			Matrix_Modern(int nrows) : Matrix_Modern{ nrows, 10 } {}
			Matrix_Modern() : Matrix_Modern{ 10 } {}

		};

		void Run()
		{
			Matrix_Modern m;
			cout << "m.nrows : " << m.nrows << " m.ncols : " << m.ncols << endl;
		}
	}

	namespace MEMBER_DEFAULT
	{
		/***********************************************************************/
		/*			  				   멤버의 기본 값 예제 					   */
		/***********************************************************************/
		class Matrix_Modern
		{
		public:
			int nrows = 10;
			int ncols = 10;
		public:
			Matrix_Modern(int nrows, int ncols) : nrows{ nrows }, ncols{ ncols } {}
			Matrix_Modern(int nrows) : nrows{nrows} {}
			Matrix_Modern(){}

		};

		void Run()
		{
			Matrix_Modern m;
			cout << "m.nrows : " << m.nrows << " m.ncols : " << m.ncols << endl;
		}
	}

	namespace INITIALIZER_LIST
	{
		/***********************************************************************/
		/*			  				   유니폼 초기화 예제 1					   */
		/***********************************************************************/
		namespace ex1
		{
			void Run()
			{
				int a[] = { 1, 2, 3 };
				int b[]{ 1, 2, 3 };

				cout << "a : ";
				for (auto v : a)
					cout << v << ", ";
				cout << endl;

				cout << "b : ";
				for (auto v : b)
					cout << v << ", ";
				cout << endl;
			}
		}

		/***********************************************************************/
		/*			  				   유니폼 초기화 예제 2					   */
		/***********************************************************************/
		namespace ex2
		{
			void Run()
			{
				std::vector<int> vec{ 1, 2, 3 };

				cout << "vec : ";
				for (auto v : vec)
					cout << v << ", ";
				cout << endl;
			}
		}

		/***********************************************************************/
		/*			  				   초기화 리스트 예제 1					   */
		/***********************************************************************/
		namespace ex3
		{
			class list
			{
			public:
				int size;
				std::unique_ptr<double[]>data;

			public:
				list(int size) : size(size), data(new double[size]) {}

				list(std::initializer_list<double> values) : size(values.size()), data(new double[size])
				{
					std::copy(std::begin(values), std::end(values), &data[0]);
				}

				list& operator=(std::initializer_list<double> values)
				{
					assert(size == values.size());
					std::copy(std::begin(values), std::end(values), &data[0]);
					return *this;
				}

				void Print()
				{
					cout << "List : ";
					for (int i = 0; i < size; ++i)
						cout << data[i] << ", ";
					cout << endl;
				}
			};

			void Run()
			{
				list l{ 1, 2, 3 };
				l.Print();

				l = { 3, 4, 5 };
				l.Print();
			}
		}

		/***********************************************************************/
		/*           아래 코드는 크기가 다른 경우 오류를 발생한다.             */
		/*           아래 코드가 실행되도록 프로그램을 수정하시오              */
		/*  Hint : unique_ptr의 함수 release()를 할 경우 모든 메모리가 해제됨  */
		/***********************************************************************/

		namespace DIY
		{
			class list
			{
			public:
				int size;
				std::unique_ptr<double[]>data;

			public:
				list(int size) : size(size), data(new double[size]) {}

				list(std::initializer_list<double> values) : size(values.size()), data(new double[size])
				{
					std::copy(std::begin(values), std::end(values), &data[0]);
				}

				list& operator=(std::initializer_list<double> values)
				{
					assert(size == values.size());
					std::copy(std::begin(values), std::end(values), &data[0]);
					return *this;
				}

				void Print()
				{
					cout << "List : ";
					for (int i = 0; i < size; ++i)
						cout << data[i] << ", ";
					cout << endl;
				}
			};

			void Run()
			{
				list l{ 1, 2, 3 };
				l.Print();

				l = { 3, 4, 5, 6 };
				l.Print();
			}
		}
	}

	namespace MOVE
	{
		/***********************************************************************/
		/*				  				  Move 예제 1						   */
		/***********************************************************************/
		namespace ex1
		{
			void Run()
			{
				std::vector<int> vec{ 1, 2, 3, 4, 5 };
				cout << "vec.size : " << vec.size() << endl << endl;;
				cout << "vec" << endl;
				for (auto val : vec)
					cout << val << ", ";
				cout << endl << endl;

				std::vector<int> vec2 = std::move(vec);
				cout << "vec.size : " << vec.size() << endl;
				cout << "vec2.size : " << vec2.size() << endl;

				cout << endl;

				cout << "vec" << endl;
				for (auto val : vec)
					cout << val << ", ";
				cout << endl;

				cout << "vec2" << endl;
				for (auto val : vec2)
					cout << val << ", ";
				cout << endl;
			}
		}

		/***********************************************************************/
		/*				  				  Move 예제 2						   */
		/***********************************************************************/
		namespace ex2
		{
			class list
			{
			public:
				int size;
				std::unique_ptr<double[]>data;

			public:
				list(int size) : size(size), data(new double[size]) {}

				list& operator=(list &&rhs)
				{
					assert(size == 0 || size == rhs.size);
					std::swap(data, rhs.data);
					rhs.data.release();
					rhs.size = 0;
					return *this;
				}

				list(list &&rhs) : size(rhs.size), data(new double[size])
				{
					std::swap(data, rhs.data);
					rhs.data.release();
					rhs.size = 0;					
				}

				list(std::initializer_list<double> values) : size(values.size()), data(new double[size])
				{
					std::copy(std::begin(values), std::end(values), &data[0]);
				}

				void Print()
				{					
					for (int i = 0; i < size; ++i)
						cout << data[i] << ", ";
					cout << endl;
				}
			};

			void Run()
			{
				list l{ 1, 2, 3 };
				list l2{ 3, 4, 5 };
				cout << "List1 : ";  l.Print();
				cout << "List2 : ";  l2.Print();
				cout << "List1 data Addr : " << l.data << endl;
				cout << "List2 data Addr : " << l2.data << endl;

				cout << endl;

				l2 = std::move(l);
				cout << "List1 : "; l.Print();
				cout << "List2 : "; l2.Print();
				cout << "List1 data Addr : " << l.data << endl;
				cout << "List2 data Addr : " << l2.data << endl;

				list l3{ std::move(l2) };
				cout << "List3 : ";  l3.Print();
				cout << "List2 data Addr : " << l2.data << endl;
				cout << "List3 data Addr : " << l3.data << endl;
			}
		}
	}
}