const Works = require('works.js');
const fs = require('fs');

function loadTemplate(path) {
    return new Promise((resolve, reject) => {
        fs.readFile(path, 'utf-8', (err, data) => {
            if (err) {
                reject(err);
            }
            resolve(data);
        });
    });
}

@Works.routes
class Index {
    @Works.route("/")
    @Works.method(["GET"])
    async index(req, res, context) {
        res.writeHead(200, {
            'Content-Type': 'text/html'
        });
        let data = await loadTemplate('templates/index.html');
        res.end(data);
    }
}

const indexInstance = new Index();