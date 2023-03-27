(module
	;; WAT Setup Declarations
	(import "env" "printInt" (func $printInt (param i32)))
	(import "env" "printFloat" (func $printFloat (param f32)))
	(import "env" "printString" (func $printString (param i32)))
	(import "env" "newline" (func $newline))
	(memory $0 100)
	(export "pagememory" (memory $0))
	(func $create_array (param $size i32) (result i32) (local $ptr i32) (set_local $ptr (i32.const 0)) (block (loop $loop (br_if $loop (i32.eq (get_local $size) (i32.const 0))) (set_local $ptr (i32.add (get_local $ptr) (i32.const 4))) (set_local $size (i32.sub (get_local $size) (i32.const 1))))) (get_local $ptr))
	(export "create_array" (func $get_element))
	(func $get_element (param $ptr i32) (param $index i32) (result i32)(i32.load (i32.add (get_local $ptr) (i32.mul (get_local $index) (i32.const 4)))))
	(export "get_element" (func $get_element))
	(func $set_element (param $ptr i32) (param $index i32) (param $value i32) (i32.store (i32.add (get_local $ptr) (i32.mul (get_local $index) (i32.const 4))) (get_local $value)))
	(export "set_element" (func $set_element))

	;; Artsy Program in WAT
	(global $x (mut i32) (i32.const 0))
	(global $y (mut i32) (i32.const 0))
	;; Start Main Function
	(func $main
		(local $_printstr_0 i32)
		(local $T0 i32)
		(local $T1 i32)

		(global.set $x
			(i32.const -1)
		)
		(global.set $y
			(i32.const 30)
		)
		(block (loop
		(br_if 1)
		(local.set $_printstr_0 (call $create_array (i32.const 9)))
		(call $set_element (local.get $_printstr_0) (i32.const 0) (i32.const 76))
		(call $set_element (local.get $_printstr_0) (i32.const 1) (i32.const 105))
		(call $set_element (local.get $_printstr_0) (i32.const 2) (i32.const 110))
		(call $set_element (local.get $_printstr_0) (i32.const 3) (i32.const 101))
		(call $set_element (local.get $_printstr_0) (i32.const 4) (i32.const 32))
		(call $set_element (local.get $_printstr_0) (i32.const 5) (i32.const 35))
		(call $printString (call $get_element (local.get $_printstr_0) (i32.const 0)))
		(call $printString (call $get_element (local.get $_printstr_0) (i32.const 1)))
		(call $printString (call $get_element (local.get $_printstr_0) (i32.const 2)))
		(call $printString (call $get_element (local.get $_printstr_0) (i32.const 3)))
		(call $printString (call $get_element (local.get $_printstr_0) (i32.const 4)))
		(call $printString (call $get_element (local.get $_printstr_0) (i32.const 5)))
		(local.set $T0
			(i32.mul
				(global.get $x)
				(global.get $x)
			)
		)
		(call $printInt (local.get $T0))
		(call $newline)
		(local.set $T1
			(i32.add
				(global.get $x)
				(i32.const 1)
			)
		)
		(global.set $x
			(local.get $T1)
		)
		(br 0)
		))	)
	(start $main)
)
