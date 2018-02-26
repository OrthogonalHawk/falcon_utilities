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
 * @file     falcon_arg_parser.h
 * @author   OrthogonalHawk
 * @date     25-Feb-2018
 *
 * @brief    Generic object that supports command-line argument parsing.
 *
 * @section  DESCRIPTION
 *
 * Defines a generic base class object that supports command-line argument
 *  parsing.
 *
 * @section  HISTORY
 *
 * 25-Feb-2018  OrthogonalHawk  File created.
 *
 *****************************************************************************/

#ifndef __FALCON_ARG_PARSER_H__
#define __FALCON_ARG_PARSER_H__

/******************************************************************************
 *                               INCLUDE_FILES
 *****************************************************************************/

#include <string>

/******************************************************************************
 *                                 CONSTANTS
 *****************************************************************************/

/******************************************************************************
 *                              ENUMS & TYPEDEFS
 *****************************************************************************/

/******************************************************************************
 *                                  MACROS
 *****************************************************************************/

/******************************************************************************
 *                              CLASS DECLARATION
 *****************************************************************************/

class falcon_arg_parser
{
public:

    falcon_arg_parser(void);
    falcon_arg_parser(const char option_val_delimiter);
    virtual ~falcon_arg_parser(void);
    void parse(int argc, char ** pArgv, bool exit_on_unsupported_arg);
    void print_usage(void);

    std::string get_program_name(void);

    /* explicitly disable these methods */
    falcon_arg_parser(const falcon_arg_parser&) = delete;
    falcon_arg_parser& operator=(const falcon_arg_parser&) = delete;

protected:

    virtual bool derived_class_parse(std::string &option, std::string &value);
    virtual std::string get_derived_class_usage(void);

    virtual bool separate_option_from_value(std::string &input, std::string &option, std::string &value);
    void print_usage(std::string &derived_class_usage_information);

private:

    char        m_delimiter;
    std::string m_program_name;
};

#endif // __FALCON_ARG_PARSER_H__
