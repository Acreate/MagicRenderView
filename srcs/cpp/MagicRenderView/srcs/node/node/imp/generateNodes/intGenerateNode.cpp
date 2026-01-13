#include "intGenerateNode.h"

#include "../../../../app/application.h"
#include "../../../../director/printerDirector.h"
#include "../../../../director/varDirector.h"
#include "../../../../srack/srackInfo.h"
#include "../../../port/inputPort/generate/generateInputPort.h"
#include "../../../port/outputPort/generate/generateIntOutputPort.h"
#include "../../../port/outputPort/unity/intOutputPort.h"
#include "../../../port/outputPort/unity/uIntOutputPort.h"

IntGenerateNode::IntGenerateNode( const QString &node_name ) : GenerateNode( node_name ) {
	arrayCount = nullptr;
	arrayIndex = nullptr;
	currentIndexVar = nullptr;
	generateInputPort = nullptr;
	outputVarPort = nullptr;
	outputIndexPort = nullptr;
	outputCountPort = nullptr;
}
bool IntGenerateNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		Def_AppendInputPortType( tr( "生成" ), generateInputPort );
		Def_AppendBindVarOutputPortType( tr( "导出值" ), outputVarPort, currentIndexVar );
		Def_AppendBindVarOutputPortType( tr( "导出下标" ), outputIndexPort, arrayIndex );
		Def_AppendBindVarOutputPortType( tr( "导出总数" ), outputCountPort, arrayCount );
		return true;
	};
	return GenerateNode::initEx( parent );
}
bool IntGenerateNode::initArrayUintyTypeName( QString &change_array_unty_type_name ) {
	return varDirector->getTypeName( typeid( TGenerateType ), change_array_unty_type_name );
}
bool IntGenerateNode::updateLayout( ) {
	if( GenerateNode::updateLayout( ) == false )
		return false;
	return true;
}
std::vector< IntGenerateNode::TGenerateType > * IntGenerateNode::getGenerateVarPtr( ) const {
	return overVarPtr;
}
bool IntGenerateNode::formUint8ArrayData( size_t &result_use_count, const uint8_t *source_array_ptr, const size_t &source_array_count ) {
	bool formUint8ArrayData = GenerateNode::formUint8ArrayData( result_use_count, source_array_ptr, source_array_count );
	return formUint8ArrayData;
}
bool IntGenerateNode::toUint8VectorData( std::vector< uint8_t > &result_vector_data ) {
	bool uint8VectorData = GenerateNode::toUint8VectorData( result_vector_data );
	return uint8VectorData;
}
bool IntGenerateNode::initVarPtr( ) {
	if( varDirector->getTypeName( typeid( TGenerateType ), generateTypeName ) == false )
		return false;
	if( varPtr != nullptr )
		if( varDirector->release( varPtr ) == false ) {
			auto printerDirector = instancePtr->getPrinterDirector( );
			printerDirector->info( tr( "释放失败 [0x%1]" ).arg( QString::number( ( size_t ) overVarPtr, 16 ).toUpper( ) ), Create_SrackInfo( ) );
			return false;
		}
	overVarPtr = nullptr;
	if( varDirector->create( overVarPtr ) == false )
		return false;
	varPtr = overVarPtr;

	return true;
}
bool IntGenerateNode::readyNodeRunData( ) {
	return true;
}
bool IntGenerateNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	*arrayCount = overVarPtr->size( );
	if( *arrayCount == 0 )
		return false;
	const auto &outputPorts = getRefPort( generateInputPort );
	size_t count = outputPorts.size( );
	if( count == 0 )
		return false;
	OutputPort *const *port = outputPorts.data( );
	OutputPort *outputPort = port[ 0 ];
	auto generateVarPtr = outputPort->getVarPtr( );
	auto nodeDirector = outputPort->getVarDirector( );
	size_t *index;
	if( nodeDirector->cast_ptr( generateVarPtr, index ) == false )
		return false;
	*arrayIndex = *index;
	if( *arrayIndex >= *arrayCount ) // 如果大于，则取重复
		*arrayIndex = *arrayIndex % *arrayCount;
	auto data = overVarPtr->data( );
	*currentIndexVar = data[ *arrayIndex ];
	return true;
}
