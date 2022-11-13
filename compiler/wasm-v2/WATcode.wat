(module
	;; WAT Setup Declarations
	(import "env" "jsprint" (func $jsprint (param i32)))
	(import "env" "newline" (func $newline))
	(import "env" "writeconsole" (func $writeconsole (param i32)))
	(memory $0 1)
	(export "pagememory" (memory $0))

	;; Artsy Program in WAT
	(global $aNumber i32)
	(global $justAverage f32)
	(export "average" (func $average))
	(func $average (param $a f32) (param $b f32) (param $c f32) (result f32)
		(local $avg f32)
		(local $T0 f32)
		(local.set $T0
			(local.get $a)
			(local.get $b)
			f32.add
		)
		(local $T1 f32)
		(local.set $T1
			(local.get $T0)
			(local.get $c)
			f32.add
		)
		(local $T2 f32)
		(local.set $T2
			(local.get $T1)
			(f32.const 3.0)
			f32.div
		)
		;; return avg
		(local.get $avg)
	)
	(export "displayMessage" (func $displayMessage))
	(func $displayMessage (result i32)
		;; output message 
		(call $writeconsole
			(global.get $message)
		)
		;; return 0
		(local.get $0)
	)
	(export "ambitiousFunction" (func $ambitiousFunction))
	(func $ambitiousFunction (param $a f32) (param $b f32) (param $c f32) (result f32)
		(local $result f32)
		(local $T2 f32)
		(local.set $T2
			(local.get $T0)
			(local.get $T1)
			f32.add
		)
		(local $T3 f32)
		(local.set $T3
			(local.get $T2)
			(f32.const 2.0)
			f32.div
		)
		;; return result
		(local.get $result)
	)
		;; output justAverage 
	(call $writeconsole
		(global.get $justAverage)
	)
	;; Print New Line
	(call $newline)
	(local $T0 f32)
	(local.set $T0
		(global.get $justAverage)
		(f32.const 2.0)
		f32.add
	)
	(local $T1 f32)
	(local.set $T1
		(global.get $justAverage)
		(local.get $T0)
		f32.mul
	)
	;; Print New Line
	(call $newline)
	(local $T0 i32)
	(local.set $T0
		(global.get $aNumber)
		(global.get $aNumber)
		i32.mul
	)
	(local $T1 i32)
	(local.set $T1
		(global.get $aNumber)
		(local.get $T0)
		i32.add
	)
	(local $T2 i32)
	(local.set $T2
		(global.get $aNumber)
		(local.get $T1)
		i32.div_s
	)
		;; output aNumber 
	(call $writeconsole
		(global.get $aNumber)
	)
	;; Print New Line
	(call $newline)
		;; output justAverage 
	(call $writeconsole
		(global.get $justAverage)
	)
	;; Print New Line
	(call $newline)
)
