const express = require('express');
const app = express();
var http = require('http');
const server = http.Server(app);
const multer = require("multer");
const path = require("path");
var bodyParser = require('body-parser');
var fs = require('fs');
const host = '0.0.0.0';
const PORT = process.env.PORT || 5000;
const {spawn} = require('child_process');
app.use(express.static(__dirname + '/public'));
app.use('/uploads', express.static(path.join(__dirname + '/uploads')));
app.use(express.json());
app.use(bodyParser.urlencoded({ extended: true }));
app.set('view engine', 'ejs');

app.get('/', function(req, res){
    res.render('index')
  }
)

const testAddon = require('./build/Release/testaddon.node');

module.exports = testAddon;
const storage = multer.diskStorage({
  destination: function(req, file, cb) {
    cb(null, "./public/uploads");
  },
  filename: function(req, file, cb) {
    cb(
      null,
      file.fieldname + "-" + Date.now() + path.extname(file.originalname)
    );
  }
});

const upload = multer({
  storage: storage
}).single('file');

app.get("/", (req, res) => {
  res.render("index");
});

// app.post("/uploadFile/:id", (req,res) =>{
app.post("/:id", (req,res) =>{
  var action = req.params.id;
  upload(req, res, (err) => {
    if (err){
      res.render('index',{
        msg1:err
      });
    }else{
      if(req.file == undefined){
        res.render('index', {
          msg1: 'Error: No File Selected!'
        });
      } else {

        //huff
        if (action == "huff"){
          processHuff(res,req);
        }else{
          processDehuff(res, req);
        }
      }
    }
  });
});

// process huff
function processHuff(res, req){
  var classInstance = new testAddon.MyClass();
  var out = req.file.fieldname + "-" + Date.now() + ".huff";
  path.extname(req.file.path)
  var isCompressed = classInstance.compress(req.file.path,"public/output/"+out);
  if(!isCompressed){
    fs.unlink(req.file.path, function(){
      console.log("File was deleted") // Callback
    });
    res.render('index', {
      msg2:{a:"False"}
    });
  }else{
    orgSize = classInstance.getSizeSource();
    cSize = classInstance.getSizeCompressed();
    fs.unlink(req.file.path, function(){
      console.log("File was deleted") // Callback
    });
    res.render('index', {
      msg2: { a: "download", sizeOriginal: orgSize,sizeComp:cSize,file:out}
    });
  }
}

//process dehuff
function processDehuff(res, req){
  var classInstance = new testAddon.MyClass();
  var out = req.file.fieldname + "-" + Date.now() + ".";
  var isdeompressed = classInstance.decompress(req.file.path,"public/output/"+out);
  if(!isdeompressed){
    fs.unlink(req.file.path, function(){
      console.log("File was deleted") // Callback
    });
    res.render('index', {
      msg2:{a:"False"}
    });
  }else{
    fs.unlink(req.file.path, function(){
      console.log("File was deleted") // Callback
    });
    out = out+classInstance.getExt();
    res.render('index', {
      msg2: {a:"download",file:out}
    });
  }
}

app.get("/:id", (req,res)=>{
  var file = req.params.id;
  res.download("public/output/"+file, function(err){
    if(err){
      res.render('index', {
        msg1:err
      });
    }else{
      fs.unlink("public/output/"+file, function(){
        console.log("File was deleted") // Callback
      });
    }
  });
});

//run python as child process
function runScript(){
   return spawn('python', [path.join(__dirname, 'python/compute_input.py'),
      "hash", "saraj"]);
}
const subprocess = runScript()

// print output of script
subprocess.stdout.on('data', (data) => {
   console.log(`data:${data}`);
});
subprocess.stderr.on('data', (data) => {
   console.log(`error:${data}`);
});
subprocess.stderr.on('close', () => {
   console.log("Closed");
});

server.listen(PORT, host, function() {
  console.log(`Server is listening on port ${PORT}`);
});

process.on('uncaughtException',(code) =>{
  console.log(`About to exit with code: ${code}`);
})
process.on('SIGTERM', (code) =>{
  console.log(`About to exit with code: ${code}`);
})
