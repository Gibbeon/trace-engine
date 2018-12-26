//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently.

#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers.
#endif

// check macros for mingw
#include <sal.h>
#ifndef _Out_writes_bytes_opt_
#define _Out_writes_bytes_opt_(s)
#endif
#ifndef _Inout_opt_bytecount_
#define _Inout_opt_bytecount_(s)
#endif
#ifndef _Pre_null_
#define _Pre_null_
#endif

#ifndef _COM_Outptr_opt_
#define _COM_Outptr_opt_
#endif
#ifndef _COM_Outptr_
#define _COM_Outptr_
#endif
#ifndef _In_range_
#define _In_range_(...)
#endif
#ifndef _Inout_updates_bytes_
#define _Inout_updates_bytes_(s)
#endif
#ifndef _Outptr_result_bytebuffer_
#define _Outptr_result_bytebuffer_(s)
#endif
#ifndef _In_reads_bytes_opt_
#define _In_reads_bytes_opt_(s)
#endif
#ifndef _In_reads_opt_
#define _In_reads_opt_(s)
#endif
#ifndef _In_reads_bytes_
#define _In_reads_bytes_(s)
#endif
#ifndef _Out_writes_bytes_
#define _Out_writes_bytes_(s)
#endif
#ifndef _In_reads_
#define _In_reads_(s)
#endif
#ifndef _Out_writes_
#define _Out_writes_(s)
#endif
#ifndef _Out_opt_
#define _Out_opt_
#endif
#ifndef _Inout_opt_
#define _Inout_opt_
#endif
#ifndef _Out_writes_opt_
#define _Out_writes_opt_(s)
#endif
#ifndef _Outptr_result_maybenull_
#define _Outptr_result_maybenull_
#endif
#ifndef _Outptr_opt_result_maybenull_
#define _Outptr_opt_result_maybenull_
#endif
#ifndef _Field_size_
#define _Field_size_(s)
#endif
#ifndef _Field_size_opt_
#define _Field_size_opt_(s)
#endif
#ifndef _Outptr_
#define _Outptr_
#endif
#ifndef _In_opt_z_
#define _In_opt_z_
#endif
#ifndef _Reserved_
#define _Reserved_
#endif
#ifndef __reserved
#define __reserved
#endif
#ifndef __in_ecount
#define __in_ecount(s)
#endif
#ifndef __in_bcount
#define __in_bcount(s)
#endif
#ifndef __out_bcount
#define __out_bcount(s)
#endif
#ifndef __out_ecount
#define __out_ecount(s)
#endif
#ifndef __in_ecount_opt
#define __in_ecount_opt(s)
#endif
#ifndef __inout
#define __inout
#endif
#ifndef __in_opt
#define __in_opt
#endif
#ifndef __deref_out
#define __deref_out
#endif
// conflict with stl vars
#ifndef __in
//#define __in
#endif
#ifndef __out
//#define __out
#endif



#include  <stdio.h>

#include <windows.h>
#include <InitGuid.h>
#include <d3d12.h>
#include <stdio.h>
#include <stdexcept>
#include <dxgi1_4.h>
//#include <D3Dcompiler.h>
//#include <DirectXMath.h>
//#include "d3dx12.h"

#include <string>
//#include <wrl.h>
#include <shellapi.h>

#ifndef _countof
#define _countof(array) (sizeof(array) / sizeof(array[0]))
#endif
#ifndef SIZE_MAX
#define SIZE_MAX 0xFFFFFFFF
#endif