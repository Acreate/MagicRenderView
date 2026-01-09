#include "imageGenerateNode.h"

#include "../../../../app/application.h"
#include "../../../../director/printerDirector.h"
#include "../../../../director/varDirector.h"
#include "../../../../srack/srackInfo.h"
#include "../../../port/inputPort/generate/generateInputPort.h"
#include "../../../port/outputPort/generate/generateIntOutputPort.h"
#include "../../../port/outputPort/unity/imageOutputPort.h"
#include "../../../port/outputPort/unity/uIntOutputPort.h"

ImageGenerateNode::ImageGenerateNode( const QString &node_name ) : GenerateNode( node_name ) {
	arrayCount = nullptr;
	arrayIndex = nullptr;
	currentIndexVar = nullptr;
	generateInputPort = nullptr;
	outputVarPort = nullptr;
	outputIndexPort = nullptr;
	outputCountPort = nullptr;
}
bool ImageGenerateNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		generateInputPort = appendInputPortType< GenerateInputPort >( tr( "生成" ) );
		if( generateInputPort == nullptr )
			return false;
		outputVarPort = appendOutputPortType< ImageOutputPort >( tr( "导出值" ) );
		if( outputVarPort == nullptr )
			return false;
		outputIndexPort = appendOutputPortType< UIntOutputPort >( tr( "导出下标" ) );
		if( outputIndexPort == nullptr )
			return false;
		outputCountPort = appendOutputPortType< UIntOutputPort >( tr( "导出总数" ) );
		if( outputCountPort == nullptr )
			return false;
		if( arrayCount == nullptr )
			if( varDirector->create( arrayCount ) == false )
				return false;
		if( arrayIndex == nullptr )
			if( varDirector->create( arrayIndex ) == false )
				return false;
		if( currentIndexVar == nullptr )
			if( varDirector->create( currentIndexVar ) == false )
				return false;
		// 绑定指针
		if( setPortVar( outputIndexPort, arrayIndex ) == false )
			return false;
		if( setPortVar( outputVarPort, currentIndexVar ) == false )
			return false;
		if( setPortVar( outputCountPort, arrayCount ) == false )
			return false;
		return true;
	};
	return GenerateNode::initEx( parent );
}
bool ImageGenerateNode::initArrayUintyTypeName( QString &change_array_unty_type_name ) {
	return varDirector->getTypeName( typeid( TGenerateType ), change_array_unty_type_name );
}
bool ImageGenerateNode::updateLayout( ) {
	if( GenerateNode::updateLayout( ) == false )
		return false;
	return true;
}
std::vector< ImageGenerateNode::TGenerateType > * ImageGenerateNode::getGenerateVarPtr( ) const {
	return overVarPtr;
}
bool ImageGenerateNode::formUint8ArrayData( size_t &result_use_count, const uint8_t *source_array_ptr, const size_t &source_array_count ) {
	bool formUint8ArrayData = GenerateNode::formUint8ArrayData( result_use_count, source_array_ptr, source_array_count );
	return formUint8ArrayData;
}
bool ImageGenerateNode::toUint8VectorData( std::vector< uint8_t > &result_vector_data ) {
	bool uint8VectorData = GenerateNode::toUint8VectorData( result_vector_data );
	return uint8VectorData;
}
bool ImageGenerateNode::initVarPtr( ) {
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
bool ImageGenerateNode::readyNodeRunData( ) {
	return true;
}
bool ImageGenerateNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
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
	auto parentNode = outputPort->getParentNode( );
	auto parentNodeDirector = parentNode->getVarDirector( );
	size_t *index;
	*arrayCount = 0;
	*arrayIndex = 0;
	*arrayCount = 0;
	if( parentNodeDirector->cast_ptr( generateVarPtr, index ) == false )
		return false;
	*arrayIndex = *index;
	if( *arrayIndex >= *arrayCount ) // 如果大于，则取重复
		*arrayIndex = *arrayIndex % *arrayCount;
	auto data = overVarPtr->data( );
	*currentIndexVar = data[ *arrayIndex ];
	return true;
}
