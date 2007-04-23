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

/** 
 * \file  sbLibraryManager.h
 * \brief Songbird Library Manager Definition.
 */

#ifndef __SB_LIBRARYMANAGER_H__
#define __SB_LIBRARYMANAGER_H__

#include <sbILibraryManager.h>

#include <nsAutoLock.h>
#include <nsCOMPtr.h>
#include <nsHashKeys.h>
#include <nsIGenericFactory.h>
#include <nsInterfaceHashtable.h>
#include <nsIObserver.h>
#include <nsTHashtable.h>

#define SONGBIRD_LIBRARYMANAGER_DESCRIPTION                \
  "Songbird Library Manager"
#define SONGBIRD_LIBRARYMANAGER_CONTRACTID                 \
  "@songbirdnest.com/Songbird/library/Manager;1"
#define SONGBIRD_LIBRARYMANAGER_CLASSNAME                  \
  "Songbird Library Manager"
#define SONGBIRD_LIBRARYMANAGER_CID                        \
{ /* ff27fd1d-183d-4c6d-89e7-1cd489f18bb9 */               \
  0xff27fd1d,                                              \
  0x183d,                                                  \
  0x4c6d,                                                  \
  { 0x89, 0xe7, 0x1c, 0xd4, 0x89, 0xf1, 0x8b, 0xb9 }       \
}

#define SB_PREFBRANCH_LIBRARY    "songbird.library."

#define SB_PREF_MAIN_LIBRARY     SB_PREFBRANCH_LIBRARY "main"
#define SB_PREF_WEB_LIBRARY      SB_PREFBRANCH_LIBRARY "web"
#define SB_PREF_DOWNLOAD_LIBRARY SB_PREFBRANCH_LIBRARY "download"

#define SB_GUID_MAIN_LIBRARY     "main@library.songbirdnest.com"
#define SB_GUID_WEB_LIBRARY      "web@library.songbirdnest.com"
#define SB_GUID_DOWNLOAD_LIBRARY "download@library.songbirdnest.com"

class nsIRDFDataSource;
class sbILibrary;
class sbILibraryFactory;

class sbLibraryManager : public sbILibraryManager,
                         public nsIObserver
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIOBSERVER
  NS_DECL_SBILIBRARYMANAGER

  sbLibraryManager();

  /**
   * See sbLibraryManager.cpp
   */
  nsresult Init();

private:
  ~sbLibraryManager();

  /**
   * See sbLibraryManager.cpp
   */
  static PLDHashOperator PR_CALLBACK
    AddLibrariesToCOMArrayCallback(nsStringHashKey::KeyType aKey,
                                   sbILibrary* aEntry,
                                   void* aUserData);

  /**
   * See sbLibraryManager.cpp
   */
  static PLDHashOperator PR_CALLBACK
    AddFactoriesToCOMArrayCallback(nsStringHashKey::KeyType aKey,
                                   sbILibraryFactory* aEntry,
                                   void* aUserData);

  /**
   * See sbLibraryManager.cpp
   */
  static PLDHashOperator PR_CALLBACK
    AssertAllLibrariesCallback(nsStringHashKey::KeyType aKey,
                               sbILibrary* aEntry,
                               void* aUserData);

  /**
   * See sbLibraryManager.cpp
   */
  static PLDHashOperator PR_CALLBACK
    ShutdownAllLibrariesCallback(nsStringHashKey::KeyType aKey,
                                 sbILibrary* aEntry,
                                 void* aUserData);

  /**
   * See sbLibraryManager.cpp
   */
  static PLDHashOperator PR_CALLBACK
    NotifyListenersLibraryRegisteredCallback(nsISupportsHashKey* aKey,
                                             void* aUserData);

  /**
   * See sbLibraryManager.cpp
   */
  static PLDHashOperator PR_CALLBACK
    NotifyListenersLibraryUnregisteredCallback(nsISupportsHashKey* aKey,
                                               void* aUserData);
  /**
   * See sbLibraryManager.cpp
   */
  static nsresult AssertLibrary(nsIRDFDataSource* aDataSource,
                                sbILibrary* aLibrary);

  /**
   * See sbLibraryManager.cpp
   */
  static nsresult UnassertLibrary(nsIRDFDataSource* aDataSource,
                                  sbILibrary* aLibrary);

  /**
   * See sbLibraryManager.cpp
   */
  nsresult GenerateDataSource();

  /**
   * See sbLibraryManager.cpp
   */
  void NotifyListenersLibraryRegistered(sbILibrary* aLibrary);

  /**
   * See sbLibraryManager.cpp
   */
  void NotifyListenersLibraryUnregistered(sbILibrary* aLibrary);

private:
  /**
   * \brief A hashtable that holds all the registered libraries.
   */
  nsInterfaceHashtableMT<nsStringHashKey, sbILibrary> mLibraryTable;

  /**
   * \brief A hashtable that holds all the registered library factories.
   */
  nsInterfaceHashtableMT<nsStringHashKey, sbILibraryFactory> mFactoryTable;

  /**
   * \brief An in-memory datasource that contains information about the
   *        registered libraries.
   */
  nsCOMPtr<nsIRDFDataSource> mDataSource;

  /**
   * \brief A list of listeners.
   */
  PRLock* mListenersLock;
  nsTHashtable<nsISupportsHashKey> mListeners;
};

#endif /* __SB_LIBRARYMANAGER_H__ */
