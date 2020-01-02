#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(RGRAPHICSLIB_LIB)
#  define RGRAPHICSLIB_EXPORT Q_DECL_EXPORT
# else
#  define RGRAPHICSLIB_EXPORT Q_DECL_IMPORT
# endif
#else
# define RGRAPHICSLIB_EXPORT
#endif
