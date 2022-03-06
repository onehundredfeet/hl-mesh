package;

import gltf.Native;
using Lambda;

class Server {

    static var _lastTime = Sys.time();
    static function delta_trace(msg : String) {
        var n =Sys.time();
        var s = n - _lastTime;
        s = Math.ceil(s * 1000) / 1000;
        trace ('${s}s ${msg}');
        _lastTime = n;
    }
	public static function main() {
        delta_trace("Start");
        /*
        Session.cacheStringType("");
        

        var x = new ServerOptions();
        delta_trace("Set");
        
        x.autoClose = false;
        x.timeoutMs = 10000;

        delta_trace("Start");
        
        var pid = x.startSocketServer(6012);        

        delta_trace ("started");
*/
        delta_trace("End");
    }

}

