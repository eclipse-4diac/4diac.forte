/*******************************************************************************
 * Copyright (c) 2011-2014 fortiss and TU Wien ACIN.
 *               2023 Martin Erich Jobst
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *    Alois Zoitl - initial implementation and rework communication infrastructure
 *    Martin Jobst - account for new FB layout and varying data type size
 *******************************************************************************/
#ifndef LOCALCOMLAYER_H_
#define LOCALCOMLAYER_H_

#include "comlayer.h"
#include "../stringdict.h"
#include <forte_sync.h>
#include <vector>

class CIEC_ANY;

namespace forte {

  namespace com_infra {

    class CLocalComLayer : public CComLayer{

      public:
        CLocalComLayer(CComLayer* paUpperLayer, CBaseCommFB * paFB);
        ~CLocalComLayer() override;

        EComResponse sendData(void *paData, unsigned int paSize) override;
        EComResponse recvData(const void *, unsigned int ) override {
          return e_ProcessDataOk;
        }

        EComResponse processInterrupt() override {
          return e_ProcessDataOk;
        }

      protected:
        virtual void setRDs(forte::com_infra::CBaseCommFB& paSubl, CIEC_ANY **paSDs, TPortId paNumSDs);


        class CLocalCommGroup {
          public:
            using TLocalComLayerList = std::vector<CLocalComLayer *>;
            using TLocalComDataTypeList = std::vector<CStringDictionary::TStringId>;

            explicit CLocalCommGroup(CStringDictionary::TStringId paGroupName, TLocalComDataTypeList paDataTypes) :
                mGroupName(paGroupName), mPublList(), mSublList(), mDataTypes(paDataTypes){
            }

            CLocalCommGroup(const CLocalCommGroup& paLocalCommGroup) :
                mGroupName(paLocalCommGroup.mGroupName),
                mPublList(paLocalCommGroup.mPublList),
                mSublList(paLocalCommGroup.mSublList),
                mDataTypes(paLocalCommGroup.mDataTypes){
            }

            ~CLocalCommGroup() = default;

            CStringDictionary::TStringId mGroupName;
            TLocalComLayerList mPublList;
            TLocalComLayerList mSublList;
            TLocalComDataTypeList mDataTypes;
        };

        class CLocalCommGroupsManager{

          public:

            bool registerPubl(const CStringDictionary::TStringId paGroupID, CLocalComLayer *paLayer);
            bool registerPubl(const CStringDictionary::TStringId paGroupID, CLocalComLayer *paLayer, CIEC_ANY **paDataPins, TPortId paNumDataPins);
            void unregisterPubl(const CStringDictionary::TStringId paGroupID, CLocalComLayer *paLayer);

            bool registerSubl(const CStringDictionary::TStringId paGroupID, CLocalComLayer *paLayer);
            void unregisterSubl(const CStringDictionary::TStringId paGroupID, CLocalComLayer *paLayer);

            CLocalCommGroup* getComGroup(const CStringDictionary::TStringId paGroupID);

          private:
            using TLocalCommGroupList = std::vector<CLocalCommGroup>;

            CLocalCommGroupsManager() = default;

            TLocalCommGroupList::iterator getLocalCommGroupIterator(CStringDictionary::TStringId paID);

            CLocalCommGroup* findOrCreateLocalCommGroup(CStringDictionary::TStringId paID, CIEC_ANY **paDataPins, TPortId paNumDataPins);
            void checkForGroupRemoval(TLocalCommGroupList::iterator comGroupIt);

            bool isGroupIteratorForGroup(TLocalCommGroupList::iterator iter, CStringDictionary::TStringId paID){
              return (iter != mLocalCommGroups.end() && iter->mGroupName == paID);
            }

            static void removeListEntry(CLocalCommGroup::TLocalComLayerList  &paComLayerList, CLocalComLayer *paLayer);
            static CLocalCommGroup::TLocalComDataTypeList buildDataTypeList(CIEC_ANY **paDataPins, TPortId paNumDataPins);
            static bool checkDataTypes(const CLocalCommGroup& group, CIEC_ANY **paDataPins, TPortId paNumDataPins);


            /*!\brief The Sync object used locking the access to the internal used datastructures
             */
            CSyncObject mSync;


            TLocalCommGroupList mLocalCommGroups;

            friend class CLocalComLayer;

          public:
            CLocalCommGroupsManager(const CLocalCommGroupsManager &) = delete;
            CLocalCommGroupsManager &operator =(const CLocalCommGroupsManager&) = delete;
        };


        static CLocalCommGroupsManager& getLocalCommGroupsManager(){
          return smLocalCommGroupsManager;
        }

        CStringDictionary::TStringId mGroupID;

      private:
        static CLocalCommGroupsManager smLocalCommGroupsManager;

        EComResponse openConnection(char *const paLayerParameter) override;
        void closeConnection() override;
    };
  }

}

#endif /* LOCALCOMLAYER_H_ */
