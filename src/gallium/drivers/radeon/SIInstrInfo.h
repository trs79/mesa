//===-- SIInstrInfo.h - SI Instruction Info Interface ---------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Interface definition for SIInstrInfo.
//
//===----------------------------------------------------------------------===//


#ifndef SIINSTRINFO_H
#define SIINSTRINFO_H

#include "AMDGPUInstrInfo.h"
#include "SIRegisterInfo.h"

namespace llvm {

class SIInstrInfo : public AMDGPUInstrInfo {
private:
  const SIRegisterInfo RI;
  AMDGPUTargetMachine &TM;

  MachineInstr * convertABS_f32(MachineInstr & absInstr, MachineFunction &MF,
                                DebugLoc DL) const;

  MachineInstr * convertCLAMP_f32(MachineInstr & clampInstr,
                                  MachineFunction &MF, DebugLoc DL) const;

public:
  explicit SIInstrInfo(AMDGPUTargetMachine &tm);

  const SIRegisterInfo &getRegisterInfo() const;

  virtual void copyPhysReg(MachineBasicBlock &MBB,
                           MachineBasicBlock::iterator MI, DebugLoc DL,
                           unsigned DestReg, unsigned SrcReg,
                           bool KillSrc) const;

  /// getEncodingType - Returns the encoding type of this instruction.  
  unsigned getEncodingType(const MachineInstr &MI) const;

  /// getEncodingBytes - Returns the size of this instructions encoding in
  /// number of bytes.
  unsigned getEncodingBytes(const MachineInstr &MI) const;

  /// convertToISA - Convert the AMDIL MachineInstr to a supported SI
  ///MachineInstr
  virtual MachineInstr * convertToISA(MachineInstr & MI, MachineFunction &MF,
                                        DebugLoc DL) const;

  /// getISAOpcode - This function takes an AMDIL opcode as an argument and
  /// returns an equivalent SI opcode.
  virtual unsigned getISAOpcode(unsigned AMDILopcode) const;

  };

} // End namespace llvm

// These must be kept in sync with SIInstructions.td and also the
// InstrEncodingInfo array in SIInstrInfo.cpp.
//
// NOTE: This enum is only used to identify the encoding type within LLVM,
// the actual encoding type that is part of the instruction format is different
namespace SIInstrEncodingType {
  enum Encoding {
    EXP = 0,
    LDS = 1,
    MIMG = 2,
    MTBUF = 3,
    MUBUF = 4,
    SMRD = 5,
    SOP1 = 6,
    SOP2 = 7,
    SOPC = 8,
    SOPK = 9,
    SOPP = 10,
    VINTRP = 11,
    VOP1 = 12,
    VOP2 = 13,
    VOP3 = 14,
    VOPC = 15
  };
}

#define SI_INSTR_FLAGS_ENCODING_MASK 0xf

namespace SIInstrFlags {
  enum Flags {
    // First 4 bits are the instruction encoding
    NEED_WAIT = 1 << 4
  };
}

#endif //SIINSTRINFO_H