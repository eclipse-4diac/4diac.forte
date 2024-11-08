/*********************************************************************
 * Copyright (c) 2022 Davor Cihlar
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

#ifndef _IF_SPEC_BUILDER_H_
#define _IF_SPEC_BUILDER_H_

#include <vector>
#include <array>
#include <tuple>
#include <funcbloc.h>

#include "mixedStorage.h"

namespace forte::core::util {

class CInputSpecTag;    ///< helper class for distinguishing inputs from outputs (not an actual class)
class COutputSpecTag;   ///< helper class for distinguishing outputs from intputs (not an actual class)
class CDataSpecTag;     ///< helper class for distinguishing data from events (not an actual class)
class CEventSpecTag;    ///< helper class for distinguishing events from data (not an actual class)


/**
 * @brief Reference to a port within CIfSpecBuilder.
 *
 * This is usually returned when adding a port.
 *
 * @tparam TypeTag port type (data or event, CDataSpecTag or CEventSpecTag)
 * @tparam DirTag port direction (input or output, CInputSpecTag or COutputSpecTag)
 */
template<class TypeTag, class DirTag>
class CSpecReference {
  public:
    constexpr CSpecReference() = default;
    constexpr CSpecReference(int paRef) : mRef(paRef >= 0 ? static_cast<TDataIOID>(paRef) : scmMaxRefValue) {
    }

    /**
     * @brief Checks if reference is valid
     * @return true if valid
     */
    constexpr bool isValid() const {
      return mRef != scmMaxRefValue;
    }

    /**
     * @brief Dereferences the reference (converts to index as integer)
     * @return port index
     */
    constexpr auto operator*() const {
      return mRef;
    }

  private:
    static constexpr auto scmMaxRefValue = std::numeric_limits<TDataIOID>::max();

    TDataIOID mRef = scmMaxRefValue;
};

/**
 * @brief Reference to a port range within CIfSpecBuilder.
 *
 * This is usually returned when adding a port range.
 * The range can not be empty.
 *
 * @tparam TypeTag port type (data or event, CDataSpecTag or CEventSpecTag)
 * @tparam DirTag port direction (input or output, CInputSpecTag or COutputSpecTag)
 */
template<class TypeTag, class DirTag>
class CSpecReferenceRange {
  public:
    using TCSpecReference = CSpecReference<TypeTag, DirTag>;

    TCSpecReference mFirst;   ///< first port reference
    TCSpecReference mLast;    ///< last port reference

    constexpr CSpecReferenceRange() = default;
    constexpr CSpecReferenceRange(TCSpecReference paFirst, TCSpecReference paLast)
      : mFirst(paFirst), mLast(paLast)
    {}
    constexpr CSpecReferenceRange(std::pair<int, int> paRangePair)
      : CSpecReferenceRange(std::get<0>(paRangePair), std::get<1>(paRangePair))
    {}

    /**
     * @brief Access one port from within the range.
     * @param offset offset within the range
     * @return reference to one port
     */
    constexpr TCSpecReference operator[](int paOffset) const {
      TDataIOID id = *mFirst + paOffset;
      return { isValid() && id >= *mFirst && id <= *mLast ? static_cast<int>(id) : -1 };
    }

    /**
     * @brief Checks if range is valid
     * @return true if valid
     */
    constexpr bool isValid() const {
      return mFirst.isValid() && mLast.isValid();
    }
};

/**
 * @brief Common string list handler for CDataSpecBuilder and CEventSpecBuilder.
 *
 * It supports both static and dynamic allocation.
 */
class CStringIdListSpecBuilder {
  public:
    CStringIdListSpecBuilder(std::size_t paMaxItems) : cmMaxItems(paMaxItems)
    {}

    /**
     * @brief Sets list to the statically allocated one.
     * @param paStaticList statically allocated list
     * @param paItemsCount number of items in the list
     */
    void setStaticList(const CStringDictionary::TStringId *paStaticList, std::size_t paItemsCount);

    /**
     * @brief Add string from dictionary to list.
     * @param paStringId string ID to add
     * @return index of the added string
     */
    int addString(const CStringDictionary::TStringId paStringId);
    /**
     * @brief Add C string to list.
     *
     * The string will be first added to CStringDictionary.
     *
     * @param paString C string to add
     * @return index of the added string
     */
    int addString(const char *paString);

