#pragma once
#include <iostream>
#include <string>
using std::cout;
using std::endl;

/***********************************************************************/
/*                        템플릿 예제 코드                             */
/***********************************************************************/

namespace Template
{
	/***********************************************************************/
	/*                                예제 1                               */
	/***********************************************************************/
	namespace ex1
	{
		template<class T>
		//template<typename T>
		T add(T a, T b)
		{
			return a + b;
		}


		void Run()
		{
			cout << add(10, 20) << endl;
			cout << add(3.14, 10.15) << endl;
			cout << add(std::string("Hello"), std::string("World")) << endl;
		}
	}

	/***********************************************************************/
	/*                                예제 2                               */
	/***********************************************************************/
	namespace ex2
	{
		template<class T>		
		T add(T a, T b)
		{
			return a + b;
		}

		template<>
		std::string add<string>(string a, string b)
		{
			return a + " " + b;
		}

		void Run()
		{			
			cout << add(std::string("Hello"), std::string("World")) << endl;
		}
	}

	/***********************************************************************/
	/*                                예제 3                               */
	/***********************************************************************/
	namespace ex3
	{
		template<class T>
		class Shape
		{
		protected:
			T height;
			T width;
		public:
			Shape(T h, T w) : height(h), width(w) {}

			T GetHeight() { return height; }
			T GetWidth() { return width; }
		};

		template<class T>
		class Polygon : public Shape<T>
		{
		private:
			T size;
		public:			
			Polygon(Shape<T> shape, T size) : Shape<T>(shape), size(size) {}
			Polygon(T h, T w, T size) : Shape<T>(h, w), size(size) {}
			T GetSize() { return size; }
		};

		void Run()
		{
			Shape<int> shape1(10, 10);
			cout << "Shape1" << endl;
			cout << shape1.GetHeight() << " " << shape1.GetWidth() << endl;
			cout << endl;

			Shape<double> shape2(1.45, 2.89);
			cout << "shape2" << endl;
			cout << shape2.GetHeight() << " " << shape2.GetWidth() << endl;
			cout << endl;

			Polygon<int> polygon1(shape1, 100);
			cout << "polygon1" << endl;
			cout << polygon1.GetHeight() << " " << polygon1.GetWidth() << " " << polygon1.GetSize() << endl;
			cout << endl;

			Polygon<int> polygon2(10, 10, 100);
			cout << "polygon2" << endl;
			cout << polygon2.GetHeight() << " " << polygon2.GetWidth() << " " << polygon2.GetSize() <<  endl;
			cout << endl;

			Polygon<double> polygon3(shape2, 4.1905);
			cout << "polygon3" << endl;
			cout << polygon3.GetHeight() << " " << polygon3.GetWidth() << " " << polygon3.GetSize() << endl;
			cout << endl;

			Polygon<double> polygon4(1.45, 2.89, 4.1905);
			cout << "polygon4" << endl;
			cout << polygon4.GetHeight() << " " << polygon4.GetWidth() << " " << polygon4.GetSize() << endl;
			cout << endl;
		}
	}

	/***********************************************************************/
	/*                          템플릿 클래스를 이용하여                   */
	/* int과 double를 모두 처리할수 있는 계산기(더하기, 빼기)를 구현하시오 */
	/***********************************************************************/
	#include <type_traits>

	namespace DIY
	{		
		void Run()
		{
			int int_val1 = 10;
			int int_val2 = 8;

			int double_val1 = 3.14;
			int double_val2 = 2.04;			
		}
	}
}