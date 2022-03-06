genhl:
	haxe -cp generator  -lib hl-idl --macro "hltf.Generator.generateCpp()"
	
genjs:
	haxe -cp generator -lib hl-idl --macro "hltf.Generator.generateJs()"
