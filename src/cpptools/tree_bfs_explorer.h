/****************************************************************************
**
**  FougTools
**  Copyright Fougue (1 Mar. 2011)
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

#pragma once

#include <queue>
#include "pusher.h"

namespace cpp {

template<typename NODE, typename TREE_MODEL>
class TreeBfsExplorer
{
public:
    TreeBfsExplorer();

    void begin(NODE* node = nullptr);
    void goNext();
    bool atEnd() const;

    NODE* current() const;
    unsigned depth() const;

private:
    NODE* m_current;
    std::queue<NODE*> m_levelNodes;
    unsigned m_depth;
};


// --
// -- Implementation
// --

/*!
 * \class TreeBfsExplorer
 * \brief Generic class for the exploration of trees using BFS (breadth-first search) algorithm
 *
 * TREE_MODEL type must be a model of TreeBfsConcept :
 *
 * \code
 *     struct TreeBfsConcept
 *     {
 *         // Is current tree node deeper (depth value) than tree node previous ?
 *         static bool isDeeper(const NODE* current, const NODE* previous);
 *
 *         // Enqueue all first-level (direct) children of tree node parentNode
 *         // using output iterator
 *         template<typename OUTPUT_ITERATOR>
 *         static void enqueueChildren(OUTPUT_ITERATOR out, NODE* parentNode);
 *     };
 * \endcode
 *
 * \headerfile tree_bfs_explorer.h <cpptools/tree_bfs_explorer.h>
 * \ingroup cpptools
 */

template<typename NODE, typename TREE_MODEL>
TreeBfsExplorer<NODE, TREE_MODEL>::TreeBfsExplorer()
    : m_current(nullptr),
      m_depth(0)
{
}

//! Prepares exploration to start from tree \p node
template<typename NODE, typename TREE_MODEL>
void TreeBfsExplorer<NODE, TREE_MODEL>::begin(NODE* node)
{
    while (!m_levelNodes.empty())
        m_levelNodes.pop();
    m_current = nullptr;
    m_depth = 0;

    if (node == nullptr)
        TREE_MODEL::enqueueChildren(cpp::pusher(m_levelNodes), node);
    else
        m_levelNodes.push(node);

    this->goNext();
}

//! Move exploration to the next tree node
template<typename NODE, typename TREE_MODEL>
void TreeBfsExplorer<NODE, TREE_MODEL>::goNext()
{
    if (m_levelNodes.empty()) {
        m_current = nullptr;
        return;
    }

    const NODE* previous = m_current;

    m_current = m_levelNodes.front();
    m_levelNodes.pop();

    if (previous != nullptr
            && m_current != nullptr
            && TREE_MODEL::isDeeper(m_current, previous))
    {
        ++m_depth;
    }

    if (m_current != nullptr)
        TREE_MODEL::enqueueChildren(cpp::pusher(m_levelNodes), m_current);
}

//! Is exploration beyond the last tree node (ended) ?
template<typename NODE, typename TREE_MODEL>
bool TreeBfsExplorer<NODE, TREE_MODEL>::atEnd() const
{
    return m_current == nullptr;
}

//! Current explored tree node
template<typename NODE, typename TREE_MODEL>
NODE* TreeBfsExplorer<NODE, TREE_MODEL>::current() const
{
    return m_current;
}

//! Depth of the current tree node
template<typename NODE, typename TREE_MODEL>
unsigned TreeBfsExplorer<NODE, TREE_MODEL>::depth() const
{
    return m_depth;
}

} // namespace cpp
