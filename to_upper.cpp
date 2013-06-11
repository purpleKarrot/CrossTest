/*
 * Copyright (C) 2013 Daniel Pfeifer <daniel@pfeifer-mail.de>
 *
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *	 http://www.boost.org/LICENSE_1_0.txt
 */

#include <string>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/detail/lightweight_test.hpp>

int to_upper(int argc, char* argv[])
{
    std::string hello = "Hello, World!";

	BOOST_TEST_EQ(boost::to_upper_copy(hello), "HELLO, WORLD!");

	return boost::report_errors();
}
