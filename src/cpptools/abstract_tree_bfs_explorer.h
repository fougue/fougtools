/****************************************************************************
**
**  FougTools
**  Copyright FougSys (1 Mar. 2011)
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

#ifndef CPPTOOLS_ABSTRACT_TREE_BFS_EXPLORER_H
#define CPPTOOLS_ABSTRACT_TREE_BFS_EXPLORER_H

#include <queue>

namespace cpp {

template<class NODE>
class AbstractTreeBfsExplorer
{
public:
  AbstractTreeBfsExplorer();
  virtual ~AbstractTreeBfsExplorer();

  void begin(NODE* node = static_cast<NODE*>(0));
  void goNext();
  bool atEnd() const;

  NODE* current() const;
  unsigned depth() const;

protected:
  virtual bool isCurrentDeeper(const NODE* previous) const = 0;
  virtual void enqueueNodeChildren(NODE* parentNode) = 0;

  void enqueueNode(NODE* node);

private:
  NODE* m_current;
  std::queue<NODE*> m_levelNodes;
  unsigned m_depth;
};

// --
// -- Implementation
// --

template<class NODE>
AbstractTreeBfsExplorer<NODE>::AbstractTreeBfsExplorer()
  : m_current(static_cast<NODE*>(0)),
    m_depth(0)
{
}

template<class NODE>
AbstractTreeBfsExplorer<NODE>::~AbstractTreeBfsExplorer()
{
}

template<class NODE>
void AbstractTreeBfsExplorer<NODE>::begin(NODE* node)
{
  while (!m_levelNodes.empty())
    m_levelNodes.pop();
  m_current = static_cast<NODE*>(0);
  m_depth = 0;

  if (node == static_cast<NODE*>(0))
    this->enqueueNodeChildren(node);
  else
    this->enqueueNode(node);

  this->goNext();
}

template<class NODE>
void AbstractTreeBfsExplorer<NODE>::goNext()
{
  if (m_levelNodes.empty()) {
    m_current = static_cast<NODE*>(0);
    return;
  }

  const NODE* previous = m_current;

  m_current = m_levelNodes.front();
  m_levelNodes.pop();

  if (previous != static_cast<const NODE*>(0) && m_current != static_cast<const NODE*>(0)
      && this->isCurrentDeeper(previous))
    ++m_depth;

  if (m_current != static_cast<const NODE*>(0))
    this->enqueueNodeChildren(m_current);
}

template<class NODE>
bool AbstractTreeBfsExplorer<NODE>::atEnd() const
{
  return m_current == static_cast<const NODE*>(0);
}

template<class NODE>
NODE* AbstractTreeBfsExplorer<NODE>::current() const
{
  return m_current;
}

template<class NODE>
unsigned AbstractTreeBfsExplorer<NODE>::depth() const
{
  return m_depth;
}

template<class NODE>
void AbstractTreeBfsExplorer<NODE>::enqueueNode(NODE* node)
{
  m_levelNodes.push(node);
}

} // namespace cpp

#endif // CPPTOOLS_ABSTRACT_TREE_BFS_EXPLORER_H
