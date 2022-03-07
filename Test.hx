package;

import haxe.Exception;
import mesh.Native;
using Lambda;

class Test {

    static var _lastTime = Sys.time();
    static function delta_trace(msg : String) {
        var n =Sys.time();
        var s = n - _lastTime;
        s = Math.ceil(s * 1000) / 1000;
        trace ('${s}s ${msg}');
        _lastTime = n;
    }
	public static function main() {
        delta_trace("running....");
        /*
        Session.cacheStringType("");
        
        delta_trace("New");

//        var x = new ServerOptions();
        delta_trace("Set");
        
  //      x.autoClose = true;
    //    x.timeoutMs = 10000;

        delta_trace("Start");
        
      //  var pid = x.startSocketServer(6012);        

        delta_trace ("started");

        var s = new Session();
        delta_trace("Session");
        try {
            s.connectBySocket("localhost", 6012);
        } catch (e : Exception) {
            trace ('${e.toString()} went wrong');
        } catch(e : Dynamic) {
            trace ('${e} something went wrong');
        }

        delta_trace("Cook options");
        var co = new CookOptions();

        delta_trace("Initializing");
        s.initialize(co, true, -1, null,null, null, null, null );
        delta_trace("Initialized");

        //delta_trace("load library");
        //var libId = s.loadAssetLibraryFromFile( "Path", true);

        delta_trace("load HIP file");
        s.loadHIP( "assets/test.hiplc", true );
        delta_trace("Loaded ");

        var mn = s.getManagerNode(HAPI_NodeType.HAPI_NODETYPE_OBJ);

        delta_trace("Manager node " + mn);
       
        var mNode = new houdini.Node( s, mn);
        delta_trace('${mNode}');

        var info = new NodeInfo();
        s.getNodeInfo(mn, info);
        delta_trace("Is valid: " + info.isValid);
        delta_trace("name = " + mNode.get_name());
        delta_trace("parmCount: " + info.parmCount + " | " + mNode.parmCount());
        
        delta_trace("childNodeCount: " + info.childNodeCount + " | " + mNode.childCount());
        delta_trace("inputCount: " + info.inputCount);
        delta_trace("outputCount: " + info.outputCount);


        // this paradigm needs to be changed
        var kids = s.getChildNodeList(mn,(HAPI_NodeType.HAPI_NODETYPE_OBJ).toValue() , (HAPI_NodeFlags.HAPI_NODEFLAGS_ANY).toValue(), false);
        var kidNodes = mNode.getChildren(true);

        delta_trace("kids " + kids + " | " + kidNodes.map(function(x) x.nodeType + " | " + x.get_name() + ","));

        for (k in kidNodes) {
            switch (k.nodeType) {
                case Object: trace('Object: ${k.get_name()}');
                case Surface: trace('Surface: ${k.get_name()}');
                case Composite: trace('Composite: ${k.get_name()}');
                    default:
            }
        }

        
        
        delta_trace("Cleanup");
        s.cleanup();
*/
        delta_trace("End");
    }

}

