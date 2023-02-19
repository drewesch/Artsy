(module
	;; WAT Setup Declarations
	(import "env" "writeconsoleInt" (func $writeconsoleInt (param i32)))
	(import "env" "writeconsoleFloat" (func $writeconsoleFloat (param f32)))
	(import "env" "writeconsoleString" (func $writeconsoleString (param i32)))
	(import "env" "newline" (func $newline))
    (memory $0 10)
	(export "pagememory" (memory $0))
    (func $create_array (param $size i32) (result i32)
        (local $ptr i32)
        (set_local $ptr (i32.const 0))
        (block
            (loop $loop
                (br_if $loop (i32.eq (get_local $size) (i32.const 0)))
                (set_local $ptr (i32.add (get_local $ptr) (i32.const 4)))
                (set_local $size (i32.sub (get_local $size) (i32.const 1)))
            )
        )
        (get_local $ptr)
    )
    (export "create_array" (func $get_element))
    (func $get_element (param $ptr i32) (param $index i32) (result i32)
        (i32.load (i32.add (get_local $ptr) (i32.mul (get_local $index) (i32.const 4))))
    )
    (export "get_element" (func $get_element))
    (func $set_element (param $ptr i32) (param $index i32) (param $value i32)
        (i32.store (i32.add (get_local $ptr) (i32.mul (get_local $index) (i32.const 4))) (get_local $value))
    )
    (export "set_element" (func $set_element))

    ;; Main function
    (func $main
        ;; Program Goal:
        ;; Print all numbers from the starting number to the ending number

        ;; Declare and set variables
        (local $start i32)
        (local $end i32)
        (local.set $start
            (i32.const 0)
		)
        (local.set $end
            (i32.const 20)
		)

        ;; Loop and print every number until the start var equals the end var
        (loop $loop
            (br_if 1 (i32.gt_s (local.get $start) (local.get $end)))
            (call $writeconsoleInt
                (local.get $start)
            )
            (call $newline)
            (local.set $start
                (i32.add (local.get $start) (i32.const 1))
            )
            (br $loop)
        )

    )
    (start $main)
)