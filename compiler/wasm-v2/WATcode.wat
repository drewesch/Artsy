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
		;; assign x:10

		(local.set $x
			(i32.const 10)
		)
		;; assign y:11

		(local.set $y
			(i32.const 11)
		)
		;; assign x:T0

		(local.set $x
			(i32.const 0)
		)
		;; assign y:21

		(local.set $y
			(i32.const 21)
		)
		;; output x 
		(call $writeconsole
			(local.get $x)
		)
		;; Print New Line
		(call $newline)
		;; ---------
		;; output y 
		(call $writeconsole
			(local.get $y)
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
	)
	(export "main" (func $main))
)
