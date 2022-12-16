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
	(global $y (mut i32) (i32.const 0))
	(func $test (param $a i32) (param $b i32) (result i32)
		(local $T0 i32)
		(local.set $T0
			(i32.div_s
				(local.get $a)
				(local.get $b)
			)
		)
		(return (local.get $T0))		
	)
	(export "test" (func $test))
	;; Start Main Function
	(func $main

		(global.set $y
			(i32.const 66)
		)
		(call $writeconsoleInt
			(global.get $y)
		)
	)
	(start $main)
)
