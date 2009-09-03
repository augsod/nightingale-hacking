/* vim: set sw=2 :miv */
/*
//
// BEGIN SONGBIRD GPL
// 
// This file is part of the Songbird web player.
//
// Copyright(c) 2005-2008 POTI, Inc.
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

#include "sbMockDevice.h"

#include <nsIPrefBranch.h>
#include <nsIPrefService.h>
#include <nsIVariant.h>
#include <nsIWritablePropertyBag.h>
#include <nsIWritablePropertyBag2.h>

#include <nsCOMPtr.h>
#include <nsComponentManagerUtils.h>
#include <nsServiceManagerUtils.h>
#include <nsXPCOMCIDInternal.h>

#include <sbIDeviceLibrary.h>
#include <sbIDeviceProperties.h>

#include <sbDeviceContent.h>

/* for an actual device, you would probably want to actually sort the prefs on
 * the device itself (and not the mozilla prefs system).  And even if you do end
 * up wanting to store things in the prefs system for some odd reason, you would
 * want to have a unique id per instance of the device and not a hard-coded one.
 */
#define DEVICE_PREF_BRANCH \
  "songbird.devices.mock.00000000-0000-0000-c000-000000000046."

NS_IMPL_THREADSAFE_ADDREF(sbMockDevice)
NS_IMPL_THREADSAFE_RELEASE(sbMockDevice)
NS_INTERFACE_MAP_BEGIN(sbMockDevice)
  NS_INTERFACE_MAP_ENTRY(sbIMockDevice)
  NS_INTERFACE_MAP_ENTRY_AMBIGUOUS(sbIDevice, sbBaseDevice)
  NS_INTERFACE_MAP_ENTRY(sbIDeviceEventTarget)
  NS_INTERFACE_MAP_ENTRY_AMBIGUOUS(nsISupports, sbIDeviceEventTarget)
NS_INTERFACE_MAP_END

sbMockDevice::sbMockDevice()
 : mIsConnected(PR_FALSE)
{
  /* member initializers and constructor code */
}

sbMockDevice::~sbMockDevice()
{
  /* destructor code */
}

/* readonly attribute AString name; */
NS_IMETHODIMP sbMockDevice::GetName(nsAString & aName)
{
  aName.AssignLiteral("Bob's Mock Device");
  return NS_OK;
}

/* readonly attribute AString productName; */
NS_IMETHODIMP sbMockDevice::GetProductName(nsAString & aProductName)
{
  aProductName.AssignLiteral("Mock Device");
  return NS_OK;
}

/* readonly attribute nsIDPtr controllerId; */
NS_IMETHODIMP sbMockDevice::GetControllerId(nsID * *aControllerId)
{
  NS_ENSURE_ARG_POINTER(aControllerId);
  
  *aControllerId = (nsID*)NS_Alloc(sizeof(nsID));
  NS_ENSURE_TRUE(*aControllerId, NS_ERROR_OUT_OF_MEMORY);
  **aControllerId = NS_GET_IID(nsISupports);
  return NS_OK;
}

/* readonly attribute nsIDPtr id; */
NS_IMETHODIMP sbMockDevice::GetId(nsID * *aId)
{
  NS_ENSURE_ARG_POINTER(aId);
  
  nsID mockDeviceID;
  
  PRBool success = 
    mockDeviceID.Parse("{3572E6FC-4954-4458-AFE7-0D0A65BF5F55}");
  NS_ENSURE_TRUE(success, NS_ERROR_FAILURE);

  *aId = (nsID*)NS_Alloc(sizeof(nsID));
  NS_ENSURE_TRUE(*aId, NS_ERROR_OUT_OF_MEMORY);

  **aId = mockDeviceID;

  return NS_OK;
}

/* void connect (); */
NS_IMETHODIMP sbMockDevice::Connect()
{
  NS_ENSURE_STATE(!mIsConnected);
  mIsConnected = PR_TRUE;
  return NS_OK;
}

