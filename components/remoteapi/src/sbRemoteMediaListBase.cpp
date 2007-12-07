/*
//
// BEGIN SONGBIRD GPL
//
// This file is part of the Songbird web player.
//
// Copyright(c) 2005-2007 POTI, Inc.
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

#include "sbRemoteAPIUtils.h"
#include "sbRemoteMediaListBase.h"
#include "sbRemoteWrappingStringEnumerator.h"
#include "sbRemotePlayer.h"

#include <sbClassInfoUtils.h>
#include <sbIRemoteMediaList.h>
#include <sbIMediaItem.h>
#include <sbIMediaList.h>
#include <sbIMediaListView.h>
#include <sbIMediaListViewTreeView.h>
#include <sbIWrappedMediaItem.h>
#include <sbIWrappedMediaList.h>
#include <sbIPropertyManager.h>
#include <sbPropertiesCID.h>

#include <nsAutoPtr.h>
#include <nsITreeSelection.h>
#include <nsITreeView.h>
#include <nsStringGlue.h>
#include <prlog.h>

/*
 * To log this module, set the following environment variable:
 *   NSPR_LOG_MODULES=sbRemoteMediaList:5
 */
#ifdef PR_LOGGING
PRLogModuleInfo* gRemoteMediaListLog = nsnull;
#endif

#undef LOG
#define LOG(args) LOG_LIST(args)

// derived classes must impl nsIClassInfo
NS_IMPL_ISUPPORTS8(sbRemoteMediaListBase,
                   nsISecurityCheckedComponent,
                   sbISecurityAggregator,
                   sbIRemoteMediaList,
                   sbIMediaList,
                   sbIWrappedMediaList,
                   sbIWrappedMediaItem,
                   sbIMediaItem,
                   sbILibraryResource)

sbRemoteMediaListBase::sbRemoteMediaListBase(sbRemotePlayer* aRemotePlayer,
                                             sbIMediaList* aMediaList,
                                             sbIMediaListView* aMediaListView) :
  mRemotePlayer(aRemotePlayer),
  mMediaList(aMediaList),
  mMediaListView(aMediaListView)
{
  NS_ASSERTION(aRemotePlayer, "Null remote player!");
  NS_ASSERTION(aMediaList, "Null media list!");
  NS_ASSERTION(aMediaListView, "Null media list view!");

  mMediaItem = do_QueryInterface(mMediaList);
  NS_ASSERTION(mMediaItem, "Could not QI media list to media item");

  mMediaItem->GetLibrary(getter_AddRefs(mLibrary));

#ifdef PR_LOGGING
  if (!gRemoteMediaListLog) {
    gRemoteMediaListLog = PR_NewLogModule("sbRemoteMediaList");
  }
  LOG_LIST(("sbRemoteMediaListBase::sbRemoteMediaListBase()"));
#endif
}

sbRemoteMediaListBase::~sbRemoteMediaListBase()
{
  LOG_LIST(("sbRemoteMediaListBase::~sbRemoteMediaListBase()"));
}

// ---------------------------------------------------------------------------
//
//                          sbISecurityAggregator
//
// ---------------------------------------------------------------------------

NS_IMETHODIMP 
sbRemoteMediaListBase::GetRemotePlayer(sbIRemotePlayer * *aRemotePlayer)
{
  NS_ENSURE_STATE(mRemotePlayer);
  NS_ENSURE_ARG_POINTER(aRemotePlayer);

  nsresult rv;
  *aRemotePlayer = nsnull;

  nsCOMPtr<sbIRemotePlayer> remotePlayer;

  rv = mRemotePlayer->QueryInterface( NS_GET_IID( sbIRemotePlayer ), getter_AddRefs( remotePlayer ) );
  NS_ENSURE_SUCCESS( rv, rv );

  remotePlayer.swap( *aRemotePlayer );

  return NS_OK;
}

// ---------------------------------------------------------------------------
//
//                        sbIWrappedMediaList
//
// ---------------------------------------------------------------------------

