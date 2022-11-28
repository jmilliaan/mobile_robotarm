const express = require("express");
const bodyParser = require("body-parser");
const multer = require('multer');

const __basefolder = ".";

const app = express();
const storage = multer.diskStorage({
    destination: (req, file, cb) => {
        cb(null, __basefolder + '/uploads/');
    },
    filename: (req, file, cb) => {
        cb(null, file.originalname);
    }
})

const upload = multer({storage});

app.use(express.static('public'));

app.set('views', './views');
app.set("view engine", "ejs");
app.use(bodyParser.urlencoded({extended: true}));

app.post('/uploadImage', upload.single('image'), function(request, respond) {
    if(request.file) console.log(request.file);
    respond.status(200).send();
});

app.listen(process.env.PORT || 5000, function(){
  console.log("Server started on port 5000");
});
