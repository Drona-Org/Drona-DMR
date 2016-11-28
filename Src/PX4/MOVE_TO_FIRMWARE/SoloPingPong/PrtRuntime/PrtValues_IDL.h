

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0613 */
/* at Mon Jan 18 19:14:07 2038
 */
/* Compiler settings for ..\API\PrtValues_IDL.idl:
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


#ifndef __PrtValues_IDL_h__
#define __PrtValues_IDL_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

/* header files for imported files */
#include "PrtTypes_IDL.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __PrtValues_IDL_INTERFACE_DEFINED__
#define __PrtValues_IDL_INTERFACE_DEFINED__

/* interface PrtValues_IDL */
/* [full][version][uuid] */ 

typedef 
enum PRT_SPECIAL_EVENT
    {
        PRT_SPECIAL_EVENT_NULL	= 0,
        PRT_SPECIAL_EVENT_HALT	= 1
    } 	PRT_SPECIAL_EVENT;

typedef 
enum PRT_VALUE_KIND
    {
        PRT_VALKIND_NULL	= 0,
        PRT_VALKIND_BOOL	= 1,
        PRT_VALKIND_INT	= 2,
        PRT_VALKIND_EVENT	= 3,
        PRT_VALKIND_MID	= 4,
        PRT_VALKIND_FORGN	= 5,
        PRT_VALKIND_TUPLE	= 6,
        PRT_VALKIND_SEQ	= 7,
        PRT_VALKIND_MAP	= 8,
        PRT_VALUE_KIND_COUNT	= 9
    } 	PRT_VALUE_KIND;

typedef struct PRT_VALUE
    {
    struct 
        {
        PRT_VALUE_KIND discriminator;
        /* [switch_is] */ /* [switch_type] */ union __MIDL_PrtValues_IDL_0002
            {
            /* [case()] */ PRT_UINT32 dummy_1;
            /* [case()] */ PRT_BOOLEAN bl;
            /* [case()] */ PRT_INT32 nt;
            /* [case()] */ PRT_UINT32 ev;
            /* [case()][unique] */ struct PRT_MACHINEID *mid;
            /* [case()][unique] */ struct PRT_FORGNVALUE *frgn;
            /* [case()][unique] */ struct PRT_TUPVALUE *tuple;
            /* [case()][unique] */ struct PRT_SEQVALUE *seq;
            /* [case()][unique] */ struct PRT_MAPVALUE *map;
            } 	valueUnion;
        } 	;
    } 	PRT_VALUE;

typedef struct PRT_MACHINEID
    {
    PRT_GUID processId;
    PRT_UINT32 machineId;
    } 	PRT_MACHINEID;

typedef struct PRT_VALUE_NODE
    {
    PRT_VALUE *value;
    struct PRT_VALUE_NODE *nextNode;
    } 	PRT_VALUE_NODE;

typedef struct PRT_TUPVALUE
    {
    PRT_UINT32 size;
    PRT_VALUE **values;
    PRT_VALUE_NODE *valuesSerialized;
    } 	PRT_TUPVALUE;

typedef struct PRT_SEQVALUE
    {
    PRT_UINT32 size;
    PRT_UINT32 capacity;
    PRT_VALUE **values;
    PRT_VALUE_NODE *valuesSerialized;
    } 	PRT_SEQVALUE;

typedef struct PRT_MAPVALUE
    {
    PRT_UINT32 size;
    PRT_UINT32 capNum;
    struct PRT_MAPNODE *first;
    struct PRT_MAPNODE *last;
    struct PRT_MAPNODE **buckets;
    } 	PRT_MAPVALUE;

typedef struct PRT_MAPNODE
    {
    PRT_VALUE *key;
    PRT_VALUE *value;
    struct PRT_MAPNODE *bucketNext;
    struct PRT_MAPNODE *insertNext;
    struct PRT_MAPNODE *insertPrev;
    } 	PRT_MAPNODE;

typedef struct PRT_FORGNVALUE
    {
    PRT_UINT16 typeTag;
    PRT_UINT64 value;
    } 	PRT_FORGNVALUE;



extern RPC_IF_HANDLE c_PrtValues_IDL_v1_0_c_ifspec;
extern RPC_IF_HANDLE PrtValues_IDL_v1_0_c_ifspec;
extern RPC_IF_HANDLE s_PrtValues_IDL_v1_0_s_ifspec;
#endif /* __PrtValues_IDL_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


