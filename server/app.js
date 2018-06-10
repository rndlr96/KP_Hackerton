var express     = require('express');
var fs          = require('fs');
var app         = express();

app.use(express.static('public'));

app.get('/', function(req, res){
  fs.readFile('index.html', function(error, data){
    res.writeHead(200, { 'Content-Type' : 'text/html'});
    res.end(data);
  });
});

app.get('/LookupPage', function(req, res){
  fs.readFile('LookupPage.html', function(error, data){
    res.writeHead(200, { 'Content-Type' : 'text/html'});
    res.end(data);
  });
});

app.listen(3030, function(){
  console.log('connected 3030 port!');
});
