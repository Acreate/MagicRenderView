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

#include <tools/pathTools.h>
#include <node/nodeTools/nodeTools.h>
#include <node/port/inputPort/dynamicTypeInputPort.h>
#include <node/port/outputPort/dynamicTypeOutputPort.h>

#include "../nodeAfterEffect/borderWidget/nodeBorderAfterEffect.h"
#include "../nodeAfterEffect/nodeAfterEffect.h"

Def_Entity_NodeTypeName_Function( Node, Node::tr( "未实现" ) );

bool Node::fillNodeCall( const QDateTime &ndoe_run_start_data_time, size_t current_frame ) {
	return true;
}
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

	delete titileLabel;
	delete titileWidgetLayout;
	delete titileWidget;

	delete outputPortWidgetLayout;
	delete outputPortWidget;

	delete inputPortWidgetLayout;
	delete inputPortWidget;

	delete connectWidgetLayout;
	delete connectWidget;

	delete mainLayout;

	delete nodeAfterEffect;
	delete nodeToolsPtr;

	if( varPtr )
		varDirector->release( varPtr );
}
Node::Node( const QString &node_name ) : nodeTitleName( node_name ) {
	hide( );
	generateCode = 0;
	varPtr = nullptr;
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
	inputPortWidgetLayout = new QVBoxLayout( inputPortWidget );
	inputPortWidgetLayout->setContentsMargins( 0, 0, 0, 0 );
	inputPortWidgetLayout->setSpacing( 0 );
	connectWidgetLayout->addWidget( inputPortWidget, 0, Qt::AlignLeft | Qt::AlignTop );
	// 输出端布局
	outputPortWidget = new QWidget( connectWidget );
	outputPortWidgetLayout = new QVBoxLayout( outputPortWidget );
	outputPortWidgetLayout->setContentsMargins( 0, 0, 0, 0 );
	outputPortWidgetLayout->setSpacing( 0 );
	connectWidgetLayout->addWidget( outputPortWidget, 0, Qt::AlignRight | Qt::AlignTop );

	// 主要布局
	auto oldLayout = layout( );
	if( oldLayout )
		delete oldLayout;
	mainLayout = new QVBoxLayout( this );
	nodeBorderWidth = 8;
	mainLayout->setContentsMargins( nodeBorderWidth, nodeBorderWidth, nodeBorderWidth, nodeBorderWidth );
	mainLayout->setSpacing( 0 );
	mainLayout->addWidget( titileWidget );
	mainLayout->addWidget( connectWidget );
	// 创建特效组件
	nodeAfterEffect = new NodeBorderAfterEffect( this );
	nodeAfterEffect->move( 0, 0 );
	// 创建节点工具
	nodeToolsPtr = new NodeTools( this );
}
NodeInfoWidget * Node::getNodeInfoWidget( ) {
	return nullptr;
}
bool Node::bindPortInfo( ) {
	size_t count = outputPortVector.size( );
	size_t index;
	OutputPort **outputPortArrayPtr;
	if( count ) {
		outputPortArrayPtr = outputPortVector.data( );
		for( index = 0; index < count; ++index )
			outputPortArrayPtr[ index ]->bindPortInfo( );
	}
	return true;
}
bool Node::releasePortInfo( ) {
	size_t count = outputPortVector.size( );
	size_t index;
	OutputPort **outputPortArrayPtr;
	if( count ) {
		outputPortArrayPtr = outputPortVector.data( );
		for( index = 0; index < count; ++index )
			outputPortArrayPtr[ index ]->releasePortInfo( );
	}
	return true;
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
bool Node::appendDynamicTypeInputPort( DynamicTypeInputPort *input_port ) {
	return appendInputPort( input_port );
}
bool Node::appendDynamicTypeOutputPort( DynamicTypeOutputPort *output_port ) {
	return appendOutputPort( output_port );
}
DynamicTypeInputPort * Node::createDynamicTypeInputPort( const NodeEnum::PortType &port_enum_type, const QString &input_port_name, const QString &input_port_var_name ) {
	QString typeName;
	if( varDirector == nullptr || varDirector->getTypeName( input_port_var_name, typeName ) == false )
		return nullptr;
	return new DynamicTypeInputPort( port_enum_type, input_port_name, typeName );
}
DynamicTypeInputPort * Node::createDynamicTypeInputPort( const NodeEnum::PortType &port_enum_type, const QString &input_port_name, const std::type_info &input_port_var_type_info ) {
	QString typeName;
	if( varDirector == nullptr || varDirector->getTypeName( input_port_var_type_info, typeName ) == false )
		return nullptr;
	return new DynamicTypeInputPort( port_enum_type, input_port_name, typeName );;
}
bool Node::releaseDynamicTypeInputPort( DynamicTypeInputPort *delete_dynamic_type_input_port ) {
	if( delete_dynamic_type_input_port == nullptr )
		return true;
	delete delete_dynamic_type_input_port;
	return true;
}
bool Node::releaseDynamicTypeOutputPort( DynamicTypeOutputPort *delete_dynamic_type_output_port ) {
	if( delete_dynamic_type_output_port == nullptr )
		return true;
	delete delete_dynamic_type_output_port;
	return true;
}
DynamicTypeOutputPort * Node::createDynamicTypeOutputPort( const NodeEnum::PortType &port_enum_type, const QString &output_port_name, const QString &output_port_var_name ) {
	QString typeName;
	if( varDirector == nullptr || varDirector->getTypeName( output_port_var_name, typeName ) == false )
		return nullptr;
	return new DynamicTypeOutputPort( port_enum_type, output_port_name, typeName );
}
DynamicTypeOutputPort * Node::createDynamicTypeOutputPort( const NodeEnum::PortType &port_enum_type, const QString &output_port_name, const type_info &output_port_var_type_info ) {
	QString typeName;
	if( varDirector == nullptr || varDirector->getTypeName( output_port_var_type_info, typeName ) == false )
		return nullptr;
	return new DynamicTypeOutputPort( port_enum_type, output_port_name, typeName );
}
void Node::setNodeTitleName( const QString &node_title_name ) {
	nodeTitleName = node_title_name;
	titileLabel->setText( node_title_name );
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

InputPort * Node::getInputPort( const size_t &input_port_generate_code ) const {
	size_t count = inputPortVector.size( );
	if( count == 0 )
		return nullptr;
	auto inputPortArrayPtr = inputPortVector.data( );
	size_t index = input_port_generate_code - 1;
	if( index < count && inputPortArrayPtr[ index ]->generateCode == input_port_generate_code )
		return inputPortArrayPtr[ index ];
	for( index = 0; index < count; ++index )
		if( inputPortArrayPtr[ index ]->generateCode == input_port_generate_code )
			return inputPortArrayPtr[ index ];
	return nullptr;
}
OutputPort * Node::getOutputPort( const size_t &output_port_generate_code ) const {
	size_t count = outputPortVector.size( );
	if( count == 0 )
		return nullptr;
	auto outputPortArrayPtr = outputPortVector.data( );
	size_t index = output_port_generate_code - 1;
	if( index < count && outputPortArrayPtr[ index ]->generateCode == output_port_generate_code )
		return outputPortArrayPtr[ index ];

	for( index = 0; index < count; ++index )
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
	size_t count = thisNodeOutputPortRefOtherNodeInputPortVector.size( );
	if( count == 0 ) {
		thisNodeOutputPortRefOtherNodeInputPortVector.emplace_back( refNode );
		emit connect_ref_input_port_node_signal( this, refNode );
		refNode->emplaceBackRefOutputPortNode( ref_input_port, output_port );
		emit connect_output_port_signal( output_port, ref_input_port );
		return true;
	}
	auto arrayPtr = thisNodeOutputPortRefOtherNodeInputPortVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( arrayPtr[ index ] == refNode )
			return false;
	thisNodeOutputPortRefOtherNodeInputPortVector.emplace_back( refNode );
	emit connect_ref_input_port_node_signal( this, refNode );
	refNode->emplaceBackRefOutputPortNode( ref_input_port, output_port );
	emit connect_output_port_signal( output_port, ref_input_port );
	return true;
}
bool Node::eraseRefInputPortNode( OutputPort *output_port, InputPort *ref_input_port ) {
	Node *refNode = ref_input_port->parentNode;
	size_t count = thisNodeOutputPortRefOtherNodeInputPortVector.size( );
	if( count == 0 )
		return false;
	auto arrayPtr = thisNodeOutputPortRefOtherNodeInputPortVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( arrayPtr[ index ] == refNode ) {
			thisNodeOutputPortRefOtherNodeInputPortVector.erase( thisNodeOutputPortRefOtherNodeInputPortVector.begin( ) + index );
			emit dis_connect_ref_input_port_node_signal( this, refNode );
			refNode->eraseRefOutputPortNode( ref_input_port, output_port );
			emit dis_connect_output_port_signal( output_port, ref_input_port );
			return true;
		}
	return false;
}
bool Node::emplaceBackRefOutputPortNode( InputPort *input_port, OutputPort *ref_output_port ) {
	Node *refNode = ref_output_port->parentNode;
	size_t count = otherNodeOutputPortRefThisNodeInputPortVector.size( );
	if( count == 0 ) {
		otherNodeOutputPortRefThisNodeInputPortVector.emplace_back( refNode );
		emit connect_ref_output_port_node_signal( this, refNode );
		refNode->emplaceBackRefInputPortNode( ref_output_port, input_port );
		emit connect_input_port_signal( input_port, ref_output_port );
		return true;
	}
	auto arrayPtr = otherNodeOutputPortRefThisNodeInputPortVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( arrayPtr[ index ] == refNode )
			return false;
	otherNodeOutputPortRefThisNodeInputPortVector.emplace_back( refNode );
	emit connect_ref_output_port_node_signal( this, refNode );
	refNode->emplaceBackRefInputPortNode( ref_output_port, input_port );
	emit connect_input_port_signal( input_port, ref_output_port );
	return true;
}
bool Node::eraseRefOutputPortNode( InputPort *input_port, OutputPort *ref_output_port ) {
	Node *refNode = ref_output_port->parentNode;
	size_t count = otherNodeOutputPortRefThisNodeInputPortVector.size( );
	if( count == 0 )
		return false;
	auto arrayPtr = otherNodeOutputPortRefThisNodeInputPortVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( arrayPtr[ index ] == refNode ) {
			otherNodeOutputPortRefThisNodeInputPortVector.erase( otherNodeOutputPortRefThisNodeInputPortVector.begin( ) + index );
			emit dis_connect_ref_output_port_node_signal( this, refNode );
			refNode->eraseRefInputPortNode( ref_output_port, input_port );
			emit dis_connect_input_port_signal( input_port, ref_output_port );
			return true;
		}
	return false;
}
void Node::releaseInputPortRefNode( Node *node ) {
	size_t count = thisNodeOutputPortRefOtherNodeInputPortVector.size( );
	if( count == 0 )
		return;
	auto arrayPtr = thisNodeOutputPortRefOtherNodeInputPortVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( arrayPtr[ index ] == node ) {
			thisNodeOutputPortRefOtherNodeInputPortVector.erase( thisNodeOutputPortRefOtherNodeInputPortVector.begin( ) + index );
			emit dis_connect_ref_input_port_node_signal( this, node );
			node->releaseOutputPortRefNode( this );
			return;
		}
}
void Node::releaseOutputPortRefNode( Node *node ) {
	size_t count = otherNodeOutputPortRefThisNodeInputPortVector.size( );
	if( count == 0 )
		return;
	auto arrayPtr = otherNodeOutputPortRefThisNodeInputPortVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( arrayPtr[ index ] == node ) {
			otherNodeOutputPortRefThisNodeInputPortVector.erase( otherNodeOutputPortRefThisNodeInputPortVector.begin( ) + index );
			emit dis_connect_ref_output_port_node_signal( this, node );
			node->releaseInputPortRefNode( this );
			return;
		}
}
void Node::releaseAllInputPortRefNode( ) {
	size_t count = thisNodeOutputPortRefOtherNodeInputPortVector.size( );
	if( count == 0 )
		return;
	for( size_t index = 0; index < count; ++index ) {
		auto node = thisNodeOutputPortRefOtherNodeInputPortVector.begin( );
		auto nodePtr = *node;
		thisNodeOutputPortRefOtherNodeInputPortVector.erase( node );
		emit dis_connect_ref_input_port_node_signal( this, nodePtr );
		nodePtr->releaseOutputPortRefNode( this );
	}
}
void Node::releaseAllOutputPortRefNode( ) {
	size_t count = otherNodeOutputPortRefThisNodeInputPortVector.size( );
	if( count == 0 )
		return;
	for( size_t index = 0; index < count; ++index ) {
		auto node = otherNodeOutputPortRefThisNodeInputPortVector.begin( );
		auto nodePtr = *node;
		otherNodeOutputPortRefThisNodeInputPortVector.erase( node );
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
NodeEnum::NodeSelctType Node::getNodeSelctType( ) const {
	return nodeAfterEffect->getNodeSelctType( );
}
void Node::setNodeSelctType( NodeEnum::NodeSelctType node_selct_type ) {
	nodeAfterEffect->setNodeSelctType( node_selct_type );
}
NodeEnum::NodeStatusType Node::getNodeStatusType( ) const {
	return nodeAfterEffect->getNodeStatusType( );
}
void Node::setNodeStatusType( NodeEnum::NodeStatusType node_status_type ) {
	nodeAfterEffect->setNodeStatusType( node_status_type );
}
bool Node::hasRefInputNodeRef( InputPort *input_port ) const {
	Node *refNode = input_port->parentNode;
	size_t count = thisNodeOutputPortRefOtherNodeInputPortVector.size( );
	if( count == 0 )
		return false;
	auto arrayPtr = thisNodeOutputPortRefOtherNodeInputPortVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( arrayPtr[ index ] == refNode )
			return true;
	return false;
}
bool Node::hasRefOutputNodeRef( OutputPort *output_port ) const {
	Node *refNode = output_port->parentNode;
	size_t count = otherNodeOutputPortRefThisNodeInputPortVector.size( );
	if( count == 0 )
		return false;
	auto arrayPtr = otherNodeOutputPortRefThisNodeInputPortVector.data( );
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

	nodeTitleName = getVirtualNodeTypeName( );
	nodeTitleName = pathTools::normalPathSeparatorToPath( nodeTitleName );
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
	if( nodeAfterEffect->updateLayout( ) == false )
		return false;
	return true;
}

void Node::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
}
void Node::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	QSize newSizet = this->size( );
	nodeAfterEffect->resize( newSizet );
}