    /**
     * @brief Returns the number of added strings.
     * @return number of added strings
     */
    std::size_t getNumStrings() const {
      return cmStaticList ? mStaticListSize : mDynamicList.size();
    }

    /**
     * @brief Refurns index of the specified C string.
     * @param paString string to find
     * @return index of the specified string
     */
    int findString(const char *paString) const;
    /**
     * @brief Refurns index of the specified dictionary string ID.
     * @param paStringId string ID to find
     * @return index of the specified string
     */
    int findString(CStringDictionary::TStringId paStringId) const;

    /**
     * @brief Calculates required dynamic data size.
     * @return required dynamic data size
     */
    std::size_t calcStorageSize() const;

    template<typename IndexType>
    std::tuple<const CStringDictionary::TStringId*, IndexType> build(CMixedStorage &paStorage) const {
      if (cmStaticList) {
        return {cmStaticList, mStaticListSize};
      }
      const CStringDictionary::TStringId* listPtr = paStorage.write(mDynamicList.data(), mDynamicList.size());
      return {listPtr, mDynamicList.size()};
    }

    /**
     * @brief Checks configuration status.
     * @return true if everything's ok
     */
    bool isGood() const { return getNumStrings() <= cmMaxItems; }

  private:
    const std::size_t cmMaxItems;
    std::vector<CStringDictionary::TStringId> mDynamicList;
    std::size_t mStaticListSize = 0;
    const CStringDictionary::TStringId *cmStaticList = nullptr;
};

/**
 * @brief Base helper for CIfSpecBuilder managing events.
 */
class CEventSpecBuilderBase {
  public:
    /**
     * @brief Set statically defined configuration.
     * @param paStaticNames see SFBInterfaceSpec.mEINames / SFBInterfaceSpec.mEONames
     * @param paEventsCount see SFBInterfaceSpec.mNumEIs / SFBInterfaceSpec.mNumEOs
     */
    void setStaticEvents(const CStringDictionary::TStringId *paStaticNames, std::size_t paEventsCount) {
      mNamesListBuilder.setStaticList(paStaticNames, paEventsCount);
    }
    /**
     * @brief Sets statically defined configuration through std::array.
     * @tparam N see SFBInterfaceSpec.mNumEIs / SFBInterfaceSpec.mNumEOs; should be automatically deduced
     * @param paStaticNames see SFBInterfaceSpec.mEINames / SFBInterfaceSpec.mEONames
     */
    template<std::size_t N>
    void setStaticEvents(const std::array<CStringDictionary::TStringId, N> &paStaticNames) {
      setStaticEvents(paStaticNames.data(), paStaticNames.size());
    }

    /**
     * @brief Gets number of added events.
     * @return number of added events
     */
    auto getNumEvents() const {
      return mNamesListBuilder.getNumStrings();
    }

    /**
     * @brief Finds port index from event port name.
     * @param paName port name
     * @return port index or -1 if not found
     */
    template<typename T>
    int findEvent(T paName) const {
      return mNamesListBuilder.findString(paName);
    }

    /**
     * @brief Calculates required dynamic data size.
     * @return required dynamic data size
     */
    auto calcStorageSize() const {
      return mNamesListBuilder.calcStorageSize();
    }
    auto build(CMixedStorage &paStorage) const {
      return mNamesListBuilder.build<TEventID>(paStorage);
    }

    /**
     * @brief Checks configuration status.
     * @return true if everything's ok
     */
    bool isGood() const {
      return mNamesListBuilder.isGood() && mIsGood;
    }

  private:
    static constexpr auto scmMaxEvents = CFunctionBlock::scmMaxInterfaceEvents;
    bool mIsGood = true;
    CStringIdListSpecBuilder mNamesListBuilder{scmMaxEvents};

  protected:
    template<typename NameType>
    int addEvent(NameType paName) {
      return mNamesListBuilder.addString(paName);
    }

    std::pair<int, int> addEventRange(const char *paPrefix, int paRangeSize);
};