already_AddRefed<sbIMediaItem>
sbRemoteMediaListBase::GetMediaItem()
{
  nsresult rv;

  nsCOMPtr<sbIMediaItem> mediaItem = do_QueryInterface(mMediaList, &rv);
  NS_ASSERTION(mediaItem, "Could not QI list to item");

  return mediaItem.forget();
}

already_AddRefed<sbIMediaList>
sbRemoteMediaListBase::GetMediaList()
{
  sbIMediaList* list = mMediaList;
  NS_ADDREF(list);
  return list;
}

// ---------------------------------------------------------------------------
//
//                        sbIMediaList
//
// ---------------------------------------------------------------------------

NS_IMETHODIMP
sbRemoteMediaListBase::GetItemByGuid(const nsAString& aGuid,
                                     sbIMediaItem** _retval)
{
  NS_ENSURE_ARG_POINTER(_retval);

  nsCOMPtr<sbIMediaItem> item;
  nsresult rv = mMediaList->GetItemByGuid(aGuid, getter_AddRefs(item));
  if (rv == NS_ERROR_NOT_AVAILABLE) {
    // This means that the item doesn't exist. Return null to be friendly to the
    // nice JS callers.
    *_retval = nsnull;
    return NS_OK;
  }
  NS_ENSURE_SUCCESS(rv, rv);

  return SB_WrapMediaItem(mRemotePlayer, item, _retval);
}

NS_IMETHODIMP
sbRemoteMediaListBase::GetItemByIndex(PRUint32 aIndex,
                                      sbIMediaItem **_retval)
{
  NS_ENSURE_ARG_POINTER(_retval);

  nsCOMPtr<sbIMediaItem> item;
  nsresult rv = mMediaList->GetItemByIndex(aIndex, getter_AddRefs(item));
  if (rv == NS_ERROR_NOT_AVAILABLE) {
    // This means that the item doesn't exist. Return null to be friendly to the
    // nice JS callers.
    *_retval = nsnull;
    return NS_OK;
  }
  NS_ENSURE_SUCCESS(rv, rv);

  return SB_WrapMediaItem(mRemotePlayer, item, _retval);
}

NS_IMETHODIMP
sbRemoteMediaListBase::EnumerateAllItems(sbIMediaListEnumerationListener *aEnumerationListener,
                                         PRUint16 aEnumerationType)
{
  NS_ENSURE_ARG_POINTER(aEnumerationListener);

  nsRefPtr<sbMediaListEnumerationListenerWrapper> wrapper(
    new sbMediaListEnumerationListenerWrapper(mRemotePlayer, aEnumerationListener));
  NS_ENSURE_TRUE(wrapper, NS_ERROR_OUT_OF_MEMORY);

  nsresult rv = mMediaList->EnumerateAllItems(wrapper, aEnumerationType);
  NS_ENSURE_SUCCESS(rv, rv);

  return NS_OK;
}

NS_IMETHODIMP
sbRemoteMediaListBase::EnumerateItemsByProperty(const nsAString& aPropertyID,
                                                const nsAString& aPropertyValue,
                                                sbIMediaListEnumerationListener* aEnumerationListener,
                                                PRUint16 aEnumerationType)
{
  NS_ENSURE_ARG_POINTER(aEnumerationListener);

  nsRefPtr<sbMediaListEnumerationListenerWrapper> wrapper(
    new sbMediaListEnumerationListenerWrapper(mRemotePlayer, aEnumerationListener));
  NS_ENSURE_TRUE(wrapper, NS_ERROR_OUT_OF_MEMORY);

  nsresult rv = mMediaList->EnumerateItemsByProperty(aPropertyID,
                                                     aPropertyValue,
                                                     wrapper,
                                                     aEnumerationType);
  NS_ENSURE_SUCCESS(rv, rv);

  return NS_OK;
}

NS_IMETHODIMP
sbRemoteMediaListBase::IndexOf(sbIMediaItem* aMediaItem,
                               PRUint32 aStartFrom,
                               PRUint32* _retval)
{
  NS_ENSURE_ARG_POINTER(aMediaItem);
  NS_ENSURE_ARG_POINTER(_retval);

  nsCOMPtr<sbIMediaItem> mediaItem;
  nsresult rv = SB_WrapMediaItem(mRemotePlayer,
                                 aMediaItem,
                                 getter_AddRefs(mediaItem));
  NS_ENSURE_SUCCESS(rv, rv);

  return mMediaList->IndexOf(mediaItem, aStartFrom, _retval);
}

