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

#include "runtime_error.h"

namespace qtcore {

/*!
 * \class RuntimeError
 * \brief Provides a std::runtime_error that can convey a QString error message
 * \headerfile runtime_error.h <qttools/core/runtime_error.h>
 * \ingroup qttools_core
 */

RuntimeError::RuntimeError(const QString& err)
    : std::runtime_error(err.toStdString()),
      m_err(err)
{
}

RuntimeError::~RuntimeError() throw()
{
}

QString RuntimeError::message() const
{
    return m_err;
}

} // namespace qtcore
