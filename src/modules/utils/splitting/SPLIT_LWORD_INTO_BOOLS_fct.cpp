/*************************************************************************
 *** Copyright (c) 2024 HR Agrartechnik GmbH
 *** This program and the accompanying materials are made available under the
 *** terms of the Eclipse Public License 2.0 which is available at
 *** http://www.eclipse.org/legal/epl-2.0.
 ***
 *** SPDX-License-Identifier: EPL-2.0
 ***
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter V1.0.x NG!
 ***
 *** Name: SPLIT_LWORD_INTO_BOOLS
 *** Description: this Function extracts the 64 BOOLS from a lword
 *** Version:
 ***     1.0: 2024-02-22/Franz Höpfinger - HR Agrartechnik - initial Implementation
 ***     1.1: 2024-07-24/Moritz Ortmeier - HR Agrartechnik - rename Function and change Output Variables
 *************************************************************************/

#include "SPLIT_LWORD_INTO_BOOLS_fct.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "SPLIT_LWORD_INTO_BOOLS_fct_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"
#include "forte_lword.h"
#include "forte_bool.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"

DEFINE_FIRMWARE_FB(FORTE_SPLIT_LWORD_INTO_BOOLS, g_nStringIdSPLIT_LWORD_INTO_BOOLS)

const CStringDictionary::TStringId FORTE_SPLIT_LWORD_INTO_BOOLS::scmDataInputNames[] = {g_nStringIdIN};
const CStringDictionary::TStringId FORTE_SPLIT_LWORD_INTO_BOOLS::scmDataInputTypeIds[] = {g_nStringIdLWORD};
const CStringDictionary::TStringId FORTE_SPLIT_LWORD_INTO_BOOLS::scmDataOutputNames[] = {g_nStringIdBIT_00, g_nStringIdBIT_01, g_nStringIdBIT_02, g_nStringIdBIT_03, g_nStringIdBIT_04, g_nStringIdBIT_05, g_nStringIdBIT_06, g_nStringIdBIT_07, g_nStringIdBIT_08, g_nStringIdBIT_09, g_nStringIdBIT_10, g_nStringIdBIT_11, g_nStringIdBIT_12, g_nStringIdBIT_13, g_nStringIdBIT_14, g_nStringIdBIT_15, g_nStringIdBIT_16, g_nStringIdBIT_17, g_nStringIdBIT_18, g_nStringIdBIT_19, g_nStringIdBIT_20, g_nStringIdBIT_21, g_nStringIdBIT_22, g_nStringIdBIT_23, g_nStringIdBIT_24, g_nStringIdBIT_25, g_nStringIdBIT_26, g_nStringIdBIT_27, g_nStringIdBIT_28, g_nStringIdBIT_29, g_nStringIdBIT_30, g_nStringIdBIT_31, g_nStringIdBIT_32, g_nStringIdBIT_33, g_nStringIdBIT_34, g_nStringIdBIT_35, g_nStringIdBIT_36, g_nStringIdBIT_37, g_nStringIdBIT_38, g_nStringIdBIT_39, g_nStringIdBIT_40, g_nStringIdBIT_41, g_nStringIdBIT_42, g_nStringIdBIT_43, g_nStringIdBIT_44, g_nStringIdBIT_45, g_nStringIdBIT_46, g_nStringIdBIT_47, g_nStringIdBIT_48, g_nStringIdBIT_49, g_nStringIdBIT_50, g_nStringIdBIT_51, g_nStringIdBIT_52, g_nStringIdBIT_53, g_nStringIdBIT_54, g_nStringIdBIT_55, g_nStringIdBIT_56, g_nStringIdBIT_57, g_nStringIdBIT_58, g_nStringIdBIT_59, g_nStringIdBIT_60, g_nStringIdBIT_61, g_nStringIdBIT_62, g_nStringIdBIT_63};
const CStringDictionary::TStringId FORTE_SPLIT_LWORD_INTO_BOOLS::scmDataOutputTypeIds[] = {g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL, g_nStringIdBOOL};
const TDataIOID FORTE_SPLIT_LWORD_INTO_BOOLS::scmEIWith[] = {0, scmWithListDelimiter};
const TForteInt16 FORTE_SPLIT_LWORD_INTO_BOOLS::scmEIWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_SPLIT_LWORD_INTO_BOOLS::scmEventInputNames[] = {g_nStringIdREQ};
const CStringDictionary::TStringId FORTE_SPLIT_LWORD_INTO_BOOLS::scmEventInputTypeIds[] = {g_nStringIdEvent};
const TDataIOID FORTE_SPLIT_LWORD_INTO_BOOLS::scmEOWith[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, scmWithListDelimiter};
const TForteInt16 FORTE_SPLIT_LWORD_INTO_BOOLS::scmEOWithIndexes[] = {0};
const CStringDictionary::TStringId FORTE_SPLIT_LWORD_INTO_BOOLS::scmEventOutputNames[] = {g_nStringIdCNF};
const CStringDictionary::TStringId FORTE_SPLIT_LWORD_INTO_BOOLS::scmEventOutputTypeIds[] = {g_nStringIdEvent};
const SFBInterfaceSpec FORTE_SPLIT_LWORD_INTO_BOOLS::scmFBInterfaceSpec = {
  1, scmEventInputNames, scmEventInputTypeIds, scmEIWith, scmEIWithIndexes,
  1, scmEventOutputNames, scmEventOutputTypeIds, scmEOWith, scmEOWithIndexes,
  1, scmDataInputNames, scmDataInputTypeIds,
  64, scmDataOutputNames, scmDataOutputTypeIds,
  0, nullptr,
  0, nullptr
};

