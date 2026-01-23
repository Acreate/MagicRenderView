#include "imageNodeStack.h"

#include "imageNode/addObjToArray/color/colorAddToArrayNode.h"
#include "imageNode/addObjToArray/iamge/imageAddToArrayNode.h"
#include "imageNode/conver/color/toColorNode.h"
#include "imageNode/conver/iamge/toImageNode.h"
#include "imageNode/create/color/colorCreateArrayNode.h"
#include "imageNode/create/color/colorCreateUnityNode.h"
#include "imageNode/create/image/imageCreateArrayNode.h"
#include "imageNode/create/image/imageCreateUnityNode.h"
#include "imageNode/operationNode/color/colorAddNode.h"
#include "imageNode/operationNode/color/colorArrayAddNode.h"
#include "imageNode/operationNode/color/colorArrayDivNode.h"
#include "imageNode/operationNode/color/colorArrayModNode.h"
#include "imageNode/operationNode/color/colorArrayMulNode.h"
#include "imageNode/operationNode/color/colorArraySelfAddNode.h"
#include "imageNode/operationNode/color/colorArraySelfMulNode.h"
#include "imageNode/operationNode/color/colorArraySubNode.h"
#include "imageNode/operationNode/color/colorDivNode.h"
#include "imageNode/operationNode/color/colorModNode.h"
#include "imageNode/operationNode/color/colorMulNode.h"
#include "imageNode/operationNode/color/colorSubNode.h"
#include "imageNode/operationNode/image/imageAddNode.h"
#include "imageNode/operationNode/image/imageArrayAddNode.h"
#include "imageNode/operationNode/image/imageArrayDivNode.h"
#include "imageNode/operationNode/image/imageArrayModNode.h"
#include "imageNode/operationNode/image/imageArrayMulNode.h"
#include "imageNode/operationNode/image/imageArraySelfAddNode.h"
#include "imageNode/operationNode/image/imageArraySelfMulNode.h"
#include "imageNode/operationNode/image/imageArraySubNode.h"
#include "imageNode/operationNode/image/imageDivNode.h"
#include "imageNode/operationNode/image/imageModNode.h"
#include "imageNode/operationNode/image/imageMulNode.h"
#include "imageNode/operationNode/image/imageSubNode.h"

bool ImageNodeStack::init( ) {
	if( NodeStack::init( ) == false )  // 释放主菜单
		return false;
	QString name = tr( "图像节点" );
	setObjectName( name );

	Def_EmaplaceBackNode( ColorCreateUnityNode );
	Def_EmaplaceBackNode( ColorCreateArrayNode );
	Def_EmaplaceBackNode( ImageCreateArrayNode );
	Def_EmaplaceBackNode( ColorAddNode );
	Def_EmaplaceBackNode( ColorSubNode );
	Def_EmaplaceBackNode( ColorDivNode );
	Def_EmaplaceBackNode( ColorMulNode );
	Def_EmaplaceBackNode( ColorModNode );
	Def_EmaplaceBackNode( ColorArrayAddNode );
	Def_EmaplaceBackNode( ColorArraySubNode );
	Def_EmaplaceBackNode( ColorArrayDivNode );
	Def_EmaplaceBackNode( ColorArrayMulNode );
	Def_EmaplaceBackNode( ColorArrayModNode );
	Def_EmaplaceBackNode( ColorArraySelfAddNode );
	Def_EmaplaceBackNode( ColorArraySelfMulNode );
	Def_EmaplaceBackNode( ToColorNode );
	Def_EmaplaceBackNode( ColorAddToArrayNode );

	Def_EmaplaceBackNode( ImageCreateUnityNode );
	Def_EmaplaceBackNode( ImageCreateArrayNode );
	Def_EmaplaceBackNode( ImageAddNode );
	Def_EmaplaceBackNode( ImageSubNode );
	Def_EmaplaceBackNode( ImageDivNode );
	Def_EmaplaceBackNode( ImageMulNode );
	Def_EmaplaceBackNode( ImageModNode );
	Def_EmaplaceBackNode( ImageArrayAddNode );
	Def_EmaplaceBackNode( ImageArraySubNode );
	Def_EmaplaceBackNode( ImageArrayDivNode );
	Def_EmaplaceBackNode( ImageArrayMulNode );
	Def_EmaplaceBackNode( ImageArrayModNode );
	Def_EmaplaceBackNode( ImageArraySelfAddNode );
	Def_EmaplaceBackNode( ImageArraySelfMulNode );
	Def_EmaplaceBackNode( ToImageNode );
	Def_EmaplaceBackNode( ImageAddToArrayNode );
	return true;
}

ImageNodeStack::ImageNodeStack( QObject *parent ) : NodeStack( parent ) {

}
