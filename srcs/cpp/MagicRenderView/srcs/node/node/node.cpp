#include "node.h"

#include <app/application.h>
#include <director/varDirector.h>
#include <node/nodeInfo/nodeClickInfo.h>
#include <node/port/inputPort/inputPort.h>
#include <node/port/outputPort/outputPort.h>
#include <QLabel>
#include <QPainter>
#include <QTimer>
#include <QVBoxLayout>
#include <srack/srackInfo.h>
#include <widget/mainWidget.h>

#include "../port/inputPort/point/pointInputPort.h"

Node::~Node( ) {

	emit release_node_signal( this, Create_SrackInfo( ) );
	releaseAllRefNode( );
	size_t count = inputPortVector.size( );
	auto inputArrayPtr = inputPortVector.data( );
	size_t index;
	for( index = 0; index < count; ++index )
		delete inputArrayPtr[ index ];
	inputPortVector.clear( );

	count = outputPortVector.size( );
	auto outputArrayPtr = outputPortVector.data( );
	for( index = 0; index < count; ++index )
		delete outputArrayPtr[ index ];
	outputPortVector.clear( );
	if( mainLayout )
		delete mainLayout;
	if( titileWidget )
		delete titileWidget;
	if( connectWidget )
		delete connectWidget;

	if( varPtr )
		varDirector->release( varPtr );
}
Node::Node( const QString &node_name ) : nodeTitleName( node_name ), mainLayout( nullptr ) {
	hide( );
	generateCode = 0;
	varPtr = nullptr;
	nonePen.setColor( Qt::GlobalColor::black );
	callFunctionPen.setColor( QColor( 0xff7900 ) );
	createPen.setColor( QColor( 0x009cff ) );
	selectActivePen.setColor( QColor( 0xff8400 ) );
	selectOldPen.setColor( QColor( 0xd191ff ) );
	selectOutputRefPen.setColor( QColor( 0xaaffa3 ) );
	selectInputRefPen.setColor( QColor( 0x12ff11 ) );
	warningPen.setColor( QColor( 0xff7559 ) );
	errorPen.setColor( QColor( 0xff0000 ) );
	advisPen.setColor( QColor( 0xff9c65 ) );
	nodeStyle = NodeEnum::NodeStyleType::Create;
	// 标题布局
	titileWidget = new QWidget( this );
	titileWidgetLayout = new QVBoxLayout( titileWidget );
	// 标题
	titileLabel = new QLabel( titileWidget );
	titileWidgetLayout->setContentsMargins( 0, 0, 0, 0 );
	titileWidgetLayout->setSpacing( 0 );
	titileWidgetLayout->addWidget( titileLabel );
	// 输出输入面板布局
	connectWidget = new QWidget( this );
	connectWidgetLayout = new QHBoxLayout( connectWidget );
	connectWidgetLayout->setContentsMargins( 0, 0, 0, 0 );
	connectWidgetLayout->setSpacing( nodeBorderWidth * 2 );
	// 输入端布局
	inputPortWidget = new QWidget( connectWidget );
	connectWidgetLayout->addWidget( inputPortWidget, 0, Qt::AlignLeft | Qt::AlignTop );
	inputPortWidgetLayout = new QVBoxLayout( inputPortWidget );
	inputPortWidgetLayout->setContentsMargins( 0, 0, 0, 0 );
	inputPortWidgetLayout->setSpacing( 0 );
	// 输出端布局
	outputPortWidget = new QWidget( connectWidget );
	connectWidgetLayout->addWidget( outputPortWidget, 0, Qt::AlignRight | Qt::AlignTop );
	outputPortWidgetLayout = new QVBoxLayout( outputPortWidget );
	outputPortWidgetLayout->setContentsMargins( 0, 0, 0, 0 );
	outputPortWidgetLayout->setSpacing( 0 );

	// 主要布局
	auto oldLayout = layout( );
	if( oldLayout )
		delete oldLayout;
	mainLayout = new QVBoxLayout( this );
	nodeBorderWidth = 5;
	mainLayout->setContentsMargins( nodeBorderWidth, nodeBorderWidth, nodeBorderWidth, nodeBorderWidth );
	mainLayout->setSpacing( 0 );
	mainLayout->addWidget( titileWidget );
	mainLayout->addWidget( connectWidget );

}
bool Node::appendInputPort( InputPort *input_port ) {
	size_t count, index;
	InputPort **outputPortArrayPtr;
	count = inputPortVector.size( );
	if( count != 0 ) {
		outputPortArrayPtr = inputPortVector.data( );
		for( index = 0; index < count; ++index )
			if( outputPortArrayPtr[ index ] == input_port )
				return true;
	}
	if( input_port->init( this ) == false )
		return false;
	inputPortVector.emplace_back( input_port );
	input_port->setParent( this );
	connect( input_port, &InputPort::connect_input_port_signal, this, &Node::inputDelRef_Slot );
	connect( input_port, &InputPort::dis_connect_input_port_signal, this, &Node::inputDelRef_Slot );
	return true;
}
bool Node::appendOutputPort( OutputPort *output_port ) {
	size_t count, index;
	OutputPort **outputPortArrayPtr;
	count = outputPortVector.size( );
	if( count != 0 ) {
		outputPortArrayPtr = outputPortVector.data( );
		for( index = 0; index < count; ++index )
			if( outputPortArrayPtr[ index ] == output_port )
				return true;
	}
	if( output_port->init( this ) == false )
		return false;
	outputPortVector.emplace_back( output_port );
	output_port->setParent( this );
	connect( output_port, &OutputPort::connect_output_port_signal, this, &Node::outputAddRef_Slot );
	connect( output_port, &OutputPort::dis_connect_output_port_signal, this, &Node::outputDelRef_Slot );
	return true;
}
bool Node::getPointInfo( const QPoint &point, NodeClickInfo &result_node_click_info ) {
	auto geometry = titileWidget->geometry( );
	if( geometry.contains( point ) ) {
		result_node_click_info.clickType = NodeEnum::NodeClickType::Titile;
		result_node_click_info.inputPort = nullptr;
		result_node_click_info.outputPort = nullptr;
		result_node_click_info.clickNode = this;
		return true;
	}
	geometry = connectWidget->geometry( );
	if( geometry.contains( point ) ) {
		result_node_click_info.clickNode = this;
		auto mapFromParent = connectWidget->mapFromParent( point );
		geometry = inputPortWidget->geometry( );
		if( geometry.contains( mapFromParent ) ) {
			result_node_click_info.outputPort = nullptr;
			mapFromParent = inputPortWidget->mapFromParent( mapFromParent );
			size_t count = inputPortVector.size( );
			auto inputPortArrayPtr = inputPortVector.data( );
			for( size_t index = 0; index < count; ++index )
				if( inputPortArrayPtr[ index ]->geometry( ).contains( mapFromParent ) ) {
					result_node_click_info.inputPort = inputPortArrayPtr[ index ];
					result_node_click_info.clickType = NodeEnum::NodeClickType::InputPort;
					return true;
				}
			result_node_click_info.clickType = NodeEnum::NodeClickType::None;
			return true;
		}
		geometry = outputPortWidget->geometry( );
		if( geometry.contains( mapFromParent ) ) {
			mapFromParent = outputPortWidget->mapFromParent( mapFromParent );
			result_node_click_info.inputPort = nullptr;
			size_t count = outputPortVector.size( );
			auto outputPortArrayPtr = outputPortVector.data( );
			for( size_t index = 0; index < count; ++index )
				if( outputPortArrayPtr[ index ]->geometry( ).contains( mapFromParent ) ) {
					result_node_click_info.outputPort = outputPortArrayPtr[ index ];
					result_node_click_info.clickType = NodeEnum::NodeClickType::OutputPort;
					return true;
				}
			result_node_click_info.clickType = NodeEnum::NodeClickType::None;
			return true;
		}
		result_node_click_info.clickType = NodeEnum::NodeClickType::None;
		result_node_click_info.clickNode = this;
		return true;
	}

	return false;
}
bool Node::hasInputPort( const InputPort *check_input_port ) const {
	auto count = inputPortVector.size( );
	if( count == 0 )
		return false;
	size_t index;
	auto inputPortArrayPtr = inputPortVector.data( );
	for( index = 0; index < count; ++index )
		if( inputPortArrayPtr[ index ] == check_input_port )
			return true;

	return false;
}
bool Node::hasOutputPort( const OutputPort *check_output_port ) const {
	auto count = outputPortVector.size( );
	if( count == 0 )
		return false;
	size_t index;
	auto outputPortArrayPtr = outputPortVector.data( );
	for( index = 0; index < count; ++index )
		if( outputPortArrayPtr[ index ] == check_output_port )
			return true;

	return false;
}

