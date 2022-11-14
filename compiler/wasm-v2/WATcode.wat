(module
	;; WAT Setup Declarations
	(import "env" "jsprint" (func $jsprint (param i32)))
	(import "env" "newline" (func $newline))
	(import "env" "writeconsole" (func $writeconsole (param i32)))
	(memory $0 1)
	(export "pagememory" (memory $0))

	;; Artsy Program in WAT
	(global $aNumber (mut i32) (i32.const 0)
	(global $justAverage (mut f32) (f32.const 0.0)
	(export "average" (func $average))
	(func $average (param $a f32) (param $b f32) (param $c f32) (result f32)
		(local $avg f32)
		(local $T0 f32)
		(local.set $T0
			(f32.add
				(local.get $a)
				(local.get $b)
			)
		)
		(local $T1 f32)
		(local.set $T1
			(f32.add
				(local.get $T0)
				(local.get $c)
			)
		)
		(local $T2 f32)
		(local.set $T2
			(f32.div
				(local.get $T1)
				(f32.const 3.0)
			)
		)
		(local.set $avg
			(local.get $T2)
		)

		;; return avg
		(local.get $avg)
	)
	(export "displayMessage" (func $displayMessage))
	(func $displayMessage 
		;; return 0
		i32.const 0
		return
	)
	(export "ambitiousFunction" (func $ambitiousFunction))
	(func $ambitiousFunction (param $a f32) (param $b f32) (param $c f32) (result f32)
		(local $result f32)
		(local $T3 f32)
		(local.set $T3
			(call $average
				(local.get $a)
				(local.get $b)
				(local.get $c)
			)
		)
		(local $T4 f32)
		(local.set $T4
			(call $average
				(local.get $a)
				(local.get $b)
				(local.get $c)
			)
		)
		(local $T5 f32)
		(local.set $T5
			(f32.add
				(local.get $T3)
				(local.get $T4)
			)
		)
		(local $T6 f32)
		(local.set $T6
			(f32.div
				(local.get $T5)
				(f32.const 2.0)
			)
		)
		(local.set $result
			(local.get $T6)
		)

		;; return result
		(local.get $result)
	)
	;; Start Main Function
	(func $main
		(local $T7 f32)
		(local.set $T7
			(call $average
				(f32.const 12.5)
				(f32.const 13.7)
				(f32.const 25.8)
			)
		)
		(global.set $justAverage
			(local.get $T7)
		)
		(local $T8 i32)
		(local.set $T8
			(call $displayMessage)
		)
		(global.set $aNumber
			(local.get $T8)
		)
		(call $writeconsole
			(global.get $justAverage)
		)
		;; Print New Line
		(call $newline)
		(local $T9 f32)
		(local.set $T9
			(f32.add
				(global.get $justAverage)
				(f32.const 2.0)
			)
		)
		(local $T10 f32)
		(local.set $T10
			(f32.mul
				(global.get $justAverage)
				(local.get $T9)
			)
		)
		(global.set $justAverage
			(local.get $T10)
		)
		(local $T11 f32)
		(local.set $T11
			(call $average
				(global.get $justAverage)
				(f32.const 0.0)
				(f32.const 0.0)
			)
		)
		(global.set $justAverage
			(local.get $T11)
		)
		(local $T12 i32)
		(local.set $T12
			(call $displayMessage)
		)
		(global.set $aNumber
			(local.get $T12)
		)
		;; Print New Line
		(call $newline)
		(local $T13 i32)
		(local.set $T13
			(call $displayMessage)
		)
		(global.set $aNumber
			(local.get $T13)
		)
		(local $T14 i32)
		(local.set $T14
			(i32.mul
				(global.get $aNumber)
				(global.get $aNumber)
			)
		)
		(local $T15 i32)
		(local.set $T15
			(i32.add
				(global.get $aNumber)
				(local.get $T14)
			)
		)
		(local $T16 i32)
		(local.set $T16
			(i32.div_s
				(global.get $aNumber)
				(local.get $T15)
			)
		)
		(global.set $aNumber
			(local.get $T16)
		)
		(call $writeconsole
			(global.get $aNumber)
		)
		;; Print New Line
		(call $newline)
		(local $T17 f32)
		(local.set $T17
			(call $ambitiousFunction
				(f32.const 1.0)
				(f32.const 2.0)
				(f32.const 3.0)
			)
		)
		(global.set $justAverage
			(local.get $T17)
		)
		(local $T18 i32)
		(local.set $T18
			(call $displayMessage)
		)
		(global.set $aNumber
			(local.get $T18)
		)
		(call $writeconsole
			(global.get $justAverage)
		)
		;; Print New Line
		(call $newline)
	)
	(start $main)
)
