#include "baseNodeStack.h"

#include <director/printerDirector.h>
#include <QMenu>

#include "baseNode/addObjToArray/bin/binAddToArrayNode.h"
#include "baseNode/addObjToArray/bool/boolAddToArrayNode.h"
#include "baseNode/addObjToArray/float/floatAddToArrayNode.h"
#include "baseNode/addObjToArray/int/intAddToArrayNode.h"
#include "baseNode/addObjToArray/uint/uIntAddToArrayNode.h"
#include "baseNode/conver/bin/toBinNode.h"
#include "baseNode/conver/bool/toBoolNode.h"
#include "baseNode/conver/float/toFloatNode.h"
#include "baseNode/conver/int/toIntNode.h"
#include "baseNode/conver/uint/toUIntNode.h"
#include "baseNode/create/bin/binCreateArrayNode.h"
#include "baseNode/create/bin/binCreateUnityNode.h"
#include "baseNode/create/bool/boolCreateArrayNode.h"
#include "baseNode/create/bool/boolCreateUnityNode.h"
#include "baseNode/create/float/floatCreateArrayNode.h"
#include "baseNode/create/float/floatCreateUnityNode.h"
#include "baseNode/create/int/intCreateArrayNode.h"
#include "baseNode/create/int/intCreateUnityNode.h"
#include "baseNode/create/uint/uIntCreateArrayNode.h"
#include "baseNode/create/uint/uIntCreateUnityNode.h"
#include "baseNode/operationNode/bin/binAddNode.h"
#include "baseNode/operationNode/bin/binArrayAddNode.h"
#include "baseNode/operationNode/bin/binArrayDivNode.h"
#include "baseNode/operationNode/bin/binArrayModNode.h"
#include "baseNode/operationNode/bin/binArrayMulNode.h"
#include "baseNode/operationNode/bin/binArraySelfAddNode.h"
#include "baseNode/operationNode/bin/binArraySelfMulNode.h"
#include "baseNode/operationNode/bin/binArraySubNode.h"
#include "baseNode/operationNode/bin/binDivNode.h"
#include "baseNode/operationNode/bin/binModNode.h"
#include "baseNode/operationNode/bin/binMulNode.h"
#include "baseNode/operationNode/bin/binSubNode.h"
#include "baseNode/operationNode/float/floatAddNode.h"
#include "baseNode/operationNode/float/floatArrayAddNode.h"
#include "baseNode/operationNode/float/floatArrayDivNode.h"
#include "baseNode/operationNode/float/floatArrayModNode.h"
#include "baseNode/operationNode/float/floatArrayMulNode.h"
#include "baseNode/operationNode/float/floatArraySelfAddNode.h"
#include "baseNode/operationNode/float/floatArraySelfMulNode.h"
#include "baseNode/operationNode/float/floatArraySubNode.h"
#include "baseNode/operationNode/float/floatDivNode.h"
#include "baseNode/operationNode/float/floatModNode.h"
#include "baseNode/operationNode/float/floatMulNode.h"
#include "baseNode/operationNode/float/floatSubNode.h"
#include "baseNode/operationNode/int/intAddNode.h"
#include "baseNode/operationNode/int/intArrayAddNode.h"
#include "baseNode/operationNode/int/intArrayDivNode.h"
#include "baseNode/operationNode/int/intArrayModNode.h"
#include "baseNode/operationNode/int/intArrayMulNode.h"
#include "baseNode/operationNode/int/intArraySelfAddNode.h"
#include "baseNode/operationNode/int/intArraySelfMulNode.h"
#include "baseNode/operationNode/int/intArraySubNode.h"
#include "baseNode/operationNode/int/intDivNode.h"
#include "baseNode/operationNode/int/intModNode.h"
#include "baseNode/operationNode/int/intMulNode.h"
#include "baseNode/operationNode/int/intSubNode.h"
#include "baseNode/operationNode/uInt/uIntAddNode.h"
#include "baseNode/operationNode/uInt/uIntArrayAddNode.h"
#include "baseNode/operationNode/uInt/uIntArrayDivNode.h"
#include "baseNode/operationNode/uInt/uIntArrayModNode.h"
#include "baseNode/operationNode/uInt/uIntArrayMulNode.h"
#include "baseNode/operationNode/uInt/uIntArraySelfAddNode.h"
#include "baseNode/operationNode/uInt/uIntArraySelfMulNode.h"
#include "baseNode/operationNode/uInt/uIntArraySubNode.h"
#include "baseNode/operationNode/uInt/uIntDivNode.h"
#include "baseNode/operationNode/uInt/uIntModNode.h"
#include "baseNode/operationNode/uInt/uIntMulNode.h"
#include "baseNode/operationNode/uInt/uIntSubNode.h"

