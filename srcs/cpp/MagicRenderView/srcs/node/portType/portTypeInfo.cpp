#include "portTypeInfo.h"

#include "../node/node.h"
#include "../port/inputPort/inputPort.h"
#include "../port/outputPort/outputPort.h"
bool PortTypeInfo::load( OutputPort *output_port, InputPort *input_port ) {
	outputNodeGeneratorCode = output_port->parentNode->generateCode;
	if( outputNodeGeneratorCode == 0 )
		return false;
	outputPortGeneratorCode = output_port->generateCode;
	if( outputPortGeneratorCode == 0 )
		return false;
	inputNodeGeneratorCode = input_port->parentNode->generateCode;
	if( inputNodeGeneratorCode == 0 )
		return false;
	inputPortGeneratorCode = input_port->generateCode;
	if( inputPortGeneratorCode == 0 )
		return false;
	return true;
}
