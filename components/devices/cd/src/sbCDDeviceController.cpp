/*
//
// BEGIN SONGBIRD GPL
//
// This file is part of the Songbird web player.
//
// Copyright(c) 2005-2009 POTI, Inc.
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

#include "sbCDDeviceController.h"

#include <nsIClassInfoImpl.h>
#include <nsIGenericFactory.h>
#include <nsIProgrammingLanguage.h>
#include <nsMemory.h>
#include <nsServiceManagerUtils.h>


NS_IMPL_THREADSAFE_ADDREF(sbCDDeviceController)
NS_IMPL_THREADSAFE_RELEASE(sbCDDeviceController)
NS_IMPL_QUERY_INTERFACE1_CI(sbCDDeviceController, sbIDeviceController)
NS_IMPL_CI_INTERFACE_GETTER1(sbCDDeviceController, sbIDeviceController)

// nsIClassInfo implementation.
NS_DECL_CLASSINFO(sbCDDeviceController)
NS_IMPL_THREADSAFE_CI(sbCDDeviceController)

sbCDDeviceController::sbCDDeviceController()
{
}

sbCDDeviceController::~sbCDDeviceController()
{
}

//------------------------------------------------------------------------------
// sbIDeviceController

NS_IMETHODIMP
sbCDDeviceController::GetCompatibility(nsIPropertyBag *aParams,
                                       sbIDeviceCompatibility **aRetVal)
{
  NS_ENSURE_ARG_POINTER(aParams);
  NS_ENSURE_ARG_POINTER(aRetVal);

  //
  // XXXkreeger WRITE ME
  //

  return NS_OK;
}

NS_IMETHODIMP
sbCDDeviceController::CreateDevice(nsIPropertyBag *aParams,
                                   sbIDevice **aRetVal)
{
  NS_ENSURE_ARG_POINTER(aParams);
  NS_ENSURE_ARG_POINTER(aRetVal);

  //
  // XXXkreeger WRITE ME
  //

  return NS_OK;
}

NS_IMETHODIMP
sbCDDeviceController::ControlsDevice(sbIDevice *aDevice, PRBool *aRetVal)
{
  return ControlsDeviceInternal(aDevice, aRetVal);
}

NS_IMETHODIMP
sbCDDeviceController::ConnectDevices()
{
  return ConnectDevicesInternal();
}

NS_IMETHODIMP
sbCDDeviceController::DisconnectDevices()
{
  return DisconnectDevicesInternal();
}

NS_IMETHODIMP
sbCDDeviceController::ReleaseDevice(sbIDevice *aDevice)
{
  return ReleaseDeviceInternal(aDevice);
}

NS_IMETHODIMP
sbCDDeviceController::ReleaseDevices()
{
  return ReleaseDevicesInternal();
}

NS_IMETHODIMP
sbCDDeviceController::GetId(nsID **aId)
{
  NS_ENSURE_ARG_POINTER(aId);

  //
  // XXXkreeger WRITE ME
  //

  return NS_OK;
}

NS_IMETHODIMP
sbCDDeviceController::GetName(nsAString & aName)
{
  return GetControllerNameInternal(aName);
}

NS_IMETHODIMP
sbCDDeviceController::GetMarshallId(nsID **aId)
{
  NS_ENSURE_ARG_POINTER(aId);

  //
  // XXXkreeger WRITE ME
  //

  return NS_OK;
}

NS_IMETHODIMP
sbCDDeviceController::GetDevices(nsIArray **aDevices)
{
  return GetDevicesInternal(aDevices);
}
