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
	(global $y (mut i32) (i32.const 0))
	(global $z (mut i32) (i32.const 0))
	(global $k (mut i32) (i32.const 0))
	(global $newVar (mut i32) (i32.const 0))
	;; Start Main Function
	(func $main

		(global.set $x
			(i32.const 10)
		)
		(global.set $y
			(i32.const 21)
		)
		(global.set $k
			(i32.const 20)
		)
		(global.set $newVar
			(i32.const 23)
		)
		(global.set $z
			(i32.const 71)
		)
		(global.set $x
			(i32.const 115)
		)
		(call $writeconsoleInt
			(global.get $x)
		)
		(call $newline)
		(call $writeconsoleInt
			(global.get $z)
		)
		(call $newline)
		(call $writeconsoleInt
			(global.get $k)
		)
		(call $newline)
		(call $writeconsoleInt
			(global.get $newVar)
		)
		(call $newline)
	)
	(start $main)
)