bool Node::toUint8VectorData( std::vector< uint8_t > &result_vector_data ) {
	VarDirector varDirector;
	if( varDirector.init( ) == false )
		return false;
	uint64_t *uint64Ptr = nullptr;
	if( varDirector.create( uint64Ptr ) == false )
		return false;
	*uint64Ptr = 0;
	if( varDirector.toVector( uint64Ptr, result_vector_data ) == false )
		return false;

	return true;
}
bool Node::formUint8ArrayData( size_t &result_use_count, const uint8_t *source_array_ptr, const size_t &source_array_count ) {
	VarDirector varDirector;
	if( varDirector.init( ) == false )
		return false;
	uint64_t *uint64Ptr = nullptr;
	if( varDirector.create( uint64Ptr ) == false )
		return false;
	void *converPtr = uint64Ptr;
	if( varDirector.toVar( result_use_count, source_array_ptr, source_array_count, converPtr ) == false )
		return false;
	return true;
}
QString Node::toQString( ) const {
	return getVirtualNodeTypeName( ) + "(0x" + QString::number( ( uintmax_t ) this, 16 ).toUpper( ) + ", #" + QString::number( generateCode, 16 ).toUpper( ) + ")";
}

void Node::setNodeStyle( NodeEnum::NodeStyleType node_style ) {
	nodeStyle = node_style;
	update( );
}
InputPort * Node::getInputPort( const size_t &input_port_generate_code ) const {
	size_t count = inputPortVector.size( );
	if( count == 0 )
		return nullptr;
	auto inputPortArrayPtr = inputPortVector.data( );
	if( inputPortArrayPtr[ input_port_generate_code - 1 ]->generateCode == input_port_generate_code )
		return inputPortArrayPtr[ input_port_generate_code - 1 ];
	for( size_t index = 0; index < count; ++index )
		if( inputPortArrayPtr[ index ]->generateCode == input_port_generate_code )
			return inputPortArrayPtr[ index ];
	return nullptr;
}
OutputPort * Node::getOutputPort( const size_t &output_port_generate_code ) const {
	size_t count = outputPortVector.size( );
	if( count == 0 )
		return nullptr;
	auto outputPortArrayPtr = outputPortVector.data( );
	if( outputPortArrayPtr[ output_port_generate_code - 1 ]->generateCode == output_port_generate_code )
		return outputPortArrayPtr[ output_port_generate_code - 1 ];

	for( size_t index = 0; index < count; ++index )
		if( outputPortArrayPtr[ index ]->generateCode == output_port_generate_code )
			return outputPortArrayPtr[ index ];
	return nullptr;
}
bool Node::updatePortGenerateCodes( ) {
	size_t count = inputPortVector.size( );
	size_t index = 0;
	if( count )
		for( auto inputPortArrayPtr = inputPortVector.data( ); index < count; ++index )
			inputPortArrayPtr[ index ]->generateCode = index + 1;
	count = outputPortVector.size( );
	if( count == 0 )
		return true;
	index = 0;
	for( auto outputPortArrayPtr = outputPortVector.data( ); index < count; ++index )
		outputPortArrayPtr[ index ]->generateCode = index + 1;
	return true;
}
void Node::inputAddRef_Slot( InputPort *input_port, OutputPort *ref_output_port ) {
	if( emplaceBackRefOutputPortNode( input_port, ref_output_port ) == false )
		return;
}
void Node::inputDelRef_Slot( InputPort *input_port, OutputPort *ref_output_port ) {
	if( eraseRefOutputPortNode( input_port, ref_output_port ) == false )
		return;
}
void Node::outputAddRef_Slot( OutputPort *output_port, InputPort *ref_input_port ) {
	if( emplaceBackRefInputPortNode( output_port, ref_input_port ) == false )
		return;
}
void Node::outputDelRef_Slot( OutputPort *output_port, InputPort *ref_input_port ) {
	if( eraseRefInputPortNode( output_port, ref_input_port ) == false )
		return;
}
bool Node::emplaceBackRefInputPortNode( OutputPort *output_port, InputPort *ref_input_port ) {
	Node *refNode = ref_input_port->parentNode;
	size_t count = refInputPortNode.size( );
	if( count == 0 ) {
		refInputPortNode.emplace_back( refNode );
		emit connect_ref_input_port_node_signal( this, refNode );
		refNode->emplaceBackRefOutputPortNode( ref_input_port, output_port );
		emit connect_output_port_signal( output_port, ref_input_port );
		return true;
	}
	auto arrayPtr = refInputPortNode.data( );
	for( size_t index = 0; index < count; ++index )
		if( arrayPtr[ index ] == refNode )
			return false;
	refInputPortNode.emplace_back( refNode );
	emit connect_ref_input_port_node_signal( this, refNode );
	refNode->emplaceBackRefOutputPortNode( ref_input_port, output_port );
	emit connect_output_port_signal( output_port, ref_input_port );
	return true;
}
bool Node::eraseRefInputPortNode( OutputPort *output_port, InputPort *ref_input_port ) {
	Node *refNode = ref_input_port->parentNode;
	size_t count = refInputPortNode.size( );
	if( count == 0 )
		return false;
	auto arrayPtr = refInputPortNode.data( );
	for( size_t index = 0; index < count; ++index )
		if( arrayPtr[ index ] == refNode ) {
			refInputPortNode.erase( refInputPortNode.begin( ) + index );
			emit dis_connect_ref_input_port_node_signal( this, refNode );
			refNode->eraseRefOutputPortNode( ref_input_port, output_port );
			emit dis_connect_output_port_signal( output_port, ref_input_port );
			return true;
		}
	return false;
}
bool Node::emplaceBackRefOutputPortNode( InputPort *input_port, OutputPort *ref_output_port ) {
	Node *refNode = ref_output_port->parentNode;
	size_t count = refOutputPortNode.size( );
	if( count == 0 ) {
		refOutputPortNode.emplace_back( refNode );
		emit connect_ref_output_port_node_signal( this, refNode );
		refNode->emplaceBackRefInputPortNode( ref_output_port, input_port );
		emit connect_input_port_signal( input_port, ref_output_port );
		return true;
	}
	auto arrayPtr = refOutputPortNode.data( );
	for( size_t index = 0; index < count; ++index )
		if( arrayPtr[ index ] == refNode )
			return false;
	refOutputPortNode.emplace_back( refNode );
	emit connect_ref_output_port_node_signal( this, refNode );
	refNode->emplaceBackRefInputPortNode( ref_output_port, input_port );
	emit connect_input_port_signal( input_port, ref_output_port );
	return true;
}
bool Node::eraseRefOutputPortNode( InputPort *input_port, OutputPort *ref_output_port ) {
	Node *refNode = ref_output_port->parentNode;
	size_t count = refOutputPortNode.size( );
	if( count == 0 )
		return false;
	auto arrayPtr = refOutputPortNode.data( );
	for( size_t index = 0; index < count; ++index )
		if( arrayPtr[ index ] == refNode ) {
			refOutputPortNode.erase( refOutputPortNode.begin( ) + index );
			emit dis_connect_ref_output_port_node_signal( this, refNode );
			refNode->eraseRefInputPortNode( ref_output_port, input_port );
			emit dis_connect_input_port_signal( input_port, ref_output_port );
			return true;
		}
	return false;
}
void Node::releaseInputPortRefNode( Node *node ) {
	size_t count = refInputPortNode.size( );
	if( count == 0 )
		return;
	auto arrayPtr = refInputPortNode.data( );
	for( size_t index = 0; index < count; ++index )
		if( arrayPtr[ index ] == node ) {
			refInputPortNode.erase( refInputPortNode.begin( ) + index );
			emit dis_connect_ref_input_port_node_signal( this, node );
			node->releaseOutputPortRefNode( this );
			return;
		}
}
void Node::releaseOutputPortRefNode( Node *node ) {
	size_t count = refOutputPortNode.size( );
	if( count == 0 )
		return;
	auto arrayPtr = refOutputPortNode.data( );
	for( size_t index = 0; index < count; ++index )
		if( arrayPtr[ index ] == node ) {
			refOutputPortNode.erase( refOutputPortNode.begin( ) + index );
			emit dis_connect_ref_output_port_node_signal( this, node );
			node->releaseInputPortRefNode( this );
			return;
		}
}
void Node::releaseAllInputPortRefNode( ) {
	size_t count = refInputPortNode.size( );
	if( count == 0 )
		return;
	for( size_t index = 0; index < count; ++index ) {
		auto node = refInputPortNode.begin( );
		auto nodePtr = *node;
		refInputPortNode.erase( node );
		emit dis_connect_ref_input_port_node_signal( this, nodePtr );
		nodePtr->releaseOutputPortRefNode( this );
	}
}
void Node::releaseAllOutputPortRefNode( ) {
	size_t count = refOutputPortNode.size( );
	if( count == 0 )
		return;
	for( size_t index = 0; index < count; ++index ) {
		auto node = refOutputPortNode.begin( );
		auto nodePtr = *node;
		refOutputPortNode.erase( node );
		emit dis_connect_ref_output_port_node_signal( this, nodePtr );
		nodePtr->releaseInputPortRefNode( this );
	}
}
void Node::releaseAllRefNode( ) {
	releaseAllInputPortRefNode( );
	releaseAllOutputPortRefNode( );
}
bool Node::initEx( MainWidget *parent ) {
	if( init( parent ) == false )
		return false;
	if( initExCallFunction( parent ) == false )
		return false;
	if( updateLayout( ) == false )
		return false;
	if( updatePortGenerateCodes( ) == false )
		return false;
	return true;
}
bool Node::hasRefInputNodeRef( InputPort *input_port ) const {
	Node *refNode = input_port->parentNode;
	size_t count = refInputPortNode.size( );
	if( count == 0 )
		return false;
	auto arrayPtr = refInputPortNode.data( );
	for( size_t index = 0; index < count; ++index )
		if( arrayPtr[ index ] == refNode )
			return true;
	return false;
}
bool Node::hasRefOutputNodeRef( OutputPort *output_port ) const {
	Node *refNode = output_port->parentNode;
	size_t count = refOutputPortNode.size( );
	if( count == 0 )
		return false;
	auto arrayPtr = refOutputPortNode.data( );
	for( size_t index = 0; index < count; ++index )
		if( arrayPtr[ index ] == refNode )
			return true;
	return false;
}
bool Node::init( MainWidget *parent ) {
	instancePtr = Application::getInstancePtr( );
	varDirector = instancePtr->getVarDirector( );
	size_t count, index;
	InputPort **inputPortArrayPtr;
	OutputPort **outputPortArrayPtr;
	count = inputPortVector.size( );
	if( count != 0 ) {
		inputPortArrayPtr = inputPortVector.data( );
		for( index = 0; index < count; ++index )
			delete inputPortArrayPtr[ index ];
		inputPortVector.clear( );
	}
	count = outputPortVector.size( );
	if( count != 0 ) {
		outputPortArrayPtr = outputPortVector.data( );
		for( index = 0; index < count; ++index )
			delete outputPortArrayPtr[ index ];
		outputPortVector.clear( );
	}

	titileLabel->setText( nodeTitleName );
	setParent( parent );
	return true;
}

