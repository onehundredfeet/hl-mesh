genhl:
	haxe -cp generator  -lib hl-idl --macro "gltf.Generator.generateCpp()"
	
genjs:
	haxe -cp generator -lib hl-idl --macro "gltf.Generator.generateJs()"