FORTE_SPLIT_LWORD_INTO_BOOLS::FORTE_SPLIT_LWORD_INTO_BOOLS(const CStringDictionary::TStringId paInstanceNameId, forte::core::CFBContainer &paContainer) :
    CFunctionBlock(paContainer, scmFBInterfaceSpec, paInstanceNameId),
    var_conn_BIT_00(var_BIT_00),
    var_conn_BIT_01(var_BIT_01),
    var_conn_BIT_02(var_BIT_02),
    var_conn_BIT_03(var_BIT_03),
    var_conn_BIT_04(var_BIT_04),
    var_conn_BIT_05(var_BIT_05),
    var_conn_BIT_06(var_BIT_06),
    var_conn_BIT_07(var_BIT_07),
    var_conn_BIT_08(var_BIT_08),
    var_conn_BIT_09(var_BIT_09),
    var_conn_BIT_10(var_BIT_10),
    var_conn_BIT_11(var_BIT_11),
    var_conn_BIT_12(var_BIT_12),
    var_conn_BIT_13(var_BIT_13),
    var_conn_BIT_14(var_BIT_14),
    var_conn_BIT_15(var_BIT_15),
    var_conn_BIT_16(var_BIT_16),
    var_conn_BIT_17(var_BIT_17),
    var_conn_BIT_18(var_BIT_18),
    var_conn_BIT_19(var_BIT_19),
    var_conn_BIT_20(var_BIT_20),
    var_conn_BIT_21(var_BIT_21),
    var_conn_BIT_22(var_BIT_22),
    var_conn_BIT_23(var_BIT_23),
    var_conn_BIT_24(var_BIT_24),
    var_conn_BIT_25(var_BIT_25),
    var_conn_BIT_26(var_BIT_26),
    var_conn_BIT_27(var_BIT_27),
    var_conn_BIT_28(var_BIT_28),
    var_conn_BIT_29(var_BIT_29),
    var_conn_BIT_30(var_BIT_30),
    var_conn_BIT_31(var_BIT_31),
    var_conn_BIT_32(var_BIT_32),
    var_conn_BIT_33(var_BIT_33),
    var_conn_BIT_34(var_BIT_34),
    var_conn_BIT_35(var_BIT_35),
    var_conn_BIT_36(var_BIT_36),
    var_conn_BIT_37(var_BIT_37),
    var_conn_BIT_38(var_BIT_38),
    var_conn_BIT_39(var_BIT_39),
    var_conn_BIT_40(var_BIT_40),
    var_conn_BIT_41(var_BIT_41),
    var_conn_BIT_42(var_BIT_42),
    var_conn_BIT_43(var_BIT_43),
    var_conn_BIT_44(var_BIT_44),
    var_conn_BIT_45(var_BIT_45),
    var_conn_BIT_46(var_BIT_46),
    var_conn_BIT_47(var_BIT_47),
    var_conn_BIT_48(var_BIT_48),
    var_conn_BIT_49(var_BIT_49),
    var_conn_BIT_50(var_BIT_50),
    var_conn_BIT_51(var_BIT_51),
    var_conn_BIT_52(var_BIT_52),
    var_conn_BIT_53(var_BIT_53),
    var_conn_BIT_54(var_BIT_54),
    var_conn_BIT_55(var_BIT_55),
    var_conn_BIT_56(var_BIT_56),
    var_conn_BIT_57(var_BIT_57),
    var_conn_BIT_58(var_BIT_58),
    var_conn_BIT_59(var_BIT_59),
    var_conn_BIT_60(var_BIT_60),
    var_conn_BIT_61(var_BIT_61),
    var_conn_BIT_62(var_BIT_62),
    var_conn_BIT_63(var_BIT_63),
    conn_CNF(this, 0),
    conn_IN(nullptr),
    conn_BIT_00(this, 0, &var_conn_BIT_00),
    conn_BIT_01(this, 1, &var_conn_BIT_01),
    conn_BIT_02(this, 2, &var_conn_BIT_02),
    conn_BIT_03(this, 3, &var_conn_BIT_03),
    conn_BIT_04(this, 4, &var_conn_BIT_04),
    conn_BIT_05(this, 5, &var_conn_BIT_05),
    conn_BIT_06(this, 6, &var_conn_BIT_06),
    conn_BIT_07(this, 7, &var_conn_BIT_07),
    conn_BIT_08(this, 8, &var_conn_BIT_08),
    conn_BIT_09(this, 9, &var_conn_BIT_09),
    conn_BIT_10(this, 10, &var_conn_BIT_10),
    conn_BIT_11(this, 11, &var_conn_BIT_11),
    conn_BIT_12(this, 12, &var_conn_BIT_12),
    conn_BIT_13(this, 13, &var_conn_BIT_13),
    conn_BIT_14(this, 14, &var_conn_BIT_14),
    conn_BIT_15(this, 15, &var_conn_BIT_15),
    conn_BIT_16(this, 16, &var_conn_BIT_16),
    conn_BIT_17(this, 17, &var_conn_BIT_17),
    conn_BIT_18(this, 18, &var_conn_BIT_18),
    conn_BIT_19(this, 19, &var_conn_BIT_19),
    conn_BIT_20(this, 20, &var_conn_BIT_20),
    conn_BIT_21(this, 21, &var_conn_BIT_21),
    conn_BIT_22(this, 22, &var_conn_BIT_22),
    conn_BIT_23(this, 23, &var_conn_BIT_23),
    conn_BIT_24(this, 24, &var_conn_BIT_24),
    conn_BIT_25(this, 25, &var_conn_BIT_25),
    conn_BIT_26(this, 26, &var_conn_BIT_26),
    conn_BIT_27(this, 27, &var_conn_BIT_27),
    conn_BIT_28(this, 28, &var_conn_BIT_28),
    conn_BIT_29(this, 29, &var_conn_BIT_29),
    conn_BIT_30(this, 30, &var_conn_BIT_30),
    conn_BIT_31(this, 31, &var_conn_BIT_31),
    conn_BIT_32(this, 32, &var_conn_BIT_32),
    conn_BIT_33(this, 33, &var_conn_BIT_33),
    conn_BIT_34(this, 34, &var_conn_BIT_34),
    conn_BIT_35(this, 35, &var_conn_BIT_35),
    conn_BIT_36(this, 36, &var_conn_BIT_36),
    conn_BIT_37(this, 37, &var_conn_BIT_37),
    conn_BIT_38(this, 38, &var_conn_BIT_38),
    conn_BIT_39(this, 39, &var_conn_BIT_39),
    conn_BIT_40(this, 40, &var_conn_BIT_40),
    conn_BIT_41(this, 41, &var_conn_BIT_41),
    conn_BIT_42(this, 42, &var_conn_BIT_42),
    conn_BIT_43(this, 43, &var_conn_BIT_43),
    conn_BIT_44(this, 44, &var_conn_BIT_44),
    conn_BIT_45(this, 45, &var_conn_BIT_45),
    conn_BIT_46(this, 46, &var_conn_BIT_46),
    conn_BIT_47(this, 47, &var_conn_BIT_47),
    conn_BIT_48(this, 48, &var_conn_BIT_48),
    conn_BIT_49(this, 49, &var_conn_BIT_49),
    conn_BIT_50(this, 50, &var_conn_BIT_50),
    conn_BIT_51(this, 51, &var_conn_BIT_51),
    conn_BIT_52(this, 52, &var_conn_BIT_52),
    conn_BIT_53(this, 53, &var_conn_BIT_53),
    conn_BIT_54(this, 54, &var_conn_BIT_54),
    conn_BIT_55(this, 55, &var_conn_BIT_55),
    conn_BIT_56(this, 56, &var_conn_BIT_56),
    conn_BIT_57(this, 57, &var_conn_BIT_57),
    conn_BIT_58(this, 58, &var_conn_BIT_58),
    conn_BIT_59(this, 59, &var_conn_BIT_59),
    conn_BIT_60(this, 60, &var_conn_BIT_60),
    conn_BIT_61(this, 61, &var_conn_BIT_61),
    conn_BIT_62(this, 62, &var_conn_BIT_62),
    conn_BIT_63(this, 63, &var_conn_BIT_63) {
}

