/**
 * @file Compiler.h
 * @author Mark & May
 * @brief This is the user interface for the compiler
 * @version 1.0.0
 * @date 2020-04-25
 * 
 * SPECIFICATION(S) : Compiler Abstraction, AUTOSAR Release 4.3.1
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef COMPILER_H
#define COMPILER_H
#include "Compiler_Cfg.h"

/* For Automatic Type */
#define AUTOMATIC
/* For Defined Data Types */
#define TYPEDEF
/* Null Pointer */
#define NULL_PTR                                        ((void*)0)
/* Inline */
#define INLINE                                          inline
/* Local Inline */
#define LOCAL_INLINE                                    static inline

/**
 * @brief A function Difinition
 * 
 * @param rettype The return type of the function
 * @param memclass The memory class
 *              @arg far
 *              @arg near
 * 
 */
#define FUNC(rettype, memclass)                         rettype

/**
 * @brief A Function that returns a pointer to a constant
 * @param rettype The return type of the function
 * @param ptrclass The pointer class
 *              @arg far
 *              @arg near
 * @param memclass The memory class
 *              @arg far
 *              @arg near
 */
#define FUNC_P2CONST(rettype, ptrclass, memclass)       const rettype *

/**
 * @brief A Function that returns a pointer to a variable
 * @param rettype The return type of the function
 * @param ptrclass The pointer class
 *              @arg far
 *              @arg near
 * @param memclass The memory class
 *              @arg far
 *              @arg near
 */
#define FUNC_P2VAR(rettype, ptrclass, memclass)         rettype * 

/**
 * @brief A pointer to a variable
 * @param ptrtype The type of the pointer
 * @param ptrclass The pointer class
 *              @arg far
 *              @arg near
 * @param memclass The memory class
 *              @arg far
 *              @arg near
 */
#define P2VAR(ptrtype, memclass, ptrclass)              ptrtype *

/**
 * @brief A pointer to a constant variable
 * @param ptrtype The type of the pointer
 * @param ptrclass The pointer class
 *              @arg far
 *              @arg near
 * @param memclass The memory class
 *              @arg far
 *              @arg near
 */
#define P2CONST(ptrtype, memclass, ptrclass)            const ptrtype *

/**
 * @brief A constant pointer to a variable
 * @param ptrtype The type of the pointer
 * @param ptrclass The pointer class
 *              @arg far
 *              @arg near
 * @param memclass The memory class
 *              @arg far
 *              @arg near
 */
#define CONSTP2VAR(ptrtype, memclass, ptrclass)         ptrtype * const 

/**
 * @brief A constant pointer to a constant variable
 * @param ptrtype The type of the pointer
 * @param ptrclass The pointer class
 *              @arg far
 *              @arg near
 * @param memclass The memory class
 *              @arg far
 *              @arg near
 */
#define CONSTP2CONST(ptrtype, memclass, ptrclass)       const ptrtype * const 

/**
 * @brief A pointer to a function
 * @param rettype The return type of the function
 * @param ptrclass The pointer class
 *              @arg far
 *              @arg near
 * @param fctname the function name
 */
#define P2FUNC(rettype, ptrclass, fctname)              rettype (*funcname)

/**
 * @brief A constant pointer to a function
 * @param rettype The return type of the function
 * @param ptrclass The pointer class
 *              @arg far
 *              @arg near
 * @param fctname the function name
 */
#define CONSTP2FUNC(rettype, ptrclass, fctname)         rettype (* const funcname)

/**
 * @brief A constant variable
 * @param consttype the type of the constant variable
 * @param memclass The memory class
 *              @arg far
 *              @arg near
 */
#define CONST(consttype, memclass)                      const consttype 

/**
 * @brief A variable
 * @param vartype the type of the variable
 * @param memclass The memory class
 *              @arg far
 *              @arg near
 */
#define VAR(vartype, memclass)                          vartype

#endif