/* Kaleidoscope - Firmware for computer input devices
 * Copyright (C) 2013-2018  Keyboard.io, Inc.
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

// clang-format off

#pragma once

// Code generated by muli-line pre-processor macros is hard to read after
//    pre-processing.
//
// When you want to check pre-processed code, e.g. for debugging or
// to understand what's going on, do the following:
//
// 1) Add the compiler command line definition
//      -DKALEIDOSCOPE_ENABLE_MACRO_NEWLINE_SUBSTITUTION
//    This prevents the __NL__ macro being defined below.
// 2) Generate the preprocessed code (it will contain a lot of __NL__ definitions).
// 3) Open the pre-processed code in your favorite editor.
//    3.1) Replace all __NL__ with newline characters.
//       In vim the command would be ':%s/__NL__/\r/g'.
//    3.2) Autocorrect code-indenting to improve readability. This is necessary
//       as pre-processor macros remove all whitespaces at the beginning of lines.
//       With vim, the command gg=G helps (just type the characters one after
//       the other).
// 4) Don't forget to remove the
//       -DKALEIDOSCOPE_ENABLE_MACRO_NEWLINE_SUBSTITUTION
//    from your compiler command line. Else the code won't compile.

#ifndef KALEIDOSCOPE_ENABLE_MACRO_NEWLINE_SUBSTITUTION
#define __NL__
#endif

#define __NN__

// Some auxiliary macros
//
#define __STRINGIZE(S) #S
#define STRINGIZE(S) __STRINGIZE(S)

#define GLUE2(A, B) A##B
#define GLUE3(A, B, C) A##B##C
#define GLUE4(A, B, C, D) A##B##C##D

#define UNWRAP(...) __VA_ARGS__

// Allow for the creation of verbose messages in static_asserts
//
#define VERBOSE_STATIC_ASSERT_HEADER                                           \
   "\n"                                                                 __NL__ \
   "\n***************************************************************"  __NL__ \
   "\n******************** READ THIS CAREFULLY! *********************"  __NL__ \
   "\n***************************************************************"  __NL__ \
   "\n"

#define VERBOSE_STATIC_ASSERT_FOOTER                                           \
   "\n"                                                                 __NL__ \
   "\n***************************************************************"  __NL__ \
   "\n***************************************************************"  __NL__ \
   "\n***************************************************************"  __NL__ \
   "\n"

#define VERBOSE_FILE_INFO                                                      \
   "\nFile: " __FILE__                                                  __NL__

#define VERBOSE_LINE_INFO                                                      \
   "\nLine: " STRINGIZE(__LINE__)                                       __NL__

// The macro function RESTRICT_ARGS_COUNT can be used to generate more
// verbose error messages when users supply an insuitable number of arguments
// to a macro.
//
// For a macro it is used wherever one of the arguments A, B, C might
// be used, e.g.
//
#if 0 // This is just so that A_MACRO is not actually defined
#define A_MACRO(A, B, C, ...) \
      (void)RESTRICT_ARGS_COUNT(0, 3, A_MACRO, ##__VA_ARGS__); \
      int a = A; \
      int b = B; \
      int c = C;
#endif
//
// Note that RESTRICT_ARGS_COUNT can also be invoked wherever one of the macro
// arguments is used, e.g.
//
#if 0 // This is just so that B_MACRO is not actually defined
#define B_MACRO(A, B, C, ...)
int array[] = { A, B, RESTRICT_ARGS_COUNT(C, 3, B_MACRO, ##__VA_ARGS__) };
#endif
//
#ifdef __clang__
// Clang does not allow temporaries of anonymous structs as they are used
// in the below definition of RESTRICT_ARGS_COUNT as accepted by gcc
// (due to a language extension,
// see https://gcc.gnu.org/onlinedocs/gcc/Compound-Literals.html)
//
// As there is currently no other known workaround available that would allow
// us to sneak a static_assert (unfortunately a statement rather
// than an expression) into the initializer list of a constexpr array,
// like the keymap.
//
// Thus, we have to disable this feature for clang builds until
// a solution becomes available.
//
#define RESTRICT_ARGS_COUNT(B,                                                 \
                            NUM_EXPECTED_ARGS,                                 \
                            ORIGINAL_MACRO,                                    \
                            ...)                                               \
   B

#else
#define RESTRICT_ARGS_COUNT(B,                                                 \
                            NUM_EXPECTED_ARGS,                                 \
                            ORIGINAL_MACRO,                                    \
                            ...)                                               \
  ((struct {                                                                __NL__ \
       /* Here we are in the body of a anonymous struct.                 */ __NL__ \
       /* It is only used to hold the static_assert that cannot be       */ __NL__ \
       /* defined directly in the keymap initializer list. By using the  */ __NL__ \
       /* comma operator ((A, B) always evaluates to b), we ensure       */ __NL__ \
       /* that not the temporary struct but B is what ASSERT_ARGS_COUNT  */ __NL__ \
       /* finally evaluates to.                                          */ __NL__ \
       /* Please note that passing B through this macro is a must        */ __NL__ \
       /* as we need it for the comma operator to work.                  */ __NL__ \
   static_assert(sizeof(const char) == sizeof(#__VA_ARGS__ ),               __NL__ \
        /* sizeof(const char) == sizeof(#__VA_ARGS__ ) checks the quoted */ __NL__ \
        /* list of additional arguments. If there are none, then the     */ __NL__ \
        /* length of #__VA_ARGS__ is a single char as it contains '\0'.  */ __NL__ \
        /* This check is not able to find the corner case of a single    */ __NL__ \
        /* superfluous comma at the end of the macro arguments as this   */ __NL__ \
        /* causes #__VA_ARGS__ being empty (only '\0').                  */ __NL__ \
     VERBOSE_STATIC_ASSERT_HEADER                                           __NL__ \
                                                                            __NL__ \
     VERBOSE_FILE_INFO                                                      __NL__ \
     VERBOSE_LINE_INFO                                                      __NL__ \
     "\n"                                                                   __NL__ \
     "\nStrange arguments found in invocation of " #ORIGINAL_MACRO "."      __NL__ \
     "\n"                                                                   __NL__ \
     "\nPlease make sure to pass exactly " #NUM_EXPECTED_ARGS               __NL__ \
                                          " macro arguments to"             __NL__ \
     "\n" #ORIGINAL_MACRO ". Also make sure that there are no dangling"     __NL__ \
     "\ncommas at the end of the argument list."                            __NL__ \
     "\n"                                                                   __NL__ \
     "\nThis is the superfluous part at the end of the macro"               __NL__ \
     "\narguments list: \'" #__VA_ARGS__ "\'"                               __NL__ \
                                                                            __NL__ \
     VERBOSE_STATIC_ASSERT_FOOTER                                           __NL__ \
   );                                                                       __NL__ \
                                                                            __NL__ \
   }){}, /* End of dummy struct, the comma operator's A operand. */         __NL__ \
   B     /* The overall ASSERT_ARGS_COUNT evaluates to B. */                __NL__ \
   )