void FORTE_SPLIT_LWORD_INTO_BOOLS::setInitialValues() {
  var_IN = 0_LWORD;
  var_BIT_00 = 0_BOOL;
  var_BIT_01 = 0_BOOL;
  var_BIT_02 = 0_BOOL;
  var_BIT_03 = 0_BOOL;
  var_BIT_04 = 0_BOOL;
  var_BIT_05 = 0_BOOL;
  var_BIT_06 = 0_BOOL;
  var_BIT_07 = 0_BOOL;
  var_BIT_08 = 0_BOOL;
  var_BIT_09 = 0_BOOL;
  var_BIT_10 = 0_BOOL;
  var_BIT_11 = 0_BOOL;
  var_BIT_12 = 0_BOOL;
  var_BIT_13 = 0_BOOL;
  var_BIT_14 = 0_BOOL;
  var_BIT_15 = 0_BOOL;
  var_BIT_16 = 0_BOOL;
  var_BIT_17 = 0_BOOL;
  var_BIT_18 = 0_BOOL;
  var_BIT_19 = 0_BOOL;
  var_BIT_20 = 0_BOOL;
  var_BIT_21 = 0_BOOL;
  var_BIT_22 = 0_BOOL;
  var_BIT_23 = 0_BOOL;
  var_BIT_24 = 0_BOOL;
  var_BIT_25 = 0_BOOL;
  var_BIT_26 = 0_BOOL;
  var_BIT_27 = 0_BOOL;
  var_BIT_28 = 0_BOOL;
  var_BIT_29 = 0_BOOL;
  var_BIT_30 = 0_BOOL;
  var_BIT_31 = 0_BOOL;
  var_BIT_32 = 0_BOOL;
  var_BIT_33 = 0_BOOL;
  var_BIT_34 = 0_BOOL;
  var_BIT_35 = 0_BOOL;
  var_BIT_36 = 0_BOOL;
  var_BIT_37 = 0_BOOL;
  var_BIT_38 = 0_BOOL;
  var_BIT_39 = 0_BOOL;
  var_BIT_40 = 0_BOOL;
  var_BIT_41 = 0_BOOL;
  var_BIT_42 = 0_BOOL;
  var_BIT_43 = 0_BOOL;
  var_BIT_44 = 0_BOOL;
  var_BIT_45 = 0_BOOL;
  var_BIT_46 = 0_BOOL;
  var_BIT_47 = 0_BOOL;
  var_BIT_48 = 0_BOOL;
  var_BIT_49 = 0_BOOL;
  var_BIT_50 = 0_BOOL;
  var_BIT_51 = 0_BOOL;
  var_BIT_52 = 0_BOOL;
  var_BIT_53 = 0_BOOL;
  var_BIT_54 = 0_BOOL;
  var_BIT_55 = 0_BOOL;
  var_BIT_56 = 0_BOOL;
  var_BIT_57 = 0_BOOL;
  var_BIT_58 = 0_BOOL;
  var_BIT_59 = 0_BOOL;
  var_BIT_60 = 0_BOOL;
  var_BIT_61 = 0_BOOL;
  var_BIT_62 = 0_BOOL;
  var_BIT_63 = 0_BOOL;
}

