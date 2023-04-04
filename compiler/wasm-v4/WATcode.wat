(module
	;; WAT Setup Declarations
	(import "env" "print_int" (func $print_int (param i32)))
	(import "env" "print_float" (func $print_float (param f32)))
	(import "env" "print_string" (func $print_string (param i32)))
	(import "env" "newline" (func $newline))
	(memory $0 100)
	(export "pagememory" (memory $0))
	(func $create_array (param $size i32) (result i32) (local $ptr i32) (set_local $ptr (i32.const 0)) (block (loop $loop (br_if $loop (i32.eq (get_local $size) (i32.const 0))) (set_local $ptr (i32.add (get_local $ptr) (i32.const 4))) (set_local $size (i32.sub (get_local $size) (i32.const 1))))) (get_local $ptr))
	(export "create_array" (func $create_array))
	(func $get_element_i32 (param $ptr i32) (param $index i32) (result i32) (i32.load (i32.add (get_local $ptr) (i32.mul (get_local $index) (i32.const 4)))))
	(export "get_element_i32" (func $get_element_i32))
	(func $set_element_i32 (param $ptr i32) (param $index i32) (param $value i32) (i32.store (i32.add (get_local $ptr) (i32.mul (get_local $index) (i32.const 4))) (get_local $value)))
	(export "set_element_i32" (func $set_element_i32))

	(func $get_element_f32 (param $ptr i32) (param $index i32) (result f32) (f32.load (i32.add (get_local $ptr) (i32.mul (get_local $index) (i32.const 4)))))
	(export "get_element_f32" (func $get_element_f32))
	(func $set_element_f32 (param $ptr i32) (param $index i32) (param $value f32) (f32.store (i32.add (get_local $ptr) (i32.mul (get_local $index) (i32.const 4))) (get_local $value)))
	(export "set_element_f32" (func $set_element_f32))

	;; Artsy Program in WAT
	(global $x (mut i32) (i32.const 0))
	(global $y (mut i32) (i32.const 0))
	(global $testArr (mut i32) (i32.const 0))
	(global $z (mut i32) (i32.const 0))
	;; Start Main Function
	(func $main
		(local $_printstr_0 i32)
		(local $_printstr_1 i32)
		(local $T0 f32)
		(local $T1 f32)

		(local.set $_printstr_0 (call $create_array (i32.const 20)))
		(call $set_element_i32 (local.get $_printstr_0) (i32.const 0) (i32.const 84))
		(call $set_element_i32 (local.get $_printstr_0) (i32.const 1) (i32.const 101))
		(call $set_element_i32 (local.get $_printstr_0) (i32.const 2) (i32.const 115))
		(call $set_element_i32 (local.get $_printstr_0) (i32.const 3) (i32.const 116))
		(call $set_element_i32 (local.get $_printstr_0) (i32.const 4) (i32.const 32))
		(call $set_element_i32 (local.get $_printstr_0) (i32.const 5) (i32.const 112))
		(call $set_element_i32 (local.get $_printstr_0) (i32.const 6) (i32.const 114))
		(call $set_element_i32 (local.get $_printstr_0) (i32.const 7) (i32.const 111))
		(call $set_element_i32 (local.get $_printstr_0) (i32.const 8) (i32.const 103))
		(call $set_element_i32 (local.get $_printstr_0) (i32.const 9) (i32.const 114))
		(call $set_element_i32 (local.get $_printstr_0) (i32.const 10) (i32.const 97))
		(call $set_element_i32 (local.get $_printstr_0) (i32.const 11) (i32.const 109))
		(call $set_element_i32 (local.get $_printstr_0) (i32.const 12) (i32.const 13))
		(call $set_element_i32 (local.get $_printstr_0) (i32.const 13) (i32.const 116))
		(call $set_element_i32 (local.get $_printstr_0) (i32.const 14) (i32.const 104))
		(call $set_element_i32 (local.get $_printstr_0) (i32.const 15) (i32.const 105))
		(call $set_element_i32 (local.get $_printstr_0) (i32.const 16) (i32.const 115))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_0) (i32.const 0)))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_0) (i32.const 1)))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_0) (i32.const 2)))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_0) (i32.const 3)))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_0) (i32.const 4)))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_0) (i32.const 5)))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_0) (i32.const 6)))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_0) (i32.const 7)))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_0) (i32.const 8)))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_0) (i32.const 9)))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_0) (i32.const 10)))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_0) (i32.const 11)))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_0) (i32.const 12)))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_0) (i32.const 13)))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_0) (i32.const 14)))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_0) (i32.const 15)))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_0) (i32.const 16)))
		(call $newline)
		(global.set $x
 (i32.const 60))
		(global.set $y
 (i32.const 30))
		(call $print_int		(global.get $x))
		(call $newline)
		(local.set $_printstr_1 (call $create_array (i32.const 26)))
		(call $set_element_i32 (local.get $_printstr_1) (i32.const 17) (i32.const 76))
		(call $set_element_i32 (local.get $_printstr_1) (i32.const 18) (i32.const 111))
		(call $set_element_i32 (local.get $_printstr_1) (i32.const 19) (i32.const 111))
		(call $set_element_i32 (local.get $_printstr_1) (i32.const 20) (i32.const 107))
		(call $set_element_i32 (local.get $_printstr_1) (i32.const 21) (i32.const 33))
		(call $set_element_i32 (local.get $_printstr_1) (i32.const 22) (i32.const 33))
		(call $set_element_i32 (local.get $_printstr_1) (i32.const 23) (i32.const 33))
		(call $set_element_i32 (local.get $_printstr_1) (i32.const 24) (i32.const 9))
		(call $set_element_i32 (local.get $_printstr_1) (i32.const 25) (i32.const 84))
		(call $set_element_i32 (local.get $_printstr_1) (i32.const 26) (i32.const 104))
		(call $set_element_i32 (local.get $_printstr_1) (i32.const 27) (i32.const 105))
		(call $set_element_i32 (local.get $_printstr_1) (i32.const 28) (i32.const 115))
		(call $set_element_i32 (local.get $_printstr_1) (i32.const 29) (i32.const 32))
		(call $set_element_i32 (local.get $_printstr_1) (i32.const 30) (i32.const 105))
		(call $set_element_i32 (local.get $_printstr_1) (i32.const 31) (i32.const 115))
		(call $set_element_i32 (local.get $_printstr_1) (i32.const 32) (i32.const 32))
		(call $set_element_i32 (local.get $_printstr_1) (i32.const 33) (i32.const 116))
		(call $set_element_i32 (local.get $_printstr_1) (i32.const 34) (i32.const 97))
		(call $set_element_i32 (local.get $_printstr_1) (i32.const 35) (i32.const 98))
		(call $set_element_i32 (local.get $_printstr_1) (i32.const 36) (i32.const 98))
		(call $set_element_i32 (local.get $_printstr_1) (i32.const 37) (i32.const 101))
		(call $set_element_i32 (local.get $_printstr_1) (i32.const 38) (i32.const 100))
		(call $set_element_i32 (local.get $_printstr_1) (i32.const 39) (i32.const 33))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_1) (i32.const 17)))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_1) (i32.const 18)))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_1) (i32.const 19)))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_1) (i32.const 20)))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_1) (i32.const 21)))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_1) (i32.const 22)))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_1) (i32.const 23)))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_1) (i32.const 24)))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_1) (i32.const 25)))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_1) (i32.const 26)))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_1) (i32.const 27)))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_1) (i32.const 28)))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_1) (i32.const 29)))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_1) (i32.const 30)))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_1) (i32.const 31)))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_1) (i32.const 32)))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_1) (i32.const 33)))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_1) (i32.const 34)))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_1) (i32.const 35)))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_1) (i32.const 36)))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_1) (i32.const 37)))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_1) (i32.const 38)))
		(call $print_string		 (call $get_element_i32 (local.get $_printstr_1) (i32.const 39)))
		(call $newline)
		(global.set $testArr (call $create_array (i32.const 3)))		(call $set_element_f32 (global.get $testArr) (i32.const 40) (f32.const 3.3))
		(call $set_element_f32 (global.get $testArr) (i32.const 41) (f32.const -129.2))
		(global.set $z
 (i32.const 290230))
		(call $print_float (f32.const -21542.224609)		)
		(call $newline)
		(local.set $T0
		(f32.add (call $get_element_f32 (global.get $testArr) (i32.const 40))
 (call $get_element_f32 (global.get $testArr) (i32.const 41))
		))
		(local.set $T1
		(f32.add		(local.get $T0) (call $get_element_f32 (global.get $testArr) (i32.const 41))
		))
		(call $print_float		(local.get $T1))
		(call $newline)
		(call $print_int (i32.const 522414000)		)
	)
	(start $main)
)
