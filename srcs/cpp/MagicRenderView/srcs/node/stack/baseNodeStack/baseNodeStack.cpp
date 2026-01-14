#include "baseNodeStack.h"

#include <director/printerDirector.h>
#include <node/node/imp/jumpNodes/gotoNode.h>
#include <node/node/imp/logicNodes/ifNode.h>
#include <node/node/imp/pointNodes/makeNode.h>
#include <node/node/imp/processNodes/addObjToArray/charAddToArrayNode.h>
#include <node/node/imp/processNodes/addObjToArray/colorAddToArrayNode.h>
#include <node/node/imp/processNodes/addObjToArray/floatAddToArrayNode.h>
#include <node/node/imp/processNodes/addObjToArray/imageAddToArrayNode.h>
#include <node/node/imp/processNodes/addObjToArray/intAddToArrayNode.h>
#include <node/node/imp/processNodes/addObjToArray/stringAddToArrayNode.h>
#include <node/node/imp/processNodes/addObjToArray/uIntAddToArrayNode.h>
#include <node/node/imp/processNodes/app/appInfoNode.h>
#include <node/node/imp/processNodes/baseOperation/array/color/colorArrayAddNode.h>
#include <node/node/imp/processNodes/baseOperation/array/color/colorArrayDivNode.h>
#include <node/node/imp/processNodes/baseOperation/array/color/colorArrayModNode.h>
#include <node/node/imp/processNodes/baseOperation/array/color/colorArrayMulNode.h>
#include <node/node/imp/processNodes/baseOperation/array/color/colorArraySubNode.h>
#include <node/node/imp/processNodes/baseOperation/array/float/floatArrayAddNode.h>
#include <node/node/imp/processNodes/baseOperation/array/float/floatArrayDivNode.h>
#include <node/node/imp/processNodes/baseOperation/array/float/floatArrayModNode.h>
#include <node/node/imp/processNodes/baseOperation/array/float/floatArrayMulNode.h>
#include <node/node/imp/processNodes/baseOperation/array/float/floatArraySubNode.h>
#include <node/node/imp/processNodes/baseOperation/array/image/imageArrayAddNode.h>
#include <node/node/imp/processNodes/baseOperation/array/image/imageArrayDivNode.h>
#include <node/node/imp/processNodes/baseOperation/array/image/imageArrayModNode.h>
#include <node/node/imp/processNodes/baseOperation/array/image/imageArrayMulNode.h>
#include <node/node/imp/processNodes/baseOperation/array/image/imageArraySubNode.h>
#include <node/node/imp/processNodes/baseOperation/array/int/intArrayAddNode.h>
#include <node/node/imp/processNodes/baseOperation/array/int/intArrayDivNode.h>
#include <node/node/imp/processNodes/baseOperation/array/int/intArrayModNode.h>
#include <node/node/imp/processNodes/baseOperation/array/int/intArrayMulNode.h>
#include <node/node/imp/processNodes/baseOperation/array/int/intArraySubNode.h>
#include <node/node/imp/processNodes/baseOperation/self/color/colorArraySelfAddNode.h>
#include <node/node/imp/processNodes/baseOperation/self/color/colorArraySelfMulNode.h>
#include <node/node/imp/processNodes/baseOperation/self/float/floatArraySelfAddNode.h>
#include <node/node/imp/processNodes/baseOperation/self/float/floatArraySelfMulNode.h>
#include <node/node/imp/processNodes/baseOperation/self/image/imageArraySelfAddNode.h>
#include <node/node/imp/processNodes/baseOperation/self/image/imageArraySelfMulNode.h>
#include <node/node/imp/processNodes/baseOperation/self/int/intArraySelfAddNode.h>
#include <node/node/imp/processNodes/baseOperation/self/int/intArraySelfMulNode.h>
#include <node/node/imp/processNodes/baseOperation/self/uint/uIntArraySelfAddNode.h>
#include <node/node/imp/processNodes/baseOperation/self/uint/uIntArraySelfMulNode.h>
#include <node/node/imp/processNodes/baseOperation/array/uint/uIntArrayAddNode.h>
#include <node/node/imp/processNodes/baseOperation/array/uint/uIntArrayDivNode.h>
#include <node/node/imp/processNodes/baseOperation/array/uint/uIntArrayModNode.h>
#include <node/node/imp/processNodes/baseOperation/array/uint/uIntArrayMulNode.h>
#include <node/node/imp/processNodes/baseOperation/array/uint/uIntArraySubNode.h>
#include <node/node/imp/processNodes/baseOperation/unity/color/colorAddNode.h>
#include <node/node/imp/processNodes/baseOperation/unity/color/colorDivNode.h>
#include <node/node/imp/processNodes/baseOperation/unity/color/colorModNode.h>
#include <node/node/imp/processNodes/baseOperation/unity/color/colorMulNode.h>
#include <node/node/imp/processNodes/baseOperation/unity/color/colorSubNode.h>
#include <node/node/imp/processNodes/baseOperation/unity/float/floatAddNode.h>
#include <node/node/imp/processNodes/baseOperation/unity/float/floatDivNode.h>
#include <node/node/imp/processNodes/baseOperation/unity/float/floatModNode.h>
#include <node/node/imp/processNodes/baseOperation/unity/float/floatMulNode.h>
#include <node/node/imp/processNodes/baseOperation/unity/float/floatSubNode.h>
#include <node/node/imp/processNodes/baseOperation/unity/image/imageAddNode.h>
#include <node/node/imp/processNodes/baseOperation/unity/image/imageDivNode.h>
#include <node/node/imp/processNodes/baseOperation/unity/image/imageModNode.h>
#include <node/node/imp/processNodes/baseOperation/unity/image/imageMulNode.h>
#include <node/node/imp/processNodes/baseOperation/unity/image/imageSubNode.h>
#include <node/node/imp/processNodes/baseOperation/unity/int/intAddNode.h>
#include <node/node/imp/processNodes/baseOperation/unity/int/intDivNode.h>
#include <node/node/imp/processNodes/baseOperation/unity/int/intModNode.h>
#include <node/node/imp/processNodes/baseOperation/unity/int/intMulNode.h>
#include <node/node/imp/processNodes/baseOperation/unity/int/intSubNode.h>
#include <node/node/imp/processNodes/baseOperation/unity/uint/uIntAddNode.h>
#include <node/node/imp/processNodes/baseOperation/unity/uint/uIntDivNode.h>
#include <node/node/imp/processNodes/baseOperation/unity/uint/uIntModNode.h>
#include <node/node/imp/processNodes/baseOperation/unity/uint/uIntMulNode.h>
#include <node/node/imp/processNodes/baseOperation/unity/uint/uIntSubNode.h>
#include <node/node/imp/processNodes/conver/toBinNode.h>
#include <node/node/imp/processNodes/conver/toCharNode.h>
#include <node/node/imp/processNodes/conver/toColorNode.h>
#include <node/node/imp/processNodes/conver/toDateTimeNode.h>
#include <node/node/imp/processNodes/conver/toFloatNode.h>
#include <node/node/imp/processNodes/conver/toImageNode.h>
#include <node/node/imp/processNodes/conver/toIntNode.h>
#include <node/node/imp/processNodes/conver/toStringNode.h>
#include <node/node/imp/processNodes/conver/toUIntNode.h>
#include <node/node/imp/processNodes/create/array/charCreateArrayNode.h>
#include <node/node/imp/processNodes/create/array/colorCreateArrayNode.h>
#include <node/node/imp/processNodes/create/array/floatCreateArrayNode.h>
#include <node/node/imp/processNodes/create/array/imageCreateArrayNode.h>
#include <node/node/imp/processNodes/create/array/intCreateArrayNode.h>
#include <node/node/imp/processNodes/create/array/stringCreateArrayNode.h>
#include <node/node/imp/processNodes/create/array/uIntCreateArrayNode.h>
#include <node/node/imp/processNodes/create/unity/charCreateUnityNode.h>
#include <node/node/imp/processNodes/create/unity/colorCreateUnityNode.h>
#include <node/node/imp/processNodes/create/unity/floatCreateUnityNode.h>
#include <node/node/imp/processNodes/create/unity/imageCreateUnityNode.h>
#include <node/node/imp/processNodes/create/unity/intCreateUnityNode.h>
#include <node/node/imp/processNodes/create/unity/stringCreateUnityNode.h>
#include <node/node/imp/processNodes/create/unity/uIntCreateUnityNode.h>
#include <node/node/imp/processNodes/dateTime/splitDataTimeNode.h>
#include <node/node/imp/processNodes/debug/debugInfoNode.h>
#include <node/node/imp/processNodes/debug/previewImageNode.h>
#include <node/node/imp/processNodes/image/imageChannelNode.h>
#include <node/node/imp/processNodes/image/imageInfoNode.h>
#include <node/node/imp/processNodes/path/fileInfoNode.h>
#include <node/node/imp/processNodes/path/systemPathInfo.h>
#include <node/node/imp/processNodes/read/readFileBinDataNode.h>
#include <node/node/imp/processNodes/read/readFileImageNode.h>
#include <node/node/imp/processNodes/read/readFileTextNode.h>
#include <node/node/imp/processNodes/write/writeFileBinDataNode.h>
#include <node/node/imp/processNodes/write/writeFileImageNode.h>
#include <node/node/imp/processNodes/write/writeFileTextNode.h>
#include <QMenu>

