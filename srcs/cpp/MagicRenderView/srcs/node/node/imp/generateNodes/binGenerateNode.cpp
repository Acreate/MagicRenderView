#include "binGenerateNode.h"

#include "../../../../app/application.h"
#include "../../../../director/printerDirector.h"
#include "../../../../director/varDirector.h"
#include "../../../../srack/srackInfo.h"
#include "../../../port/inputPort/generate/generateInputPort.h"
#include "../../../port/outputPort/unity/binOutputPort.h"
#include "../../../port/outputPort/unity/uIntOutputPort.h"

BinGenerateNode::BinGenerateNode( const QString &node_name ) : GenerateNode( node_name ) {
	arrayCount = nullptr;
	arrayIndex = nullptr;
	currentIndexVar = nullptr;
	generateInputPort = nullptr;
	outputVarPort = nullptr;
	outputIndexPort = nullptr;
	outputCountPort = nullptr;
}
bool BinGenerateNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		generateInputPort = appendInputPortType< GenerateInputPort >( tr( "生成" ) );
		if( generateInputPort == nullptr )
			return false;
		outputVarPort = appendOutputPortType< BinOutputPort >( tr( "导出值" ) );
		if( outputVarPort == nullptr )
			return false;
		outputIndexPort = appendOutputPortType< UIntOutputPort >( tr( "导出下标" ) );
		if( outputIndexPort == nullptr )
			return false;
		outputCountPort = appendOutputPortType< UIntOutputPort >( tr( "导出总数" ) );
		if( outputCountPort == nullptr )
			return false;
		// 绑定指针
		if( setInfo( outputIndexPort, varDirector, arrayIndex ) == false )
			return false;
		if( setInfo( outputVarPort, varDirector, currentIndexVar ) == false )
			return false;
		if( setInfo( outputCountPort, varDirector, arrayCount ) == false )
			return false;
		return true;
	};
	return GenerateNode::initEx( parent );
}
bool BinGenerateNode::initArrayUintyTypeName( QString &change_array_unty_type_name ) {
	return varDirector->getTypeName( typeid( TGenerateType ), change_array_unty_type_name );
}
bool BinGenerateNode::updateLayout( ) {
	if( GenerateNode::updateLayout( ) == false )
		return false;
	return true;
}
std::vector< BinGenerateNode::TGenerateType > * BinGenerateNode::getGenerateVarPtr( ) const {
	return overVarPtr;
}
bool BinGenerateNode::formUint8ArrayData( size_t &result_use_count, const uint8_t *source_array_ptr, const size_t &source_array_count ) {
	bool formUint8ArrayData = GenerateNode::formUint8ArrayData( result_use_count, source_array_ptr, source_array_count );
	return formUint8ArrayData;
}
bool BinGenerateNode::toUint8VectorData( std::vector< uint8_t > &result_vector_data ) {
	bool uint8VectorData = GenerateNode::toUint8VectorData( result_vector_data );
	return uint8VectorData;
}
bool BinGenerateNode::initVarPtr( ) {
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
bool BinGenerateNode::readyNodeRunData( ) {
	return true;
}
bool BinGenerateNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
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
	*arrayCount = 0;
	*arrayIndex = 0;
	*arrayCount = 0;
	if( nodeDirector->cast_ptr( generateVarPtr, index ) == false )
		return true;
	*arrayIndex = *index;
	if( *arrayIndex >= *arrayCount ) // 如果大于，则取重复
		*arrayIndex = *arrayIndex % *arrayCount;
	auto data = overVarPtr->data( );
	*currentIndexVar = data[ *arrayIndex ];
	return true;
}
