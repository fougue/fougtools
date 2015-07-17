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

#include "calculator.h"

namespace qtscript {

/*!
 * \class Calculator
 * \brief Provides evaluation of expressions
 *
 * \note Author of the evaluation script is Yves Bailly (kafka DOT fr AT laposte DOT net)
 *
 * \headerfile calculator.h <qttools/script/calculator.h>
 * \ingroup qttools_script
 */

Calculator::Calculator()
    : m_lastResult(0)
{
    m_scriptEngine.evaluate(
                "var PI = Math.PI\n"
                "var RAD_TO_DEG = 180.0/PI\n"
                "var DEG_TO_RAD = PI/180.0\n"
                "function round_int(x)\n"
                "{ \n"
                "  if (Math.abs(Math.round(x)-x) < 1.0E-5)\n"
                "  {\n"
                "    return Math.round(x);"
                "  }\n"
                "  else\n"
                "  {\n"
                "    return x;"
                "  }\n"
                "}\n"
                "var abs    = new Function(\"x\", \"return round_int(Math.abs(x))\")\n"
                "var acos   = new Function(\"x\", \"return round_int(Math.acos(x))\")\n"
                "var asin   = new Function(\"x\", \"return round_int(Math.asin(x))\")\n"
                "var atan   = new Function(\"x\", \"return round_int(Math.atan(x))\")\n"
                "var atan2  = new Function(\"y\", \"x\", \"return round_int(Math.atan2(y, x))\")\n"
                "var ceil   = new Function(\"x\", \"return round_int(Math.ceil(x))\")\n"
                "var cos    = new Function(\"x\", \"return round_int(Math.cos(x))\")\n"
                "var exp    = new Function(\"x\", \"return round_int(Math.exp(x))\")\n"
                "var floor  = new Function(\"x\", \"return round_int(Math.floor(x))\")\n"
                "var log    = new Function(\"x\", \"return round_int(Math.log(x))\")\n"
                "var pow    = new Function(\"x\", \"y\", \"return round_int(Math.pow(x, y))\")\n"
                "var random = new Function(\"return Math.random()\")\n"
                "var round  = new Function(\"x\", \"return Math.round(x)\")\n"
                "var sin    = new Function(\"x\", \"return round_int(Math.sin(x))\")\n"
                "var sqrt   = new Function(\"x\", \"return round_int(Math.sqrt(x))\")\n"
                "var tan    = new Function(\"x\", \"return round_int(Math.tan(x))\")\n"
                );
}

void Calculator::evaluate(const QString& program)
{
    m_lastResult = m_scriptEngine.evaluate(program);
}

bool Calculator::hasResult() const
{
    return
            !m_scriptEngine.hasUncaughtException()
            && (m_lastResult.isNumber() || m_lastResult.isString());
}

QString Calculator::lastErrorText() const
{
    if (m_scriptEngine.hasUncaughtException())
        return m_scriptEngine.uncaughtException().toString();
    else if (!(m_lastResult.isNumber() || m_lastResult.isString()))
        return QLatin1String("?");
    return QString();
}

double Calculator::lastResult() const
{
    return m_lastResult.toNumber();
}

QString Calculator::lastResultText() const
{
    return m_lastResult.toString();
}

} // namespace qtscript
