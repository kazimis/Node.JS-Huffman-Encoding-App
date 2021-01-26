const express = require("express");
const path = require("path");
const multer = require("multer");
var bodyParser = require("body-parser");
var fs = require("fs");
const PORT = process.env.PORT || 4000;
const app = express();

app
  .use(express.static(path.join(__dirname, "public")))
  .use("/uploads", express.static(path.join(__dirname + "/uploads")))
  .set("views", path.join(__dirname, "views"))
  .set("view engine", "ejs")
  .get("/", (req, res) => res.render("pages/index"))
  .listen(PORT, () => console.log(`Listening on ${PORT}`));

const testAddon = require("./build/Release/testaddon.node");

module.exports = testAddon;
const storage = multer.diskStorage({
  destination: function (req, file, cb) {
    cb(null, "./public/uploads");
  },
  filename: function (req, file, cb) {
    cb(
      null,
      file.fieldname + "-" + Date.now() + path.extname(file.originalname)
    );
  },
});

const upload = multer({
  storage: storage,
}).single("file");
// app.post("/uploadFile/:id", (req,res) =>{
app.post("/:id", (req, res) => {
  var action = req.params.id;
  upload(req, res, (err) => {
    if (err) {
      res.render("index", {
        msg1: err,
      });
    } else {
      if (req.file == undefined) {
        res.render("pages/index", {
          msg1: "Error: No File Selected!",
        });
      } else {
        //huff
        if (action == "huff") {
          processHuff(res, req);
        } else {
          processDehuff(res, req);
        }
      }
    }
  });
});

// process huff
function processHuff(res, req) {
  var classInstance = new testAddon.MyClass();
  var out = req.file.fieldname + "-" + Date.now() + ".huff";
  path.extname(req.file.path);
  var isCompressed = classInstance.compress(
    req.file.path,
    "public/output/" + out
  );
  if (!isCompressed) {
    fs.unlink(req.file.path, function () {
      console.log("File was deleted"); // Callback
    });
    res.render("pages/index", {
      msg2: { a: "False" },
    });
  } else {
    orgSize = classInstance.getSizeSource();
    cSize = classInstance.getSizeCompressed();
    fs.unlink(req.file.path, function () {
      console.log("File was deleted"); // Callback
    });
    res.render("pages/index", {
      msg2: {
        a: "download",
        sizeOriginal: orgSize,
        sizeComp: cSize,
        file: out,
      },
    });
  }
}

//process dehuff
function processDehuff(res, req) {
  var classInstance = new testAddon.MyClass();
  var out = req.file.fieldname + "-" + Date.now() + ".";
  var isdeompressed = classInstance.decompress(
    req.file.path,
    "public/output/" + out
  );
  if (!isdeompressed) {
    fs.unlink(req.file.path, function () {
      console.log("File was deleted"); // Callback
    });
    res.render("pages/index", {
      msg2: { a: "False" },
    });
  } else {
    fs.unlink(req.file.path, function () {
      console.log("File was deleted"); // Callback
    });
    out = out + classInstance.getExt();
    res.render("pages/index", {
      msg2: { a: "download", file: out },
    });
  }
}

app.get("/:id", (req, res) => {
  var file = req.params.id;
  res.download("public/output/" + file, function (err) {
    if (err) {
      res.render("pages/index", {
        msg1: err,
      });
    } else {
      fs.unlink("public/output/" + file, function () {
        console.log("File was deleted"); // Callback
      });
    }
  });
});

process.on("uncaughtException", (code) => {
  console.log(`About to exit with code: ${code}`);
});
process.on("SIGTERM", (code) => {
  console.log(`About to exit with code: ${code}`);
});
