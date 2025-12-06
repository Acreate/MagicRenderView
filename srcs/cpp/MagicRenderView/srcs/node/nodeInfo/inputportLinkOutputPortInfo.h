#ifndef INPUTPORTLINKOUTPUTPORTINFO_H_H_HEAD__FILE__
#define INPUTPORTLINKOUTPUTPORTINFO_H_H_HEAD__FILE__
#pragma once
#include <vector>
#include <QString>

#include <tools/aliasType.h>

class OutputPort;
class InputPort;
class InputportLinkOutputPortInfo {
	friend class NodeBuilderStream;
	friend class NodeBuilderTools;
private:
	InputPort *inputPort;
	std::vector< OutputPort * > outputPortVector;
public:
	InputportLinkOutputPortInfo( InputPort *input_port = nullptr );
	virtual ~InputportLinkOutputPortInfo( ) { }
	virtual bool appendOutputPort( OutputPort *output_port );
	virtual bool removeOutputPort( OutputPort *output_port );
	virtual size_t linkInputPortCount( ) const;
	virtual InputPort * getInputPort( ) const { return inputPort; }
	virtual const std::vector< OutputPort * > & getOutputPortVector( ) const { return outputPortVector; }
	virtual bool toUint8VectorData( std::vector< uint8_t > &result_vector_data );
	virtual bool toLinkMap( InputportLinkOutputPortInfoMap &result_map, size_t &user_data_count, const uint8_t *source_data_ptr, const size_t &source_data_count ) const;
};

#endif // INPUTPORTLINKOUTPUTPORTINFO_H_H_HEAD__FILE__
