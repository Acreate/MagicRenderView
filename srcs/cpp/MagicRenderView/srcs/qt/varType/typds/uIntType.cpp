#include "./uIntType.h"

#include "../I_Type.h"
UIntType::UIntType( QObject *parent ): BaseVarType( parent, std_shared_ptr< I_Type >( new I_Type( typeid( t_current_type ) ) ) ), var( new t_current_type( ) ) {
}
