#ifndef PORTTYPEINFO_H_H_HEAD__FILE__
#define PORTTYPEINFO_H_H_HEAD__FILE__
#pragma once
#include <cstdint>
class InputPort;
class OutputPort;
class PortTypeInfo {
	friend class NodeTypeInfo;
	friend class NodeTypeInfoSerializeion;
	friend class NodeTypeInfoStack;
protected:
	uint64_t outputNodeGeneratorCode;
	uint64_t outputPortGeneratorCode;
	uint64_t inputNodeGeneratorCode;
	uint64_t inputPortGeneratorCode;
public:
	virtual ~PortTypeInfo( ) = default;
	virtual bool load( OutputPort *output_port, InputPort *input_port );
	virtual uint64_t getOutputNodeGeneratorCode( ) const { return outputNodeGeneratorCode; }
	virtual uint64_t getOutputPortGeneratorCode( ) const { return outputPortGeneratorCode; }
	virtual uint64_t getInputNodeGeneratorCode( ) const { return inputNodeGeneratorCode; }
	virtual uint64_t getInputPortGeneratorCode( ) const { return inputPortGeneratorCode; }
};

#endif // PORTTYPEINFO_H_H_HEAD__FILE__
