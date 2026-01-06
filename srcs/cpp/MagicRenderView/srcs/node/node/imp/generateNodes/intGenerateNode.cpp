#include "intGenerateNode.h"

#include "../../../../app/application.h"
#include "../../../../director/printerDirector.h"
#include "../../../../director/varDirector.h"
#include "../../../../srack/srackInfo.h"
#include "../../../port/inputPort/generate/generateInputPort.h"
#include "../../../port/outputPort/generate/generateIntOutputPort.h"

bool IntGenerateNode::initEx( MainWidget *parent ) {
	initExCallFunction = [this] ( MainWidget *draw_node_widget ) {
		if( appendInputPortType< GenerateInputPort >( tr( "生成" ) ) == nullptr )
			return false;
		if( appendOutputPortType< GenerateIntOutputPort >( tr( "导出值" ) ) == nullptr )
			return false;
		if( appendOutputPortType< GenerateIntOutputPort >( tr( "导出下标" ) ) == nullptr )
			return false;
		if( appendOutputPortType< GenerateIntOutputPort >( tr( "导出总数" ) ) == nullptr )
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
bool IntGenerateNode::readNodeRunData( ) {
	return true;
}
bool IntGenerateNode::fillInputPortCall( const QDateTime &ndoe_run_start_data_time, std::vector< Node * > &result_need_run_ref_node_vector ) {
	return true;
}
bool IntGenerateNode::fillNodeCall( const QDateTime &ndoe_run_start_data_time ) {
	return true;
}
bool IntGenerateNode::fillOutputPortCall( std::vector< Node * > &result_next_run_advise_node_vector, const QDateTime &ndoe_run_start_data_time ) {
	return true;
}