NS_IMETHODIMP
sbRemoteMediaListBase::LastIndexOf(sbIMediaItem* aMediaItem,
                                   PRUint32 aStartFrom,
                                   PRUint32* _retval)
{
  NS_ENSURE_ARG_POINTER(aMediaItem);
  NS_ENSURE_ARG_POINTER(_retval);

  nsCOMPtr<sbIMediaItem> mediaItem;
  nsresult rv = SB_WrapMediaItem(mRemotePlayer,
                                 aMediaItem,
                                 getter_AddRefs(mediaItem));
  NS_ENSURE_SUCCESS(rv, rv);

  return mMediaList->LastIndexOf(mediaItem, aStartFrom, _retval);
}

NS_IMETHODIMP
sbRemoteMediaListBase::Contains(sbIMediaItem* aMediaItem, PRBool* _retval)
{
  NS_ENSURE_ARG_POINTER(aMediaItem);
  NS_ENSURE_ARG_POINTER(_retval);

  nsCOMPtr<sbIMediaItem> mediaItem;
  nsresult rv = SB_WrapMediaItem(mRemotePlayer,
                                 aMediaItem,
                                 getter_AddRefs(mediaItem));
  NS_ENSURE_SUCCESS(rv, rv);

  return mMediaList->Contains(mediaItem, _retval);
}

NS_IMETHODIMP
sbRemoteMediaListBase::Add(sbIMediaItem *aMediaItem)
{
  LOG_LIST(("sbRemoteMediaListBase::Add()"));
  NS_ENSURE_ARG_POINTER(aMediaItem);

  nsresult rv;
  nsCOMPtr<sbIWrappedMediaItem> wrappedMediaItem =
    do_QueryInterface(aMediaItem, &rv);
  NS_ENSURE_SUCCESS(rv, rv);

  nsCOMPtr<sbIMediaItem> internalMediaItem = wrappedMediaItem->GetMediaItem();
  NS_ENSURE_TRUE(internalMediaItem, NS_ERROR_FAILURE);

  rv = mMediaList->Add(internalMediaItem);
  if (NS_SUCCEEDED(rv)) {
    mRemotePlayer->GetNotificationManager()
      ->Action(sbRemoteNotificationManager::eEditedPlaylist, mLibrary);
  }
  NS_ENSURE_SUCCESS(rv, rv);

  return NS_OK;
}

NS_IMETHODIMP
sbRemoteMediaListBase::AddAll(sbIMediaList *aMediaList)
{
  NS_ENSURE_ARG_POINTER(aMediaList);

  nsresult rv;
  nsCOMPtr<sbIWrappedMediaList> wrappedMediaList =
    do_QueryInterface(aMediaList, &rv);
  NS_ENSURE_SUCCESS(rv, rv);

  nsCOMPtr<sbIMediaList> internalMediaList = wrappedMediaList->GetMediaList();
  NS_ENSURE_TRUE(internalMediaList, NS_ERROR_FAILURE);

  rv = mMediaList->AddAll(internalMediaList);
  if (NS_SUCCEEDED(rv)) {
    mRemotePlayer->GetNotificationManager()
      ->Action(sbRemoteNotificationManager::eEditedPlaylist, mLibrary);
  }
  NS_ENSURE_SUCCESS(rv, rv);

  return NS_OK;
}

NS_IMETHODIMP
sbRemoteMediaListBase::AddSome(nsISimpleEnumerator* aMediaItems)
{
  NS_ENSURE_ARG_POINTER(aMediaItems);

  nsRefPtr<sbUnwrappingSimpleEnumerator> wrapper(
    new sbUnwrappingSimpleEnumerator(aMediaItems));
  NS_ENSURE_TRUE(wrapper, NS_ERROR_OUT_OF_MEMORY);

  nsresult rv = mMediaList->AddSome(wrapper);
  if (NS_SUCCEEDED(rv)) {
    mRemotePlayer->GetNotificationManager()
      ->Action(sbRemoteNotificationManager::eEditedPlaylist, mLibrary);
  }
  NS_ENSURE_SUCCESS(rv, rv);

  return NS_OK;
}