/**
 * @brief Helper for CIfSpecBuilder managing events with direction dependency.
 *
 * Template is used to make input and output events incompatible.
 *
 * @tparam DirTag defines input or output events
 */
template<class DirTag>
class CEventSpecBuilder : public CEventSpecBuilderBase {
  public:
    using TCSpecReference = CSpecReference<CEventSpecTag, DirTag>;
    using TCSpecReferenceRange = CSpecReferenceRange<CEventSpecTag, DirTag>;

    /**
     * @brief Adds event port.
     * @param paName port name
     * @return reference to the added port
     */
    template<typename TNameType>
    TCSpecReference addEvent(TNameType paName) {
      return CEventSpecBuilderBase::addEvent(paName);
    }

    /**
     * @brief Adds a range of numerated event ports with the same name prefix.
     * @param paPrefix name prefix
     * @param paRangeSize number of event ports in range
     * @return reference to the whole range added
     */
    TCSpecReferenceRange addEventRange(const char *paPrefix, int paRangeSize) {
      return CEventSpecBuilderBase::addEventRange(paPrefix, paRangeSize);
    }

    /**
     * @brief Access reference of a given port.
     * @return reference
     */
    template<typename TNameType>
    TCSpecReference operator[] (TNameType paName) const {
      return { findEvent(paName) };
    }
};

/**
 * @brief Base helper for CIfSpecBuilder managing data.
 */
class CDataSpecBuilderBase {
  public:
    /**
     * @brief Sets statically defined configuration.
     * @param paStaticDataNames see SFBInterfaceSpec.mDINames / SFBInterfaceSpec.mDONames
     * @param paStaticTypeNames see SFBInterfaceSpec.mDIDataTypeNames / SFBInterfaceSpec.mDODataTypeNames
     * @param paDataCount see SFBInterfaceSpec.mNumDIs / SFBInterfaceSpec.mNumDOs
     */
    void setStaticData(const CStringDictionary::TStringId *paStaticDataNames, const CStringDictionary::TStringId *paStaticTypeNames, std::size_t paDataCount) {
      mNamesListBuilder.setStaticList(paStaticDataNames, paDataCount);
      mTypesListBuilder.setStaticList(paStaticTypeNames, paDataCount);
    }
    /**
     * @brief Sets statically defined configuration through std::array.
     * @tparam N see SFBInterfaceSpec.mNumDIs / SFBInterfaceSpec.mNumDOs; should be automatically deduced
     * @param paStaticDataNames see SFBInterfaceSpec.mDINames / SFBInterfaceSpec.mDONames
     * @param paStaticTypeNames see SFBInterfaceSpec.mDIDataTypeNames / SFBInterfaceSpec.mDODataTypeNames
     */
    template<std::size_t N>
    void setStaticData(const std::array<CStringDictionary::TStringId, N> &paStaticDataNames, const std::array<CStringDictionary::TStringId, N> &paStaticTypeNames) {
      setStaticData(paStaticDataNames.data(), paStaticTypeNames.data(), N);
    }

    /**
     * @brief Finds port index from data port name.
     * @param paName port name
     * @return port index or -1 if not found
     */
    template<typename T>
    int findData(T paName) const {
      return mNamesListBuilder.findString(paName);
    }

    /**
     * @brief Calculates required dynamic data size.
     * @return required dynamic data size
     */
    std::size_t calcStorageSize() const {
      return mNamesListBuilder.calcStorageSize() + mTypesListBuilder.calcStorageSize();
    }
    std::tuple<const CStringDictionary::TStringId*, const CStringDictionary::TStringId*, TPortId> build(CMixedStorage &paStorage) const;

    /**
     * @brief Checks configuration status.
     * @return true if everything's ok
     */
    bool isGood() const {
      return mNamesListBuilder.isGood() && mTypesListBuilder.isGood() && mIsGood;
    }

  private:
    static constexpr auto scmMaxData = CFunctionBlock::scmMaxInterfaceEvents;
    bool mIsGood = true;
    CStringIdListSpecBuilder mNamesListBuilder{scmMaxData};
    CStringIdListSpecBuilder mTypesListBuilder{scmMaxData};

