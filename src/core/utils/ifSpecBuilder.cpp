/* Copyright (c) 2022 Davor Cihlar
 *
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Davor Cihlar
 *     - initial implementation
 **********************************************************************/

#include <algorithm>
#include <cstdio>

#include "forte_printer.h"
#include "ifSpecBuilder.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "ifSpecBuilder_gen.cpp"
#endif

using namespace forte::core::util;


void CStringIdListSpecBuilder::setStaticList(const CStringDictionary::TStringId *paStaticList, std::size_t paItemsCount) {
  mDynamicList.clear();
  cmStaticList = paStaticList;
  mStaticListSize = paItemsCount;
}

int CStringIdListSpecBuilder::addString(CStringDictionary::TStringId paString) {
  if (!isGood()) {
    return -1;
  }
  if (cmStaticList) {
    mDynamicList.insert(mDynamicList.end(), cmStaticList, cmStaticList + mStaticListSize);
  }
  cmStaticList = nullptr;
  mStaticListSize = 0;
  mDynamicList.push_back(paString);
  return (int)mDynamicList.size() - 1;
}

int CStringIdListSpecBuilder::addString(const char *paString) {
  return addString(CStringDictionary::getInstance().insert(paString));
}

int CStringIdListSpecBuilder::findString(const char *paString) const {
  auto nString = CStringDictionary::getInstance().getId(paString);
  if (nString == CStringDictionary::scmInvalidStringId) {
    return -1;
  }
  return findString(nString);
}

int CStringIdListSpecBuilder::findString(CStringDictionary::TStringId paStringId) const {
  int retVal = -1;
  if (cmStaticList) {
    const auto end = cmStaticList + mStaticListSize;
    auto pos = std::find(cmStaticList, end, paStringId);
    if (pos != end) {
      retVal = (int)(pos - cmStaticList);
    }
  } else {
    auto pos = std::find(mDynamicList.begin(), mDynamicList.end(), paStringId);
    if (pos != mDynamicList.end()) {
      retVal = (int)(pos - mDynamicList.begin());
    }
  }
  return retVal;
}

std::size_t CStringIdListSpecBuilder::calcStorageSize() const {
  return cmStaticList ? 0 : mDynamicList.size() * sizeof(CStringDictionary::TStringId);
}


static bool makeName(char *paName, const char *paPrefix, int paNumber) {
  const int retVal = forte_snprintf(paName, sizeof(TIdentifier), "%s%d", paPrefix, paNumber);
  return (retVal < static_cast<int>(sizeof(TIdentifier)) && retVal > 0);
}

std::pair<int, int> CEventSpecBuilderBase::addEventRange(const char *paPrefix, int paRangeSize) {
  TIdentifier name;
  int firstId = (int)mNamesListBuilder.getNumStrings();
  int lastId = firstId;
  for (int i = 0; i < paRangeSize; ++i) {
    if (!makeName(name, paPrefix, i + 1)) {
      mIsGood = false;
      break;
    }
    lastId = addEvent(name);
  }
  return {firstId, lastId};
}

std::pair<int, int> CDataSpecBuilderBase::addDataRange(const char *paPrefix, int paRangeSize) {
  return addDataRange(paPrefix, paRangeSize, g_nStringIdANY);
}

std::pair<int, int> CDataSpecBuilderBase::addDataRange(const char *paPrefix, int paRangeSize, const char *paTypeName) {
  return addDataRange(paPrefix, paRangeSize, CStringDictionary::getInstance().insert(paTypeName));
}

std::pair<int, int> CDataSpecBuilderBase::addDataRange(const char *paPrefix, int paRangeSize, CStringDictionary::TStringId paTypeName) {
  TIdentifier name;
  int firstId = (int)mNamesListBuilder.getNumStrings();
  int lastId = firstId;
  for (int i = 0; i < paRangeSize; ++i) {
    if (!makeName(name, paPrefix, i + 1)) {
      mIsGood = false;
      break;
    }
    lastId = addData(name, paTypeName);
  }
  return {firstId, lastId};
}

std::tuple<const CStringDictionary::TStringId*, const CStringDictionary::TStringId*, TPortId>
CDataSpecBuilderBase::build(CMixedStorage &paStorage) const {
  auto nameData = mNamesListBuilder.build<TPortId>(paStorage);
  auto typeData = mTypesListBuilder.build<TPortId>(paStorage);
  return {std::get<0>(nameData), std::get<0>(typeData), std::get<1>(nameData) };
}


void CWithSpecBuilderBase::grow(std::size_t paNumEvents) {
  if (paNumEvents > mDynamicList.size()) {
    mDynamicList.resize(paNumEvents);
  }
}

void CWithSpecBuilderBase::setStaticBindings(const TDataIOID *paStaticBindings, const TForteInt16 *paStaticIndexes, std::size_t paNumEvents) {
  mDynamicList.clear();
  mStaticBindings = paStaticBindings;
  mStaticIndexes = paStaticIndexes;
  mNumStaticEvents = paNumEvents;
}

void CWithSpecBuilderBase::bind(TDataIOID paEventId, TDataIOID paDataId) {
  if (mStaticBindings) {
    mIsGood = false;
    return;
  }
  grow(paEventId + 1);
  mDynamicList[paEventId].push_back(paDataId);
}

void CWithSpecBuilderBase::bindRange(TDataIOID paEventId, TDataIOID paFirstDataId, TDataIOID paLastDataId) {
  for (TDataIOID runnerPort = paFirstDataId; runnerPort <= paLastDataId; ++runnerPort) {
    bind(paEventId, runnerPort);
  }
}

