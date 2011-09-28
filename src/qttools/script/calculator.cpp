#include "calculator.h"

namespace qttools {
  /*! \class Calculator
   *  \brief Provides evaluation of expressions
   *
   */

  Calculator::Calculator() :
      _scriptEngine(),
      _lastResult(0)
  {
    _scriptEngine.evaluate(
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
    _lastResult = _scriptEngine.evaluate(program);
  }

  bool Calculator::hasResult() const
  {
    return
        !_scriptEngine.hasUncaughtException() &&
        (_lastResult.isNumber() || _lastResult.isString());
  }

  QString Calculator::lastErrorText() const
  {
    if (_scriptEngine.hasUncaughtException())
      return _scriptEngine.uncaughtException().toString();
    else if (!(_lastResult.isNumber() || _lastResult.isString()))
      return QString("?");
    return QString();
  }

  double Calculator::lastResult() const
  {
    return _lastResult.toNumber();
  }

  QString Calculator::lastResultText() const
  {
    return _lastResult.toString();
  }
} // namespace qttools