  protected:
    template<typename TNameType1, typename TNameType2>
    int addData(TNameType1 paName, TNameType2 paTypeName) {
      mNamesListBuilder.addString(paName);
      return mTypesListBuilder.addString(paTypeName);
    }
    std::pair<int, int> addDataRange(const char *paPrefix, int paRangeSize);
    std::pair<int, int> addDataRange(const char *paPrefix, int paRangeSize, CStringDictionary::TStringId paTypeName);
    std::pair<int, int> addDataRange(const char *paPrefix, int paRangeSize, const char *paTypeName);
};

/**
 * @brief Helper for CIfSpecBuilder managing data with direction dependency.
 *
 * Template is used to make input and output data incompatible.
 *
 * @tparam DirTag defines input or output data
 */
template<class DirTag>
class CDataSpecBuilder : public CDataSpecBuilderBase {
  public:
    using TCSpecReference = CSpecReference<CDataSpecTag, DirTag>;
    using TCSpecReferenceRange = CSpecReferenceRange<CDataSpecTag, DirTag>;

    /**
     * @brief Adds data port.
     * @param paName port name
     * @param paTypeName port data type name
     * @return reference to the added port
     */
    template<typename TNameType1, typename TNameType2>
    TCSpecReference addData(TNameType1 paName, TNameType2 paTypeName) {
      return CDataSpecBuilderBase::addData(paName, paTypeName);
    }

    /**
     * @brief Adds a range of numerated data ports with the same name prefix and of ANY type.
     * @param paPrefix name prefix
     * @param paRangeSize number of data ports in range
     * @return reference to the whole range added
     */
    TCSpecReferenceRange addDataRange(const char *paPrefix, int paRangeSize) {
      return CDataSpecBuilderBase::addDataRange(paPrefix, paRangeSize);
    }
    /**
     * @brief Adds a range of numerated data ports with the same name prefix.
     * @param paPrefix name prefix
     * @param paRangeSize number of data ports in range
     * @param paTypeName data type name for every port
     * @return reference to the whole range added
     */
    template<typename TNameType>
    TCSpecReferenceRange addDataRange(const char *paPrefix, int paRangeSize, TNameType paTypeName) {
      return CDataSpecBuilderBase::addDataRange(paPrefix, paRangeSize, paTypeName);
    }

    /**
     * @brief Access reference of a given port.
     * @return reference
     */
    template<typename TNameType>
    TCSpecReference operator[] (TNameType paName) const {
      return { findData(paName) };
    }
};

/**
 * @brief Base helper for CIfSpecBuilder managing bindings (withs).
 *
 * This base class is unaware of data and event directions so
 * it's not recommended to be used directly.
 */
class CWithSpecBuilderBase {
  public:
    /**
     * @brief Sets statically defined configuration.
     * @param paStaticBindings see SFBInterfaceSpec.mEIWith / SFBInterfaceSpec.mEOWith
     * @param paStaticIndexes see SFBInterfaceSpec.mEIWithIndexes / SFBInterfaceSpec.mEOWithIndexes
     * @param paNumEvents see SFBInterfaceSpec.mNumEIs / SFBInterfaceSpec.mNumEOs
     */
    void setStaticBindings(const TDataIOID *paStaticBindings, const TForteInt16 *paStaticIndexes, std::size_t paNumEvents);
    /**
     * @brief Sets statically defined configuration through std::array.
     * @tparam NBindings number of bindings; should be automatically deduced
     * @tparam NEvents see SFBInterfaceSpec.mNumEIs / SFBInterfaceSpec.mNumEOs; should be automatically deduced
     * @param paStaticBindings see SFBInterfaceSpec.mEIWith / SFBInterfaceSpec.mEOWith
     * @param paStaticIndexes see SFBInterfaceSpec.mEIWithIndexes / SFBInterfaceSpec.mEOWithIndexes
     */
    template<std::size_t NBindings, std::size_t NEvents>
    void setStaticBindings(const std::array<TDataIOID, NBindings> &paStaticBindings, const std::array<TForteInt16, NEvents> &paStaticIndexes) {
      setStaticBindings(paStaticBindings.data(), paStaticIndexes.data(), NEvents);
    }

