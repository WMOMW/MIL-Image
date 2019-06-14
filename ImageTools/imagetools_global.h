#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(IMAGETOOLS_LIB)
#  define IMAGETOOLS_EXPORT Q_DECL_EXPORT
# else
#  define IMAGETOOLS_EXPORT Q_DECL_IMPORT
# endif
#else
# define IMAGETOOLS_EXPORT
#endif
