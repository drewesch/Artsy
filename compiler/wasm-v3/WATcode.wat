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
	(global $x (mut i32) (i32.const 0))
	(func $test (param $z i32) (result i32)
		(return (local.get $z))		
	)
	(export "test" (func $test))
	;; Start Main Function
	(func $main
		(local $T0 i32)

		(local.set $T0
			(call $test
				(global.get $y)
			)
		)
		(global.set $x
			(local.get $T0)
		)
		(call $writeconsoleInt
			(global.get $x)
		)
	)
	(start $main)
)