bool BaseNodeStack::init( ) {
	if( NodeStack::init( ) == false )  // 释放主菜单
		return false;
	QString name = tr( "基础节点" );
	setObjectName( name );

	Def_EmaplaceBackNode( BoolAddToArrayNode );
	Def_EmaplaceBackNode( BoolCreateUnityNode );
	Def_EmaplaceBackNode( BoolCreateArrayNode );
	Def_EmaplaceBackNode( ToBoolNode );

	Def_EmaplaceBackNode( FloatAddToArrayNode );
	Def_EmaplaceBackNode( FloatCreateUnityNode );
	Def_EmaplaceBackNode( FloatCreateArrayNode );
	Def_EmaplaceBackNode( FloatAddNode );
	Def_EmaplaceBackNode( FloatSubNode );
	Def_EmaplaceBackNode( FloatDivNode );
	Def_EmaplaceBackNode( FloatMulNode );
	Def_EmaplaceBackNode( FloatModNode );
	Def_EmaplaceBackNode( FloatArrayAddNode );
	Def_EmaplaceBackNode( FloatArraySubNode );
	Def_EmaplaceBackNode( FloatArrayDivNode );
	Def_EmaplaceBackNode( FloatArrayMulNode );
	Def_EmaplaceBackNode( FloatArrayModNode );
	Def_EmaplaceBackNode( FloatArraySelfAddNode );
	Def_EmaplaceBackNode( FloatArraySelfMulNode );
	Def_EmaplaceBackNode( ToFloatNode );

	Def_EmaplaceBackNode( IntAddToArrayNode );
	Def_EmaplaceBackNode( IntCreateUnityNode );
	Def_EmaplaceBackNode( IntCreateArrayNode );
	Def_EmaplaceBackNode( IntAddNode );
	Def_EmaplaceBackNode( IntSubNode );
	Def_EmaplaceBackNode( IntDivNode );
	Def_EmaplaceBackNode( IntMulNode );
	Def_EmaplaceBackNode( IntModNode );
	Def_EmaplaceBackNode( IntArrayAddNode );
	Def_EmaplaceBackNode( IntArraySubNode );
	Def_EmaplaceBackNode( IntArrayDivNode );
	Def_EmaplaceBackNode( IntArrayMulNode );
	Def_EmaplaceBackNode( IntArrayModNode );
	Def_EmaplaceBackNode( IntArraySelfAddNode );
	Def_EmaplaceBackNode( IntArraySelfMulNode );
	Def_EmaplaceBackNode( ToIntNode );

	Def_EmaplaceBackNode( UIntAddToArrayNode );
	Def_EmaplaceBackNode( UIntCreateUnityNode );
	Def_EmaplaceBackNode( UIntCreateArrayNode );
	Def_EmaplaceBackNode( UIntAddNode );
	Def_EmaplaceBackNode( UIntSubNode );
	Def_EmaplaceBackNode( UIntDivNode );
	Def_EmaplaceBackNode( UIntMulNode );
	Def_EmaplaceBackNode( UIntModNode );
	Def_EmaplaceBackNode( UIntArrayAddNode );
	Def_EmaplaceBackNode( UIntArraySubNode );
	Def_EmaplaceBackNode( UIntArrayDivNode );
	Def_EmaplaceBackNode( UIntArrayMulNode );
	Def_EmaplaceBackNode( UIntArrayModNode );
	Def_EmaplaceBackNode( UIntArraySelfAddNode );
	Def_EmaplaceBackNode( UIntArraySelfMulNode );
	Def_EmaplaceBackNode( ToUIntNode );

	Def_EmaplaceBackNode( BinAddToArrayNode );
	Def_EmaplaceBackNode( BinCreateUnityNode );
	Def_EmaplaceBackNode( BinCreateArrayNode );
	Def_EmaplaceBackNode( BinAddNode );
	Def_EmaplaceBackNode( BinSubNode );
	Def_EmaplaceBackNode( BinDivNode );
	Def_EmaplaceBackNode( BinMulNode );
	Def_EmaplaceBackNode( BinModNode );
	Def_EmaplaceBackNode( BinArrayAddNode );
	Def_EmaplaceBackNode( BinArraySubNode );
	Def_EmaplaceBackNode( BinArrayDivNode );
	Def_EmaplaceBackNode( BinArrayMulNode );
	Def_EmaplaceBackNode( BinArrayModNode );
	Def_EmaplaceBackNode( BinArraySelfAddNode );
	Def_EmaplaceBackNode( BinArraySelfMulNode );
	Def_EmaplaceBackNode( ToBinNode );
	return true;
}

BaseNodeStack::BaseNodeStack( QObject *parent ) : NodeStack( parent ) {

}