InputPort * Node::getInputPort( const QString &port_name ) const {
	size_t count = inputPortVector.size( );
	if( count == 0 )
		return nullptr;
	auto inputPortArrayPtr = inputPortVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( inputPortArrayPtr[ index ]->portName == port_name )
			return inputPortArrayPtr[ index ];
	return nullptr;
}
OutputPort * Node::getOutputPort( const QString &port_name ) const {
	size_t count = outputPortVector.size( );
	if( count == 0 )
		return nullptr;
	auto outputPortArrayPtr = outputPortVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( outputPortArrayPtr[ index ]->portName == port_name )
			return outputPortArrayPtr[ index ];
	return nullptr;
}
bool Node::updateLayout( ) {

	size_t count = inputPortVector.size( );
	size_t index;
	auto inputPortArrayPtr = inputPortVector.data( );
	for( index = 0; index < count; ++index )
		inputPortWidgetLayout->addWidget( inputPortArrayPtr[ index ], 0, Qt::AlignLeft | Qt::AlignHCenter );

	count = outputPortVector.size( );
	auto outputPortArrayPtr = outputPortVector.data( );
	for( index = 0; index < count; ++index )
		outputPortWidgetLayout->addWidget( outputPortArrayPtr[ index ], 0, Qt::AlignRight | Qt::AlignHCenter );

	return true;
}

