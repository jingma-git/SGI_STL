#pragma once
// macros for different compilers
#ifdef __GNUC__
#if __GNUC__ >= 2
#define _MJ_CLASS_PARTIAL_SPECIALIZATION // class template partial specialization
#endif
#endif

#if defined(_MJ_CLASS_PARTIAL_SPECIALIZATION)
#define _MJ_TEMPLATE_NULL template <>
#else
#define _MJ_TEMPLATE_NULL template
#endif