void FORTE_SPLIT_LWORD_INTO_BOOLS::readInputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventREQID: {
      readData(0, var_IN, conn_IN);
      break;
    }
    default:
      break;
  }
}

void FORTE_SPLIT_LWORD_INTO_BOOLS::writeOutputData(const TEventID paEIID) {
  switch(paEIID) {
    case scmEventCNFID: {
      writeData(0, var_BIT_00, conn_BIT_00);
      writeData(1, var_BIT_01, conn_BIT_01);
      writeData(2, var_BIT_02, conn_BIT_02);
      writeData(3, var_BIT_03, conn_BIT_03);
      writeData(4, var_BIT_04, conn_BIT_04);
      writeData(5, var_BIT_05, conn_BIT_05);
      writeData(6, var_BIT_06, conn_BIT_06);
      writeData(7, var_BIT_07, conn_BIT_07);
      writeData(8, var_BIT_08, conn_BIT_08);
      writeData(9, var_BIT_09, conn_BIT_09);
      writeData(10, var_BIT_10, conn_BIT_10);
      writeData(11, var_BIT_11, conn_BIT_11);
      writeData(12, var_BIT_12, conn_BIT_12);
      writeData(13, var_BIT_13, conn_BIT_13);
      writeData(14, var_BIT_14, conn_BIT_14);
      writeData(15, var_BIT_15, conn_BIT_15);
      writeData(16, var_BIT_16, conn_BIT_16);
      writeData(17, var_BIT_17, conn_BIT_17);
      writeData(18, var_BIT_18, conn_BIT_18);
      writeData(19, var_BIT_19, conn_BIT_19);
      writeData(20, var_BIT_20, conn_BIT_20);
      writeData(21, var_BIT_21, conn_BIT_21);
      writeData(22, var_BIT_22, conn_BIT_22);
      writeData(23, var_BIT_23, conn_BIT_23);
      writeData(24, var_BIT_24, conn_BIT_24);
      writeData(25, var_BIT_25, conn_BIT_25);
      writeData(26, var_BIT_26, conn_BIT_26);
      writeData(27, var_BIT_27, conn_BIT_27);
      writeData(28, var_BIT_28, conn_BIT_28);
      writeData(29, var_BIT_29, conn_BIT_29);
      writeData(30, var_BIT_30, conn_BIT_30);
      writeData(31, var_BIT_31, conn_BIT_31);
      writeData(32, var_BIT_32, conn_BIT_32);
      writeData(33, var_BIT_33, conn_BIT_33);
      writeData(34, var_BIT_34, conn_BIT_34);
      writeData(35, var_BIT_35, conn_BIT_35);
      writeData(36, var_BIT_36, conn_BIT_36);
      writeData(37, var_BIT_37, conn_BIT_37);
      writeData(38, var_BIT_38, conn_BIT_38);
      writeData(39, var_BIT_39, conn_BIT_39);
      writeData(40, var_BIT_40, conn_BIT_40);
      writeData(41, var_BIT_41, conn_BIT_41);
      writeData(42, var_BIT_42, conn_BIT_42);
      writeData(43, var_BIT_43, conn_BIT_43);
      writeData(44, var_BIT_44, conn_BIT_44);
      writeData(45, var_BIT_45, conn_BIT_45);
      writeData(46, var_BIT_46, conn_BIT_46);
      writeData(47, var_BIT_47, conn_BIT_47);
      writeData(48, var_BIT_48, conn_BIT_48);
      writeData(49, var_BIT_49, conn_BIT_49);
      writeData(50, var_BIT_50, conn_BIT_50);
      writeData(51, var_BIT_51, conn_BIT_51);
      writeData(52, var_BIT_52, conn_BIT_52);
      writeData(53, var_BIT_53, conn_BIT_53);
      writeData(54, var_BIT_54, conn_BIT_54);
      writeData(55, var_BIT_55, conn_BIT_55);
      writeData(56, var_BIT_56, conn_BIT_56);
      writeData(57, var_BIT_57, conn_BIT_57);
      writeData(58, var_BIT_58, conn_BIT_58);
      writeData(59, var_BIT_59, conn_BIT_59);
      writeData(60, var_BIT_60, conn_BIT_60);
      writeData(61, var_BIT_61, conn_BIT_61);
      writeData(62, var_BIT_62, conn_BIT_62);
      writeData(63, var_BIT_63, conn_BIT_63);
      break;
    }
    default:
      break;
  }
}

