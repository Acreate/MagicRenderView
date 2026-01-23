#include "numberNodeStack.h"

#include <director/printerDirector.h>
#include <QMenu>

#include "numberNode/addObjToArray/bin/binAddToArrayNode.h"
#include "numberNode/addObjToArray/bool/boolAddToArrayNode.h"
#include "numberNode/addObjToArray/float/floatAddToArrayNode.h"
#include "numberNode/addObjToArray/int/intAddToArrayNode.h"
#include "numberNode/addObjToArray/uint/uIntAddToArrayNode.h"
#include "numberNode/conver/bin/toBinNode.h"
#include "numberNode/conver/bool/toBoolNode.h"
#include "numberNode/conver/float/toFloatNode.h"
#include "numberNode/conver/int/toIntNode.h"
#include "numberNode/conver/uint/toUIntNode.h"
#include "numberNode/create/bin/binCreateArrayNode.h"
#include "numberNode/create/bin/binCreateUnityNode.h"
#include "numberNode/create/bool/boolCreateArrayNode.h"
#include "numberNode/create/bool/boolCreateUnityNode.h"
#include "numberNode/create/float/floatCreateArrayNode.h"
#include "numberNode/create/float/floatCreateUnityNode.h"
#include "numberNode/create/int/intCreateArrayNode.h"
#include "numberNode/create/int/intCreateUnityNode.h"
#include "numberNode/create/uint/uIntCreateArrayNode.h"
#include "numberNode/create/uint/uIntCreateUnityNode.h"
#include "numberNode/operationNode/bin/binAddNode.h"
#include "numberNode/operationNode/bin/binArrayAddNode.h"
#include "numberNode/operationNode/bin/binArrayDivNode.h"
#include "numberNode/operationNode/bin/binArrayModNode.h"
#include "numberNode/operationNode/bin/binArrayMulNode.h"
#include "numberNode/operationNode/bin/binArraySelfAddNode.h"
#include "numberNode/operationNode/bin/binArraySelfMulNode.h"
#include "numberNode/operationNode/bin/binArraySubNode.h"
#include "numberNode/operationNode/bin/binDivNode.h"
#include "numberNode/operationNode/bin/binModNode.h"
#include "numberNode/operationNode/bin/binMulNode.h"
#include "numberNode/operationNode/bin/binSubNode.h"
#include "numberNode/operationNode/float/floatAddNode.h"
#include "numberNode/operationNode/float/floatArrayAddNode.h"
#include "numberNode/operationNode/float/floatArrayDivNode.h"
#include "numberNode/operationNode/float/floatArrayModNode.h"
#include "numberNode/operationNode/float/floatArrayMulNode.h"
#include "numberNode/operationNode/float/floatArraySelfAddNode.h"
#include "numberNode/operationNode/float/floatArraySelfMulNode.h"
#include "numberNode/operationNode/float/floatArraySubNode.h"
#include "numberNode/operationNode/float/floatDivNode.h"
#include "numberNode/operationNode/float/floatModNode.h"
#include "numberNode/operationNode/float/floatMulNode.h"
#include "numberNode/operationNode/float/floatSubNode.h"
#include "numberNode/operationNode/int/intAddNode.h"
#include "numberNode/operationNode/int/intArrayAddNode.h"
#include "numberNode/operationNode/int/intArrayDivNode.h"
#include "numberNode/operationNode/int/intArrayModNode.h"
#include "numberNode/operationNode/int/intArrayMulNode.h"
#include "numberNode/operationNode/int/intArraySelfAddNode.h"
#include "numberNode/operationNode/int/intArraySelfMulNode.h"
#include "numberNode/operationNode/int/intArraySubNode.h"
#include "numberNode/operationNode/int/intDivNode.h"
#include "numberNode/operationNode/int/intModNode.h"
#include "numberNode/operationNode/int/intMulNode.h"
#include "numberNode/operationNode/int/intSubNode.h"
#include "numberNode/operationNode/uInt/uIntAddNode.h"
#include "numberNode/operationNode/uInt/uIntArrayAddNode.h"
#include "numberNode/operationNode/uInt/uIntArrayDivNode.h"
#include "numberNode/operationNode/uInt/uIntArrayModNode.h"
#include "numberNode/operationNode/uInt/uIntArrayMulNode.h"
#include "numberNode/operationNode/uInt/uIntArraySelfAddNode.h"
#include "numberNode/operationNode/uInt/uIntArraySelfMulNode.h"
#include "numberNode/operationNode/uInt/uIntArraySubNode.h"
#include "numberNode/operationNode/uInt/uIntDivNode.h"
#include "numberNode/operationNode/uInt/uIntModNode.h"
#include "numberNode/operationNode/uInt/uIntMulNode.h"
#include "numberNode/operationNode/uInt/uIntSubNode.h"

bool NumberNodeStack::init( ) {
	if( NodeStack::init( ) == false )  // 释放主菜单
		return false;
	QString name = tr( "数值节点" );
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

NumberNodeStack::NumberNodeStack( QObject *parent ) : NodeStack( parent ) {

}
