/******************************************************************************
 *
 * MIT License
 *
 * Copyright (c) 2018 OrthogonalHawk
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 *****************************************************************************/

/******************************************************************************
 *
 * @file     falcon_arg_parser.cc
 * @author   OrthogonalHawk
 * @date     25-Feb-2018
 *
 * @brief    Generic object that supports command-line argument parsing.
 *
 * @section  DESCRIPTION
 *
 * Implements a generic base class object that supports command-line argument
 *  parsing.
 *
 * @section  HISTORY
 *
 * 25-Feb-2018  OrthogonalHawk  File created.
 *
 *****************************************************************************/

/******************************************************************************
 *                               INCLUDE_FILES
 *****************************************************************************/

#include <iostream>
#include <stdint.h>

#include "falcon_arg_parser.h"

/******************************************************************************
 *                                 CONSTANTS
 *****************************************************************************/

const char DEFAULT_COMMAND_LINE_ARGUMENT_DELIMITER = '=';

/******************************************************************************
 *                              ENUMS & TYPEDEFS
 *****************************************************************************/

/******************************************************************************
 *                                  MACROS
 *****************************************************************************/

/******************************************************************************
 *                            CLASS IMPLEMENTATION
 *****************************************************************************/

/* workaround to silence compiler warnings about unused variables */
namespace falcon_arg_parser_ns
{
template <class T>
void ignore_unused_variable(T&) {}
};

/*
 * @brief  Class constructor; all default settings
 */
falcon_arg_parser::falcon_arg_parser(void)
  : falcon_arg_parser(DEFAULT_COMMAND_LINE_ARGUMENT_DELIMITER)
{
    /* no action needed */
}

/*
 * @brief  Class constructor; custom delimiter
 */
falcon_arg_parser::falcon_arg_parser(const char option_val_delimiter)
  : m_delimiter(option_val_delimiter),
    m_program_name("")
{
    /* no action needed */
}

/*
 * @brief  Class destructor
 */
falcon_arg_parser::~falcon_arg_parser(void)
{
    /* no action needed */
}

/*
 * @brief  Parse provided command-line arguments. Sets object state variables based on provided arguments.
 *
 * @note   Will call 'exit()' with 0 return status code if -h/--help option is detected.
 *         Will call 'exit()' with -1 return status code for invalid and unsupported command lines.
 *
 * @param  argc Number of arguments (argc from command-line)
 * @param  pArgv Array of arguments (argv from command-line)
 */
void falcon_arg_parser::parse(int argc, char ** pArgv)
{
    /* verify that at least one argument is provided */
    if (argc == 0 || pArgv == nullptr)
    {
        std::cout << "ERROR: Unable to parse argc with 0 element and/or pArgv=nullptr" << std::endl;
        return;
    }

    /* get the program name */
    m_program_name = std::string(pArgv[0]);

    /* parse the provided arguments */
    for (int32_t i = 1; i < argc; ++i)
    {
        std::string arg(pArgv[i]);
        std::string option = "";
        std::string value  = "";

        if (separate_option_from_value(arg, option, value))
        {
            if (option == "h" || option == "--help")
            {
                std::string derived_class_usage = get_derived_class_usage();
                print_usage(derived_class_usage);

                exit(0);
            }
            else
            {
                if (!derived_class_parse(option, value))
                {
                    std::cout << "ERROR: Unsupported option: " << option << std::endl;

                    std::string derived_class_usage = get_derived_class_usage();
                    print_usage(derived_class_usage);

                    exit(-1);
                }
            }
        }
        else
        {
            std::cout << "ERROR: Invalid argument string: " << arg << std::endl;

            std::string derived_class_usage = get_derived_class_usage();
            print_usage(derived_class_usage);

            exit(-1);
        }
    }
}

/*
 * @brief  Displays usage information on standard out
 */
void falcon_arg_parser::print_usage(void)
{
    std::string derived_class_usage = get_derived_class_usage();
    print_usage(derived_class_usage);
}

/*
 * @brief  Allows a derived class to handle custom arguments
 *
 * @param  option The option argument to parse.
 * @param  value  The corresponding option value
 *
 * @return True if the argument was parsed/handled by the derived class; false otherwise.
 */
bool falcon_arg_parser::derived_class_parse(std::string &option, std::string &value)
{
    falcon_arg_parser_ns::ignore_unused_variable(option);
    falcon_arg_parser_ns::ignore_unused_variable(value);

    /* override in a derived class */
    return false;
}

/*
 * @brief  Allows a derived class to contribute to the 'help' output
 *
 * @return Usage information as a preformatted string
 */
std::string falcon_arg_parser::falcon_arg_parser::get_derived_class_usage(void)
{
    return "";
}

/*
 * @brief  Separate command-line options from values using a delimiter
 *
 * @param[in]  input  The input string
 * @param[out] option The parsed option string
 * @param[out] value  The parsed value string
 *
 * @return True if an option/value pair is found; false otherwise.
 */
bool falcon_arg_parser::separate_option_from_value(std::string &input, std::string &option, std::string &value)
{
    bool ret = true;
    bool found_delimiter = false;

    /* initialize the output parameters */
    option = "";
    value = "";

    for (uint32_t i = 0; i < input.length() && ret; ++i)
    {
        if (input[i] == m_delimiter && !found_delimiter)
        {
            /* first instance of the delimiter */
            found_delimiter = true;
        }
        else if (input[i] == m_delimiter && found_delimiter)
        {
            /* found two copies of the delimiter */
            ret = false;
        }
        else if (!found_delimiter)
        {
            option += input[i];
        }
        else
        {
            value += input[i];
        }
    }

    if ((found_delimiter && value.length() == 0) || (!found_delimiter && option.length() == 0))
    {
        ret = false;
    }

    return ret;
}

/*
 * @brief  Displays usage information on standard out
 *
 * @param  derived_class_usage_information Usage information from a derived class
 */
void falcon_arg_parser::print_usage(std::string &derived_class_usage_information)
{
    std::cout << "Usage: " << m_program_name << " <options>" << std::endl;
    std::cout << std::endl;
    std::cout << "  -h,--help" << std::endl;
    std::cout << "                       display usage information (this message)" << std::endl;
    std::cout << std::endl;
    std::cout << derived_class_usage_information;
}