CIEC_ANY *FORTE_SPLIT_LWORD_INTO_BOOLS::getDI(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_IN;
  }
  return nullptr;
}

CIEC_ANY *FORTE_SPLIT_LWORD_INTO_BOOLS::getDO(const size_t paIndex) {
  switch(paIndex) {
    case 0: return &var_BIT_00;
    case 1: return &var_BIT_01;
    case 2: return &var_BIT_02;
    case 3: return &var_BIT_03;
    case 4: return &var_BIT_04;
    case 5: return &var_BIT_05;
    case 6: return &var_BIT_06;
    case 7: return &var_BIT_07;
    case 8: return &var_BIT_08;
    case 9: return &var_BIT_09;
    case 10: return &var_BIT_10;
    case 11: return &var_BIT_11;
    case 12: return &var_BIT_12;
    case 13: return &var_BIT_13;
    case 14: return &var_BIT_14;
    case 15: return &var_BIT_15;
    case 16: return &var_BIT_16;
    case 17: return &var_BIT_17;
    case 18: return &var_BIT_18;
    case 19: return &var_BIT_19;
    case 20: return &var_BIT_20;
    case 21: return &var_BIT_21;
    case 22: return &var_BIT_22;
    case 23: return &var_BIT_23;
    case 24: return &var_BIT_24;
    case 25: return &var_BIT_25;
    case 26: return &var_BIT_26;
    case 27: return &var_BIT_27;
    case 28: return &var_BIT_28;
    case 29: return &var_BIT_29;
    case 30: return &var_BIT_30;
    case 31: return &var_BIT_31;
    case 32: return &var_BIT_32;
    case 33: return &var_BIT_33;
    case 34: return &var_BIT_34;
    case 35: return &var_BIT_35;
    case 36: return &var_BIT_36;
    case 37: return &var_BIT_37;
    case 38: return &var_BIT_38;
    case 39: return &var_BIT_39;
    case 40: return &var_BIT_40;
    case 41: return &var_BIT_41;
    case 42: return &var_BIT_42;
    case 43: return &var_BIT_43;
    case 44: return &var_BIT_44;
    case 45: return &var_BIT_45;
    case 46: return &var_BIT_46;
    case 47: return &var_BIT_47;
    case 48: return &var_BIT_48;
    case 49: return &var_BIT_49;
    case 50: return &var_BIT_50;
    case 51: return &var_BIT_51;
    case 52: return &var_BIT_52;
    case 53: return &var_BIT_53;
    case 54: return &var_BIT_54;
    case 55: return &var_BIT_55;
    case 56: return &var_BIT_56;
    case 57: return &var_BIT_57;
    case 58: return &var_BIT_58;
    case 59: return &var_BIT_59;
    case 60: return &var_BIT_60;
    case 61: return &var_BIT_61;
    case 62: return &var_BIT_62;
    case 63: return &var_BIT_63;
  }
  return nullptr;
}

CEventConnection *FORTE_SPLIT_LWORD_INTO_BOOLS::getEOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_CNF;
  }
  return nullptr;
}

CDataConnection **FORTE_SPLIT_LWORD_INTO_BOOLS::getDIConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_IN;
  }
  return nullptr;
}

CDataConnection *FORTE_SPLIT_LWORD_INTO_BOOLS::getDOConUnchecked(const TPortId paIndex) {
  switch(paIndex) {
    case 0: return &conn_BIT_00;
    case 1: return &conn_BIT_01;
    case 2: return &conn_BIT_02;
    case 3: return &conn_BIT_03;
    case 4: return &conn_BIT_04;
    case 5: return &conn_BIT_05;
    case 6: return &conn_BIT_06;
    case 7: return &conn_BIT_07;
    case 8: return &conn_BIT_08;
    case 9: return &conn_BIT_09;
    case 10: return &conn_BIT_10;
    case 11: return &conn_BIT_11;
    case 12: return &conn_BIT_12;
    case 13: return &conn_BIT_13;
    case 14: return &conn_BIT_14;
    case 15: return &conn_BIT_15;
    case 16: return &conn_BIT_16;
    case 17: return &conn_BIT_17;
    case 18: return &conn_BIT_18;
    case 19: return &conn_BIT_19;
    case 20: return &conn_BIT_20;
    case 21: return &conn_BIT_21;
    case 22: return &conn_BIT_22;
    case 23: return &conn_BIT_23;
    case 24: return &conn_BIT_24;
    case 25: return &conn_BIT_25;
    case 26: return &conn_BIT_26;
    case 27: return &conn_BIT_27;
    case 28: return &conn_BIT_28;
    case 29: return &conn_BIT_29;
    case 30: return &conn_BIT_30;
    case 31: return &conn_BIT_31;
    case 32: return &conn_BIT_32;
    case 33: return &conn_BIT_33;
    case 34: return &conn_BIT_34;
    case 35: return &conn_BIT_35;
    case 36: return &conn_BIT_36;
    case 37: return &conn_BIT_37;
    case 38: return &conn_BIT_38;
    case 39: return &conn_BIT_39;
    case 40: return &conn_BIT_40;
    case 41: return &conn_BIT_41;
    case 42: return &conn_BIT_42;
    case 43: return &conn_BIT_43;
    case 44: return &conn_BIT_44;
    case 45: return &conn_BIT_45;
    case 46: return &conn_BIT_46;
    case 47: return &conn_BIT_47;
    case 48: return &conn_BIT_48;
    case 49: return &conn_BIT_49;
    case 50: return &conn_BIT_50;
    case 51: return &conn_BIT_51;
    case 52: return &conn_BIT_52;
    case 53: return &conn_BIT_53;
    case 54: return &conn_BIT_54;
    case 55: return &conn_BIT_55;
    case 56: return &conn_BIT_56;
    case 57: return &conn_BIT_57;
    case 58: return &conn_BIT_58;
    case 59: return &conn_BIT_59;
    case 60: return &conn_BIT_60;
    case 61: return &conn_BIT_61;
    case 62: return &conn_BIT_62;
    case 63: return &conn_BIT_63;
  }
  return nullptr;
}

