#pragma once

#ifndef _MSC_VER
#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif
#define _WIN32_WINNT 0x0A00
#endif

#include <stdint.h>

// Used for some refcounted COM objects that need to be released.
#define SAFE_RELEASE(p)   { if (p) { (p)->Release(); (p) = nullptr; } }

#include <d3d8.h>

// Declare __uuidof for D3D8 interfaces
#ifdef __CRT_UUID_DECL
__CRT_UUID_DECL(IDirect3D8,              0x1DD9E8DA,0x1C77,0x4D40,0xB0,0xCF,0x98,0xFE,0xFD,0xFF,0x95,0x12);
__CRT_UUID_DECL(IDirect3DDevice8,        0x7385E5DF,0x8FE8,0x41D5,0x86,0xB6,0xD7,0xB4,0x85,0x47,0xB6,0xCF);
__CRT_UUID_DECL(IDirect3DResource8,      0x1B36BB7B,0x09B7,0x410A,0xB4,0x45,0x7D,0x14,0x30,0xD7,0xB3,0x3F);
__CRT_UUID_DECL(IDirect3DVertexBuffer8,  0x8AEEEAC7,0x05F9,0x44D4,0xB5,0x91,0x00,0x0B,0x0D,0xF1,0xCB,0x95);
__CRT_UUID_DECL(IDirect3DVolume8,        0xBD7349F5,0x14F1,0x42E4,0x9C,0x79,0x97,0x23,0x80,0xDB,0x40,0xC0);
__CRT_UUID_DECL(IDirect3DSwapChain8,     0x928C088B,0x76B9,0x4C6B,0xA5,0x36,0xA5,0x90,0x85,0x38,0x76,0xCD);
__CRT_UUID_DECL(IDirect3DSurface8,       0xB96EEBCA,0xB326,0x4EA5,0x88,0x2F,0x2F,0xF5,0xBA,0xE0,0x21,0xDD);
__CRT_UUID_DECL(IDirect3DIndexBuffer8,   0x0E689C9A,0x053D,0x44A0,0x9D,0x92,0xDB,0x0E,0x3D,0x75,0x0F,0x86);
__CRT_UUID_DECL(IDirect3DBaseTexture8,   0xB4211CFA,0x51B9,0x4A9F,0xAB,0x78,0xDB,0x99,0xB2,0xBB,0x67,0x8E);
__CRT_UUID_DECL(IDirect3DTexture8,       0xE4CDD575,0x2866,0x4F01,0xB1,0x2E,0x7E,0xEC,0xE1,0xEC,0x93,0x58);
__CRT_UUID_DECL(IDirect3DCubeTexture8,   0x3EE5B968,0x2ACA,0x4C34,0x8B,0xB5,0x7E,0x0C,0x3D,0x19,0xB7,0x50);
__CRT_UUID_DECL(IDirect3DVolumeTexture8, 0x4B8AAAFA,0x140F,0x42BA,0x91,0x31,0x59,0x7E,0xAF,0xAA,0x2E,0xAD);
#endif

// Undefine D3D8 macros //
#undef DIRECT3D_VERSION
#undef D3D_SDK_VERSION

#undef D3DCS_ALL            // parentheses added in DX9
#undef D3DFVF_POSITION_MASK // changed from 0x00E to 0x400E in DX9
#undef D3DFVF_RESERVED2     // reduced from 4 to 2 in DX9

#undef D3DSP_REGNUM_MASK    // changed from 0x00000FFF to 0x000007FF in DX9


#if defined(__MINGW32__) || defined(__GNUC__)

// Avoid redundant definitions (add D3D*_DEFINED macros here) //
#define D3DRECT_DEFINED
#define D3DMATRIX_DEFINED

// Temporarily override __CRT_UUID_DECL to allow usage in d3d9 namespace
#pragma push_macro("__CRT_UUID_DECL")
#ifdef __CRT_UUID_DECL
#undef __CRT_UUID_DECL
#endif

#ifdef __MINGW32__
#define __CRT_UUID_DECL(type,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)         \
}                                                                     \
    extern "C++" {                                                    \
    template<> struct __mingw_uuidof_s<d3d9::type> {                  \
        static constexpr IID __uuid_inst = {                          \
            l,w1,w2, {b1,b2,b3,b4,b5,b6,b7,b8}                        \
        };                                                            \
    };                                                                \
    template<> constexpr const GUID &__mingw_uuidof<d3d9::type>() {   \
        return __mingw_uuidof_s<d3d9::type>::__uuid_inst;             \
    }                                                                 \
    template<> constexpr const GUID &__mingw_uuidof<d3d9::type*>() {  \
        return  __mingw_uuidof_s<d3d9::type>::__uuid_inst;            \
    }                                                                 \
    }                                                                 \
