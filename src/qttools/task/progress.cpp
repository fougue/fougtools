/****************************************************************************
**
**  FougTools
**  Copyright Fougue (27 Feb. 2015)
**  contact@fougsys.fr
**
** This software is a computer program whose purpose is to provide utility
** tools for the C++ language and the Qt toolkit.
**
** This software is governed by the CeCILL-C license under French law and
** abiding by the rules of distribution of free software.  You can  use,
** modify and/ or redistribute the software under the terms of the CeCILL-C
** license as circulated by CEA, CNRS and INRIA at the following URL
** "http://www.cecill.info".
**
** As a counterpart to the access to the source code and  rights to copy,
** modify and redistribute granted by the license, users are provided only
** with a limited warranty  and the software's author,  the holder of the
** economic rights,  and the successive licensors  have only  limited
** liability.
**
** In this respect, the user's attention is drawn to the risks associated
** with loading,  using,  modifying and/or developing or reproducing the
** software by the user in light of its specific status of free software,
** that may mean  that it is complicated to manipulate,  and  that  also
** therefore means  that it is reserved for developers  and  experienced
** professionals having in-depth computer knowledge. Users are therefore
** encouraged to load and test the software's suitability as regards their
** requirements in conditions enabling the security of their systems and/or
** data to be ensured and,  more generally, to use and operate it in the
** same conditions as regards security.
**
** The fact that you are presently reading this means that you have had
** knowledge of the CeCILL-C license and that you accept its terms.
**
****************************************************************************/

#include "progress.h"

#include "base_runner.h"

namespace qttask {

Progress::Progress(BaseRunner *runner)
    : m_runner(runner),
      m_value(0)
{ }

Progress::~Progress()
{ }

int Progress::value() const
{
    return m_value;
}

void Progress::setValue(int pct)
{
    m_value = pct;
    m_runner->qtSignals()->emitProgress(pct);
}

const QString& Progress::step() const
{
    return m_step;
}

void Progress::setStep(const QString &title)
{
    m_step = title;
    m_runner->qtSignals()->emitProgressStep(title);
}

void Progress::outputMessage(const QString &msg)
{
    m_runner->qtSignals()->emitMessage(msg);
}

/*! \brief Returns this progress' custom data for the key \p key as a QVariant
 *
 * Custom progress data is useful for storing arbitrary properties in any progress.\n
 * TaskManager does not use this feature for storing data; it is provided solely for the convenience
 * of the user.
 */
QVariant Progress::data(int key) const
{
    auto it = m_dataHash.find(key);
    return it != m_dataHash.end() ? (*it).second : QVariant();
}

/*! \brief Set this progress' custom data for the key \p key to \p value
 *
 * Custom progress data is useful for storing arbitrary properties for any item. TaskManager does
 * not use this feature for storing data; it is provided solely for the convenience of the user.
 */
void Progress::setData(int key, const QVariant &value)
{
    m_dataHash.emplace(key, value);
}

bool Progress::isAbortRequested() const
{
    return m_runner->isAbortRequested();
}

} // namespace qttask
