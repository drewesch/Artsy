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
	(func $test (param $a i32) (param $b i32) (result i32)
		(local $T0 i32)
		(local $T1 i32)
		(global.set $x
			(i32.const 2)
		)
		(local.set $T0
			(i32.add
				(local.get $a)
				(i32.const 2)
			)
		)
		(local.set $a
			(local.get $T0)
		)
		(local.set $T1
			(i32.div_s
				(local.get $a)
				(local.get $b)
			)
		)
		(return (local.get $T1))		
	)
	(export "test" (func $test))
	;; Start Main Function
	(func $main
		(local $T2 i32)
		(local $T3 i32)

		(global.set $y
			(i32.const 66)
		)
		(local.set $T2
			(call $test
				(global.get $y)
				(i32.const 3)
			)
		)
		(global.set $x
			(local.get $T2)
		)
		(local.set $T3
			(call $test
				(global.get $y)
				(i32.const 3)
			)
		)
		(global.set $x
			(local.get $T3)
		)
		(call $writeconsoleInt
			(global.get $y)
		)
	)
	(start $main)
)
