/****************************************************************************
**  FougTools
**  Copyright Fougue (30 Mar. 2015)
**  contact@fougue.pro
**
** This software is a computer program whose purpose is to provide utility
** tools for the C++ language and the Qt toolkit.
**
** This software is governed by the CeCILL-C license under French law and
** abiding by the rules of distribution of free software.  You can  use,
** modify and/ or redistribute the software under the terms of the CeCILL-C
** license as circulated by CEA, CNRS and INRIA at the following URL
** "http://www.cecill.info".
****************************************************************************/

#pragma once

#include "core.h"
#include <QtCore/QtPlugin>

#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
# define Q_PLUGIN_METADATA(def)
# define QTTOOLS_QT4_EXPORT_PLUGIN2(target, className)  Q_EXPORT_PLUGIN2(target, className)
#else
# define QTTOOLS_QT4_EXPORT_PLUGIN2(target, className)
#endif
