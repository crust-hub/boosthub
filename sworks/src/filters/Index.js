const Works = require('works.js');

@Works.routes
class Index {
    @Works.filter("/")
    @Works.method(["GET"])
    index(req, res, context) {
        //console.log("filter /");
        return true;
    }

    @Works.filter("/*")
    @Works.method(["GET"])
    indexAll(req, res, context) {
        //console.log("filter /*");
        return indexFilterInstance.index(req, res, context);
    }
}

const indexFilterInstance = new Index();