

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0613 */
/* at Mon Jan 18 19:14:07 2038
 */
/* Compiler settings for ..\API\PrtTypes_IDL.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.00.0613 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */


#ifndef __PrtTypes_IDL_h__
#define __PrtTypes_IDL_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

/* header files for imported files */
#include "PrtBaseTypes_IDL.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __PrtTypes_IDL_INTERFACE_DEFINED__
#define __PrtTypes_IDL_INTERFACE_DEFINED__

/* interface PrtTypes_IDL */
/* [full][version][uuid] */ 

typedef struct PRT_GUID
    {
    PRT_UINT32 data1;
    PRT_UINT16 data2;
    PRT_UINT16 data3;
    PRT_UINT64 data4;
    } 	PRT_GUID;

typedef 
enum PRT_TYPE_KIND
    {
        PRT_KIND_ANY	= 0,
        PRT_KIND_BOOL	= 1,
        PRT_KIND_EVENT	= 2,
        PRT_KIND_FORGN	= 3,
        PRT_KIND_MACHINE	= 4,
        PRT_KIND_INT	= 5,
        PRT_KIND_MAP	= 6,
        PRT_KIND_NMDTUP	= 7,
        PRT_KIND_NULL	= 8,
        PRT_KIND_SEQ	= 9,
        PRT_KIND_TUPLE	= 10,
        PRT_TYPE_KIND_COUNT	= 11,
        PRT_TYPE_KIND_CANARY	= 0xff
    } 	PRT_TYPE_KIND;

typedef struct PRT_TYPE
    {
    PRT_TYPE_KIND typeKind;
    /* [switch_is] */ /* [switch_type] */ union __MIDL_PrtTypes_IDL_0001
        {
        /* [case()] */ struct PRT_MAPTYPE *map;
        /* [case()] */ PRT_UINT32 *dummy_1;
        /* [case()] */ PRT_UINT32 *dummy_2;
        /* [case()] */ PRT_UINT32 *dummy_3;
        /* [case()] */ PRT_UINT32 *dummy_4;
        /* [case()] */ PRT_UINT32 *dummy_5;
        /* [case()] */ PRT_UINT32 *dummy_6;
        /* [case()] */ PRT_UINT16 typeTag;
        /* [case()] */ struct PRT_NMDTUPTYPE *nmTuple;
        /* [case()] */ struct PRT_SEQTYPE *seq;
        /* [case()] */ struct PRT_TUPTYPE *tuple;
        } 	typeUnion;
    } 	PRT_TYPE;

typedef struct PRT_MAPTYPE
    {
    PRT_TYPE *domType;
    PRT_TYPE *codType;
    } 	PRT_MAPTYPE;

typedef struct PRT_TYPE_NODE
    {
    PRT_TYPE *type;
    struct PRT_TYPE_NODE *nextNode;
    } 	PRT_TYPE_NODE;

typedef struct PRT_STRING_NODE
    {
    PRT_STRING name;
    struct PRT_STRING_NODE *nextNode;
    } 	PRT_STRING_NODE;

typedef struct PRT_NMDTUPTYPE
    {
    PRT_UINT32 arity;
    PRT_STRING *fieldNames;
    PRT_TYPE **fieldTypes;
    PRT_TYPE_NODE *fieldTypesSerialized;
    PRT_STRING_NODE *fieldNamesSerialized;
    } 	PRT_NMDTUPTYPE;

typedef struct PRT_SEQTYPE
    {
    PRT_TYPE *innerType;
    } 	PRT_SEQTYPE;

typedef struct PRT_TUPTYPE
    {
    PRT_UINT32 arity;
    PRT_TYPE **fieldTypes;
    PRT_TYPE_NODE *fieldTypesSerialized;
    } 	PRT_TUPTYPE;

typedef struct PRT_FORGNTYPE
    {
    int __dummy;
    } 	PRT_FORGNTYPE;



extern RPC_IF_HANDLE c_PrtTypes_IDL_v1_0_c_ifspec;
extern RPC_IF_HANDLE PrtTypes_IDL_v1_0_c_ifspec;
extern RPC_IF_HANDLE s_PrtTypes_IDL_v1_0_s_ifspec;
#endif /* __PrtTypes_IDL_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