NS_IMETHODIMP
sbRemoteMediaListBase::Remove(sbIMediaItem* aMediaItem)
{
  NS_ENSURE_ARG_POINTER(aMediaItem);
  LOG_LIST(("sbRemoteMediaListBase::Remove()"));

  nsresult rv;
  nsCOMPtr<sbIWrappedMediaItem> wrappedMediaItem =
    do_QueryInterface(aMediaItem, &rv);
  NS_ENSURE_SUCCESS(rv, rv);

  nsCOMPtr<sbIMediaItem> internalMediaItem = wrappedMediaItem->GetMediaItem();
  NS_ENSURE_TRUE(internalMediaItem, NS_ERROR_FAILURE);

  rv = mMediaList->Remove(internalMediaItem);
  if (NS_SUCCEEDED(rv)) {
    mRemotePlayer->GetNotificationManager()
      ->Action(sbRemoteNotificationManager::eEditedPlaylist, mLibrary);
  }
  NS_ENSURE_SUCCESS(rv, rv);

  return NS_OK;
}

NS_IMETHODIMP
sbRemoteMediaListBase::GetDistinctValuesForProperty(const nsAString &aPropertyID,
                                                    nsIStringEnumerator **_retval)
{
  NS_ENSURE_ARG_POINTER(_retval);
  LOG_LIST(("sbRemoteMediaListBase::GetDistinctValuesForProperty()"));

  // get enumeration of stuff
  nsCOMPtr<nsIStringEnumerator> enumeration;
  nsresult rv =
    mMediaList->GetDistinctValuesForProperty( aPropertyID,
                                              getter_AddRefs(enumeration) );
  NS_ENSURE_SUCCESS( rv, rv );

  nsRefPtr<sbRemoteWrappingStringEnumerator> wrapped(
    new sbRemoteWrappingStringEnumerator( enumeration, mRemotePlayer ) );
  NS_ENSURE_TRUE( wrapped, NS_ERROR_OUT_OF_MEMORY );

  rv = wrapped->Init();
  NS_ENSURE_SUCCESS( rv, rv );

  NS_ADDREF( *_retval = wrapped );

  return NS_OK;
}

// ---------------------------------------------------------------------------
//
//                        sbIRemoteMediaList
//
// ---------------------------------------------------------------------------

NS_IMETHODIMP
sbRemoteMediaListBase::GetView( sbIMediaListView **aView )
{
  LOG_LIST(("sbRemoteMediaListBase::GetView()"));
  NS_ENSURE_ARG_POINTER(aView);
  NS_ASSERTION(mMediaListView, "No View");
  NS_ADDREF( *aView = mMediaListView );
  return NS_OK;
}


// ---------------------------------------------------------------------------
//
//                    sbIMediaListEnumerationListener
//
// ---------------------------------------------------------------------------

NS_IMPL_ISUPPORTS1(sbMediaListEnumerationListenerWrapper,
                   sbIMediaListEnumerationListener)

sbMediaListEnumerationListenerWrapper::sbMediaListEnumerationListenerWrapper(sbRemotePlayer* aRemotePlayer,
                                                                             sbIMediaListEnumerationListener* aWrapped) :
  mRemotePlayer(aRemotePlayer),
  mWrapped(aWrapped)
{
  NS_ASSERTION(aRemotePlayer, "Null remote player!");
  NS_ASSERTION(aWrapped, "Null wrapped enumerator!");
}

NS_IMETHODIMP
sbMediaListEnumerationListenerWrapper::OnEnumerationBegin(sbIMediaList *aMediaList,
                                                           PRBool *_retval)
{
  NS_ENSURE_ARG_POINTER(aMediaList);
  NS_ENSURE_ARG_POINTER(_retval);

  nsCOMPtr<sbIMediaList> mediaList;
  nsresult rv = SB_WrapMediaList(mRemotePlayer,
                                 aMediaList,
                                 getter_AddRefs(mediaList));
  NS_ENSURE_SUCCESS(rv, rv);

  return mWrapped->OnEnumerationBegin(mediaList, _retval);
}