#define emaplace_back_node( _Type) appendNodeGenerateUnity( _Type::getStaticNodeTypeName( ), [](const QString& node_name) { return new _Type( node_name ); }  )
bool BaseNodeStack::init( ) {
	if( NodeStack::init( ) == false )  // 释放主菜单
		return false;
	QString name = tr( "基础节点" );
	setObjectName( name );

	// 跳转
	emaplace_back_node( GotoNode );
	// 逻辑
	emaplace_back_node( IfNode );
	// 标记
	emaplace_back_node( MakeNode );
	// 单元基础四则运算
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

	emaplace_back_node( ColorAddNode );
	emaplace_back_node( ColorSubNode );
	emaplace_back_node( ColorDivNode );
	emaplace_back_node( ColorMulNode );
	emaplace_back_node( ColorModNode );

	emaplace_back_node( ImageAddNode );
	emaplace_back_node( ImageSubNode );
	emaplace_back_node( ImageDivNode );
	emaplace_back_node( ImageMulNode );
	emaplace_back_node( ImageModNode );
	// 序列基础四则运算
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

	emaplace_back_node( ColorArrayAddNode );
	emaplace_back_node( ColorArraySubNode );
	emaplace_back_node( ColorArrayDivNode );
	emaplace_back_node( ColorArrayMulNode );
	emaplace_back_node( ColorArrayModNode );

	emaplace_back_node( ImageArrayAddNode );
	emaplace_back_node( ImageArraySubNode );
	emaplace_back_node( ImageArrayDivNode );
	emaplace_back_node( ImageArrayMulNode );
	emaplace_back_node( ImageArrayModNode );
	// 序列自运算
	emaplace_back_node( IntArraySelfAddNode );
	emaplace_back_node( IntArraySelfMulNode );

	emaplace_back_node( FloatArraySelfAddNode );
	emaplace_back_node( FloatArraySelfMulNode );

	emaplace_back_node( UIntArraySelfAddNode );
	emaplace_back_node( UIntArraySelfMulNode );

	emaplace_back_node( ColorArraySelfAddNode );
	emaplace_back_node( ColorArraySelfMulNode );

	emaplace_back_node( ImageArraySelfAddNode );
	emaplace_back_node( ImageArraySelfMulNode );
	// 组成序列
	emaplace_back_node( CharAddToArrayNode );
	emaplace_back_node( ColorAddToArrayNode );
	emaplace_back_node( FloatAddToArrayNode );
	emaplace_back_node( ImageAddToArrayNode );
	emaplace_back_node( IntAddToArrayNode );
	emaplace_back_node( StringAddToArrayNode );
	emaplace_back_node( UIntAddToArrayNode );
	// 生成序列
	emaplace_back_node( CharCreateArrayNode );
	emaplace_back_node( ColorCreateArrayNode );
	emaplace_back_node( FloatCreateArrayNode );
	emaplace_back_node( ImageCreateArrayNode );
	emaplace_back_node( IntCreateArrayNode );
	emaplace_back_node( StringCreateArrayNode );
	emaplace_back_node( UIntCreateArrayNode );
	// 生成单元
	emaplace_back_node( CharCreateUnityNode );
	emaplace_back_node( ColorCreateUnityNode );
	emaplace_back_node( FloatCreateUnityNode );
	emaplace_back_node( ImageCreateUnityNode );
	emaplace_back_node( IntCreateUnityNode );
	emaplace_back_node( StringCreateUnityNode );
	emaplace_back_node( UIntCreateUnityNode );

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
	emaplace_back_node( ToDateTimeNode );
	// 调试
	emaplace_back_node( DebugInfoNode );
	// 预览
	emaplace_back_node( PreviewImageNode );
	// 图像
	emaplace_back_node( ImageInfoNode );
	emaplace_back_node( ImageChannelNode );

	// 路径
	emaplace_back_node( FileInfoNode );
	emaplace_back_node( SystemPathInfo );

	// 软件
	emaplace_back_node( AppInfoNode );

	// 时间
	emaplace_back_node( SplitDataTimeNode );
	return true;
}

BaseNodeStack::BaseNodeStack( QObject *parent ) : NodeStack( parent ) {

}
