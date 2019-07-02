#pragma once
#include <iostream>
using std::cout;
using std::endl;
namespace NotNarrowed
{
	namespace ex
	{
		void Overflow()
		{
			long l = 1234567890123; // out : 1912276171
			cout << l << endl;

			//long l2 = { 1234567890123 }; // out : 1912276171
			//cout << l2 << endl; // '__int64'에서 'long'(으)로의 변환에는 축소 변환이 필요합니다.

			long long l3 = { 1234567890123 };
			cout << l3 << endl;
		}

		void Noimplict()
		{
			int i = 3.14;
			cout << i << endl; // out : 3

			//int i2 = { 3.14 };
			//cout << i << endl; // double'에서 'int'(으)로의 변환에는 축소 변환이 필요합니다.
		}

		void NoUnsigned()
		{
			unsigned char c = -3;
			cout << (int)c << endl; // out : 253

			//unsigned char c2 = { -3 };
			//cout << c2 << endl; // 'int'에서 'unsigned char'(으)로의 변환에는 축소 변환이 필요합니다.

			//unsigned int i = 3;
			//int i2 = { i }; // 'unsigned int'에서 'int'(으)로의 변환에는 축소 변환이 필요합니다.
		}

		void Noimplict2()
		{
			float f = { 3.14 };
			cout << f << endl; // out : 3.14

			double d = { 3.14 };
			cout << d << endl; // out : 3.14

			//float f2 = { d };
			//cout << f2 << endl; // 'double'에서 'float'(으)로의 변환에는 축소 변환이 필요합니다.
		}

		/***********************************************************************/
		/*                      축소하지 않는 초기화 예제                      */
		/***********************************************************************/
		void Run()
		{
			//Overflow();
			//Noimplict();
			//NoUnsigned();
			//Noimplict2();
		}
	}
}

namespace NULLPOINTER
{
	namespace ex
	{
		/***********************************************************************/
		/*								nullptr 예제						   */
		/***********************************************************************/
		void Run()
		{
			int *pi = NULL;
			int *pi2 = 0;

			int *pi3 = nullptr;
			int *pi4{};

			cout <<"pi : " << pi << endl;
			cout <<"pi2 : " << pi2 << endl;
			cout <<"pi3 : " << pi3 << endl;
			cout <<"pi4 : " << pi4 << endl;
		}
	}
}

#include <memory>
#include <functional>
namespace SMART_POINTER
{
	namespace UNIQUE_PTR
	{
		/***********************************************************************/
		/*			  				unique_ptr 예제 1					       */
		/***********************************************************************/
		namespace ex1
		{
			void Run()
			{
				std::unique_ptr<double> dp{ new double };
				cout << dp << endl;
				cout << dp.get() << endl;
				cout << *dp.get() << endl;

				*dp.get() = 10;
				cout << *dp.get() << endl;
				*dp = 20;
				cout << *dp << endl;
			}
		}

		/***********************************************************************/
		/*			  				unique_ptr 예제 2					       */
		/***********************************************************************/

		namespace ex2
		{
			class foo
			{
				static int cnt;
				int id = 0;
			public:
				foo()
				{
					id = cnt++;
				}

				~foo()
				{
					cout << "ID(" << id << ")" << "foo Deconstruction" << endl;
				}

				void Print()
				{
					cout << "My ID is " << id << endl;
				}
			};

			int foo::cnt = 0;

			void Run()
			{
				cout << "unique_ptr for foo class" << endl;
				std::unique_ptr<foo> pt{ new foo };
				// Another Version
				//std::unique_ptr<foo> pt = std::make_unique<foo>();
				cout << "End block" << endl;
			}
		}

		/***********************************************************************/
		/*			  				unique_ptr 예제 3					       */
		/***********************************************************************/

		namespace ex3
		{						
			void Run()
			{
				cout << "unique_ptr for foo class" << endl;
				std::unique_ptr<ex2::foo[]> pt{ new ex2::foo[5] };
				// Another Version
				//std::unique_ptr<ex2::foo[]> pt = std::make_unique<ex2::foo[]>(5);
				pt[0].Print();
				pt[1].Print();
				cout << "End block" << endl;
			}
		}

		/***********************************************************************/
		/*			  				unique_ptr 예제 4					       */
		/***********************************************************************/

		namespace ex4
		{			
			void Run()
			{				
				std::unique_ptr<ex2::foo> pt{ new ex2::foo };
				std::unique_ptr<ex2::foo> pt2;

				cout << "Before Copy" << endl;

				cout << "pt : "  << pt << endl;
				cout << "pt2 : " << pt2 << endl;

				cout << endl;

				//pt2 = pt; // 복사 금지
				pt2 = std::move(pt);

				cout << "After Copy" << endl;
				cout << "pt : " << pt << endl;
				cout << "pt2 : " << pt2 << endl;
			}
		}
	}

	namespace SHARED_PTR
	{
		class foo
		{
			static int cnt;
			int id = 0;
		public:
			foo()
			{
				id = cnt++;
			}

			~foo()
			{
				cout << "ID(" << id << ")" << "foo Deconstruction" << endl;
			}

			void Print()
			{
				cout << "My ID is " << id << endl;
			}
		};

		int foo::cnt = 0;

		/***********************************************************************/
		/*			  				shared_ptr 예제 1					       */
		/***********************************************************************/

		namespace ex1
		{
			void Run()
			{
				std::shared_ptr<double> dp{ new double };
				// Another Version
				//std::shared_ptr<double> dp = std::make_shared<double>();
				cout << dp << endl;
				cout << dp.get() << endl;
				cout << *dp.get() << endl;

				*dp.get() = 10;
				cout << *dp.get() << endl;
				*dp = 20;
				cout << *dp << endl;
			}			
		}

		/***********************************************************************/
		/*			  				shared_ptr 예제 2					       */
		/***********************************************************************/

		namespace ex2
		{
			void Run()
			{
				std::shared_ptr<double> dp{ new double };				
				std::shared_ptr<double> dp2;
				cout << "dp.use_count() : " << dp.use_count() << endl;
				cout << "dp2.use_count() : " << dp2.use_count() << endl;
				
				cout << endl;

				dp2 = dp;

				cout << "dp.use_count() : " << dp.use_count() << endl;
				cout << "dp2.use_count() : " << dp2.use_count() << endl;
			}
		}

		/***********************************************************************/
		/*			  				shared_ptr 예제 3					       */
		/***********************************************************************/

		namespace ex3
		{
			void func2(std::shared_ptr<foo> dp)
			{
				cout << "In Function 2" << endl;
				cout << "dp.use_count() : " << dp.use_count() << endl;
				cout << "In Function 2 out" << endl;
			}

			void func1()
			{
				cout << "In Function 1" << endl;
				std::shared_ptr<foo> dp = std::make_shared<foo>();
				cout << "dp.use_count() : " << dp.use_count() << endl;
				func2(dp);
				cout << "dp.use_count() : " << dp.use_count() << endl;
				cout << "In Function 1 out" << endl;

			}

			void Run()
			{
				func1();
			}
		}

		/***********************************************************************/
		/*			  				shared_ptr 예제 4					       */
		/***********************************************************************/

		namespace ex4
		{			
			void Run()
			{
				cout << "shared_ptr for foo class" << endl;
				std::shared_ptr<foo[]> pt{ new foo[5] };
				// 현재는 아래 코드 불가
				// c++20 부터 지원
				//std::shared_ptr<foo[]> pt = std::make_shared<foo[]>(5);					
				pt[0].Print();
				pt[1].Print();
				cout << "End block" << endl;
			}
		}
	}
}