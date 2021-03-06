/*
//
// BEGIN SONGBIRD GPL
//
// This file is part of the Songbird web player.
//
// Copyright(c) 2005-2011 POTI, Inc.
// http://songbirdnest.com
//
// This file may be licensed under the terms of of the
// GNU General Public License Version 2 (the "GPL").
//
// Software distributed under the License is distributed
// on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, either
// express or implied. See the GPL for the specific language
// governing rights and limitations.
//
// You should have received a copy of the GPL along with this
// program. If not, go to http://www.gnu.org/licenses/gpl.html
// or write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
//
// END SONGBIRD GPL
//
*/

/**
 * \file  sbIdentityServiceComponent.cpp
 * \brief Songbird Identity Service Component Factory and Main Entry Point.
 */

#include <nsIClassInfoImpl.h>
#include <mozilla/ModuleUtils.h>

#include "sbIdentityService.h"

NS_GENERIC_FACTORY_CONSTRUCTOR(sbIdentityService);

NS_DEFINE_NAMED_CID(SONGBIRD_IDENTITY_SERVICE_CID);

static const mozilla::Module::CIDEntry kIdentityServiceCIDs[] =
{
  { &kSONGBIRD_IDENTITY_SERVICE_CID, false, NULL,
    sbIdentityServiceConstructor },
  { NULL }
};

static const mozilla::Module::ContractIDEntry kIdentityServiceContracts[] =
{
  { SONGBIRD_IDENTITY_SERVICE_CONTRACTID,
    &kSONGBIRD_IDENTITY_SERVICE_CID },
  { NULL }
};

static const mozilla::Module::CategoryEntry kIdentityServiceCategories[] =
{
  { NULL }
};

static const mozilla::Module kIdentityServiceComponent =
{
  mozilla::Module::kVersion,
  kIdentityServiceCIDs,
  kIdentityServiceContracts,
  kIdentityServiceCategories
};

NSMODULE_DEFN(SongbirdIdentityServiceComponent) = &kIdentityServiceComponent;
