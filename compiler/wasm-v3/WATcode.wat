(module
	;; WAT Setup Declarations
	(import "env" "jsprint" (func $jsprint (param i32)))
	(import "env" "newline" (func $newline))
	(import "env" "writeconsoleInt" (func $writeconsoleInt (param i32)))
	(import "env" "writeconsoleFloat" (func $writeconsoleFloat (param f32)))
	(import "env" "writeconsoleString" (func $writeconsoleString (param i64)))
	(memory $0 1)
	(export "pagememory" (memory $0))

	;; Artsy Program in WAT
	(func $add (param $z i32) (result i32)
		(local.set $T0
			(i32.add
				(local.get $z)
				(i32.const 2)
			)
		)
		(local.set $z
			(local.get $T0)
		)
		(return (local.get $z))		
	)
	(export "add" (func $add))
	;; Start Main Function
	(func $main
		(local $T1 i32)

		(local.set $T1
			(call $add
				(global.get $x)
			)
		)
	)
	(start $main)
)
