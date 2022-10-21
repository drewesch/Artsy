(module
	(import "env" "jsprint" (func $jsprint (param i32)))
	(import "env" "newline" (func $newline))
	(import "env" "writeconsole" (func $writeconsole (param i32)))
	(memory $0 1)
	(export "pagememory" (memory $0))

	(func $main
		(local $x i32)
		(local $y i32)
		(local $z i32)
		(local $k i32)
		(local $newVar i32)
		;; assign x:10

		(local.set $x
			(i32.const 10)
		)
		;; assign y:11

		(local.set $y
			(i32.const 11)
		)
		;; assign k:18

		(local.set $k
			(i32.const 18)
		)
		;; assign newVar:2

		(local.set $newVar
			(i32.const 2)
		)
		;; assign z:28

		(local.set $z
			(i32.const 28)
		)
		;; assign x:41

		(local.set $x
			(i32.const 41)
		)
		;; output x 
		(call $writeconsole
			(local.get $x)
		)
		;; Print New Line
		(call $newline)
		;; ---------
		;; output z 
		(call $writeconsole
			(local.get $z)
		)
		;; Print New Line
		(call $newline)
		;; ---------
		;; output k 
		(call $writeconsole
			(local.get $k)
		)
		;; Print New Line
		(call $newline)
		;; ---------
		;; output newVar 
		(call $writeconsole
			(local.get $newVar)
		)
		;; Print New Line
		(call $newline)
		;; ---------
	)
	(export "main" (func $main))
)