/* void disconnect (); */
NS_IMETHODIMP sbMockDevice::Disconnect()
{
  NS_ENSURE_STATE(mIsConnected);
  
  nsresult rv;
  if (mContent) {
    rv = mContent->Finalize();
    NS_ENSURE_SUCCESS(rv, rv);
  }
  
  mIsConnected = PR_FALSE;
  return NS_OK;
}

/* readonly attribute boolean connected; */
NS_IMETHODIMP sbMockDevice::GetConnected(PRBool *aConnected)
{
  NS_ENSURE_ARG_POINTER(aConnected);
  *aConnected = mIsConnected;
  return NS_OK;
}

/* readonly attribute boolean threaded; */
NS_IMETHODIMP sbMockDevice::GetThreaded(PRBool *aThreaded)
{
  NS_ENSURE_ARG_POINTER(aThreaded);
  *aThreaded = PR_FALSE;
  return NS_OK;
}

/* nsIVariant getPreference (in AString aPrefName); */
NS_IMETHODIMP sbMockDevice::GetPreference(const nsAString & aPrefName, nsIVariant **_retval)
{
  /* what, you expect a mock device to be actually useful? */
  NS_ENSURE_ARG_POINTER(_retval);
  nsresult rv;

  nsCOMPtr<nsIPrefService> prefRoot =
    do_GetService("@mozilla.org/preferences-service;1", &rv);
  NS_ENSURE_SUCCESS(rv, rv);
  
  nsCOMPtr<nsIPrefBranch> prefBranch;
  rv = prefRoot->GetBranch(DEVICE_PREF_BRANCH, getter_AddRefs(prefBranch));
  NS_ENSURE_SUCCESS(rv, rv);
  
  NS_LossyConvertUTF16toASCII prefNameC(aPrefName);
  
  PRInt32 prefType;
  rv = prefBranch->GetPrefType(prefNameC.get(),
                               &prefType);
  NS_ENSURE_SUCCESS(rv, rv);
  
  nsCOMPtr<nsIWritableVariant> result =
    do_CreateInstance("@songbirdnest.com/Songbird/Variant;1", &rv);
  NS_ENSURE_SUCCESS(rv, rv);
  
  switch(prefType) {
    case nsIPrefBranch::PREF_INVALID: {
      rv = result->SetAsVoid();
      NS_ENSURE_SUCCESS(rv, rv);
      break;
    }
    case nsIPrefBranch::PREF_STRING: {
      char *value = nsnull;
      rv = prefBranch->GetCharPref(prefNameC.get(), &value);
      NS_ENSURE_SUCCESS(rv, rv);
      rv = result->SetAsString(value);
      NS_Free(value);
      NS_ENSURE_SUCCESS(rv, rv);
      break;
    }
    case nsIPrefBranch::PREF_INT: {
      PRInt32 value;
      rv = prefBranch->GetIntPref(prefNameC.get(), &value);
      NS_ENSURE_SUCCESS(rv, rv);
      rv = result->SetAsInt32(value);
      NS_ENSURE_SUCCESS(rv, rv);
      break;
    }
    case nsIPrefBranch::PREF_BOOL: {
      PRBool value;
      rv = prefBranch->GetBoolPref(prefNameC.get(), &value);
      NS_ENSURE_SUCCESS(rv, rv);
      rv = result->SetAsBool(value);
      NS_ENSURE_SUCCESS(rv, rv);
      break;
    }
    default: {
      /* wtf? */
      return NS_ERROR_UNEXPECTED;
    }
  }
  
  return CallQueryInterface(result, _retval);
}

