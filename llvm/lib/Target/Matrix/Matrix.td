//===-- Matrix.td - Describe the Matrix Target Machine ---------*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// Without this will have error: 'matrix32I' is not a recognized processor for 
//  this target (ignoring processor)
//===----------------------------------------------------------------------===//
// Matrix Subtarget features                                                    //
//===----------------------------------------------------------------------===//

def FeatureChapter3_1  : SubtargetFeature<"ch3_1", "HasChapterDummy", "true",
                                "Enable Chapter instructions.">;
def FeatureChapter3_2  : SubtargetFeature<"ch3_2", "HasChapterDummy", "true",
                                "Enable Chapter instructions.">;
def FeatureChapter3_3  : SubtargetFeature<"ch3_3", "HasChapterDummy", "true",
                                "Enable Chapter instructions.">;
def FeatureChapter3_4  : SubtargetFeature<"ch3_4", "HasChapterDummy", "true",
                                "Enable Chapter instructions.">;
def FeatureChapter3_5  : SubtargetFeature<"ch3_5", "HasChapterDummy", "true",
                                "Enable Chapter instructions.">;
def FeatureChapter4_1  : SubtargetFeature<"ch4_1", "HasChapterDummy", "true",
                                "Enable Chapter instructions.">;
def FeatureChapter4_2  : SubtargetFeature<"ch4_2", "HasChapterDummy", "true",
                                "Enable Chapter instructions.">;
def FeatureChapter5_1  : SubtargetFeature<"ch5_1", "HasChapterDummy", "true",
                                "Enable Chapter instructions.">;
def FeatureChapter6_1  : SubtargetFeature<"ch6_1", "HasChapterDummy", "true",
                                "Enable Chapter instructions.">;
def FeatureChapter7_1  : SubtargetFeature<"ch7_1", "HasChapterDummy", "true",
                                "Enable Chapter instructions.">;
def FeatureChapter8_1  : SubtargetFeature<"ch8_1", "HasChapterDummy", "true",
                                "Enable Chapter instructions.">;
def FeatureChapter8_2  : SubtargetFeature<"ch8_2", "HasChapterDummy", "true",
                                "Enable Chapter instructions.">;
def FeatureChapter9_1  : SubtargetFeature<"ch9_1", "HasChapterDummy", "true",
                                "Enable Chapter instructions.">;
def FeatureChapter9_2  : SubtargetFeature<"ch9_2", "HasChapterDummy", "true",
                                "Enable Chapter instructions.">;
def FeatureChapter9_3  : SubtargetFeature<"ch9_3", "HasChapterDummy", "true",
                                "Enable Chapter instructions.">;
def FeatureChapter10_1 : SubtargetFeature<"ch10_1", "HasChapterDummy", "true",
                                "Enable Chapter instructions.">;
def FeatureChapter11_1 : SubtargetFeature<"ch11_1", "HasChapterDummy", "true",
                                "Enable Chapter instructions.">;
def FeatureChapter11_2 : SubtargetFeature<"ch11_2", "HasChapterDummy", "true",
                                "Enable Chapter instructions.">;
def FeatureChapter12_1 : SubtargetFeature<"ch12_1", "HasChapterDummy", "true",
                                "Enable Chapter instructions.">;
def FeatureChapterAll  : SubtargetFeature<"chall", "HasChapterDummy", "true",
                                "Enable Chapter instructions.",
                                [FeatureChapter3_1, FeatureChapter3_2, 
                                 FeatureChapter3_3, FeatureChapter3_4, 
                                 FeatureChapter3_5, 
                                 FeatureChapter4_1, FeatureChapter4_2, 
                                 FeatureChapter5_1, FeatureChapter6_1, 
                                 FeatureChapter7_1, FeatureChapter8_1, 
                                 FeatureChapter8_2, FeatureChapter9_1, 
                                 FeatureChapter9_2, FeatureChapter9_3, 
                                 FeatureChapter10_1, 
                                 FeatureChapter11_1, FeatureChapter11_2, 
                                 FeatureChapter12_1]>;

def FeatureCmp         : SubtargetFeature<"cmp", "HasCmp", "true",
                                "Enable 'cmp' instructions.">;
def FeatureSlt         : SubtargetFeature<"slt", "HasSlt", "true",
                                "Enable 'slt' instructions.">;
def FeatureMatrix32I     : SubtargetFeature<"matrix32I", "MatrixArchVersion", 
                                "Matrix32I", "Matrix32I ISA Support",
                                [FeatureCmp, FeatureChapterAll]>;
def FeatureMatrix32II    : SubtargetFeature<"matrix32II", "MatrixArchVersion",                      
                               "Matrix32II", "Matrix32II ISA Support (slt)",
                                [FeatureCmp, FeatureSlt, FeatureChapterAll]>;

//===----------------------------------------------------------------------===//
// Calling Conv, Instruction Descriptions
//===----------------------------------------------------------------------===//

include "MatrixSchedule.td"
include "MatrixInstrInfo.td"
include "MatrixCallingConv.td"

def MatrixInstrInfo : InstrInfo;
//===----------------------------------------------------------------------===//
// Matrix processors supported.
//===----------------------------------------------------------------------===//

class Proc<string Name, list<SubtargetFeature> Features>
 : Processor<Name, MatrixGenericItineraries, Features>;

def : Proc<"matrix32I",  [FeatureMatrix32I]>;
def : Proc<"matrix32II", [FeatureMatrix32II]>;
// Above make MatrixGenSubtargetInfo.inc set feature bit as the following order
// enum {
//   FeatureCmp =  1ULL << 0,
//   FeatureMatrix32I =  1ULL << 1,
//   FeatureMatrix32II =  1ULL << 2,
//   FeatureSlt =  1ULL << 3
// };

// Will generate MatrixGenAsmWrite.inc included by MatrixInstPrinter.cpp, contents 
//  as follows,
// void MatrixInstPrinter::printInstruction(const MCInst *MI, raw_ostream &O) {...}
// const char *MatrixInstPrinter::getRegisterName(unsigned RegNo) {...}
def Matrix : Target {
// def MatrixInstrInfo : InstrInfo as before.
  let InstructionSet = MatrixInstrInfo;
}

