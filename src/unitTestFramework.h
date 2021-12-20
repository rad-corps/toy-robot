#pragma once

#include <string>
#include <sstream>
#include <cassert>
#include <iostream>
#include <functional>
#include <vector>

namespace unit_tests
{
	/**
	 * @brief Report pass or failure based on bool param
	 * @param param true for pass
	 * @param msg optional message to display on pass or failure
	 * @return true on success, false on failure
	*/
	bool IS_TRUE(bool param, const std::string& msg = "")
	{
		if (param)
		{
			std::cout << "TEST PASSED: \t " << msg << std::endl;
		}
		else
		{
			std::cout << "TEST FAILED: \t " << msg << std::endl;
		}
		return param;
	}
	
	/**
	 * @brief inverse of IS_TRUE allows us to not both overloading operator != on older compilers
	 * @param param fail if true
	 * @param msg optional message to display
	 * @return true on success, false on failure
	*/
	bool IS_FALSE(bool param, const std::string& msg)
	{
		return IS_TRUE(!param, msg);
	}

	/**
	 * @brief
	 * @tparam T type to check for equality
	 * @param a LHS of equality
	 * @param b RHS of equality
	 * @param msg message supplied from unit test
	 * @return true on success, false on failure
	*/
	template<typename T>
	bool IS_EQUAL(const T& a, const T& b, const std::string& msg)
	{
		if (a == b)
		{
			return IS_TRUE(true, msg);
		}
		else
		{
			std::stringstream msgStream;
			msgStream << msg << std::endl;
			msgStream << a << " did not match " << b << std::endl;
			std::string failureMsg = msgStream.str();
			return IS_TRUE(false, failureMsg);
		}
	}
}

// internal use only. Use the macros at the bottom of this file instead
namespace test_framework_internal
{
	struct UnitTest
	{
		UnitTest(const std::string& testName, std::function<void()> testFunc)
			:m_testFunc{ testFunc },
			m_testName{ testName }
		{}

		void run() const
		{
			std::cout
				<< "--------------------------------------" << std::endl
				<< m_testName << std::endl
				<< "--------------------------------------" << std::endl;

			m_testFunc();
		}
		std::function<void()> m_testFunc;
		const std::string m_testName;
	};

	struct TestCollection
	{
		TestCollection() :m_tests(){}

		void add(UnitTest test)
		{
			m_tests.push_back(test);
		}
		void runAll()
		{
			for (const UnitTest& test : m_tests)
			{
				test.run();
			}
		}

		std::vector<UnitTest> m_tests;
	};
}

#define INIT_TEST_FRAMEWORK() test_framework_internal::TestCollection _testCollection;
#define ADD_TEST(name,func) _testCollection.add(test_framework_internal::UnitTest(name, []() func ));
#define RUN_TESTS() _testCollection.runAll();