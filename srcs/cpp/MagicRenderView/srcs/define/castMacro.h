#ifndef CASTMACRO_H_H_HEAD__FILE__
#define CASTMACRO_H_H_HEAD__FILE__

#define Reinterpret_Cast( source_ptr, cast_ptr ) source_ptr = reinterpret_cast< decltype(source_ptr) >( cast_ptr )
#define Static_Cast( source_ptr, cast_ptr ) source_ptr = static_cast< decltype(source_ptr) >( cast_ptr )
#define Dynamic_Cast( source_ptr, cast_ptr ) source_ptr = dynamic_cast< decltype(source_ptr) >( cast_ptr )
#define QObject_Cast( source_ptr, cast_ptr ) source_ptr = qobject_cast< decltype(source_ptr) >( cast_ptr )
#endif // CASTMACRO_H_H_HEAD__FILE__