void FORTE_SPLIT_LWORD_INTO_BOOLS::executeEvent(const TEventID, CEventChainExecutionThread *const paECET) {
  func_SPLIT_LWORD_INTO_BOOLS(var_IN, var_BIT_00, var_BIT_01, var_BIT_02, var_BIT_03, var_BIT_04, var_BIT_05, var_BIT_06, var_BIT_07, var_BIT_08, var_BIT_09, var_BIT_10, var_BIT_11, var_BIT_12, var_BIT_13, var_BIT_14, var_BIT_15, var_BIT_16, var_BIT_17, var_BIT_18, var_BIT_19, var_BIT_20, var_BIT_21, var_BIT_22, var_BIT_23, var_BIT_24, var_BIT_25, var_BIT_26, var_BIT_27, var_BIT_28, var_BIT_29, var_BIT_30, var_BIT_31, var_BIT_32, var_BIT_33, var_BIT_34, var_BIT_35, var_BIT_36, var_BIT_37, var_BIT_38, var_BIT_39, var_BIT_40, var_BIT_41, var_BIT_42, var_BIT_43, var_BIT_44, var_BIT_45, var_BIT_46, var_BIT_47, var_BIT_48, var_BIT_49, var_BIT_50, var_BIT_51, var_BIT_52, var_BIT_53, var_BIT_54, var_BIT_55, var_BIT_56, var_BIT_57, var_BIT_58, var_BIT_59, var_BIT_60, var_BIT_61, var_BIT_62, var_BIT_63);
  sendOutputEvent(scmEventCNFID, paECET);
}

