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

    (func $check_number (param i32) (result i32)
        ;; Type must be declared
        (local $type i32)

        ;; Three possible examples: If-Elif-Else, If-Else, and If

        ;; If-Elif-Else Example
        (if (i32.eq (get_local 0) (i32.const 0))
        (then (local.set $type (i32.const 0)))
        (else (if (i32.eq (get_local 0) (i32.const 1))
        (then (local.set $type (i32.const 1)))
        (else (local.set $type (i32.const -1)))
        )
        )
        )

        ;; If-Else example
        ;; (if (i32.gt_s (get_local 0) (i32.const 0))
        ;;     (then (local.set $type (i32.const 1)))
        ;;     (else (local.set $type (i32.const 0)))
        ;; )

        ;; If example
        ;; (if (i32.gt_s (get_local 0) (i32.const 0))
        ;;     (then (local.set $type (i32.const 1)))
        ;; )

        ;; Return
        (return (local.get $type))
    )
    (export "check_number" (func $check_number))

    (func $main
        (local $num1 i32)
        (local $num2 i32)

        (local.set $num1
            (i32.const 3)
		)
        (local.set $num2
            (call $check_number
                (local.get $num1)
            )
		)
        (call $writeconsoleInt
			(local.get $num2)
		)
    )
    (start $main)
)
