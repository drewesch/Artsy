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
	(global $x (mut f32) (f32.const 0.0))
	;; Start Main Function
	(func $main

		(global.set $x
			(f32.const 10.0)
		)
		(call $writeconsoleFloat
			(global.get $x)
		)
	)
	(start $main)
)