void func_SPLIT_LWORD_INTO_BOOLS(CIEC_LWORD st_lv_IN, CIEC_BOOL &st_lv_BIT_00, CIEC_BOOL &st_lv_BIT_01, CIEC_BOOL &st_lv_BIT_02, CIEC_BOOL &st_lv_BIT_03, CIEC_BOOL &st_lv_BIT_04, CIEC_BOOL &st_lv_BIT_05, CIEC_BOOL &st_lv_BIT_06, CIEC_BOOL &st_lv_BIT_07, CIEC_BOOL &st_lv_BIT_08, CIEC_BOOL &st_lv_BIT_09, CIEC_BOOL &st_lv_BIT_10, CIEC_BOOL &st_lv_BIT_11, CIEC_BOOL &st_lv_BIT_12, CIEC_BOOL &st_lv_BIT_13, CIEC_BOOL &st_lv_BIT_14, CIEC_BOOL &st_lv_BIT_15, CIEC_BOOL &st_lv_BIT_16, CIEC_BOOL &st_lv_BIT_17, CIEC_BOOL &st_lv_BIT_18, CIEC_BOOL &st_lv_BIT_19, CIEC_BOOL &st_lv_BIT_20, CIEC_BOOL &st_lv_BIT_21, CIEC_BOOL &st_lv_BIT_22, CIEC_BOOL &st_lv_BIT_23, CIEC_BOOL &st_lv_BIT_24, CIEC_BOOL &st_lv_BIT_25, CIEC_BOOL &st_lv_BIT_26, CIEC_BOOL &st_lv_BIT_27, CIEC_BOOL &st_lv_BIT_28, CIEC_BOOL &st_lv_BIT_29, CIEC_BOOL &st_lv_BIT_30, CIEC_BOOL &st_lv_BIT_31, CIEC_BOOL &st_lv_BIT_32, CIEC_BOOL &st_lv_BIT_33, CIEC_BOOL &st_lv_BIT_34, CIEC_BOOL &st_lv_BIT_35, CIEC_BOOL &st_lv_BIT_36, CIEC_BOOL &st_lv_BIT_37, CIEC_BOOL &st_lv_BIT_38, CIEC_BOOL &st_lv_BIT_39, CIEC_BOOL &st_lv_BIT_40, CIEC_BOOL &st_lv_BIT_41, CIEC_BOOL &st_lv_BIT_42, CIEC_BOOL &st_lv_BIT_43, CIEC_BOOL &st_lv_BIT_44, CIEC_BOOL &st_lv_BIT_45, CIEC_BOOL &st_lv_BIT_46, CIEC_BOOL &st_lv_BIT_47, CIEC_BOOL &st_lv_BIT_48, CIEC_BOOL &st_lv_BIT_49, CIEC_BOOL &st_lv_BIT_50, CIEC_BOOL &st_lv_BIT_51, CIEC_BOOL &st_lv_BIT_52, CIEC_BOOL &st_lv_BIT_53, CIEC_BOOL &st_lv_BIT_54, CIEC_BOOL &st_lv_BIT_55, CIEC_BOOL &st_lv_BIT_56, CIEC_BOOL &st_lv_BIT_57, CIEC_BOOL &st_lv_BIT_58, CIEC_BOOL &st_lv_BIT_59, CIEC_BOOL &st_lv_BIT_60, CIEC_BOOL &st_lv_BIT_61, CIEC_BOOL &st_lv_BIT_62, CIEC_BOOL &st_lv_BIT_63) {
  st_lv_BIT_00 = 0_BOOL;
  st_lv_BIT_01 = 0_BOOL;
  st_lv_BIT_02 = 0_BOOL;
  st_lv_BIT_03 = 0_BOOL;
  st_lv_BIT_04 = 0_BOOL;
  st_lv_BIT_05 = 0_BOOL;
  st_lv_BIT_06 = 0_BOOL;
  st_lv_BIT_07 = 0_BOOL;
  st_lv_BIT_08 = 0_BOOL;
  st_lv_BIT_09 = 0_BOOL;
  st_lv_BIT_10 = 0_BOOL;
  st_lv_BIT_11 = 0_BOOL;
  st_lv_BIT_12 = 0_BOOL;
  st_lv_BIT_13 = 0_BOOL;
  st_lv_BIT_14 = 0_BOOL;
  st_lv_BIT_15 = 0_BOOL;
  st_lv_BIT_16 = 0_BOOL;
  st_lv_BIT_17 = 0_BOOL;
  st_lv_BIT_18 = 0_BOOL;
  st_lv_BIT_19 = 0_BOOL;
  st_lv_BIT_20 = 0_BOOL;
  st_lv_BIT_21 = 0_BOOL;
  st_lv_BIT_22 = 0_BOOL;
  st_lv_BIT_23 = 0_BOOL;
  st_lv_BIT_24 = 0_BOOL;
  st_lv_BIT_25 = 0_BOOL;
  st_lv_BIT_26 = 0_BOOL;
  st_lv_BIT_27 = 0_BOOL;
  st_lv_BIT_28 = 0_BOOL;
  st_lv_BIT_29 = 0_BOOL;
  st_lv_BIT_30 = 0_BOOL;
  st_lv_BIT_31 = 0_BOOL;
  st_lv_BIT_32 = 0_BOOL;
  st_lv_BIT_33 = 0_BOOL;
  st_lv_BIT_34 = 0_BOOL;
  st_lv_BIT_35 = 0_BOOL;
  st_lv_BIT_36 = 0_BOOL;
  st_lv_BIT_37 = 0_BOOL;
  st_lv_BIT_38 = 0_BOOL;
  st_lv_BIT_39 = 0_BOOL;
  st_lv_BIT_40 = 0_BOOL;
  st_lv_BIT_41 = 0_BOOL;
  st_lv_BIT_42 = 0_BOOL;
  st_lv_BIT_43 = 0_BOOL;
  st_lv_BIT_44 = 0_BOOL;
  st_lv_BIT_45 = 0_BOOL;
  st_lv_BIT_46 = 0_BOOL;
  st_lv_BIT_47 = 0_BOOL;
  st_lv_BIT_48 = 0_BOOL;
  st_lv_BIT_49 = 0_BOOL;
  st_lv_BIT_50 = 0_BOOL;
  st_lv_BIT_51 = 0_BOOL;
  st_lv_BIT_52 = 0_BOOL;
  st_lv_BIT_53 = 0_BOOL;
  st_lv_BIT_54 = 0_BOOL;
  st_lv_BIT_55 = 0_BOOL;
  st_lv_BIT_56 = 0_BOOL;
  st_lv_BIT_57 = 0_BOOL;
  st_lv_BIT_58 = 0_BOOL;
  st_lv_BIT_59 = 0_BOOL;
  st_lv_BIT_60 = 0_BOOL;
  st_lv_BIT_61 = 0_BOOL;
  st_lv_BIT_62 = 0_BOOL;
  st_lv_BIT_63 = 0_BOOL;

  #line 75 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_00 = st_lv_IN.cpartial<CIEC_BOOL>(0);
  #line 76 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_01 = st_lv_IN.cpartial<CIEC_BOOL>(1);
  #line 77 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_02 = st_lv_IN.cpartial<CIEC_BOOL>(2);
  #line 78 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_03 = st_lv_IN.cpartial<CIEC_BOOL>(3);
  #line 79 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_04 = st_lv_IN.cpartial<CIEC_BOOL>(4);
  #line 80 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_05 = st_lv_IN.cpartial<CIEC_BOOL>(5);
  #line 81 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_06 = st_lv_IN.cpartial<CIEC_BOOL>(6);
  #line 82 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_07 = st_lv_IN.cpartial<CIEC_BOOL>(7);
  #line 83 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_08 = st_lv_IN.cpartial<CIEC_BOOL>(8);
  #line 84 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_09 = st_lv_IN.cpartial<CIEC_BOOL>(9);
  #line 85 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_10 = st_lv_IN.cpartial<CIEC_BOOL>(10);
  #line 86 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_11 = st_lv_IN.cpartial<CIEC_BOOL>(11);
  #line 87 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_12 = st_lv_IN.cpartial<CIEC_BOOL>(12);
  #line 88 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_13 = st_lv_IN.cpartial<CIEC_BOOL>(13);
  #line 89 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_14 = st_lv_IN.cpartial<CIEC_BOOL>(14);
  #line 90 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_15 = st_lv_IN.cpartial<CIEC_BOOL>(15);
  #line 91 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_16 = st_lv_IN.cpartial<CIEC_BOOL>(16);
  #line 92 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_17 = st_lv_IN.cpartial<CIEC_BOOL>(17);
  #line 93 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_18 = st_lv_IN.cpartial<CIEC_BOOL>(18);
  #line 94 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_19 = st_lv_IN.cpartial<CIEC_BOOL>(19);
  #line 95 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_20 = st_lv_IN.cpartial<CIEC_BOOL>(20);
  #line 96 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_21 = st_lv_IN.cpartial<CIEC_BOOL>(21);
  #line 97 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_22 = st_lv_IN.cpartial<CIEC_BOOL>(22);
  #line 98 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_23 = st_lv_IN.cpartial<CIEC_BOOL>(23);
  #line 99 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_24 = st_lv_IN.cpartial<CIEC_BOOL>(24);
  #line 100 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_25 = st_lv_IN.cpartial<CIEC_BOOL>(25);
  #line 101 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_26 = st_lv_IN.cpartial<CIEC_BOOL>(26);
  #line 102 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_27 = st_lv_IN.cpartial<CIEC_BOOL>(27);
  #line 103 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_28 = st_lv_IN.cpartial<CIEC_BOOL>(28);
  #line 104 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_29 = st_lv_IN.cpartial<CIEC_BOOL>(29);
  #line 105 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_30 = st_lv_IN.cpartial<CIEC_BOOL>(30);
  #line 106 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_31 = st_lv_IN.cpartial<CIEC_BOOL>(31);
  #line 107 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_32 = st_lv_IN.cpartial<CIEC_BOOL>(32);
  #line 108 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_33 = st_lv_IN.cpartial<CIEC_BOOL>(33);
  #line 109 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_34 = st_lv_IN.cpartial<CIEC_BOOL>(34);
  #line 110 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_35 = st_lv_IN.cpartial<CIEC_BOOL>(35);
  #line 111 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_36 = st_lv_IN.cpartial<CIEC_BOOL>(36);
  #line 112 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_37 = st_lv_IN.cpartial<CIEC_BOOL>(37);
  #line 113 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_38 = st_lv_IN.cpartial<CIEC_BOOL>(38);
  #line 114 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_39 = st_lv_IN.cpartial<CIEC_BOOL>(39);
  #line 115 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_40 = st_lv_IN.cpartial<CIEC_BOOL>(40);
  #line 116 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_41 = st_lv_IN.cpartial<CIEC_BOOL>(41);
  #line 117 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_42 = st_lv_IN.cpartial<CIEC_BOOL>(42);
  #line 118 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_43 = st_lv_IN.cpartial<CIEC_BOOL>(43);
  #line 119 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_44 = st_lv_IN.cpartial<CIEC_BOOL>(44);
  #line 120 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_45 = st_lv_IN.cpartial<CIEC_BOOL>(45);
  #line 121 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_46 = st_lv_IN.cpartial<CIEC_BOOL>(46);
  #line 122 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_47 = st_lv_IN.cpartial<CIEC_BOOL>(47);
  #line 123 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_48 = st_lv_IN.cpartial<CIEC_BOOL>(48);
  #line 124 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_49 = st_lv_IN.cpartial<CIEC_BOOL>(49);
  #line 125 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_50 = st_lv_IN.cpartial<CIEC_BOOL>(50);
  #line 126 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_51 = st_lv_IN.cpartial<CIEC_BOOL>(51);
  #line 127 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_52 = st_lv_IN.cpartial<CIEC_BOOL>(52);
  #line 128 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_53 = st_lv_IN.cpartial<CIEC_BOOL>(53);
  #line 129 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_54 = st_lv_IN.cpartial<CIEC_BOOL>(54);
  #line 130 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_55 = st_lv_IN.cpartial<CIEC_BOOL>(55);
  #line 131 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_56 = st_lv_IN.cpartial<CIEC_BOOL>(56);
  #line 132 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_57 = st_lv_IN.cpartial<CIEC_BOOL>(57);
  #line 133 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_58 = st_lv_IN.cpartial<CIEC_BOOL>(58);
  #line 134 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_59 = st_lv_IN.cpartial<CIEC_BOOL>(59);
  #line 135 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_60 = st_lv_IN.cpartial<CIEC_BOOL>(60);
  #line 136 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_61 = st_lv_IN.cpartial<CIEC_BOOL>(61);
  #line 137 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_62 = st_lv_IN.cpartial<CIEC_BOOL>(62);
  #line 138 "SPLIT_LWORD_INTO_BOOLS.fct"
  st_lv_BIT_63 = st_lv_IN.cpartial<CIEC_BOOL>(63);

}

