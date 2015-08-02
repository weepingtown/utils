#include "stdafx.h"
#include "CppUnitTest.h"
#include "../algorithm/avl/avl.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{		
	TEST_CLASS(UnitTestAvl)
	{
	public:
		
		TEST_METHOD(InitAvl)
		{
			
            avl_node_t node;
            avl_init_node(&node);
            
		}

	};
}