#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(TRAININGTOOLS_LIB)
#  define TRAININGTOOLS_EXPORT Q_DECL_EXPORT
# else
#  define TRAININGTOOLS_EXPORT Q_DECL_IMPORT
# endif
#else
# define TRAININGTOOLS_EXPORT
#endif
