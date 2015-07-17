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

#include "script.h"
#include <QtScript/QScriptEngine>

namespace qtscript {

class QTTOOLS_SCRIPT_EXPORT Calculator
{
public:
    Calculator();

    void evaluate(const QString& program);
    bool hasResult() const;
    QString lastErrorText() const;

    double lastResult() const;
    QString lastResultText() const;

private:
    QScriptEngine m_scriptEngine;
    QScriptValue m_lastResult;
};

} // namespace qtscript