std::size_t CWithSpecBuilderBase::calcStorageSize(std::size_t paNumEvents) const {
  if (mStaticBindings) {
    return 0;
  }
  std::size_t sumSize = mDynamicList.size();
  for (const auto &lst : mDynamicList) {
    if (!lst.empty()) {
      sumSize += (lst.size() + 1) * sizeof(TDataIOID);
    }
    sumSize += sizeof(TForteInt16);
  }
  sumSize += sizeof(TForteInt16) * (paNumEvents - mDynamicList.size());
  return sumSize;
}

std::tuple<const TDataIOID*, const TForteInt16*> CWithSpecBuilderBase::build(CMixedStorage &paStorage, std::size_t paNumEvents) {
  // special case for building with static data
  if (mStaticBindings) {
    check(mNumStaticEvents == paNumEvents);
    return {mStaticBindings, mStaticIndexes};
  }

  // build with reference list
  auto pWiths = paStorage.end<TDataIOID>();
  for (const auto &lst : mDynamicList) {
    if (!lst.empty()) {
      paStorage.write(lst.data(), lst.size());
      paStorage.write<TDataIOID>(CFunctionBlock::scmWithListDelimiter);
    }
  }

  // build indexes list
  auto pIndexes = paStorage.end<TForteInt16>();
  TForteInt16 idx = 0;
  for (const auto &lst : mDynamicList) {
    if (lst.empty()) {
      paStorage.write<TForteInt16>(-1);
    } else {
      paStorage.write(idx);
      idx += (TForteInt16)(lst.size() + 1);
    }
  }
  // handle unspecified events
  check(mDynamicList.size() <= paNumEvents);
  for (std::size_t ei = mDynamicList.size(); ei < paNumEvents; ++ei) {
    paStorage.write<TForteInt16>(-1);
  }

  return {pWiths, pIndexes};
}


void CAdapterSpecBuilder::setStaticAdapters(const SAdapterInstanceDef *paStaticAdapters, std::size_t paAdaptersCount) {
  mDynamicList.clear();
  mStaticAdapters = paStaticAdapters;
  mStaticAdaptersCount = paAdaptersCount;
}

void CAdapterSpecBuilder::addAdapter(const CStringDictionary::TStringId paName, const CStringDictionary::TStringId paType, bool paIsPlug) {
  if (mStaticAdapters) {
    mDynamicList.insert(mDynamicList.end(), mStaticAdapters, mStaticAdapters + mStaticAdaptersCount);
  }
  mStaticAdapters = nullptr;
  mStaticAdaptersCount = 0;
  mDynamicList.push_back({paType, paName, paIsPlug});
}

void CAdapterSpecBuilder::addAdapter(const char *paName, const char *paType, bool paIsPlug) {
  auto &str_dict = CStringDictionary::getInstance();

  addAdapter(
      str_dict.insert(paName),
      str_dict.insert(paType),
      paIsPlug
  );
}

std::size_t CAdapterSpecBuilder::calcStorageSize() const {
  return mStaticAdapters ? 0 : mDynamicList.size() * sizeof(SAdapterInstanceDef);
}

std::tuple<const SAdapterInstanceDef*, TPortId> CAdapterSpecBuilder::build(CMixedStorage &paStorage) {
  if (mStaticAdapters) {
    return {mStaticAdapters, mStaticAdaptersCount};
  }
  const SAdapterInstanceDef *aidefPtr = paStorage.write(mDynamicList.data(), mDynamicList.size());
  return {aidefPtr, mDynamicList.size()};
}


bool CIfSpecBuilder::build(CMixedStorage &paStorage, SFBInterfaceSpec &paInterfaceSpec) {
  if (!isGood()) {
    return false;
  }

  std::size_t storageSize =
    mEI.calcStorageSize() + mEO.calcStorageSize() +
    mEITypes.calcStorageSize() + mEOTypes.calcStorageSize() +
    mDI.calcStorageSize() + mDO.calcStorageSize() +
    mIWith.calcStorageSize(mEI.getNumEvents()) + mOWith.calcStorageSize(mEO.getNumEvents()) +
    mAdapter.calcStorageSize();
  paStorage.reserve(storageSize);
  std::tie(paInterfaceSpec.mEINames, paInterfaceSpec.mNumEIs) = mEI.build(paStorage);
  std::tie(paInterfaceSpec.mEONames, paInterfaceSpec.mNumEOs) = mEO.build(paStorage);
  std::tie(paInterfaceSpec.mEITypeNames, paInterfaceSpec.mNumEIs) = mEITypes.build(paStorage);
  std::tie(paInterfaceSpec.mEOTypeNames, paInterfaceSpec.mNumEOs) = mEOTypes.build(paStorage);
  std::tie(
    paInterfaceSpec.mDINames, paInterfaceSpec.mDIDataTypeNames,
    paInterfaceSpec.mNumDIs
  ) = mDI.build(paStorage);
  std::tie(
    paInterfaceSpec.mDONames, paInterfaceSpec.mDODataTypeNames,
    paInterfaceSpec.mNumDOs
  ) = mDO.build(paStorage);
  std::tie(paInterfaceSpec.mEIWith, paInterfaceSpec.mEIWithIndexes) = mIWith.build(paStorage, mEI.getNumEvents());
  std::tie(paInterfaceSpec.mEOWith, paInterfaceSpec.mEOWithIndexes) = mOWith.build(paStorage, mEO.getNumEvents());
  std::tie(paInterfaceSpec.mAdapterInstanceDefinition, paInterfaceSpec.mNumAdapters) = mAdapter.build(paStorage);

  mIsGood = paStorage.size() <= storageSize;
  return isGood();
}

bool CIfSpecBuilder::isGood() const {
  return mEI.isGood() && mEO.isGood() && mDI.isGood() && mDO.isGood() && mIWith.isGood() && mOWith.isGood() && mEOTypes.isGood() && mEITypes.isGood() && mIsGood;
}