/* void setPreference (in AString aPrefName, in nsIVariant aPrefValue); */
NS_IMETHODIMP sbMockDevice::SetPreference(const nsAString & aPrefName, nsIVariant *aPrefValue)
{
  NS_ENSURE_ARG_POINTER(aPrefValue);
  nsresult rv;

  nsCOMPtr<nsIPrefService> prefRoot =
    do_GetService("@mozilla.org/preferences-service;1", &rv);
  NS_ENSURE_SUCCESS(rv, rv);
  
  nsCOMPtr<nsIPrefBranch> prefBranch;
  rv = prefRoot->GetBranch(DEVICE_PREF_BRANCH, getter_AddRefs(prefBranch));
  NS_ENSURE_SUCCESS(rv, rv);
  
  NS_LossyConvertUTF16toASCII prefNameC(aPrefName);
  
  PRUint16 prefType;
  rv = aPrefValue->GetDataType(&prefType);
  NS_ENSURE_SUCCESS(rv, rv);
  
  PRInt32 oldPrefType;
  rv = prefBranch->GetPrefType(prefNameC.get(), &oldPrefType);
  NS_ENSURE_SUCCESS(rv, rv);
  
  switch(prefType) {
    case nsIDataType::VTYPE_INT8:
    case nsIDataType::VTYPE_INT16:
    case nsIDataType::VTYPE_INT32:
    case nsIDataType::VTYPE_INT64:
    case nsIDataType::VTYPE_UINT8:
    case nsIDataType::VTYPE_UINT16:
    case nsIDataType::VTYPE_UINT32:
    case nsIDataType::VTYPE_UINT64:
    {
      if (oldPrefType != nsIPrefBranch::PREF_INVALID &&
          oldPrefType != nsIPrefBranch::PREF_INT) {
        rv = prefBranch->ClearUserPref(prefNameC.get());
        NS_ENSURE_SUCCESS(rv, rv);
      }
      PRInt32 value;
      rv = aPrefValue->GetAsInt32(&value);
      NS_ENSURE_SUCCESS(rv, rv);
      rv = prefBranch->SetIntPref(prefNameC.get(), value);
      NS_ENSURE_SUCCESS(rv, rv);
  
      /* special case for state */
      if (aPrefName.Equals(NS_LITERAL_STRING("state"))) {
        mState = value;
      }

      break;
    }
    case nsIDataType::VTYPE_BOOL:
    {
      if (oldPrefType != nsIPrefBranch::PREF_INVALID &&
          oldPrefType != nsIPrefBranch::PREF_BOOL) {
        rv = prefBranch->ClearUserPref(prefNameC.get());
        NS_ENSURE_SUCCESS(rv, rv);
      }
      PRBool value;
      rv = aPrefValue->GetAsBool(&value);
      NS_ENSURE_SUCCESS(rv, rv);
      rv = prefBranch->SetBoolPref(prefNameC.get(), value);
      NS_ENSURE_SUCCESS(rv, rv);
      break;
    }
    default:
    {
      if (oldPrefType != nsIPrefBranch::PREF_INVALID &&
          oldPrefType != nsIPrefBranch::PREF_STRING) {
        rv = prefBranch->ClearUserPref(prefNameC.get());
        NS_ENSURE_SUCCESS(rv, rv);
      }
      nsCString value;
      rv = aPrefValue->GetAsACString(value);
      NS_ENSURE_SUCCESS(rv, rv);
      rv = prefBranch->SetCharPref(prefNameC.get(), value.get());
      NS_ENSURE_SUCCESS(rv, rv);
      break;
    }
  }

  return NS_OK;
}

/* readonly attribute sbIDeviceCapabilities capabilities; */
NS_IMETHODIMP sbMockDevice::GetCapabilities(sbIDeviceCapabilities * *aCapabilities)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute sbIDeviceContent content; */
NS_IMETHODIMP sbMockDevice::GetContent(sbIDeviceContent * *aContent)
{
  nsresult rv;
  if (!mContent) {
    nsRefPtr<sbDeviceContent> deviceContent = sbDeviceContent::New();
    NS_ENSURE_TRUE(deviceContent, NS_ERROR_OUT_OF_MEMORY);
    rv = deviceContent->Initialize();
    NS_ENSURE_SUCCESS(rv, rv);
    mContent = deviceContent;
    
    // make a mock library too
    NS_NAMED_LITERAL_STRING(LIBID, "mock-library.mock-device");
    nsCOMPtr<sbIDeviceLibrary> devLib;
    rv = CreateDeviceLibrary(LIBID, nsnull, getter_AddRefs(devLib));
    NS_ENSURE_SUCCESS(rv, rv);
    
    rv = mContent->AddLibrary(devLib);
    NS_ENSURE_SUCCESS(rv, rv);
    
  }
  NS_ADDREF(*aContent = mContent);
  return NS_OK;
}

