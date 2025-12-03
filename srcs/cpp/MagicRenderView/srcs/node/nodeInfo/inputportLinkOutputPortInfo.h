#ifndef INPUTPORTLINKOUTPUTPORTINFO_H_H_HEAD__FILE__
#define INPUTPORTLINKOUTPUTPORTINFO_H_H_HEAD__FILE__
#pragma once
#include <vector>

class OutputPort;
class InputPort;
class InputportLinkOutputPortInfo {
	InputPort *inputPort;
	std::vector< OutputPort * > outputPortVector;
public:
	InputportLinkOutputPortInfo( InputPort *input_port );
	virtual ~InputportLinkOutputPortInfo( ) { }
	virtual bool appendOutputPort( OutputPort *output_port );
	virtual bool removeOutputPort( OutputPort *output_port );
	virtual size_t linkInputPortCount( ) const;
	virtual InputPort * getInputPort( ) const { return inputPort; }
	virtual const std::vector< OutputPort * > & getOutputPortVector( ) const { return outputPortVector; }
};

#endif // INPUTPORTLINKOUTPUTPORTINFO_H_H_HEAD__FILE__
