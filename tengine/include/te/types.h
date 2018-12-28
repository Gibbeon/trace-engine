#pragma once

template <typename TType = void>
class ptr_t {
public:
    ptr_t(TType* ptr = nullptr) { m_ptr = ptr; }    
    ptr_t(ptr_t<TType>& ptr) { m_ptr = ptr.ptr(); }

    TType* ptr() { return m_ptr; }

    operator TType*() const { return ptr(); }
    operator TType*() { return ptr(); }

    TType* operator->() { return ptr(); }

    ptr_t<TType>& operator=(TType* other) { m_ptr = other;  return *this;}
    ptr_t<TType>& operator=(std::nullptr_t other) { m_ptr = other; return *this; }

    template <typename TOtherType>
    TOtherType* As() { return reinterpret_cast<TOtherType*>(m_ptr); }

private:
    TType* m_ptr;
};

template<typename TType>
using out_ptr_t = TType**;

typedef unsigned long long u64;
typedef signed long long s64;

typedef unsigned long u32;
typedef signed long s32;

typedef unsigned short u16;
typedef signed short s16;

typedef unsigned char u8;
typedef signed char s8;

typedef unsigned char ubyte;
typedef signed char sbyte;

typedef float single;
typedef long double triple;

typedef bool bool_t;

typedef double real_t;
typedef char char_t;
typedef const char_t* string_t;

typedef s32 int_t;
typedef s64 long_t;
typedef u32 uint_t;
typedef u64 ulong_t;

typedef void (*Action)();

template <class TResult>
struct FuncType
{
    typedef TResult (*Func)();
};

struct Vec3
{

    float x,y,z;
};

struct Color
{
    float r,g,b,a;
};

struct Vertex
{
    Vec3 position;
    Color color;
};