/* readonly attribute nsIPropertyBag2 parameters; */
NS_IMETHODIMP sbMockDevice::GetParameters(nsIPropertyBag2 * *aParameters)
{
  nsresult rv;

  nsCOMPtr<nsIWritablePropertyBag> writeBag =
        do_CreateInstance("@mozilla.org/hash-property-bag;1", &rv);
  NS_ENSURE_SUCCESS(rv, rv);

  nsCOMPtr<nsIWritableVariant> deviceType = 
    do_CreateInstance("@songbirdnest.com/Songbird/Variant;1", &rv);
  NS_ENSURE_SUCCESS(rv, rv);

  // Pretend like we're an MTP device.
  rv = deviceType->SetAsAString(NS_LITERAL_STRING("MTP"));
  NS_ENSURE_SUCCESS(rv, rv);

  rv = writeBag->SetProperty(NS_LITERAL_STRING("DeviceType"), 
                             deviceType);
  NS_ENSURE_SUCCESS(rv, rv);

  nsCOMPtr<nsIPropertyBag2> propBag = do_QueryInterface(writeBag, &rv);
  NS_ENSURE_SUCCESS(rv, rv);

  propBag.forget(aParameters);

  return NS_OK;
}

NS_IMETHODIMP sbMockDevice::GetProperties(sbIDeviceProperties * *theProperties)
{
  nsresult rv = NS_ERROR_UNEXPECTED;

  if(!mProperties) {
    nsCOMPtr<sbIDeviceProperties> properties = 
      do_CreateInstance("@songbirdnest.com/Songbird/Device/DeviceProperties;1", &rv);
    NS_ENSURE_SUCCESS(rv, rv);

    rv = properties->InitFriendlyName(NS_LITERAL_STRING("Testing Device"));
    NS_ENSURE_SUCCESS(rv, rv);

    rv = properties->InitVendorName(NS_LITERAL_STRING("ACME Inc."));
    NS_ENSURE_SUCCESS(rv, rv);

    nsCOMPtr<nsIWritableVariant> modelNumber =
      do_CreateInstance("@songbirdnest.com/Songbird/Variant;1", &rv);
    NS_ENSURE_SUCCESS(rv, rv);

    rv = modelNumber->SetAsString("ACME 9000");
    NS_ENSURE_SUCCESS(rv, rv);

    rv = properties->InitModelNumber(modelNumber);
    NS_ENSURE_SUCCESS(rv, rv);

    nsCOMPtr<nsIWritableVariant> serialNumber =
      do_CreateInstance("@songbirdnest.com/Songbird/Variant;1", &rv);
    NS_ENSURE_SUCCESS(rv, rv);

    rv = serialNumber->SetAsString("ACME-9000-0001-2000-3000");
    NS_ENSURE_SUCCESS(rv, rv);

    rv = properties->InitSerialNumber(serialNumber);
    NS_ENSURE_SUCCESS(rv, rv);

    rv = properties->InitFirmwareVersion(NS_LITERAL_STRING("1.0.0.0"));
    NS_ENSURE_SUCCESS(rv, rv);

    nsCOMPtr<nsIWritablePropertyBag> writeBag =
        do_CreateInstance("@mozilla.org/hash-property-bag;1", &rv);
    NS_ENSURE_SUCCESS(rv, rv);

    nsCOMPtr<nsIWritableVariant> freeSpace = 
      do_CreateInstance("@songbirdnest.com/Songbird/Variant;1", &rv);
    NS_ENSURE_SUCCESS(rv, rv);

    rv = freeSpace->SetAsString("17179869184");
    NS_ENSURE_SUCCESS(rv, rv);

    rv = writeBag->SetProperty(NS_LITERAL_STRING("http://songbirdnest.com/device/1.0#freeSpace"), 
                               freeSpace);
    NS_ENSURE_SUCCESS(rv, rv);

    nsCOMPtr<nsIWritableVariant> totalUsedSpace = 
      do_CreateInstance("@songbirdnest.com/Songbird/Variant;1", &rv);
    NS_ENSURE_SUCCESS(rv, rv);

    rv = totalUsedSpace->SetAsString("4294967296");
    NS_ENSURE_SUCCESS(rv, rv);

    rv = writeBag->SetProperty(NS_LITERAL_STRING("http://songbirdnest.com/device/1.0#totalUsedSpace"),
                               totalUsedSpace);
    NS_ENSURE_SUCCESS(rv, rv);

    nsCOMPtr<nsIPropertyBag2> propBag = do_QueryInterface(writeBag, &rv);
    NS_ENSURE_SUCCESS(rv, rv);

    rv = properties->InitDeviceProperties(propBag);
    NS_ENSURE_SUCCESS(rv, rv);

    rv = properties->InitDone();
    NS_ENSURE_SUCCESS(rv, rv);

    mProperties = properties;
  }

  NS_ADDREF(*theProperties = mProperties);

  return NS_OK;  
}

