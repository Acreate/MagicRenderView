#include "./colorType.h"

#include <QColor>
#include "../I_Type.h"
ColorType::ColorType( QObject *parent ) : BaseVarType( parent, std_shared_ptr< I_Type >( new I_Type( typeid( t_current_type ) ) ) ), var( new t_current_type( ) ) {
	I_Type *typeInfo = initTypeInfo( );
}
ColorType::ColorType( ) : ColorType( nullptr ) {
}
ColorType::~ColorType( ) {
	delete var;
}
void ColorType::resetVar( ) {
	*var = t_current_type( );
}
