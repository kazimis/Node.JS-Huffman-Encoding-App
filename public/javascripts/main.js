
// var uploadButton = document.getElementById('uploadButton');
var cButton = document.getElementById('cButton');
var dButton = document.getElementById('dButton');
var form = document.getElementById('theForm');
var loadCirlce = document.getElementById('loaderCrile');
var ejsTemp = document.getElementById('ejs');
var aboutPage = document.getElementById('aboutPage');
// document.getElementById('uploadButton').addEventListener('click', openDialog);

// uploadButton.addEventListener('click', upload);
 function upload() {
  document.getElementById('fileInput').click();
  document.getElementById('error').style.display ='none';
}
cButton.addEventListener('click', compress) ;
dButton.addEventListener('click', decompress);
function compress() {
  cButton.style.display = 'none';
  dButton.style.display = 'none';
  loadCirlce.style.display = 'block';
  uploadButton.style.display ='none';
  form.action = "huff";
  form.submit();
  form.style.display = 'none';
}
function decompress() {
  cButton.style.display = 'none';
  loadCirlce.style.display = 'block';
  uploadButton.style.display ='none';
  form.action = "dehuff";
  form.submit();
  form.style.display = 'none';
}

function d_load(){
  form.submit();
  form.style.display = 'none';
}


function loadAbout(){
  aboutPage.style.display = 'block';
  ejsTemp.style.display = 'none';
}
