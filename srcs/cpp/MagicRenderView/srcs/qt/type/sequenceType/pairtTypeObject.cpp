#include "pairtTypeObject.h"
PairtTypeObject::PairtTypeObject( const std_function< std_shared_ptr<IVarStack> ( ) > &gener_var_stack, const std_vector< QString > &alias_type_name, QObject *parnet ): ITypeObject( gener_var_stack, alias_type_name, parnet ) {
}
PairtTypeObject::PairtTypeObject( const std_function< std_shared_ptr<IVarStack> ( ) > &gener_var_stack, const std_vector< QString > &alias_type_name, QObject *const parent, const std_shared_ptr< ITypeObject > &first, const std_shared_ptr< ITypeObject > &scond ): ITypeObject( gener_var_stack, alias_type_name, parent ),
	first( first ),
	scond( scond ) {
	currentTypeName.emplace_back( PairtTypeObject::staticMetaObject.className( ) );
}
PairtTypeObject::PairtTypeObject( const std_function< std_shared_ptr<IVarStack> ( ) > &gener_var_stack, const std_shared_ptr< ITypeObject > &first, const std_shared_ptr< ITypeObject > &scond ) : ITypeObject( gener_var_stack, { }, nullptr ), first( first ), scond( scond ) {
	currentTypeName.emplace_back( PairtTypeObject::staticMetaObject.className( ) );
}
PairtTypeObject & PairtTypeObject::operator=( const PairtTypeObject &other ) {
	if( this == nullptr || thisPtr == nullptr )
		return *this;
	auto typeObject = &other;
	if( typeObject != nullptr && other.thisPtr != nullptr ) {
		if( this == typeObject )
			return *this;
		ITypeObject::operator =( other );
		first = other.first;
		scond = other.scond;
	} else
		thisPtr = nullptr;
	return *this;
}

size_t PairtTypeObject::serializeToObjectData( const uint8_t *read_data_vector, const size_t data_count ) {
	if( data_count == 0 )
		return 0;
	auto fromUtf8 = QString::fromUtf8( read_data_vector );
	qsizetype indexOf = fromUtf8.indexOf( "{" );
	if( indexOf == -1 ) // 必须存在 {} 组成的列表
		return 0;
	auto end = fromUtf8.indexOf( "}", indexOf + 1 );
	if( end == -1 ) // 必须存在 {} 组成的列表
		return 0;
	auto string = fromUtf8.mid( indexOf, end - indexOf );
	auto stringList = string.split( "," );
	// 媒体信息
	const QMetaObject *meta = metaObject( );
	// 该类名称
	auto className = meta->className( );
	auto superClass = meta->superClass( );

	return 0;
}
bool PairtTypeObject::serializeToVectorData( std_vector< uint8_t > *result_data_vector ) const {
	return false;
}
