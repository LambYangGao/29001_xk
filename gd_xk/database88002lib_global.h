#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(DATABASE88002_LIB)
#  define DATABASE88002_EXPORT Q_DECL_EXPORT
# else
#  define DATABASE88002_EXPORT Q_DECL_IMPORT
# endif
#else
# define DATABASE88002_EXPORT
#endif
