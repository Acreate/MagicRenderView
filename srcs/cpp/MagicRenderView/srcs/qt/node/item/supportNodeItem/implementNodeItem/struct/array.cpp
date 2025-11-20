#include "array.h"

#include "../../../../../generate/varGenerate.h"

#include "../../../../prot/inputProt/inpInputPort/any/anyInputPort.h"
#include "../../../../prot/inputProt/inpInputPort/int/uIntInputPort.h"
#include "../../../../prot/outputProt/impOutputPort/any/anyOutputPort.h"
#include "../../../../prot/outputProt/impOutputPort/int/uIntOutputPort.h"

Imp_StaticMetaInfo( Array, QObject::tr( "数组" ), QObject::tr( "结构体" ) );
Array::Array( ) {
}
bool Array::intPortItems( MainWidget *parent ) {
	return initNodeItem(
		parent,
		[this] ( MainWidget *main_widget_parent ) {
			// 初始化节点名称
			setNodeTitleName( getMetaObjectName( ) );
			addInputProt< AnyInputPort >( "索引节点值", false );
			auto indexInprot = addInputProt< UIntInputPort >( "下标", false );
			auto elemtOutPort = addOutputProt< AnyOutputPort >( "元素值" );
			addOutputProt< UIntOutputPort >( "数据量" );
			this->nodeItemFcuntion = [this,&] ( const size_t &index, QString &result_msg )->nodeItemEnum::Node_Item_Result_Type {
				size_t arrayIndex = 0;
				if( varGenerate->conver( typeid( size_t ), &arrayIndex, indexInprot->getVar( ) ) == false )
					return nodeItemEnum::Node_Item_Result_Type::Param_Error;
				size_t count = arrayVar.size( );
				auto arrayPtr = arrayVar.data( );
				if( arrayIndex >= count )
					arrayIndex = count - 1;
				auto &pair = arrayPtr[ 0 ];
				auto &second = pair.second;
				std::shared_ptr< I_Var > rightTypeInfo = second.at( arrayIndex );
				if( varGenerate->conver( elemtOutPort->getVar( ), rightTypeInfo.get( ) ) == false )
					return nodeItemEnum::Node_Item_Result_Type::Param_Error;
				return nodeItemEnum::Node_Item_Result_Type::Finish;
			};
			return true;
		} );
}
bool Array::appendVar( NodePort *app_port, const std_shared_ptr< I_Var > &append_var ) {
	size_t count = arrayVar.size( );
	auto arrayPtr = arrayVar.data( );
	for( size_t index = 0; index < count; ++index )
		if( arrayPtr[ index ].first == app_port ) {
			arrayPtr[ index ].second.emplace_back( append_var );
			return true;
		}
	return ProcessNodeItem::appendVar( app_port, append_var );
}