NS_IMETHODIMP sbMockDevice::SubmitRequest(PRUint32 aRequest, nsIPropertyBag2 *aRequestParameters)
{
  nsRefPtr<TransferRequest> transferRequest;
  nsresult rv = CreateTransferRequest(aRequest,
                                      aRequestParameters,
                                      getter_AddRefs(transferRequest));
  NS_ENSURE_SUCCESS(rv, rv);
  
  return PushRequest(transferRequest);
}

nsresult sbMockDevice::ProcessRequest()
{
  /* don't process, let the js deal with it */
  return NS_OK;
}

NS_IMETHODIMP sbMockDevice::CancelRequests()
{
  nsID* id;
  nsresult rv = GetId(&id);
  NS_ENSURE_SUCCESS(rv, rv);
  
  char idString[NSID_LENGTH];
  id->ToProvidedString(idString);
  NS_Free(id);
  
  return ClearRequests(NS_ConvertASCIItoUTF16(idString));
}

NS_IMETHODIMP sbMockDevice::Eject()
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP sbMockDevice::GetIsBusy(PRBool *aIsBusy)
{
  nsCOMPtr<nsIVariant> busyVariant;
  nsresult rv = 
    GetPreference(NS_LITERAL_STRING("testing.busy"), 
                  getter_AddRefs(busyVariant));
  NS_ENSURE_SUCCESS(rv, rv);

  PRUint16 dataType = 0;
  rv = busyVariant->GetDataType(&dataType);
  NS_ENSURE_SUCCESS(rv, rv);

  if(dataType == nsIDataType::VTYPE_BOOL) {
    rv = busyVariant->GetAsBool(aIsBusy);
    NS_ENSURE_SUCCESS(rv, rv);
  }
  else {
    rv = sbBaseDevice::GetIsBusy(aIsBusy);
    NS_ENSURE_SUCCESS(rv, rv);
  }

  return NS_OK;
}

NS_IMETHODIMP sbMockDevice::GetCanDisconnect(PRBool *aCanDisconnect)
{
  return sbBaseDevice::GetCanDisconnect(aCanDisconnect);
}

NS_IMETHODIMP sbMockDevice::GetState(PRUint32 *aState)
{
  return sbBaseDevice::GetState(aState);
}

NS_IMETHODIMP sbMockDevice::GetPreviousState(PRUint32 *aState)
{
  return sbBaseDevice::GetPreviousState(aState);
}

NS_IMETHODIMP sbMockDevice::SyncLibraries()
{
  return sbBaseDevice::SyncLibraries();
}