    /**
     * @brief Binds data to event.
     * @param paEventId event port id
     * @param paDataId data port id
     */
    void bind(TDataIOID paEventId, TDataIOID paDataId);
    /**
     * @brief Binds multiple data to a single event.
     * @param paEventId event port id
     * @param paDataId a list of data port ids
     */
    void bind(TDataIOID paEventId, std::initializer_list<TDataIOID> paDataIds) {
      for (auto dataId : paDataIds) {
        bind(paEventId, dataId);
      }
    }
    /**
     * @brief Binds a range of data ports to an event.
     * @param paEventId event port id
     * @param paFirstDataId first data port id
     * @param paLastDataId last data port id
     */
    void bindRange(TDataIOID paEventId, TDataIOID paFirstDataId, TDataIOID paLastDataId);

    /**
     * @brief Calculates required dynamic data size.
     * @param paNumEvents number of events in the FB
     * @return required dynamic data size
     */
    std::size_t calcStorageSize(std::size_t paNumEvents) const;
    std::tuple<const TDataIOID*, const TForteInt16*> build(CMixedStorage &paStorage, std::size_t paNumEvents);

    /**
     * @brief Checks configuration status.
     * @return true if everything's ok
     */
    bool isGood() const { return mIsGood; }

  private:
    bool mIsGood = true;
    const TDataIOID *mStaticBindings = nullptr;
    const TForteInt16 *mStaticIndexes = nullptr;
    std::size_t mNumStaticEvents = 0;
    std::vector<std::vector<TDataIOID>> mDynamicList;

    void grow(std::size_t paNumEvents);

  protected:
    bool check(bool paState) {
      mIsGood = mIsGood && paState;
      return isGood();
    }
};

/**
 * @brief Helper for CIfSpecBuilder managing bindings (withs) with direction dependency.
 *
 * If explicit with specification is not required then simple and automatic binding
 * through CIfSpecBuilder is recommended.
 *
 * Template is used to make input and output withs incompatible.
 *
 * @tparam DirTag defines input or output withs
 */
template<class DirTag>
class CWithSpecBuilder : public CWithSpecBuilderBase {
  public:
    using TCSpecEventReference = CSpecReference<CEventSpecTag, DirTag>;
    using TCSpecDataReference = CSpecReference<CDataSpecTag, DirTag>;
    using TCSpecDataReferenceRange = CSpecReferenceRange<CDataSpecTag, DirTag>;

    /**
     * @brief Add a binding with a single data port.
     * @param paEventRef event to bind to
     * @param paDataRef data
     */
    void bind(TCSpecEventReference paEventRef, TCSpecDataReference paDataRef) {
      if (check(paEventRef.isValid() && paDataRef.isValid())) {
        CWithSpecBuilderBase::bind(*paEventRef, *paDataRef);
      }
    }
    /**
     * @brief Add a binding with multiple data ports.
     * @param paEventRef event to bind to
     * @param paDataRefs list with data ports
     */
    void bind(TCSpecEventReference paEventRef, std::initializer_list<TCSpecDataReference> paDataRefs) {
      check(paEventRef.isValid());
      for (auto ref : paDataRefs) {
        if (!check(ref.isValid()))
            break;
        bind(paEventRef, static_cast<int>(*ref));
      }
    }

    /**
     * @brief Add bindings to a range of data ports.
     * @param paEventRef event to bind to
     * @param paFirstDataRef first data port
     * @param paLastDataRef last data port
     */
    void bindRange(TCSpecEventReference paEventRef, TCSpecDataReference paFirstDataRef, TCSpecDataReference paLastDataRef) {
      if (check(paEventRef.isValid() && paFirstDataRef.isValid() && paLastDataRef.isValid())) {
        CWithSpecBuilderBase::bindRange(*paEventRef, *paFirstDataRef, *paLastDataRef);
      }
    }
    /**
     * @brief Add bindings to a range of data ports.
     * @param paEventRef event to bind to
     * @param paDataRefRange data port range
     */
    void bindRange(TCSpecEventReference paEventRef, TCSpecDataReferenceRange paDataRefRange) {
      if (check(paEventRef.isValid() && paDataRefRange.isValid())) {
        CWithSpecBuilderBase::bindRange(*paEventRef, *paDataRefRange.mFirst, *paDataRefRange.mLast);
      }
    }
};

