/*******************************************************************************
 * Copyright (c) 2022 Davor Cihlar
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Davor Cihlar  - initial API and implementation and/or initial documentation
 *******************************************************************************/

#include <cstring>
#include <boost/test/unit_test.hpp>
#include "../../../src/core/utils/mixedStorage.h"
#include "../../../src/core/utils/ifSpecBuilder.h"

#if BOOST_VERSION < 106400
    BOOST_TEST_DONT_PRINT_LOG_VALUE(std::nullptr_t)
#endif

using namespace forte::core::util;


static bool operator==(const SAdapterInstanceDef &a, const SAdapterInstanceDef &b) {
  return
    a.mAdapterTypeNameID == b.mAdapterTypeNameID &&
    a.mAdapterNameID     == b.mAdapterNameID     &&
    a.mIsPlug            == b.mIsPlug;
}

static std::ostream& operator<<(std::ostream &os, const SAdapterInstanceDef &ai) {
  return os << '{' << ai.mAdapterTypeNameID << ", " << ai.mAdapterNameID << ", " << ai.mIsPlug << "}";
}

BOOST_AUTO_TEST_SUITE(IfSpecBuilder_Test)
  using CSpecEIReference = CSpecReference<CEventSpecTag, CInputSpecTag>;
  using CSpecEIRefRange = CSpecReferenceRange<CEventSpecTag, CInputSpecTag>;

  static constexpr const CStringDictionary::TStringId constStringIdList1[] = {1, 2, 3};
  static constexpr const CStringDictionary::TStringId constStringIdList2[] = {4, 5, 6};
  static constexpr std::array<TDataIOID, 3> staticBindings = {0, 1, CFunctionBlock::scmWithListDelimiter};
  static constexpr std::array<TForteInt16, 1> staticIndexes = {0};
  static constexpr std::array<SAdapterInstanceDef, 2> staticAdapters = {
    SAdapterInstanceDef{1, 2, true},
    SAdapterInstanceDef{3, 4, false},
  };

  SFBInterfaceSpec ifspec;
  CMixedStorage storage;


  BOOST_AUTO_TEST_CASE(IfSpecBuilder_UninitializedReferenceIsInvalid) {
    CSpecEIReference uut;
    BOOST_CHECK(!uut.isValid());
  }

  BOOST_AUTO_TEST_CASE(IfSpecBuilder_NegativeReferenceIsInvalid) {
    CSpecEIReference uut{-1};
    BOOST_CHECK(!uut.isValid());
  }

  BOOST_AUTO_TEST_CASE(IfSpecBuilder_ReferenceHoldsValue) {
    CSpecEIReference uut{42};
    BOOST_CHECK(uut.isValid());
    BOOST_CHECK_EQUAL(*uut, 42);
  }

  BOOST_AUTO_TEST_CASE(IfSpecBuilder_RangeReferenceNoHalfValid) {
    CSpecEIRefRange uut;
    uut = CSpecEIRefRange{-1, 0};
    BOOST_CHECK(!uut.isValid());
    uut = CSpecEIRefRange{0, -1};
    BOOST_CHECK(!uut.isValid());
    uut = CSpecEIRefRange{0, 0};
    BOOST_CHECK(uut.isValid());
  }

  BOOST_AUTO_TEST_CASE(IfSpecBuilder_PickFromRange) {
    CSpecEIRefRange uut{1, 3};
    BOOST_CHECK_EQUAL(*uut[0], 1);
    BOOST_CHECK_EQUAL(*uut[2], 3);
    BOOST_CHECK(!uut[-1].isValid());
    BOOST_CHECK(uut[0].isValid());
    BOOST_CHECK(uut[2].isValid());
    BOOST_CHECK(!uut[3].isValid());
  }

  void build(CIfSpecBuilder &uut) {
    memset(&ifspec, 0xCC, sizeof(ifspec));
    storage.clear();
    BOOST_REQUIRE(uut.build(storage, ifspec));
  }

  BOOST_AUTO_TEST_CASE(IfSpecBuilder_EmptyBuild) {
    CIfSpecBuilder uut;
    build(uut);
    BOOST_CHECK_EQUAL(ifspec.mNumEIs, 0);
    BOOST_CHECK_EQUAL(ifspec.mNumEOs, 0);
    BOOST_CHECK_EQUAL(ifspec.mNumDIs, 0);
    BOOST_CHECK_EQUAL(ifspec.mNumDOs, 0);
    BOOST_CHECK_EQUAL(ifspec.mNumAdapters, 0);
  }

  static auto strid(const char *s) {
    auto strId = CStringDictionary::getInstance().getId(s);
    BOOST_REQUIRE(strId != CStringDictionary::scmInvalidStringId);
    return strId;
  }

  template<class DirTag>
  void add_events(CEventSpecBuilder<DirTag> &e, int n) {
    for (int i = 0; i < n; ++i) {
      char name[16];
      snprintf(name, sizeof(name), "E%d", i + 1);
      e.addEvent(name);
    }
    BOOST_REQUIRE(e.isGood());
  }

  template<class DirTag>
  void add_data(CDataSpecBuilder<DirTag> &e, int n) {
    for (int i = 0; i < n; ++i) {
      char name[16], typeName[16];
      snprintf(name, sizeof(name), "D%d", i + 1);
      snprintf(typeName, sizeof(typeName), "T%d", i);
      e.addData(name, typeName);
    }
    BOOST_REQUIRE(e.isGood());
  }

  void test_events(CIfSpecBuilder &uut, TEventID &n, const CStringDictionary::TStringId *&f) {
    build(uut);
    BOOST_REQUIRE_EQUAL(n, 2);
    BOOST_REQUIRE_NE(f, nullptr);
    BOOST_CHECK_EQUAL(f[0], strid("E1"));
    BOOST_CHECK_EQUAL(f[1], strid("E2"));
  }

  BOOST_AUTO_TEST_CASE(IfSpecBuilder_SetStaticInputEvents) {
    CIfSpecBuilder uut;
    uut.mEI.setStaticEvents(constStringIdList1, 3);
    uut.mEITypes.setStaticEvents(constStringIdList1, 3);
    build(uut);
    BOOST_CHECK_EQUAL(ifspec.mNumEIs, 3);
    BOOST_CHECK_EQUAL(ifspec.mEINames, constStringIdList1);
  }

  BOOST_AUTO_TEST_CASE(IfSpecBuilder_SetStaticOutputEvents) {
    CIfSpecBuilder uut;
    uut.mEO.setStaticEvents(constStringIdList2, 3);
    uut.mEOTypes.setStaticEvents(constStringIdList2, 3);
    build(uut);
    BOOST_CHECK_EQUAL(ifspec.mNumEOs, 3);
    BOOST_CHECK_EQUAL(ifspec.mEONames, constStringIdList2);
  }

  BOOST_AUTO_TEST_CASE(IfSpecBuilder_AddInputEvents) {
    CIfSpecBuilder uut;
    add_events(uut.mEI, 2);
    uut.mEITypes.setStaticEvents(constStringIdList2, 2);
    test_events(uut, ifspec.mNumEIs, ifspec.mEINames);
  }

  BOOST_AUTO_TEST_CASE(IfSpecBuilder_AddOutputEvents) {
    CIfSpecBuilder uut;
    add_events(uut.mEO, 2);
    uut.mEOTypes.setStaticEvents(constStringIdList2, 2);
    test_events(uut, ifspec.mNumEOs, ifspec.mEONames);
  }

  BOOST_AUTO_TEST_CASE(IfSpecBuilder_AddEventsRange) {
    CIfSpecBuilder uut;
    auto range = uut.mEI.addEventRange("E", 2);
    uut.mEITypes.addEventRange("E", 2);
    test_events(uut, ifspec.mNumEIs, ifspec.mEINames);
    BOOST_CHECK(range.isValid());
    BOOST_CHECK_EQUAL(*range.mFirst, 0);
    BOOST_CHECK_EQUAL(*range.mLast, 1);
  }

  BOOST_AUTO_TEST_CASE(IfSpecBuilder_AddEventReturningReference) {
    CIfSpecBuilder uut;
    BOOST_CHECK_EQUAL(*uut.mEI.addEvent("IE0"), 0);
    BOOST_CHECK_EQUAL(*uut.mEI.addEvent("IE1"), 1);
    BOOST_CHECK_EQUAL(*uut.mEO.addEvent("OE0"), 0);
  }

  BOOST_AUTO_TEST_CASE(IfSpecBuilder_DefaultWith) {
    CIfSpecBuilder uut;
    add_events(uut.mEI, 2);
    add_events(uut.mEO, 1);
    build(uut);
    BOOST_CHECK_EQUAL(ifspec.mEIWithIndexes[0], -1);
    BOOST_CHECK_EQUAL(ifspec.mEIWithIndexes[1], -1);
    BOOST_CHECK_EQUAL(ifspec.mEOWithIndexes[0], -1);
  }

  void test_data(CIfSpecBuilder &uut, TPortId &n, const CStringDictionary::TStringId *&f, const CStringDictionary::TStringId *&t, CStringDictionary::TStringId dataTypeId = CStringDictionary::scmInvalidStringId) {
    build(uut);
    BOOST_REQUIRE_EQUAL(n, 2);
    BOOST_REQUIRE_NE(f, nullptr);
    BOOST_REQUIRE_NE(t, nullptr);
    BOOST_CHECK_EQUAL(f[0], strid("D1"));
    BOOST_CHECK_EQUAL(f[1], strid("D2"));
    if (dataTypeId == CStringDictionary::scmInvalidStringId) {
      BOOST_CHECK_EQUAL(t[0], strid("T0"));
      BOOST_CHECK_EQUAL(t[1], strid("T1"));
    } else {
      BOOST_CHECK_EQUAL(t[0], strid("ANY"));
      BOOST_CHECK_EQUAL(t[1], strid("ANY"));
    }
  }

  BOOST_AUTO_TEST_CASE(IfSpecBuilder_AddInputData) {
    CIfSpecBuilder uut;
    add_data(uut.mDI, 2);
    test_data(uut, ifspec.mNumDIs, ifspec.mDINames, ifspec.mDIDataTypeNames);
  }

  BOOST_AUTO_TEST_CASE(IfSpecBuilder_AddOutputData) {
    CIfSpecBuilder uut;
    add_data(uut.mDO, 2);
    test_data(uut, ifspec.mNumDOs, ifspec.mDONames, ifspec.mDODataTypeNames);
  }

  BOOST_AUTO_TEST_CASE(IfSpecBuilder_AddDataRange) {
    CIfSpecBuilder uut;
    auto range = uut.mDI.addDataRange("D", 2);
    test_data(uut, ifspec.mNumDIs, ifspec.mDINames, ifspec.mDIDataTypeNames, strid("ANY"));
    BOOST_CHECK(range.isValid());
    BOOST_CHECK_EQUAL(*range.mFirst, 0);
    BOOST_CHECK_EQUAL(*range.mLast, 1);
  }

  BOOST_AUTO_TEST_CASE(IfSpecBuilder_AddDataReturningReference) {
    CIfSpecBuilder uut;
    BOOST_CHECK_EQUAL(*uut.mDI.addData("ID0", 0), 0);
    BOOST_CHECK_EQUAL(*uut.mDI.addData("ID1", 0), 1);
    BOOST_CHECK_EQUAL(*uut.mDO.addData("OD0", 0), 0);
  }

  BOOST_AUTO_TEST_CASE(IfSpecBuilder_SetStaticInputData) {
    CIfSpecBuilder uut;
    uut.mDI.setStaticData(constStringIdList1, constStringIdList2, 3);
    build(uut);
    BOOST_CHECK_EQUAL(ifspec.mNumDIs, 3);
    BOOST_CHECK_EQUAL(ifspec.mDINames, constStringIdList1);
    BOOST_CHECK_EQUAL(ifspec.mDIDataTypeNames, constStringIdList2);
  }

  BOOST_AUTO_TEST_CASE(IfSpecBuilder_SetStaticOuputData) {
    CIfSpecBuilder uut;
    uut.mDO.setStaticData(constStringIdList1, constStringIdList2, 3);
    build(uut);
    BOOST_CHECK_EQUAL(ifspec.mNumDOs, 3);
    BOOST_CHECK_EQUAL(ifspec.mDONames, constStringIdList1);
    BOOST_CHECK_EQUAL(ifspec.mDODataTypeNames, constStringIdList2);
  }

  BOOST_AUTO_TEST_CASE(IfSpecBuilder_FindValidEventPort) {
    CEventSpecBuilder<CInputSpecTag> uut;
    uut.addEventRange("E", 2);
    auto portRef = uut["E1"];
    BOOST_CHECK(portRef.isValid());
    BOOST_CHECK_EQUAL(*portRef, 0);
    portRef = uut["E2"];
    BOOST_CHECK(portRef.isValid());
    BOOST_CHECK_EQUAL(*portRef, 1);
  }

  BOOST_AUTO_TEST_CASE(IfSpecBuilder_FindInvalidEventPort) {
    CEventSpecBuilder<CInputSpecTag> uut;
    uut.addEventRange("E", 2);
    auto portRef = uut["E3"];
    BOOST_CHECK(!portRef.isValid());
    portRef = uut["foo"];
    BOOST_CHECK(!portRef.isValid());
  }

  BOOST_AUTO_TEST_CASE(IfSpecBuilder_FindValidDataPort) {
    CDataSpecBuilder<CInputSpecTag> uut;
    uut.addDataRange("D", 2);
    auto portRef = uut["D1"];
    BOOST_CHECK(portRef.isValid());
    BOOST_CHECK_EQUAL(*portRef, 0);
    portRef = uut["D2"];
    BOOST_CHECK(portRef.isValid());
    BOOST_CHECK_EQUAL(*portRef, 1);
  }

  BOOST_AUTO_TEST_CASE(IfSpecBuilder_FindInvalidDataPort) {
    CDataSpecBuilder<CInputSpecTag> uut;
    uut.addDataRange("D", 2);
    auto portRef = uut["D3"];
    BOOST_CHECK(!portRef.isValid());
    portRef = uut["bar"];
    BOOST_CHECK(!portRef.isValid());
  }

  void test_bind(const TDataIOID *&w, const TForteInt16 *&i) {
    static constexpr std::array<TDataIOID, 5>tw = {0, 2, CFunctionBlock::scmWithListDelimiter, 1, CFunctionBlock::scmWithListDelimiter};
    BOOST_CHECK_EQUAL_COLLECTIONS(w, w + tw.size(), tw.begin(), tw.end());
    static constexpr std::array<TForteInt16, 3>ti = {0, 3, -1};
    BOOST_CHECK_EQUAL_COLLECTIONS(i, i + ti.size(), ti.begin(), ti.end());
  }

  BOOST_AUTO_TEST_CASE(IfSpecBuilder_InputWith) {
    CIfSpecBuilder uut;
    uut.mEI.addEventRange("E", 3);
    uut.mDI.addDataRange("D", 3);
    uut.bind(uut.mEI["E1"], {uut.mDI["D1"], uut.mDI["D3"]});
    uut.bind(uut.mEI["E2"], uut.mDI["D2"]);
    build(uut);
    test_bind(ifspec.mEIWith, ifspec.mEIWithIndexes);
  }

  BOOST_AUTO_TEST_CASE(IfSpecBuilder_OutputWith) {
    CIfSpecBuilder uut;
    uut.mEO.addEventRange("E", 3);
    uut.mDO.addDataRange("D", 3);
    uut.bind(uut.mEO["E1"], {uut.mDO["D1"], uut.mDO["D3"]});
    uut.bind(uut.mEO["E2"], uut.mDO["D2"]);
    build(uut);
    test_bind(ifspec.mEOWith, ifspec.mEOWithIndexes);
  }

  BOOST_AUTO_TEST_CASE(IfSpecBuilder_RangeWithExplicit) {
    CIfSpecBuilder uut;
    uut.mEO.addEvent("E");
    uut.mDO.addDataRange("D", 3);
    uut.bindRange(uut.mEO["E"], uut.mDO["D1"], uut.mDO["D3"]);
    build(uut);
    static constexpr std::array<TDataIOID, 4> tw = {0, 1, 2, CFunctionBlock::scmWithListDelimiter};
    BOOST_CHECK_EQUAL_COLLECTIONS(ifspec.mEOWith, ifspec.mEOWith + tw.size(), tw.begin(), tw.end());
  }

  BOOST_AUTO_TEST_CASE(IfSpecBuilder_RangeWithDirect) {
    CIfSpecBuilder uut;
    auto eRef = uut.mEO.addEvent("E");
    auto dRange = uut.mDO.addDataRange("D", 3);
    uut.bindRange(eRef, dRange);
    build(uut);
    BOOST_CHECK_EQUAL(ifspec.mEOWith[0], 0);
    BOOST_CHECK_EQUAL(ifspec.mEOWith[2], 2);
    BOOST_CHECK_EQUAL(ifspec.mEOWith[3], CFunctionBlock::scmWithListDelimiter);
  }

  BOOST_AUTO_TEST_CASE(IfSpecBuilder_StaticWith) {
    CIfSpecBuilder uut;
    uut.mEO.addEvent("E");
    uut.mOWith.setStaticBindings(staticBindings, staticIndexes);
    build(uut);
    BOOST_CHECK_EQUAL(ifspec.mEOWith, staticBindings.data());
    BOOST_CHECK_EQUAL(ifspec.mEOWithIndexes, staticIndexes.data());
  }

  BOOST_AUTO_TEST_CASE(IfSpecBuilder_CombinedStaticAndDynamicWith) {
    CWithSpecBuilderBase uut;
    uut.setStaticBindings(staticBindings, staticIndexes);
    BOOST_CHECK(uut.isGood());
    uut.bind(0, 0);
    BOOST_CHECK(!uut.isGood());
  }

  BOOST_AUTO_TEST_CASE(IfSpecBuilder_CombinedDynamicAndStaticWith) {
    CWithSpecBuilderBase uut;
    uut.bind(0, 0);
    BOOST_CHECK(uut.isGood());
    uut.setStaticBindings(staticBindings, staticIndexes);
    BOOST_CHECK(uut.isGood());
    auto out = uut.build(storage, staticIndexes.size());
    BOOST_CHECK_EQUAL(std::get<0>(out), staticBindings.data());
  }

  BOOST_AUTO_TEST_CASE(IfSpecBuilder_StaticWithsAndEventsCountDifferenceHandling) {
    CWithSpecBuilderBase uut;
    uut.setStaticBindings(staticBindings, staticIndexes);
    BOOST_CHECK(uut.isGood());
    uut.build(storage, 0);
    BOOST_CHECK(!uut.isGood());
  }

  BOOST_AUTO_TEST_CASE(IfSpecBuilder_DynamicWithsAndEventsCountDifferenceHandling) {
    CIfSpecBuilder uut;
    uut.mOWith.setStaticBindings(staticBindings, staticIndexes);
    storage.clear();
    BOOST_CHECK(!uut.build(storage, ifspec));
  }

  BOOST_AUTO_TEST_CASE(IfSpecBuilder_StaticAdapters) {
    CIfSpecBuilder uut;
    uut.mAdapter.setStaticAdapters(staticAdapters);
    build(uut);
    BOOST_CHECK_EQUAL(ifspec.mAdapterInstanceDefinition, staticAdapters.data());
    BOOST_CHECK_EQUAL(ifspec.mNumAdapters, staticAdapters.size());
  }

  BOOST_AUTO_TEST_CASE(IfSpecBuilder_DynamicAdapters) {
    CIfSpecBuilder uut;
    uut.mAdapter.addAdapter(1, 2, true);
    uut.mAdapter.addAdapter(3, 4, false);
    uut.mIAdapter.addAdapter(5, 6);
    uut.mOAdapter.addAdapter(7, 8);
    build(uut);
    BOOST_REQUIRE_EQUAL(ifspec.mNumAdapters, 4);
    const auto adapter = ifspec.mAdapterInstanceDefinition;
    BOOST_CHECK_EQUAL(adapter[0], (SAdapterInstanceDef{2, 1, true }));
    BOOST_CHECK_EQUAL(adapter[1], (SAdapterInstanceDef{4, 3, false}));
    BOOST_CHECK_EQUAL(adapter[2], (SAdapterInstanceDef{6, 5, false}));
    BOOST_CHECK_EQUAL(adapter[3], (SAdapterInstanceDef{8, 7, true }));
  }

  BOOST_AUTO_TEST_CASE(IfSpecBuilder_AdaptersCString) {
    CIfSpecBuilder uut;
    uut.mAdapter.addAdapter("adapter", "type", true);
    build(uut);
    BOOST_REQUIRE_EQUAL(ifspec.mNumAdapters, 1);
    BOOST_CHECK_EQUAL(ifspec.mAdapterInstanceDefinition[0], (SAdapterInstanceDef{strid("type"), strid("adapter"), true}));
  }

  BOOST_AUTO_TEST_CASE(IfSpecBuilder_AddToStaticAdapters) {
    CIfSpecBuilder uut;
    uut.mAdapter.setStaticAdapters(staticAdapters);
    uut.mAdapter.addAdapter(5, 6, true);
    build(uut);
    BOOST_REQUIRE_EQUAL(ifspec.mNumAdapters, 3);
    const auto adapter = ifspec.mAdapterInstanceDefinition;
    BOOST_CHECK_EQUAL(adapter[0], (SAdapterInstanceDef{1, 2, true }));
    BOOST_CHECK_EQUAL(adapter[1], (SAdapterInstanceDef{3, 4, false}));
    BOOST_CHECK_EQUAL(adapter[2], (SAdapterInstanceDef{6, 5, true}));
  }

  BOOST_AUTO_TEST_CASE(IfSpecBuilder_CombinedStaticAndDynamicString) {
    CStringIdListSpecBuilder uut{16};
    uut.setStaticList(constStringIdList1, 3);
    uut.addString(4);
    auto out = uut.build<size_t>(storage);
    BOOST_CHECK_NE(std::get<0>(out), constStringIdList1);
    BOOST_CHECK_EQUAL(std::get<1>(out), 4);
    static constexpr std::array<CStringDictionary::TStringId, 4> expected = {1, 2, 3, 4};
    BOOST_CHECK_EQUAL_COLLECTIONS(std::get<0>(out), std::get<0>(out) + 4, expected.begin(), expected.end());
  }

  BOOST_AUTO_TEST_CASE(IfSpecBuilder_StringListOverflow) {
    CStringIdListSpecBuilder uut{2};
    uut.addString(1);
    uut.addString(1);
    BOOST_CHECK(uut.isGood());
    uut.addString(1);
    BOOST_CHECK(!uut.isGood());
  }

  BOOST_AUTO_TEST_SUITE_END()
