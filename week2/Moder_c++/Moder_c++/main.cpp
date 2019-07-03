#include "chapter01.hpp"
#include "chapter02.hpp"

#include <crtdbg.h>
#include <iostream>

#ifdef _DEBUG
#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)
#define malloc(c) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif

int main()
{	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	int *a = new int[10];
	_CrtDumpMemoryLeaks();	

	int b = 0;
}

/*int main()
{
	NotNarrowed::ex::Run();

	NULLPOINTER::ex::Run();

	SMART_POINTER::UNIQUE_PTR::ex1::Run();
	SMART_POINTER::UNIQUE_PTR::ex2::Run();
	SMART_POINTER::UNIQUE_PTR::ex3::Run();
	SMART_POINTER::UNIQUE_PTR::ex4::Run();

	SMART_POINTER::SHARED_PTR::ex1::Run();
	SMART_POINTER::SHARED_PTR::ex2::Run();
	SMART_POINTER::SHARED_PTR::ex3::Run();
	SMART_POINTER::SHARED_PTR::ex4::Run();

	CONSTRUCTOR::COPY_CONSTRUCTOR::ex1::Run();

	CONSTRUCTOR::COPY_CONSTRUCTOR::DIY::Run();

	CONSTRUCTOR::EXPLICIT::ex1::Run();
	CONSTRUCTOR::EXPLICIT::ex2::Run();

	CONSTRUCTOR::Delegating::Run();

	CONSTRUCTOR::MEMBER_DEFAULT::Run();

	CONSTRUCTOR::INITIALIZER_LIST::ex1::Run();
	CONSTRUCTOR::INITIALIZER_LIST::ex2::Run();
	CONSTRUCTOR::INITIALIZER_LIST::ex3::Run();

	CONSTRUCTOR::INITIALIZER_LIST::DIY::Run();

	CONSTRUCTOR::MOVE::ex1::Run();
	CONSTRUCTOR::MOVE::ex2::Run();		
}*/