#include "intGenerateNode.h"

#include "../../../../app/application.h"
#include "../../../../director/printerDirector.h"
#include "../../../../director/varDirector.h"
#include "../../../../srack/srackInfo.h"

#include "../../../port/inputPort/any/anyInputPort.h"
#include "../../../port/outputPort/array/intVectorOutputPort.h"

bool IntGenerateNode::init( DrawNodeWidget *parent ) {
	if( GenerateNode::init( parent ) == false )
		return false;
	if( appendInputPortType< AnyInputPort >( tr( "过程接入" ) ) == nullptr )
		return false;
	if( appendOutputPortType< IntVectorOutputPort >( tr( "导出生成整数序列" ) ) == nullptr )
		return false;
	initVarPtr( );
	return true;

}
bool IntGenerateNode::updateLayout( ) {
	if( GenerateNode::updateLayout( ) == false )
		return false;
	return true;
}
std::vector< int64_t > * IntGenerateNode::getGenerateVarPtr( ) const {
	return overVarPtr;
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