/**
 * @brief Helper for CIfSpecBuilder managing adapters.
 */
class CAdapterSpecBuilder {
  public:
    /**
     * @brief Set statically defined configuration.
     * @param paStaticAdapters see SFBInterfaceSpec.mAdapterInstanceDefinition
     * @param paAdaptersCount see SFBInterfaceSpec.mNumAdapters
     */
    void setStaticAdapters(const SAdapterInstanceDef *paStaticAdapters, std::size_t paAdaptersCount);

    /**
     * @brief Sets statically defined configuration through std::array.
     * @tparam N see SFBInterfaceSpec.mNumAdapters
     * @param paStaticAdapters see SFBInterfaceSpec.mAdapterInstanceDefinition
     */
    template<std::size_t N>
    void setStaticAdapters(const std::array<SAdapterInstanceDef, N> &paStaticAdapters) {
      setStaticAdapters(paStaticAdapters.data(), paStaticAdapters.size());
    }

    /**
     * @brief Adds adapter port (socket/plug).
     * @param paName port name
     * @param paTypeName port type (adapter name)
     * @param paIsPlug true when port is plug (output)
     */
    void addAdapter(const CStringDictionary::TStringId paName, const CStringDictionary::TStringId paType, bool paIsPlug);

    /**
     * @brief Adds adapter port (socket/plug) using C strings.
     *
     * C strings are automatically converted to CStringDictionary.
     *
     * @param paName port name
     * @param paTypeName port type (adapter name)
     * @param paIsPlug true when port is plug (output)
     */
    void addAdapter(const char *paName, const char *paType, bool paIsPlug);

    /**
     * @brief Calculates required dynamic data size.
     * @return required dynamic data size
     */
    std::size_t calcStorageSize() const;
    std::tuple<const SAdapterInstanceDef*, TPortId> build(CMixedStorage &paStorage);

  private:
    std::vector<SAdapterInstanceDef> mDynamicList;
    std::size_t mStaticAdaptersCount = 0;
    const SAdapterInstanceDef *mStaticAdapters = nullptr;
};

/**
 * @brief Base helper for CAdapterSpecBuilder.
 */
class CAdapterDirHelperBase {
  public:
    /**
     * @brief Adds adapter port (socket/plug).
     * @param paName port name
     * @param paTypeName port type (adapter name)
     * @tparam TNameType string type
     */
    template<typename TNameType>
    void addAdapter(TNameType paName, TNameType paTypeName) {
      mBuilder.addAdapter(paName, paTypeName, mIsPlug);
    }

  protected:
    constexpr CAdapterDirHelperBase(CAdapterSpecBuilder &paBuilder, bool paIsPlug)
      : mBuilder(paBuilder), mIsPlug(paIsPlug)
    {}

  private:
    CAdapterSpecBuilder &mBuilder;
    bool mIsPlug;
};

/**
 * @brief Helper for CAdapterSpecBuilder handling different directions.
 *
 * @tparam DirTag defines input or output adapter
 */
template<class DirTag>
class CAdapterDirHelper;

template<>
class CAdapterDirHelper<CInputSpecTag> : public CAdapterDirHelperBase {
  public:
    constexpr CAdapterDirHelper(CAdapterSpecBuilder &paBuilder)
      : CAdapterDirHelperBase(paBuilder, false)
    {}
};

template<>
class CAdapterDirHelper<COutputSpecTag> : public CAdapterDirHelperBase {
  public:
    constexpr CAdapterDirHelper(CAdapterSpecBuilder &paBuilder)
      : CAdapterDirHelperBase(paBuilder, true)
    {}
};

/**
 * @brief @ref SFBInterfaceSpec structure builder
 *
 * Simplifies filling out @ref SFBInterfaceSpec structure and
 * memory management that goes along with it.
 */
