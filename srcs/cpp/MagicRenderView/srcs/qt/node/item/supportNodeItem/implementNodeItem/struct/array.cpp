#include "array.h"

#include "../../../../../generate/varGenerate.h"

#include "../../../../prot/inputProt/inpInputPort/any/anyInputPort.h"
#include "../../../../prot/inputProt/inpInputPort/int/uIntInputPort.h"
#include "../../../../prot/inputProt/inpInputPort/struct/anyArrayInputPort.h"
#include "../../../../prot/outputProt/impOutputPort/any/anyOutputPort.h"
#include "../../../../prot/outputProt/impOutputPort/int/uIntOutputPort.h"

#include <qt/varType/I_Var.h>

#include "../../../../prot/outputProt/impOutputPort/struct/anyArrayOutputPort.h"
Imp_StaticMetaInfo( Array, QObject::tr( "数组" ), QObject::tr( "结构体" ) );
Array::Array( ) {
}
bool Array::intPortItems( MainWidget *parent ) {
	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			auto arrayInputPort = addInputProt< AnyArrayInputPort >( "值", true );
			auto arrayoutputPort = addOutputProt< AnyArrayOutputPort >( "数组" );
			auto indexInprot = addInputProt< UIntInputPort >( "下标", false );
			auto elemtOutPort = addOutputProt< AnyOutputPort >( "元素值" );
			auto indexOutprot = addOutputProt< UIntOutputPort >( "下标" );
			auto intOutputPort = addOutputProt< UIntOutputPort >( "数据量" );
			this->nodeItemFcuntion = [this, &indexInprot, &elemtOutPort, &arrayoutputPort, &arrayInputPort, &intOutputPort, &indexOutprot] ( const size_t &index, QString &result_msg )->nodeItemEnum::Node_Item_Result_Type {

				size_t arrayIndex = 0;
				if( varGenerate->conver( typeid( size_t ), &arrayIndex, indexInprot->getVar( ) ) == false )
					return nodeItemEnum::Node_Item_Result_Type::Param_Error;
				auto &varVector = getPortVarVector( arrayoutputPort );
				auto &sourceVarVector = getPortVarVector( arrayInputPort );
				varVector = sourceVarVector;
				size_t count = varVector.size( );
				I_Var *rightTypeInfo = getPortVar( intOutputPort ).get( );
				if( varGenerate->conver( rightTypeInfo, typeid( size_t ), &count ) == false )
					return nodeItemEnum::Node_Item_Result_Type::Param_Error;
				auto arrayPtr = varVector.data( );
				if( arrayIndex >= count )
					arrayIndex = count - 1;

				rightTypeInfo = getPortVar( indexOutprot ).get( );
				if( varGenerate->conver( rightTypeInfo, typeid( size_t ), &arrayIndex ) == false )
					return nodeItemEnum::Node_Item_Result_Type::Param_Error;

				rightTypeInfo = arrayPtr[ arrayIndex ].get( );
				if( varGenerate->conver( elemtOutPort->getVar( ), rightTypeInfo ) == false )
					return nodeItemEnum::Node_Item_Result_Type::Param_Error;

				return nodeItemEnum::Node_Item_Result_Type::Finish;
			};
			return true;
		} );
}