/****************************** sbIMockDevice ******************************/

#define SET_PROP(type, name) \
  rv = bag->SetPropertyAs ## type(NS_LITERAL_STRING(#name), request->name); \
  NS_ENSURE_SUCCESS(rv, rv);

/* nsIPropertyBag2 PopRequest (); */
NS_IMETHODIMP sbMockDevice::PopRequest(nsIPropertyBag2 **_retval)
{
  // while it's easier to reuse PeekRequest, that sort of defeats the purpose
  // of testing.
  NS_ENSURE_ARG_POINTER(_retval);
  
  nsRefPtr<TransferRequest> request;
  nsresult rv = sbBaseDevice::PopRequest(getter_AddRefs(request));
  NS_ENSURE_SUCCESS(rv, rv);
  NS_ENSURE_TRUE(request, NS_ERROR_FAILURE);
  
  nsCOMPtr<nsIWritablePropertyBag2> bag =
    do_CreateInstance(NS_HASH_PROPERTY_BAG_CONTRACTID, &rv);
  NS_ENSURE_SUCCESS(rv, rv);
  
  SET_PROP(Interface, item);
  SET_PROP(Interface, list);
  SET_PROP(Interface, data);
  SET_PROP(Uint32, index);
  SET_PROP(Uint32, otherIndex);
  SET_PROP(Uint32, batchCount);
  SET_PROP(Uint32, batchIndex);
  SET_PROP(Uint32, itemTransferID);
  SET_PROP(Int32, priority);
  
  return CallQueryInterface(bag, _retval);
}

/* nsIPropertyBag2 PeekRequest (); */
NS_IMETHODIMP sbMockDevice::PeekRequest(nsIPropertyBag2 **_retval)
{
  NS_ENSURE_ARG_POINTER(_retval);
  
  nsRefPtr<TransferRequest> request;
  nsresult rv = sbBaseDevice::PeekRequest(getter_AddRefs(request));
  NS_ENSURE_SUCCESS(rv, rv);
  NS_ENSURE_TRUE(request, NS_ERROR_FAILURE);
  
  nsCOMPtr<nsIWritablePropertyBag2> bag =
    do_CreateInstance(NS_HASH_PROPERTY_BAG_CONTRACTID, &rv);
  NS_ENSURE_SUCCESS(rv, rv);
  
  SET_PROP(Interface, item);
  SET_PROP(Interface, list);
  SET_PROP(Interface, data);
  SET_PROP(Uint32, index);
  SET_PROP(Uint32, otherIndex);
  SET_PROP(Uint32, batchCount);
  SET_PROP(Uint32, batchIndex);
  SET_PROP(Uint32, itemTransferID);
  SET_PROP(Int32, priority);
  
  return CallQueryInterface(bag, _retval);
}

NS_IMETHODIMP sbMockDevice::SetWarningDialogEnabled(const nsAString & aWarning, PRBool aEnabled)
{
  return sbBaseDevice::SetWarningDialogEnabled(aWarning, aEnabled);
}

NS_IMETHODIMP sbMockDevice::GetWarningDialogEnabled(const nsAString & aWarning, PRBool *_retval)
{
  return sbBaseDevice::GetWarningDialogEnabled(aWarning, _retval);
}

NS_IMETHODIMP sbMockDevice::ResetWarningDialogs()
{
  return sbBaseDevice::ResetWarningDialogs();
}

NS_IMETHODIMP sbMockDevice::GetCurrentStatus(sbIDeviceStatus * *aCurrentStatus)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}


/* void Format(); */
NS_IMETHODIMP sbMockDevice::Format()
{
  return NS_ERROR_NOT_IMPLEMENTED;
}
/* readonly attribute boolean supportsReformat; */
NS_IMETHODIMP sbMockDevice::GetSupportsReformat(PRBool *_retval)
{
  NS_ENSURE_ARG_POINTER(_retval);
  *_retval = PR_FALSE;
  return NS_OK;
}