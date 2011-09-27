#ifndef QTTOOLS_CALCULATOR_H
# define QTTOOLS_CALCULATOR_H

# include <QtScript/QScriptEngine>

namespace qttools {
  class Calculator
  {
  public:
    Calculator();

    void evaluate(const QString& program);
    bool hasResult() const;
    QString lastErrorText() const;

    double lastResult() const;
    QString lastResultText() const;

  private:
    QScriptEngine _scriptEngine;
    QScriptValue _lastResult;
  }; // namespace qttools
} // namespace qttools

#endif // QTTOOLS_CALCULATOR_H
