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

#include "sbIDevice.h"
#include "sbBaseDeviceEventTarget.h"

#include <nsAutoPtr.h>
#include <nsCOMPtr.h>
#include <nsDeque.h>
#include <nsISupportsImpl.h>
#include <prlock.h>

class sbIMediaItem;
class sbIMediaList;

class sbBaseDeviceLibraryListener;
class sbDeviceBaseLibraryCopyListener;

class sbBaseDevice : public sbIDevice,
                     public sbBaseDeviceEventTarget
{
public:
  struct TransferRequest : public nsISupports {
    /* types of requests. not all types necessarily apply to all types of
     * devices, and devices may have custom types.
     * Request types that should result in delaying shutdown (e.g. writing to
     * the device) should have the write flag set.
     * The specific device may internally define more request types.
     */

    static const int REQUEST_FLAG_USER  = 0x80000000;
    static const int REQUEST_FLAG_WRITE = 0x40000000;

    /* note that type 0 is reserved */
    enum {
      REQUEST_RESERVED = 0,

      /* read requests */
      REQUEST_MOUNT,
      REQUEST_READ,
      REQUEST_EJECT,
      REQUEST_SUSPEND,
      
      /* write requests */
      REQUEST_WRITE = REQUEST_FLAG_WRITE + 1,
      REQUEST_DELETE,
      REQUEST_SYNC,
      REQUEST_WIPE,                    /* delete all files */
      REQUEST_MOVE,                    /* move an item in one playlist */
      REQUEST_UPDATE,
      REQUEST_NEW_PLAYLIST
    };
    
    int type;                          /* one of the REQUEST_* constants,
                                          or a custom type */
    nsCOMPtr<sbIMediaItem> item;       /* the item this request pertains to */
    nsCOMPtr<sbIMediaList> list;       /* the list this request is to act on */
    PRUint32 index;                    /* the index in the list for this action */

    PRUint32 batchCount;        /* the number of items in this batch
                                   (batch = run of requests of the same type) */

    NS_DECL_ISUPPORTS
  private:
    ~TransferRequest(){} /* we're refcounted, no manual deleting! */
  };
  
public:
  sbBaseDevice();
  ~sbBaseDevice();
  
  /* add a transfer/action request to the request queue */
  nsresult  PushRequest(const int aType,
                        sbIMediaItem* aItem = nsnull,
                        sbIMediaList* aList = nsnull);

  /* remove the next request to be processed; note that _retval will be null
     if there are no requests left */
  nsresult PopRequest(TransferRequest** _retval);

  /* get a reference to the next request without removing it; note that _retval
     will be null if there are no requests left */
  nsresult PeekRequest(TransferRequest** _retval);
  
  /* remove a given request from the transfer queue
     note: returns NS_OK on sucessful removal,
           and NS_SUCCESS_LOSS_OF_INSIGNIFICANT_DATA if no match was found.
     if the request is not unique, removes the first matching one */
  nsresult RemoveRequest(const int aType,
                         sbIMediaItem* aItem = nsnull,
                         sbIMediaList* aList = nsnull);
  
  /* clear the request queue */
  nsresult ClearRequests();
  
  /* A request has been added, process the request
     (or schedule it to be processed) */
  virtual nsresult ProcessRequest() = 0;

  /* sbIDevice */
  /* note to device implementors: just set mState directly. */
  NS_IMETHOD GetState(PRUint32 *aState);

protected:
  PRLock *mRequestLock;
  nsDeque/*<TransferRequest>*/ mRequests;
  nsDequeFunctor* mRequestDeallocator;
  PRInt32 mState;
  
  nsRefPtr<sbBaseDeviceLibraryListener> mLibraryListener;
  nsRefPtr<sbDeviceBaseLibraryCopyListener> mLibraryCopyListener;
};
