#ifndef DYNAMIXEL_ANALYZER_H
#define DYNAMIXEL_ANALYZER_H

#include <Analyzer.h>
#include "DynamixelAnalyzerResults.h"
#include "DynamixelSimulationDataGenerator.h"

class DynamixelAnalyzerSettings;
class ANALYZER_EXPORT DynamixelAnalyzer : public Analyzer
{
public:
	DynamixelAnalyzer();
	virtual ~DynamixelAnalyzer();
	virtual void WorkerThread();

	virtual U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channels );
	virtual U32 GetMinimumSampleRateHz();

	virtual const char* GetAnalyzerName() const;
	virtual bool NeedsRerun();

	enum INSTRUCTION
	{
	  NONE,
	  APING,
	  READ,
	  WRITE,
	  REG_WRITE,
	  ACTION,
	  RESET,
	  SYNC_WRITE=0x83
	};

	enum DECODE_STEP
	{
	  DE_HEADER1,
	  DE_HEADER2,
	  DE_ID,
	  DE_LENGTH,
	  DE_INSTRUCTION,
	  DE_DATA,
	  DE_CHECKSUM
	};

protected: //vars
	std::auto_ptr< DynamixelAnalyzerSettings > mSettings;
	std::auto_ptr< DynamixelAnalyzerResults > mResults;
	AnalyzerChannelData* mSerial;

	DynamixelSimulationDataGenerator mSimulationDataGenerator;
	bool mSimulationInitilized;

	//Serial analysis vars:
	U32 mSampleRateHz;
	U32 mStartOfStopBitOffset;
	U32 mEndOfStopBitOffset;

	//Dynamixel analysis vars:
	int DecodeIndex;
    U8 mID;
    U8 mCount;
    U8 mLength;
    U8 mInstruction;
    U8 mData[ 256 ];
    U8 mChecksum;
};

extern "C" ANALYZER_EXPORT const char* __cdecl GetAnalyzerName();
extern "C" ANALYZER_EXPORT Analyzer* __cdecl CreateAnalyzer( );
extern "C" ANALYZER_EXPORT void __cdecl DestroyAnalyzer( Analyzer* analyzer );

#endif //DYNAMIXEL_ANALYZER_H