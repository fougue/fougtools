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

#include "kernel_utils.h"

namespace occ {

/*! \class KernelUtils
 *  \brief Collection of tools for the Kernel toolkit
 *
 *  \headerfile kernel_utils.h <occtools/kernel_utils.h>
 *  \ingroup occtools
 */

Quantity_Color KernelUtils::rgbColor(int red, int blue, int green)
{
    return Quantity_Color(red / 255., blue / 255., green / 255., Quantity_TOC_RGB);
}

} // namespace occ