void Node::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );

	switch( nodeStyle ) {
		case NodeEnum::NodeStyleType::None :
			painter.setPen( nonePen );
			penWidth = nonePen.width( );
			doubleWidth = penWidth * 2;
			painter.drawRect( penWidth, penWidth, width( ) - doubleWidth, height( ) - doubleWidth );
			break;
		case NodeEnum::NodeStyleType::Call_Function :
			painter.setPen( callFunctionPen );
			penWidth = callFunctionPen.width( );
			doubleWidth = penWidth * 2;
			painter.drawRect( penWidth, penWidth, width( ) - doubleWidth, height( ) - doubleWidth );
			break;
		case NodeEnum::NodeStyleType::Create :
			painter.setPen( createPen );
			penWidth = createPen.width( );
			doubleWidth = penWidth * 2;
			painter.drawRect( penWidth, penWidth, width( ) - doubleWidth, height( ) - doubleWidth );
			break;
		case NodeEnum::NodeStyleType::Select_Active :
			painter.setPen( selectActivePen );
			penWidth = selectActivePen.width( );
			doubleWidth = penWidth * 2;
			painter.drawRect( penWidth, penWidth, width( ) - doubleWidth, height( ) - doubleWidth );
			break;
		case NodeEnum::NodeStyleType::Select_Old :
			painter.setPen( selectOldPen );
			penWidth = selectOldPen.width( );
			doubleWidth = penWidth * 2;
			painter.drawRect( penWidth, penWidth, width( ) - doubleWidth, height( ) - doubleWidth );
			break;
		case NodeEnum::NodeStyleType::Warning :
			painter.setPen( warningPen );
			penWidth = warningPen.width( );
			doubleWidth = penWidth * 2;
			painter.drawRect( penWidth, penWidth, width( ) - doubleWidth, height( ) - doubleWidth );
			break;
		case NodeEnum::NodeStyleType::Error :
			painter.setPen( errorPen );
			penWidth = errorPen.width( );
			doubleWidth = penWidth * 2;
			painter.drawRect( penWidth, penWidth, width( ) - doubleWidth, height( ) - doubleWidth );
			break;
		case NodeEnum::NodeStyleType::Advise :
			painter.setPen( advisPen );
			penWidth = advisPen.width( );
			doubleWidth = penWidth * 2;
			painter.drawRect( penWidth, penWidth, width( ) - doubleWidth, height( ) - doubleWidth );
			break;
		case NodeEnum::NodeStyleType::Select_Output_Ref :
			painter.setPen( selectOutputRefPen );
			penWidth = selectOutputRefPen.width( );
			doubleWidth = penWidth * 2;
			painter.drawRect( penWidth, penWidth, width( ) - doubleWidth, height( ) - doubleWidth );
			break;
		case NodeEnum::NodeStyleType::Select_Input_Ref :
			painter.setPen( selectInputRefPen );
			penWidth = selectInputRefPen.width( );
			doubleWidth = penWidth * 2;
			painter.drawRect( penWidth, penWidth, width( ) - doubleWidth, height( ) - doubleWidth );
			break;
	}
}
const std::vector< InputPort * > & Node::getRefPort( const OutputPort *output_port ) {
	return output_port->refInputPortVector;
}
const std::vector< OutputPort * > & Node::getRefPort( const InputPort *input_port ) {
	return input_port->refOutputPortVector;
}