class CIfSpecBuilder {
  public:
    CEventSpecBuilder<CInputSpecTag>  mEI;       ///< event inputs
    CEventSpecBuilder<CInputSpecTag>  mEITypes;
    CEventSpecBuilder<COutputSpecTag> mEO;       ///< event outputs
    CEventSpecBuilder<COutputSpecTag> mEOTypes;
    CDataSpecBuilder<CInputSpecTag>   mDI;       ///< data inputs
    CDataSpecBuilder<COutputSpecTag>  mDO;       ///< data outputs
    CWithSpecBuilder<CInputSpecTag>   mIWith;    ///< input withs
    CWithSpecBuilder<COutputSpecTag>  mOWith;    ///< output withs
    CAdapterSpecBuilder               mAdapter;  ///< all adapters
    CAdapterDirHelper<CInputSpecTag>  mIAdapter{mAdapter}; ///< input adapters
    CAdapterDirHelper<COutputSpecTag> mOAdapter{mAdapter}; ///< output adapters

    /**
     * @brief Binds event to a single data port.
     * @tparam DirTag defines event/data direction; should be automatically deduced
     * @param paEventRef event from #mEI or #mEO
     * @param paDataRef data from #mDI or #mDO
     */
    template<class DirTag>
    void bind(CSpecReference<CEventSpecTag, DirTag> paEventRef, CSpecReference<CDataSpecTag, DirTag> paDataRef) {
      getWithFromDir(paEventRef).bind(paEventRef, paDataRef);
    }
    /**
     * @brief Binds event to multiple data ports.
     * @tparam DirTag defines event/data direction; should be automatically deduced
     * @param paEventRef event from #mEI or #mEO
     * @param paDataRef multiple data from #mDI or #mDO
     */
    template<class DirTag>
    void bind(CSpecReference<CEventSpecTag, DirTag> paEventRef, std::initializer_list<CSpecReference<CDataSpecTag, DirTag>> &&paDataRef) {
      getWithFromDir(paEventRef).bind(paEventRef, std::move(paDataRef));
    }
    /**
     * @brief Binds event to data port range.
     * @tparam DirTag defines event/data direction; should be automatically deduced
     * @param paEventRef event from #mEI or #mEO
     * @param paFirstDataRef first data from #mDI or #mDO
     * @param paFirstDataRef last data from #mDI or #mDO
     */
    template<class DirTag>
    void bindRange(CSpecReference<CEventSpecTag, DirTag> paEventRef, CSpecReference<CDataSpecTag, DirTag> paFirstDataRef, CSpecReference<CDataSpecTag, DirTag> paLastDataRef) {
      getWithFromDir(paEventRef).bindRange(paEventRef, paFirstDataRef, paLastDataRef);
    }
    /**
     * @brief Binds event to data port range.
     * @tparam DirTag defines event/data direction; should be automatically deduced
     * @param paEventRef event from #mEI or #mEO
     * @param paDataRefRange data range from #mDI or #mDO
     */
    template<class DirTag>
    void bindRange(CSpecReference<CEventSpecTag, DirTag> paEventRef, CSpecReferenceRange<CDataSpecTag, DirTag> paDataRefRange) {
      getWithFromDir(paEventRef).bindRange(paEventRef, paDataRefRange);
    }

    /**
     * @brief Builds @ref SFBInterfaceSpec and fills storage with dynamic data.
     *
     * Before calling this function events, data and withs need to be configured.
     *
     * @param paStorage storage containing dynamic data
     * @param paInterfaceSpec @ref SFBInterfaceSpec to fill out
     * @return isGood()
     */
    bool build(CMixedStorage &paStorage, SFBInterfaceSpec &paInterfaceSpec);

    /**
     * @brief Checks builder status
     * @return true if everything's ok
     */
    bool isGood() const;

  private:
    bool mIsGood = true;

    constexpr CWithSpecBuilder<CInputSpecTag>& getWithFromDir(CSpecReference<CEventSpecTag, CInputSpecTag>) {
      return mIWith;
    }
    constexpr CWithSpecBuilder<COutputSpecTag>& getWithFromDir(CSpecReference<CEventSpecTag, COutputSpecTag>) {
      return mOWith;
    }
};

}

#endif /* _IF_SPEC_BUILDER_H_ */