namespace d3d9 {

#elif defined(__GNUC__)
#define __CRT_UUID_DECL(type, a, b, c, d, e, f, g, h, i, j, k) \
}                                                                                                                               \
  extern "C++" { template <> constexpr GUID __uuidof_helper<d3d9::type>() { return GUID{a,b,c,{d,e,f,g,h,i,j,k}}; } }           \
  extern "C++" { template <> constexpr GUID __uuidof_helper<d3d9::type*>() { return __uuidof_helper<d3d9::type>(); } }          \
  extern "C++" { template <> constexpr GUID __uuidof_helper<const d3d9::type*>() { return __uuidof_helper<d3d9::type>(); } }    \
  extern "C++" { template <> constexpr GUID __uuidof_helper<d3d9::type&>() { return __uuidof_helper<d3d9::type>(); } }          \
  extern "C++" { template <> constexpr GUID __uuidof_helper<const d3d9::type&>() { return __uuidof_helper<d3d9::type>(); } }    \
namespace d3d9 {
#endif

#endif // defined(__MINGW32__) || defined(__GNUC__)


/**
* \brief Direct3D 9
* 
* All D3D9 interfaces are included within
* a namespace, so as not to collide with
* D3D8 interfaces.
*/
namespace d3d9 {
#include <d3d9.h>
}

// Indicates d3d9:: namespace is in-use.
#define DXVK_D3D9_NAMESPACE

#if defined(__MINGW32__) || defined(__GNUC__)
#pragma pop_macro("__CRT_UUID_DECL")
#endif

//for some reason we need to specify __declspec(dllexport) for MinGW
#if defined(__WINE__)
#define DLLEXPORT __attribute__((visibility("default")))
#else
#define DLLEXPORT
#endif


#include "../util/com/com_guid.h"
#include "../util/com/com_object.h"
#include "../util/com/com_pointer.h"

#include "../util/log/log.h"
#include "../util/log/log_debug.h"

#include "../util/rc/util_rc.h"
#include "../util/rc/util_rc_ptr.h"

#include "../util/sync/sync_recursive.h"

#include "../util/util_env.h"
#include "../util/util_enum.h"
#include "../util/util_error.h"
#include "../util/util_flags.h"
#include "../util/util_likely.h"
#include "../util/util_math.h"
#include "../util/util_misc.h"
#include "../util/util_string.h"

// Missed definitions in Wine/MinGW.

#ifndef D3DPRESENT_BACK_BUFFERS_MAX_EX
#define D3DPRESENT_BACK_BUFFERS_MAX_EX 30
#endif

#ifndef D3DSI_OPCODE_MASK
#define D3DSI_OPCODE_MASK 0x0000FFFF
#endif

#ifndef D3DSP_TEXTURETYPE_MASK
#define D3DSP_TEXTURETYPE_MASK 0x78000000
#endif

#ifndef D3DUSAGE_AUTOGENMIPMAP
#define D3DUSAGE_AUTOGENMIPMAP 0x00000400L
#endif

#ifndef D3DSP_DCL_USAGE_MASK
#define D3DSP_DCL_USAGE_MASK 0x0000000f
#endif

#ifndef D3DSP_OPCODESPECIFICCONTROL_MASK
#define D3DSP_OPCODESPECIFICCONTROL_MASK 0x00ff0000
#endif

#ifndef D3DSP_OPCODESPECIFICCONTROL_SHIFT
#define D3DSP_OPCODESPECIFICCONTROL_SHIFT 16
#endif

#ifndef D3DCURSOR_IMMEDIATE_UPDATE
#define D3DCURSOR_IMMEDIATE_UPDATE             0x00000001L
#endif

#ifndef D3DPRESENT_FORCEIMMEDIATE
#define D3DPRESENT_FORCEIMMEDIATE              0x00000100L
#endif

// From d3dtypes.h

#ifndef D3DDEVINFOID_TEXTUREMANAGER
#define D3DDEVINFOID_TEXTUREMANAGER    1
#endif

#ifndef D3DDEVINFOID_D3DTEXTUREMANAGER
#define D3DDEVINFOID_D3DTEXTUREMANAGER 2
#endif

#ifndef D3DDEVINFOID_TEXTURING
#define D3DDEVINFOID_TEXTURING         3
#endif

// From d3dhal.h

#ifndef D3DDEVINFOID_VCACHE
#define D3DDEVINFOID_VCACHE            4
#endif

// MinGW headers are broken. Who'dve guessed?
#ifndef _MSC_VER

// Missing from d3d8types.h
#ifndef D3DDEVINFOID_RESOURCEMANAGER
#define D3DDEVINFOID_RESOURCEMANAGER    5
#endif

#ifndef D3DDEVINFOID_VERTEXSTATS
#define D3DDEVINFOID_VERTEXSTATS        6			// Aka D3DDEVINFOID_D3DVERTEXSTATS
#endif

#ifndef __WINE__
extern "C" WINUSERAPI WINBOOL WINAPI SetProcessDPIAware(VOID);
#endif
#endif

// This is the managed pool on D3D9Ex, it's just hidden!
#define D3DPOOL_MANAGED_EX D3DPOOL(6)

//using D3D9VertexElements = std::vector<D3DVERTEXELEMENT9>;
