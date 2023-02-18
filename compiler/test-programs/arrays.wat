(module
	;; WAT Setup Declarations
	(import "env" "jsprint" (func $jsprint (param i32)))
	(import "env" "newline" (func $newline))
	(import "env" "writeconsoleInt" (func $writeconsoleInt (param i32)))
	(import "env" "writeconsoleFloat" (func $writeconsoleFloat (param f32)))
	(import "env" "writeconsoleString" (func $writeconsoleString (param i32)))
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

    (global $globarrPtr (mut i32) (i32.const 0))
    (func $main
        (local $arrPtr i32)
        (local $arrPtr2 i32)
        (local $getValTest1 i32)
        (local $getValTest2 i32)

        (global.set $globarrPtr
		    (call $create_array
                (i32.const 10)
            )
		)

        (local.set $arrPtr
		    (call $create_array
                (i32.const 10)
            )
		)
        
        (call $set_element
            (local.get $arrPtr)
            (i32.const 0)
            (i32.const 65)
        )

        (call $set_element
            (local.get $arrPtr)
            (i32.const 1)
            (i32.const 66)
        )

        (local.set $arrPtr2
		    (call $create_array
                (i32.const 20)
            )
		)

        (call $set_element
            (local.get $arrPtr2)
            (i32.const 0)
            (i32.const 67)
        )

        (local.set $getValTest1
		    (call $get_element
                (local.get $arrPtr)
                (i32.const 1)
            )
		)

        (local.set $getValTest2
		    (call $get_element
                (local.get $arrPtr2)
                (i32.const 0)
            )
		)

		(call $writeconsoleString
			(local.get $getValTest1)
		)
		(call $newline)
		(call $writeconsoleString
			(local.get $getValTest2)
		)
	)
	(start $main)
)
