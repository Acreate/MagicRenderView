#include "imageNodeStack.h"

#include "imageNode/operationNode/colorAddNode.h"
#include "imageNode/operationNode/colorArrayAddNode.h"
#include "imageNode/operationNode/colorArrayDivNode.h"
#include "imageNode/operationNode/colorArrayModNode.h"
#include "imageNode/operationNode/colorArrayMulNode.h"
#include "imageNode/operationNode/colorArraySelfAddNode.h"
#include "imageNode/operationNode/colorArraySelfMulNode.h"
#include "imageNode/operationNode/colorArraySubNode.h"
#include "imageNode/operationNode/colorDivNode.h"
#include "imageNode/operationNode/colorModNode.h"
#include "imageNode/operationNode/colorMulNode.h"
#include "imageNode/operationNode/colorSubNode.h"
#include "imageNode/operationNode/imageAddNode.h"
#include "imageNode/operationNode/imageArrayAddNode.h"
#include "imageNode/operationNode/imageArrayDivNode.h"
#include "imageNode/operationNode/imageArrayModNode.h"
#include "imageNode/operationNode/imageArrayMulNode.h"
#include "imageNode/operationNode/imageArraySelfAddNode.h"
#include "imageNode/operationNode/imageArraySelfMulNode.h"
#include "imageNode/operationNode/imageArraySubNode.h"
#include "imageNode/operationNode/imageDivNode.h"
#include "imageNode/operationNode/imageModNode.h"
#include "imageNode/operationNode/imageMulNode.h"
#include "imageNode/operationNode/imageSubNode.h"

bool ImageNodeStack::init( ) {
	if( NodeStack::init( ) == false )  // 释放主菜单
		return false;
	QString name = tr( "图像节点" );
	setObjectName( name );

	Def_EmaplaceBackNode( ColorAddNode );
	Def_EmaplaceBackNode( ColorSubNode );
	Def_EmaplaceBackNode( ColorDivNode );
	Def_EmaplaceBackNode( ColorMulNode );
	Def_EmaplaceBackNode( ColorModNode );

	Def_EmaplaceBackNode( ImageAddNode );
	Def_EmaplaceBackNode( ImageSubNode );
	Def_EmaplaceBackNode( ImageDivNode );
	Def_EmaplaceBackNode( ImageMulNode );
	Def_EmaplaceBackNode( ImageModNode );

	Def_EmaplaceBackNode( ColorArrayAddNode );
	Def_EmaplaceBackNode( ColorArraySubNode );
	Def_EmaplaceBackNode( ColorArrayDivNode );
	Def_EmaplaceBackNode( ColorArrayMulNode );
	Def_EmaplaceBackNode( ColorArrayModNode );

	Def_EmaplaceBackNode( ImageArrayAddNode );
	Def_EmaplaceBackNode( ImageArraySubNode );
	Def_EmaplaceBackNode( ImageArrayDivNode );
	Def_EmaplaceBackNode( ImageArrayMulNode );
	Def_EmaplaceBackNode( ImageArrayModNode );

	Def_EmaplaceBackNode( ColorArraySelfAddNode );
	Def_EmaplaceBackNode( ColorArraySelfMulNode );

	Def_EmaplaceBackNode( ImageArraySelfAddNode );
	Def_EmaplaceBackNode( ImageArraySelfMulNode );
	return true;
}

ImageNodeStack::ImageNodeStack( QObject *parent ) : NodeStack( parent ) {

}
