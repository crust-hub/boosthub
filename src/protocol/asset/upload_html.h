static const char *upload_html = "<!DOCTYPE html>\
            <html lang =\"en\">\
                <head>\
                    <meta charset = \"UTF-8\">\
                    <title> boosthub </title>\
                    <style>\
                        *{\
                            color:#707070;\
                            border:0px;\
                            margin:0px;\
                            padding:0px;\
                         }\
                         header,footer{\
                            padding:1rem;\
                            height:5rem;\
                            display:flex;\
                            justify-content:flex-start;\
                            align-items:center;\
                            background-color:#1d1d1f;\
                         }\
                         main{\
                            min-height:calc(100vh - 14rem);\
                            display:flex;\
                            justify-content:center;\
                            align-items:center;\
                            background-color:#1d1d1f;\
                         }\
                    </style>\
                </head>\
                <body>\
                    <header>\
                        <span>Boosthub</span>\
                    </header>\
                    <main>\
                        <div>\
                            <input id=\"file\" type=\"file\" name=\"file\"/>\
                            <button id=\"submit\" type=\"submit\">upload</button>\
                        </div>\
                        <div id=\"progress\"></div>\
                    </main>\
                    <footer>\
                        <span>2022 power by <a href=\"https://github.com/crust-hub\">@crust-hub</a></span>\
                    </footer>\
                </body>\
                <script>\
                    let progressDOM=document.getElementById(\"progress\");\
                    document.getElementById(\"submit\").onclick = function() {\
                        let ajax = new XMLHttpRequest();\
                        let url=\"/\";\
                        ajax.open(\"POST\", url, true);\
                        ajax.addEventListener(\"progress\", (e)=>{\
                            if(e.lengthComputable){\
                                let percentComplete = e.loaded / e.total * 100;\
                                progressDOM.innerHTML=\"progress \"+percentComplete+\" %\";\
                                console.log(percentComplete);\
                            }\
                        });\
                        ajax.addEventListener(\"error\", (e)=>{\
                            alert(\"upload error\");\
                        });\
                        ajax.addEventListener(\"abort\", (e)=>{\
                            alert(\"upload abort\");\
                        });\
                        ajax.addEventListener(\"load\", (e)=>{\
                            if(e.currentTarget.status==200){\
                                alert(\"upload success\");\
                                location.reload();\
                            }\
                        });\
                        let blob=document.getElementById(\"file\").files[0];\
                        ajax.send(blob);\
                    }\
                </script>\
            </html>";