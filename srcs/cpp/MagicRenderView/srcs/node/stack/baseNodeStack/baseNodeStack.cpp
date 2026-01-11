#include "baseNodeStack.h"

#include <QMenu>

#include <director/printerDirector.h>

#include "../../node/imp/arrayNodes/baseOperation/float/floatArrayAddNode.h"
#include "../../node/imp/arrayNodes/baseOperation/float/floatArrayDivNode.h"
#include "../../node/imp/arrayNodes/baseOperation/float/floatArrayModNode.h"
#include "../../node/imp/arrayNodes/baseOperation/float/floatArrayMulNode.h"
#include "../../node/imp/arrayNodes/baseOperation/float/floatArraySubNode.h"
#include "../../node/imp/arrayNodes/baseOperation/int/intArrayAddNode.h"
#include "../../node/imp/arrayNodes/baseOperation/int/intArrayDivNode.h"
#include "../../node/imp/arrayNodes/baseOperation/int/intArrayModNode.h"
#include "../../node/imp/arrayNodes/baseOperation/int/intArrayMulNode.h"
#include "../../node/imp/arrayNodes/baseOperation/int/intArraySubNode.h"
#include "../../node/imp/arrayNodes/baseOperation/uint/uIntArrayAddNode.h"
#include "../../node/imp/arrayNodes/baseOperation/uint/uIntArrayDivNode.h"
#include "../../node/imp/arrayNodes/baseOperation/uint/uIntArrayModNode.h"
#include "../../node/imp/arrayNodes/baseOperation/uint/uIntArrayMulNode.h"
#include "../../node/imp/arrayNodes/baseOperation/uint/uIntArraySubNode.h"
#include "../../node/imp/beginNodes/startNode.h"
#include "../../node/imp/cacheNode/combinationArray/conbinationCharArrayNode.h"
#include "../../node/imp/cacheNode/combinationArray/conbinationColorArrayNode.h"
#include "../../node/imp/cacheNode/combinationArray/conbinationFloatArrayNode.h"
#include "../../node/imp/cacheNode/combinationArray/conbinationImageArrayNode.h"
#include "../../node/imp/cacheNode/combinationArray/conbinationIntArrayNode.h"
#include "../../node/imp/cacheNode/combinationArray/conbinationStringArrayNode.h"
#include "../../node/imp/cacheNode/combinationArray/conbinationUIntArrayNode.h"
#include "../../node/imp/endNodes/resultNode.h"
#include "../../node/imp/generateNodes/binGenerateNode.h"
#include "../../node/imp/generateNodes/charGenerateNode.h"
#include "../../node/imp/generateNodes/colorGenerateNode.h"
#include "../../node/imp/generateNodes/floatGenerateNode.h"
#include "../../node/imp/generateNodes/imageGenerateNode.h"
#include "../../node/imp/generateNodes/intGenerateNode.h"
#include "../../node/imp/generateNodes/stringGenerateNode.h"
#include "../../node/imp/generateNodes/uIntGenerateNode.h"
#include "../../node/imp/jumpNodes/gotoNode.h"
#include "../../node/imp/logicNodes/ifNode.h"
#include "../../node/imp/pointNodes/makeNode.h"
#include "../../node/imp/unityNode/baseOperation/float/floatAddNode.h"
#include "../../node/imp/unityNode/baseOperation/float/floatDivNode.h"
#include "../../node/imp/unityNode/baseOperation/float/floatModNode.h"
#include "../../node/imp/unityNode/baseOperation/float/floatMulNode.h"
#include "../../node/imp/unityNode/baseOperation/float/floatSubNode.h"
#include "../../node/imp/unityNode/baseOperation/int/intAddNode.h"
#include "../../node/imp/unityNode/baseOperation/int/intDivNode.h"
#include "../../node/imp/unityNode/baseOperation/int/intModNode.h"
#include "../../node/imp/unityNode/baseOperation/int/intMulNode.h"
#include "../../node/imp/unityNode/baseOperation/int/intSubNode.h"
#include "../../node/imp/unityNode/baseOperation/uint/uIntAddNode.h"
#include "../../node/imp/unityNode/baseOperation/uint/uIntDivNode.h"
#include "../../node/imp/unityNode/baseOperation/uint/uIntModNode.h"
#include "../../node/imp/unityNode/baseOperation/uint/uIntMulNode.h"
#include "../../node/imp/unityNode/baseOperation/uint/uIntSubNode.h"
#include "../../node/imp/processNodes/conver/toBinNode.h"
#include "../../node/imp/processNodes/conver/toCharNode.h"
#include "../../node/imp/processNodes/conver/toColorNode.h"
#include "../../node/imp/processNodes/conver/toFloatNode.h"
#include "../../node/imp/processNodes/conver/toImageNode.h"
#include "../../node/imp/processNodes/conver/toIntNode.h"
#include "../../node/imp/processNodes/conver/toStringNode.h"
#include "../../node/imp/processNodes/conver/toUIntNode.h"
#include "../../node/imp/processNodes/debug/debugInfoNode.h"
#include "../../node/imp/processNodes/file/readFileBinDataNode.h"
#include "../../node/imp/processNodes/file/readFileImageNode.h"
#include "../../node/imp/processNodes/file/readFileTextNode.h"
#include "../../node/imp/processNodes/file/writeFileBinDataNode.h"
#include "../../node/imp/processNodes/file/writeFileImageNode.h"
#include "../../node/imp/processNodes/file/writeFileTextNode.h"

