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

#include "ais_utils.h"

#include <AIS_InteractiveContext.hxx>
#include <AIS_InteractiveObject.hxx>
#include <SelectMgr_SelectionManager.hxx>
#include <Standard_Version.hxx>

namespace occ {

/*! \class AisUtils
 *  \brief Collection of tools for the AIS package
 *
 *  \headerfile ais_utils.h <occtools/ais_utils.h>
 *  \ingroup occtools
 */

void AisUtils::eraseObjectFromContext(
        const Handle_AIS_InteractiveObject &object,
        const Handle_AIS_InteractiveContext &context)
{
    if (!object.IsNull()) {
        context->Erase(object, Standard_False);
        context->Remove(object, Standard_False);
#if OCC_VERSION_HEX < 0x060900
        context->Clear(object, Standard_False); // Remove() can be used too
#else
        context->ClearPrs(object, 0, Standard_False);
#endif
        context->SelectionManager()->Remove(object);

        Handle_AIS_InteractiveObject objectHCopy = object;
        while (!objectHCopy.IsNull())
            objectHCopy.Nullify();
    }
}

} // namespace occ