bool Node::getFilterRefPortNodeVector( const OutputPort *output_port, std::vector< Node * > &result_filter_node_vector, NodeEnum::NodeType node_type ) {
	size_t refInputPortCount;
	InputPort **refInputPortArray;
	size_t refInputPortIndex;
	size_t desIndex;
	size_t desCount;

	Node *current;
	Node **destArray;
	auto ref = getRefPort( output_port );
	refInputPortCount = ref.size( );
	if( refInputPortCount == 0 )
		return true;

	result_filter_node_vector.resize( refInputPortCount );
	refInputPortArray = ref.data( );
	destArray = result_filter_node_vector.data( );

	desCount = 0;
	refInputPortIndex = 0;
	for( ; refInputPortIndex < refInputPortCount; refInputPortIndex += 1 )
		if( refInputPortArray[ refInputPortIndex ] == nullptr )
			continue;
		else if( current = refInputPortArray[ refInputPortIndex ]->getParentNode( ), current->getNodeType( ) == node_type ) {
			for( desIndex = 0; desIndex < desCount; desIndex += 1 )
				if( destArray[ desIndex ] == current )
					break;
			if( desIndex < desCount )
				continue;
			destArray[ desCount ] = current;
			desCount += 1;

		}
	result_filter_node_vector.resize( desCount );
	return true;
}
bool Node::getFilterNotRefPortNodeVector( const OutputPort *output_port, std::vector< Node * > &result_filter_node_vector, NodeEnum::NodeType node_type ) {
	size_t refInputPortCount;
	InputPort **refInputPortArray;
	size_t refInputPortIndex;
	size_t desIndex;
	size_t desCount;

	Node *current;
	Node **destArray;
	auto ref = getRefPort( output_port );
	refInputPortCount = ref.size( );
	if( refInputPortCount == 0 )
		return true;

	result_filter_node_vector.resize( refInputPortCount );
	refInputPortArray = ref.data( );
	destArray = result_filter_node_vector.data( );

	desCount = 0;
	refInputPortIndex = 0;
	for( ; refInputPortIndex < refInputPortCount; refInputPortIndex += 1 )
		if( refInputPortArray[ refInputPortIndex ] == nullptr )
			continue;
		else if( current = refInputPortArray[ refInputPortIndex ]->getParentNode( ), current->getNodeType( ) != node_type ) {
			for( desIndex = 0; desIndex < desCount; desIndex += 1 )
				if( destArray[ desIndex ] == current )
					break;
			if( desIndex < desCount )
				continue;
			destArray[ desCount ] = current;
			desCount += 1;

		}
	result_filter_node_vector.resize( desCount );
	return true;
}
bool Node::getFilterRefPortNodeVector( const InputPort *input_port, std::vector< Node * > &result_filter_node_vector, NodeEnum::NodeType node_type ) {
	size_t refOutputPortCount;
	OutputPort **refOutputPortArray;
	size_t refOutputPortIndex;
	size_t desIndex;
	size_t desCount;

	Node *current;
	Node **destArray;
	auto ref = getRefPort( input_port );
	refOutputPortCount = ref.size( );
	if( refOutputPortCount == 0 )
		return true;

	result_filter_node_vector.resize( refOutputPortCount );
	refOutputPortArray = ref.data( );
	destArray = result_filter_node_vector.data( );

	desCount = 0;
	refOutputPortIndex = 0;
	for( ; refOutputPortIndex < refOutputPortCount; refOutputPortIndex += 1 )
		if( refOutputPortArray[ refOutputPortIndex ] == nullptr )
			continue;
		else if( current = refOutputPortArray[ refOutputPortIndex ]->getParentNode( ), current->getNodeType( ) == node_type ) {
			for( desIndex = 0; desIndex < desCount; desIndex += 1 )
				if( destArray[ desIndex ] == current )
					break;
			if( desIndex < desCount )
				continue;
			destArray[ desCount ] = current;
			desCount += 1;

		}
	result_filter_node_vector.resize( desCount );
	return true;
}
bool Node::getFilterNotRefPortNodeVector( const InputPort *input_port, std::vector< Node * > &result_filter_node_vector, NodeEnum::NodeType node_type ) {
	size_t refOutputPortCount;
	OutputPort **refOutputPortArray;
	size_t refOutputPortIndex;
	size_t desIndex;
	size_t desCount;

	Node *current;
	Node **destArray;
	auto ref = getRefPort( input_port );
	refOutputPortCount = ref.size( );
	if( refOutputPortCount == 0 )
		return true;

	result_filter_node_vector.resize( refOutputPortCount );
	refOutputPortArray = ref.data( );
	destArray = result_filter_node_vector.data( );

	desCount = 0;
	refOutputPortIndex = 0;
	for( ; refOutputPortIndex < refOutputPortCount; refOutputPortIndex += 1 )
		if( refOutputPortArray[ refOutputPortIndex ] == nullptr )
			continue;
		else if( current = refOutputPortArray[ refOutputPortIndex ]->getParentNode( ), current->getNodeType( ) != node_type ) {
			for( desIndex = 0; desIndex < desCount; desIndex += 1 )
				if( destArray[ desIndex ] == current )
					break;
			if( desIndex < desCount )
				continue;
			destArray[ desCount ] = current;
			desCount += 1;

		}
	result_filter_node_vector.resize( desCount );
	return true;
}
