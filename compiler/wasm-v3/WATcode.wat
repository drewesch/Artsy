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
	(global $z (mut i32) (i32.const 0))
	;; Start Main Function
	(func $main

		(global.set $z
			(i32.const 9)
		)
		(call $writeconsoleInt
			(global.get $z)
		)
	)
	(start $main)
)