#define emaplace_back_node( _Type) appendNodeGenerateUnity( _Type::getStaticNodeTypeName( ), [](const QString& node_name) { return new _Type( node_name ); }  )
bool BaseNodeStack::init( ) {
	if( NodeStack::init( ) == false )  // 释放主菜单
		return false;
	QString name = tr( "基础节点" );
	setObjectName( name );
	// 开始
	emaplace_back_node( StartNode );
	// 结束返回
	emaplace_back_node( ResultNode );
	// 数组运算
	emaplace_back_node( IntArrayAddNode );
	emaplace_back_node( IntArraySubNode );
	emaplace_back_node( IntArrayDivNode );
	emaplace_back_node( IntArrayMulNode );
	emaplace_back_node( IntArrayModNode );

	emaplace_back_node( UIntArrayAddNode );
	emaplace_back_node( UIntArraySubNode );
	emaplace_back_node( UIntArrayDivNode );
	emaplace_back_node( UIntArrayMulNode );
	emaplace_back_node( UIntArrayModNode );

	emaplace_back_node( FloatArrayAddNode );
	emaplace_back_node( FloatArraySubNode );
	emaplace_back_node( FloatArrayDivNode );
	emaplace_back_node( FloatArrayMulNode );
	emaplace_back_node( FloatArrayModNode );
	// 缓存
	emaplace_back_node( ConbinationCharArrayNode );
	emaplace_back_node( ConbinationStringArrayNode );
	emaplace_back_node( ConbinationColorArrayNode );
	emaplace_back_node( ConbinationImageArrayNode );
	emaplace_back_node( ConbinationIntArrayNode );
	emaplace_back_node( ConbinationUIntArrayNode );
	emaplace_back_node( ConbinationFloatArrayNode );
	// 生成
	emaplace_back_node( BinGenerateNode );
	emaplace_back_node( UIntGenerateNode );
	emaplace_back_node( IntGenerateNode );
	emaplace_back_node( FloatGenerateNode );
	emaplace_back_node( CharGenerateNode );
	emaplace_back_node( StringGenerateNode );
	emaplace_back_node( ColorGenerateNode );
	emaplace_back_node( ImageGenerateNode );
	// 跳转
	emaplace_back_node( GotoNode );
	// 逻辑
	emaplace_back_node( IfNode );
	// 标记
	emaplace_back_node( MakeNode );
	// 基础四则运算
	emaplace_back_node( IntAddNode );
	emaplace_back_node( IntSubNode );
	emaplace_back_node( IntDivNode );
	emaplace_back_node( IntMulNode );
	emaplace_back_node( IntModNode );

	emaplace_back_node( UIntAddNode );
	emaplace_back_node( UIntSubNode );
	emaplace_back_node( UIntDivNode );
	emaplace_back_node( UIntMulNode );
	emaplace_back_node( UIntModNode );

	emaplace_back_node( FloatAddNode );
	emaplace_back_node( FloatSubNode );
	emaplace_back_node( FloatDivNode );
	emaplace_back_node( FloatMulNode );
	emaplace_back_node( FloatModNode );
	// 文件
	emaplace_back_node( WriteFileTextNode );
	emaplace_back_node( WriteFileBinDataNode );
	emaplace_back_node( WriteFileImageNode );
	emaplace_back_node( ReadFileTextNode );
	emaplace_back_node( ReadFileBinDataNode );
	emaplace_back_node( ReadFileImageNode );
	// 转换
	emaplace_back_node( ToCharNode );
	emaplace_back_node( ToStringNode );
	emaplace_back_node( ToBinNode );
	emaplace_back_node( ToIntNode );
	emaplace_back_node( ToUIntNode );
	emaplace_back_node( ToFloatNode );
	emaplace_back_node( ToColorNode );
	emaplace_back_node( ToImageNode );
	// 调试
	emaplace_back_node( DebugInfoNode );
	return true;
}

BaseNodeStack::BaseNodeStack( QObject *parent ) : NodeStack( parent ) {

}