#endif

/* Count the args in a list */
#define NUM_ARGS(...)  (sizeof((int[])__VA_ARGS__)/sizeof(int))

// Macro MAKE_TEMPLATE_SIGNATURE(...) wraps arguments 2..last in a template
// signature like 'template<ARG2, ARG3, ...>' only if it is passed more
// than one argument. Otherwise it generates an empty string.
//
#define MAKE_TEMPLATE_SIGNATURE(UNUSED, ...)                                   \
   SELECT_ON_EMPTY_SIGNATURE(MAKE_TEMPLATE_SIGNATURE_, UNUSED,##__VA_ARGS__)
#define MAKE_TEMPLATE_SIGNATURE_0(...)
#define MAKE_TEMPLATE_SIGNATURE_1(...) template<__VA_ARGS__>

// Macro ADD_TEMPLATE_BRACES(...) wraps arguments 2..last in angle brackets
// only if it is passed more than one argument. Otherwise it generates an
// empty string.
//
#define ADD_TEMPLATE_BRACES(UNUSED, ...)                                       \
   SELECT_ON_EMPTY_SIGNATURE(ADD_TEMPLATE_BRACES_, UNUSED,##__VA_ARGS__)
#define ADD_TEMPLATE_BRACES_0(...)
#define ADD_TEMPLATE_BRACES_1(...) <__VA_ARGS__>

// Macro TEMPLATE_KEYWORD(...) generates the 'template' keyword only if it is
// passed more than one argument.
//
#define TEMPLATE_KEYWORD(UNUSED, ...)                                          \
   SELECT_ON_EMPTY_SIGNATURE(TEMPLATE_KEYWORD_, UNUSED,##__VA_ARGS__)
#define TEMPLATE_KEYWORD_0(...)
#define TEMPLATE_KEYWORD_1(...) template

// Helper macros for template parameter list treatment

#define GLUE2_AUX(...) GLUE2(__VA_ARGS__)

#define HAS_MORE_THAN_2_ARGS_1(UNUSED, A, B, C, D,                             \
                                       E, F, G, H,                             \
                                       I, J, K, L,                             \
                                       M, N, O, P,                             \
                                       Q, ...) Q
#define HAS_MORE_THAN_2_ARGS(...) HAS_MORE_THAN_2_ARGS_1(__VA_ARGS__)
#define CHOICE(UNUSED, ...) ,##__VA_ARGS__, 1, 1, 1, 1,                        \
                                            1, 1, 1, 1,                        \
                                            1, 1, 1, 1,                        \
                                            1, 1, 1, 1,                        \
                                            0
#define SELECT_ON_EMPTY_SIGNATURE(MACRO_BASE_NAME, UNUSED, ...)                \
   GLUE2_AUX(                                                                  \
      MACRO_BASE_NAME,                                                         \
      HAS_MORE_THAN_2_ARGS(CHOICE(1,##__VA_ARGS__))                            \
   )(__VA_ARGS__)
