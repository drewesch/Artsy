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
		;; assign y:21

		(local.set $y
			(i32.const 21)
		)
		;; assign k:20

		(local.set $k
			(i32.const 20)
		)
		;; assign newVar:23

		(local.set $newVar
			(i32.const 23)
		)
		;; assign z:71

		(local.set $z
			(i32.const 71)
		)
		;; assign x:115

		(local.set $x
			(i32.const 115)
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