NS_IMETHODIMP
sbMediaListEnumerationListenerWrapper::OnEnumeratedItem(sbIMediaList *aMediaList,
                                                         sbIMediaItem *aMediaItem,
                                                         PRBool *_retval)
{
  NS_ENSURE_ARG_POINTER(aMediaList);
  NS_ENSURE_ARG_POINTER(aMediaItem);
  NS_ENSURE_ARG_POINTER(_retval);

  nsCOMPtr<sbIMediaList> mediaList;
  nsresult rv = SB_WrapMediaList(mRemotePlayer,
                                 aMediaList,
                                 getter_AddRefs(mediaList));
  NS_ENSURE_SUCCESS(rv, rv);

  nsCOMPtr<sbIMediaItem> mediaItem;
  rv = SB_WrapMediaItem(mRemotePlayer, aMediaItem, getter_AddRefs(mediaItem));
  NS_ENSURE_SUCCESS(rv, rv);

  return mWrapped->OnEnumeratedItem(mediaList, mediaItem, _retval);
}

NS_IMETHODIMP
sbMediaListEnumerationListenerWrapper::OnEnumerationEnd(sbIMediaList *aMediaList,
                                                         nsresult aStatusCode)
{
  NS_ENSURE_ARG_POINTER(aMediaList);

  nsCOMPtr<sbIMediaList> mediaList;
  nsresult rv = SB_WrapMediaList(mRemotePlayer,
                                 aMediaList,
                                 getter_AddRefs(mediaList));
  NS_ENSURE_SUCCESS(rv, rv);

  return mWrapped->OnEnumerationEnd(mediaList, aStatusCode);;
}

// ---------------------------------------------------------------------------
//
//                          nsISimpleEnumerator
//
// ---------------------------------------------------------------------------

NS_IMPL_ISUPPORTS1(sbUnwrappingSimpleEnumerator, nsISimpleEnumerator)

sbUnwrappingSimpleEnumerator::sbUnwrappingSimpleEnumerator(nsISimpleEnumerator* aWrapped) :
  mWrapped(aWrapped)
{
  NS_ASSERTION(aWrapped, "Null wrapped enumerator!");
}

NS_IMETHODIMP
sbUnwrappingSimpleEnumerator::HasMoreElements(PRBool *_retval)
{
  NS_ENSURE_ARG_POINTER(_retval);

  return mWrapped->HasMoreElements(_retval);
}

NS_IMETHODIMP
sbUnwrappingSimpleEnumerator::GetNext(nsISupports **_retval)
{
  NS_ENSURE_ARG_POINTER(_retval);

  nsresult rv;

  nsCOMPtr<nsISupports> supports;
  rv = mWrapped->GetNext(getter_AddRefs(supports));
  NS_ENSURE_SUCCESS(rv, rv);

  // if it's an indexed mediaItem, get the wrapped internal item.
  nsCOMPtr<sbIIndexedMediaItem> indexedMediaItem = do_QueryInterface(supports, &rv);
  if (NS_SUCCEEDED(rv)) {
    nsCOMPtr<sbIMediaItem> item;
    indexedMediaItem->GetMediaItem( getter_AddRefs(item) );
    NS_ENSURE_SUCCESS( rv, rv );

    // make the supports that item
    supports = do_QueryInterface( item, &rv );
    NS_ENSURE_SUCCESS( rv, rv );
  }

  nsCOMPtr<sbIWrappedMediaList> mediaList = do_QueryInterface(supports, &rv);
  if (NS_SUCCEEDED(rv)) {
    *_retval = mediaList->GetMediaList().get();
    return NS_OK;
  }

  nsCOMPtr<sbIWrappedMediaItem> mediaItem = do_QueryInterface(supports, &rv);
  if (NS_SUCCEEDED(rv)) {
    *_retval = mediaItem->GetMediaItem().get();
    return NS_OK;
  }

  return NS_ERROR_UNEXPECTED;
}
