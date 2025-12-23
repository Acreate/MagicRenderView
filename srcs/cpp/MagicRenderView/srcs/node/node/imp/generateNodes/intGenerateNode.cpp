#include "intGenerateNode.h"

#include "../../../../app/application.h"
#include "../../../../director/printerDirector.h"
#include "../../../../director/varDirector.h"
#include "../../../../srack/srackInfo.h"
#include "../../../port/inputPort/interface/interFaceInputPort.h"

#include "../../../port/outputPort/generate/generateIntOutputPort.h"

bool IntGenerateNode::initEx( DrawNodeWidget *parent ) {
	initExCallFunction = [this] ( DrawNodeWidget *draw_node_widget ) {
		if( appendInputPortType< InterFaceInputPort >( tr( "过程接入" ) ) == nullptr )
			return false;
		if( appendOutputPortType< GenerateIntOutputPort >( tr( "导出生成整数序列" ) ) == nullptr )
			return false;
		return true;
	};
	return GenerateNode::initEx( parent );
}
bool IntGenerateNode::initArrayUintyTypeName( QString &change_array_unty_type_name ) {
	return varDirector->getTypeName( typeid( int64_t ), change_array_unty_type_name );
}
bool IntGenerateNode::updateLayout( ) {
	if( GenerateNode::updateLayout( ) == false )
		return false;
	return true;
}
std::vector< int64_t > * IntGenerateNode::getGenerateVarPtr( ) const {
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
	if( varDirector->getTypeName( typeid( int64_t ), generateTypeName ) == false )
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
